// MIT License
//
// Copyright (c) 2023-2025 Advanced Micro Devices, Inc. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#pragma once

#include <rocprofiler-sdk/vulkan.h>

#include <cstdio>
#include <iomanip>
#include <ostream>
#include <string>
#include <string_view>

namespace rocprofiler
{
namespace vulkan
{
namespace detail
{
static int              HIP_depth_max     = 1;
static thread_local int HIP_depth_max_cnt = 0;
static std::string_view HIP_structs_regex = {};

inline static void
print_escaped_string(std::ostream& out, const char* v, size_t len)
{
    out << '"';
    for(size_t i = 0; i < len && v[i] != '\0'; ++i)
    {
        switch(v[i])
        {
            case '\"': out << "\\\""; break;
            case '\\': out << "\\\\"; break;
            case '\b': out << "\\\b"; break;
            case '\f': out << "\\\f"; break;
            case '\n': out << "\\\n"; break;
            case '\r': out << "\\\r"; break;
            case '\t': out << "\\\t"; break;
            default:
                if(std::isprint((unsigned char) v[i]) != 0)
                    std::operator<<(out, v[i]);
                else
                {
                    std::ios_base::fmtflags flags(out.flags());
                    out << "\\x" << std::setfill('0') << std::setw(2) << std::hex
                        << (unsigned int) (unsigned char) v[i];
                    out.flags(flags);
                }
                break;
        }
    }
    out << '"';
}

template <typename T>
inline static std::ostream&
operator<<(std::ostream& out, const T& v)
{
    using std::              operator<<;
    static thread_local bool recursion = false;
    if(recursion == false)
    {
        recursion = true;
        out << v;
        recursion = false;
    }
    return out;
}

inline static std::ostream&
operator<<(std::ostream& out, const unsigned char& v)
{
    out << (unsigned int) v;
    return out;
}

inline static std::ostream&
operator<<(std::ostream& out, const char& v)
{
    out << (unsigned char) v;
    return out;
}

template <size_t N>
inline static std::ostream&
operator<<(std::ostream& out, const char (&v)[N])
{
    print_escaped_string(out, v, N);
    return out;
}

inline static std::ostream&
operator<<(std::ostream& out, const char* v)
{
    print_escaped_string(out, v, strlen(v));
    return out;
}

}  // namespace detail
}  // namespace vulkan
}  // namespace rocprofiler
