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

#include "vulkan.hpp"

#include <cstdint>
#include <vulkan/vulkan.hpp>

//
#include <vulkan/utility/vk_dispatch_table.h>
#include <vulkan/vk_layer.h>
#include <vulkan/vulkan_core.h>
#include <atomic>

#include "vulkan.hpp"

namespace
{
std::atomic<int> load_count{-1};

namespace rvk = rocprofiler::vulkan;

#define ROCPROFILER_SDK_VK_PROCADDR(param_name, func_name)                                         \
    if(std::string_view{param_name} == std::string_view{"vk" #func_name})                          \
    {                                                                                              \
        return reinterpret_cast<PFN_vkVoidFunction>(&func_name);                                   \
    }

VkResult
CreateInstance(const VkInstanceCreateInfo*  create_info,
               const VkAllocationCallbacks* alloc_callbacks,
               VkInstance*                  vk_instance)
{
    auto& core_table = *rvk::init_next_dispatch().core;

    auto pnext_layer = const_cast<VkLayerInstanceCreateInfo*>(
        reinterpret_cast<const VkLayerInstanceCreateInfo*>(create_info->pNext));

    while((pnext_layer != nullptr) &&
          ((pnext_layer->sType != VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO) ||
           (pnext_layer->function != VkLayerFunction::VK_LAYER_LINK_INFO)))
    {
        pnext_layer = const_cast<VkLayerInstanceCreateInfo*>(
            reinterpret_cast<const VkLayerInstanceCreateInfo*>(pnext_layer->pNext));
    }

    if(pnext_layer == nullptr) return VK_ERROR_INITIALIZATION_FAILED;

    core_table.vkGetInstanceProcAddr_fn = pnext_layer->u.pLayerInfo->pfnNextGetInstanceProcAddr;
    core_table.vkCreateInstance_fn      = reinterpret_cast<PFN_vkCreateInstance>(
        core_table.vkGetInstanceProcAddr_fn(nullptr, "vkCreateInstance"));

    {
        // need to cast constness away
        auto pnext_layer_mut          = const_cast<VkLayerInstanceCreateInfo*>(pnext_layer);
        pnext_layer_mut->u.pLayerInfo = pnext_layer->u.pLayerInfo->pNext;
        auto result = core_table.vkCreateInstance_fn(create_info, alloc_callbacks, vk_instance);

        core_table.vkCreateDevice_fn = reinterpret_cast<PFN_vkCreateDevice>(
            core_table.vkGetInstanceProcAddr_fn(*vk_instance, "vkCreateDevice"));

        // TODO: correctly handle tbl_instance

        if(result != VK_SUCCESS) return result;
    }

    return VK_SUCCESS;
}

VkResult
CreateDevice(VkPhysicalDevice             vk_phy_dev,
             const VkDeviceCreateInfo*    create_info,
             const VkAllocationCallbacks* alloc_callbacks,
             VkDevice*                    vk_dev)
{
    auto& core_table = *rvk::init_next_dispatch().core;

    auto pnext_layer = const_cast<VkLayerDeviceCreateInfo*>(
        reinterpret_cast<const VkLayerDeviceCreateInfo*>(create_info->pNext));

    while((pnext_layer != nullptr) &&
          ((pnext_layer->sType != VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO) ||
           (pnext_layer->function != VkLayerFunction::VK_LAYER_LINK_INFO)))
    {
        pnext_layer = const_cast<VkLayerDeviceCreateInfo*>(
            reinterpret_cast<const VkLayerDeviceCreateInfo*>(pnext_layer->pNext));
    }

    if(pnext_layer == nullptr) return VK_ERROR_INITIALIZATION_FAILED;

    core_table.vkGetDeviceProcAddr_fn = pnext_layer->u.pLayerInfo->pfnNextGetDeviceProcAddr;

    {
        // need to cast constness away
        auto pnext_layer_mut          = const_cast<VkLayerDeviceCreateInfo*>(pnext_layer);
        pnext_layer_mut->u.pLayerInfo = pnext_layer->u.pLayerInfo->pNext;
        auto result =
            core_table.vkCreateDevice_fn(vk_phy_dev, create_info, alloc_callbacks, vk_dev);

        if(result != VK_SUCCESS) return result;
    }

    return VK_SUCCESS;
}

PFN_vkVoidFunction
GetInstanceProcAddr(VkInstance instance, const char* name)
{
    auto& core_table = *rvk::init_next_dispatch().core;

    // TODO: per-instance and per-device functions
    ROCPROFILER_SDK_VK_PROCADDR(name, GetInstanceProcAddr);
    ROCPROFILER_SDK_VK_PROCADDR(name, CreateInstance);
    ROCPROFILER_SDK_VK_PROCADDR(name, CreateDevice);

    // intercept during query
    auto next_ptr = rvk::try_intercept_func(
        &core_table, instance, core_table.vkGetInstanceProcAddr_fn, name, 0);
    return next_ptr;
}

PFN_vkVoidFunction
GetDeviceProcAddr(VkDevice device, const char* name)
{
    auto& core_table = *rvk::init_next_dispatch().core;

    // TODO: per-instance and per-device functions
    ROCPROFILER_SDK_VK_PROCADDR(name, GetDeviceProcAddr);

    // intercept during query
    auto next_ptr =
        rvk::try_intercept_func(&core_table, device, core_table.vkGetDeviceProcAddr_fn, name, 0);
    return next_ptr;
}

VkResult
negotiate_layer_interface(VkNegotiateLayerInterface* pVersionStruct)
{
    if(pVersionStruct->loaderLayerInterfaceVersion == 2)
    {
        pVersionStruct->pfnGetInstanceProcAddr = &GetInstanceProcAddr;
        pVersionStruct->pfnGetDeviceProcAddr   = &GetDeviceProcAddr;
        return VK_SUCCESS;
    }
    else
    {
        return VK_ERROR_INITIALIZATION_FAILED;
    }
}

}  // namespace

extern "C" {
VkResult ROCPROFILER_PUBLIC_API
VK_LAYER_ROCPROFILER_SDK_NegotiateLoaderLayerInterfaceVersion(
    VkNegotiateLayerInterface* pVersionStruct)
{
    load_count.fetch_add(1);
    return negotiate_layer_interface(pVersionStruct);
}
}
