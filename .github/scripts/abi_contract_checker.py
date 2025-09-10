#!/usr/bin/env python3
"""
HIP & HSA ABI Contract Checker

This script validates that HIP and HSA runtimes maintain ABI contract compatibility
with the ROCProfiler-SDK API definitions. It ensures that:

1. New APIs added to HIP/HSA are reflected in rocprofiler-sdk
2. Deprecated APIs are properly marked
3. API removals follow the proper deprecation process
4. ABI compatibility is maintained

Copyright (c) 2025 Advanced Micro Devices, Inc. All rights reserved.
"""

import os
import re
import sys
import argparse
from pathlib import Path
from typing import Dict, List, Set, Tuple, Optional
from enum import Enum


def strip_comments(path: Path):
    contents = path.read_text()

    trimmed_contents = []
    in_multiline_comment = False

    for _line in contents.split("\n"):
        line = _line.strip()

        if line.startswith("/*"):
            in_multiline_comment = True

        if line.startswith("*/"):
            in_multiline_comment = False
            continue

        if not line.startswith("//") and not in_multiline_comment:
            trimmed_contents.append(line)

    return "\n".join(trimmed_contents)


class ApiStatus(Enum):
    ACTIVE = "active"
    DEPRECATED = "deprecated"
    REMOVED = "removed"


class ABIViolation:
    def __init__(
        self,
        violation_type: str,
        api_name: str,
        description: str,
        severity: str = "error",
    ):
        self.violation_type = violation_type
        self.api_name = api_name
        self.description = description
        self.severity = severity

    def __str__(self):
        return f"[{self.severity.upper()}] {self.violation_type}: {self.api_name} - {self.description}"


class APIExtractor:
    """Extract API function names from runtime headers"""

    @staticmethod
    def extract_hip_apis(clr_path: Path) -> Dict[str, ApiStatus]:
        """Extract HIP runtime APIs from CLR project"""
        apis = {}

        # Look for HIP runtime API declarations
        hip_api_file = (
            clr_path / "hipamd" / "include" / "hip" / "amd_detail" / "hip_api_trace.hpp"
        )

        if hip_api_file.exists():
            content = strip_comments(hip_api_file)

            # Extract function pointer typedefs which represent the API
            typedef_pattern = (
                r"typedef\s+\w+\s*\*?\s*\(\s*\*\s*t_([a-zA-Z_][a-zA-Z0-9_]*)\s*\)"
            )
            matches = re.findall(typedef_pattern, content)

            for match in matches:
                apis[match] = ApiStatus.ACTIVE

        return apis

    @staticmethod
    def extract_hsa_apis(rocr_path: Path) -> Dict[str, ApiStatus]:
        """Extract HSA APIs from ROCR runtime project"""
        apis = {}

        headers = ["hsa.h", "hsa_ext_amd.h", "hsa_ext_finalize.h", "hsa_ext_image.h"]

        for header in headers:
            file = rocr_path / "runtime" / "hsa-runtime" / "inc" / header
            content = strip_comments(file)

            func_pattern = r"HSA_API\s+(hsa_[a-zA-Z_][a-zA-Z0-9_]*)\s*\("
            matches = re.findall(func_pattern, content)

            for match in matches:
                apis[match] = ApiStatus.ACTIVE

        return apis


class ROCProfilerAPIExtractor:
    """Extract API definitions from ROCProfiler-SDK"""

    @staticmethod
    def extract_hip_rocprofiler_apis(rocprofiler_path: Path) -> Dict[str, ApiStatus]:
        """Extract HIP APIs tracked by rocprofiler-sdk"""
        apis = {}

        headers = {"RUNTIME": "runtime_api_id.h", "COMPILER": "compiler_api_id.h"}

        for id_sub, header in headers.items():
            header_file = (
                rocprofiler_path
                / "source"
                / "include"
                / "rocprofiler-sdk"
                / "hip"
                / header
            )
            content = strip_comments(header_file)

            # Extract enum values for HIP runtime APIs
            lines = content.split("\n")
            for line in lines:
                match = re.search(
                    rf"ROCPROFILER_HIP_{id_sub}_API_ID_([a-zA-Z_][a-zA-Z0-9_]*)", line
                )
                if match:
                    api_name = match.group(1)
                    if api_name in ["NONE"]:
                        continue

                    # Check if marked as deprecated or removed in the same line
                    if "///< deprecated or removed" in line:
                        apis[api_name] = ApiStatus.DEPRECATED
                    else:
                        apis[api_name] = ApiStatus.ACTIVE

        return apis

    @staticmethod
    def extract_hsa_rocprofiler_apis(rocprofiler_path: Path) -> Dict[str, ApiStatus]:
        """Extract HSA APIs tracked by rocprofiler-sdk"""
        apis = {}

        headers = {
            "CORE": "core_api_id.h",
            "AMD_EXT": "amd_ext_api_id.h",
            "IMAGE_EXT": "image_ext_api_id.h",
            "FINALIZE_EXT": "finalize_ext_api_id.h",
        }

        for id_sub, header in headers.items():
            # Check core API IDs
            header_file = (
                rocprofiler_path
                / "source"
                / "include"
                / "rocprofiler-sdk"
                / "hsa"
                / header
            )
            content = strip_comments(header_file)

            # Extract enum values for HSA core APIs
            enum_pattern = rf"ROCPROFILER_HSA_{id_sub}_API_ID_([a-zA-Z_][a-zA-Z0-9_]*)"
            matches = re.findall(enum_pattern, content)

            for match in matches:
                if match in ["NONE"]:
                    continue
                apis[match] = ApiStatus.ACTIVE
        return apis


