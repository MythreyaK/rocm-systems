# HIP & HSA ABI Contract Checker

## Overview

The ABI Contract Checker ensures that HIP and HSA runtimes maintain compatibility with ROCProfiler-SDK API definitions. This system validates that API changes follow proper deprecation processes and maintain ABI stability.

## Components

### 1. ABI Contract Checker Script (`/.github/scripts/abi_contract_checker.py`)

A Python script that analyzes API definitions across:
- **HIP Runtime (CLR)**: `projects/clr/hipamd/include/hip/amd_detail/hip_api_trace.hpp`
- **HSA Runtime (ROCR)**: `projects/rocr-runtime/runtime/hsa-runtime/inc/hsa*.h`
- **ROCProfiler-SDK**: `projects/rocprofiler-sdk/source/include/rocprofiler-sdk/{hip,hsa}/*_api_id.h`

### 2. GitHub Workflows

Three workflows monitor ABI contract compliance:

#### HIP ABI Contract Checker (`.github/workflows/hip-abi-contract-checker.yml`)
- **Triggers**: PRs to `projects/clr/` or `projects/hip/`
- **Purpose**: Validates HIP runtime API changes against rocprofiler-sdk

#### HSA ABI Contract Checker (`.github/workflows/hsa-abi-contract-checker.yml`)
- **Triggers**: PRs to `projects/rocr-runtime/`
- **Purpose**: Validates HSA runtime API changes against rocprofiler-sdk

#### ROCProfiler-SDK ABI Contract Checker (`.github/workflows/rocprofiler-sdk-abi-contract-checker.yml`)
- **Triggers**: PRs to `projects/rocprofiler-sdk/`
- **Purpose**: Validates rocprofiler-sdk API definitions and consistency

## Validation Rules

### Error Conditions (Build Failures)
1. **Missing API Tracking**: New runtime APIs not reflected in rocprofiler-sdk
2. **API ID Conflicts**: Duplicate or inconsistent API enumeration values
3. **Invalid API Definitions**: Malformed API definition files

### Warning Conditions (Informational)
1. **Deprecated APIs Still Present**: APIs marked deprecated in rocprofiler-sdk but still active in runtime
2. **API Documentation Issues**: Missing or incomplete API documentation

## Usage

### Running Locally

```bash
# Check both HIP and HSA ABI contracts
python3 .github/scripts/abi_contract_checker.py --repo-root . --verbose

# Check only HIP ABI contract
python3 .github/scripts/abi_contract_checker.py --check-hip --verbose

# Check only HSA ABI contract  
python3 .github/scripts/abi_contract_checker.py --check-hsa --verbose
```

### GitHub Workflow Integration

The workflows automatically run on relevant PRs and provide:
- **Automated ABI compliance checking**
- **API change detection and reporting**
- **Guidance for maintaining ABI compatibility**

## API Change Process

### Adding New APIs

1. **Runtime Implementation**: Add new API to HIP or HSA runtime
2. **ROCProfiler Integration**: Add corresponding enum to rocprofiler-sdk API definitions
3. **Version Management**: Update API table version numbers appropriately
4. **Documentation**: Update API documentation and changelogs

### Deprecating APIs

1. **Mark as Deprecated**: Add `///< deprecated or removed` comment in rocprofiler-sdk
2. **Runtime Notification**: Coordinate with runtime teams for deprecation timeline
3. **Version Planning**: Plan removal for appropriate major version
4. **Documentation**: Document deprecation and migration path

### Removing APIs

1. **Ensure Deprecation Period**: APIs must be deprecated for at least one major release
2. **ABI Compatibility**: Follow ABI compatibility rules from hip_api_trace.hpp
3. **Coordinate Removal**: Remove from both runtime and rocprofiler-sdk simultaneously

## ABI Compatibility Rules

Based on `hip_api_trace.hpp` guidelines:

1. **NEVER re-arrange** the order of member variables in dispatch tables
2. **Always add** new function pointers to the end of tables
3. **Increment step version** when adding new APIs
4. **Increment major version** only for fundamental breaking changes
5. **DO NOT REMOVE** function pointers; set to nullptr if necessary

## Troubleshooting

### Common Issues

#### "Missing API Tracking" Errors
- **Cause**: New runtime API not in rocprofiler-sdk
- **Solution**: Add corresponding enum to appropriate `*_api_id.h` file

#### "Deprecated API Still Present" Warnings
- **Cause**: API marked deprecated but still active
- **Solution**: Either remove the API or update deprecation status

#### "API ID Conflicts" Errors
- **Cause**: Duplicate or inconsistent enum values
- **Solution**: Resolve numbering conflicts in API definition files

### Getting Help

1. **Review existing API patterns** in rocprofiler-sdk headers
2. **Check version compatibility** requirements
3. **Coordinate with teams** for cross-project changes
4. **Follow deprecation timelines** for API removals

## Configuration

The checker can be configured by modifying:
- **Script parameters**: Add command-line options for custom checking
- **Workflow triggers**: Adjust file path patterns in workflow YAML
- **Severity levels**: Modify violation categories in the script

## Maintenance

Regular maintenance tasks:
1. **Update API extraction patterns** as header formats evolve
2. **Enhance validation rules** based on new requirements  
3. **Monitor false positives** and adjust checking logic
4. **Keep documentation current** with process changes