class ABIContractChecker:
    """Main ABI contract checker"""

    def __init__(self, repo_root: Path):
        self.repo_root = repo_root
        self.violations = []

    def check_hip_abi_contract(self) -> List[ABIViolation]:
        """Check HIP ABI contract compliance"""
        violations = []

        clr_path = self.repo_root / "projects" / "clr"
        rocprofiler_path = self.repo_root / "projects" / "rocprofiler-sdk"

        if not clr_path.exists():
            violations.append(
                ABIViolation(
                    "missing_project",
                    "clr",
                    "CLR project directory not found",
                    "warning",
                )
            )
            return violations

        if not rocprofiler_path.exists():
            violations.append(
                ABIViolation(
                    "missing_project",
                    "rocprofiler-sdk",
                    "ROCProfiler-SDK project directory not found",
                    "error",
                )
            )
            return violations

        # Extract APIs
        hip_runtime_apis = APIExtractor.extract_hip_apis(clr_path)
        rocprofiler_hip_apis = ROCProfilerAPIExtractor.extract_hip_rocprofiler_apis(
            rocprofiler_path
        )

        # Convert rocprofiler API names (remove prefix and normalize)
        rocprofiler_normalized = {}
        for api_name, status in rocprofiler_hip_apis.items():
            # Convert from ROCPROFILER format to function name format
            # API names in rocprofiler are the actual function names
            rocprofiler_normalized[api_name] = status

        # Check for missing APIs in rocprofiler-sdk
        for api_name in hip_runtime_apis:
            if api_name not in rocprofiler_normalized:
                violations.append(
                    ABIViolation(
                        "missing_api_tracking",
                        api_name,
                        f"HIP API '{api_name}' is not tracked in rocprofiler-sdk",
                    )
                )

        # Check for APIs marked as removed but still present
        for api_name, status in rocprofiler_normalized.items():
            if status == ApiStatus.DEPRECATED and api_name in hip_runtime_apis:
                violations.append(
                    ABIViolation(
                        "deprecated_api_still_present",
                        api_name,
                        f"API marked as deprecated in rocprofiler-sdk but still present in HIP runtime",
                        "warning",
                    )
                )

        return violations

    def check_hsa_abi_contract(self) -> List[ABIViolation]:
        """Check HSA ABI contract compliance"""
        violations = []

        rocr_path = self.repo_root / "projects" / "rocr-runtime"
        rocprofiler_path = self.repo_root / "projects" / "rocprofiler-sdk"

        if not rocr_path.exists():
            violations.append(
                ABIViolation(
                    "missing_project",
                    "rocr-runtime",
                    "ROCR runtime project directory not found",
                    "warning",
                )
            )
            return violations

        if not rocprofiler_path.exists():
            violations.append(
                ABIViolation(
                    "missing_project",
                    "rocprofiler-sdk",
                    "ROCProfiler-SDK project directory not found",
                    "error",
                )
            )
            return violations

        # Extract APIs
        hsa_runtime_apis = APIExtractor.extract_hsa_apis(rocr_path)
        rocprofiler_hsa_apis = ROCProfilerAPIExtractor.extract_hsa_rocprofiler_apis(
            rocprofiler_path
        )

        # Convert rocprofiler API names (remove prefix and normalize)
        rocprofiler_normalized = {}
        for api_name, status in rocprofiler_hsa_apis.items():
            # API names in rocprofiler are the actual function names
            rocprofiler_normalized[api_name] = status

        # Check for missing APIs in rocprofiler-sdk
        for api_name in hsa_runtime_apis:
            if api_name not in rocprofiler_normalized:
                violations.append(
                    ABIViolation(
                        "missing_api_tracking",
                        api_name,
                        f"HSA API '{api_name}' is not tracked in rocprofiler-sdk",
                    )
                )

        return violations

    def run_checks(
        self, check_hip: bool = True, check_hsa: bool = True
    ) -> Tuple[List[ABIViolation], bool]:
        """Run all ABI contract checks"""
        violations = []

        if check_hip:
            violations.extend(self.check_hip_abi_contract())

        if check_hsa:
            violations.extend(self.check_hsa_abi_contract())

        # Determine if there are any critical violations
        has_errors = any(v.severity == "error" for v in violations)

        return violations, has_errors


def main():
    parser = argparse.ArgumentParser(description="HIP & HSA ABI Contract Checker")
    parser.add_argument(
        "--repo-root",
        type=Path,
        default=Path.cwd(),
        help="Root directory of the rocm-systems repository",
    )
    parser.add_argument(
        "--check-hip",
        action="store_true",
        default=False,
        help="Check HIP ABI contract (CLR project)",
    )
    parser.add_argument(
        "--check-hsa",
        action="store_true",
        default=False,
        help="Check HSA ABI contract (ROCR runtime project)",
    )
    parser.add_argument("--verbose", "-v", action="store_true", help="Verbose output")

    args = parser.parse_args()

    # If no specific checks requested, check both
    if not args.check_hip and not args.check_hsa:
        args.check_hip = True
        args.check_hsa = True

    checker = ABIContractChecker(args.repo_root)
    violations, has_errors = checker.run_checks(args.check_hip, args.check_hsa)

    if not violations:
        print("✅ ABI contract checks passed - no violations found")
        return 0

    print(f"⚠️  Found {len(violations)} ABI contract violation(s):")
    print()

    error_count = 0
    warning_count = 0

    for violation in violations:
        print(f"  {violation}")
        if violation.severity == "error":
            error_count += 1
        else:
            warning_count += 1

    print()
    print(f"Summary: {error_count} error(s), {warning_count} warning(s)")

    if has_errors:
        print("\n❌ ABI contract check failed due to errors")
        return 1
    else:
        print("\n⚠️  ABI contract check completed with warnings only")
        return 0


if __name__ == "__main__":
    sys.exit(main())
