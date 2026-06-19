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

#include <rocprofiler-sdk/defines.h>
#include <rocprofiler-sdk/fwd.h>

#include <stdint.h>
#include <vulkan/vulkan.h>

ROCPROFILER_EXTERN_C_INIT

// Empty struct has a size of 0 in C but size of 1 in C++.
// This struct is added to the union members which represent
// functions with no arguments to ensure ABI compatibility
typedef struct rocprofiler_vulkan_api_no_args
{
    char empty;
} rocprofiler_vulkan_api_no_args;

typedef union rocprofiler_vulkan_api_retval_t
{
#ifdef __cplusplus
    rocprofiler_vulkan_api_retval_t()  = default;
    ~rocprofiler_vulkan_api_retval_t() = default;
#endif

    void*              voidp_retval;
    uint64_t           uint64_t_retval;
    VkResult           VkResult_retval;
    PFN_vkVoidFunction PFN_vkVoidFunction_retval;
    VkDeviceAddress    VkDeviceAddress_retval;
} rocprofiler_vulkan_api_retval_t;

typedef union rocprofiler_vulkan_api_args_t
{
#ifdef __cplusplus
    rocprofiler_vulkan_api_args_t()  = default;
    ~rocprofiler_vulkan_api_args_t() = default;
#endif
    struct
    {
        VkInstance  instance;
        const char* pName;
    } vkGetInstanceProcAddr;
    struct
    {
        VkDevice    device;
        const char* pName;
    } vkGetDeviceProcAddr;
    struct
    {
        const VkInstanceCreateInfo*  pCreateInfo;
        const VkAllocationCallbacks* pAllocator;
        VkInstance*                  pInstance;
    } vkCreateInstance;
    struct
    {
        VkInstance                   instance;
        const VkAllocationCallbacks* pAllocator;
    } vkDestroyInstance;
    struct
    {
        VkInstance        instance;
        uint32_t*         pPhysicalDeviceCount;
        VkPhysicalDevice* pPhysicalDevices;
    } vkEnumeratePhysicalDevices;
    struct
    {
        VkPhysicalDevice          physicalDevice;
        VkPhysicalDeviceFeatures* pFeatures;
    } vkGetPhysicalDeviceFeatures;
    struct
    {
        VkPhysicalDevice    physicalDevice;
        VkFormat            format;
        VkFormatProperties* pFormatProperties;
    } vkGetPhysicalDeviceFormatProperties;
    struct
    {
        VkPhysicalDevice         physicalDevice;
        VkFormat                 format;
        VkImageType              type;
        VkImageTiling            tiling;
        VkImageUsageFlags        usage;
        VkImageCreateFlags       flags;
        VkImageFormatProperties* pImageFormatProperties;
    } vkGetPhysicalDeviceImageFormatProperties;
    struct
    {
        VkPhysicalDevice            physicalDevice;
        VkPhysicalDeviceProperties* pProperties;
    } vkGetPhysicalDeviceProperties;
    struct
    {
        VkPhysicalDevice         physicalDevice;
        uint32_t*                pQueueFamilyPropertyCount;
        VkQueueFamilyProperties* pQueueFamilyProperties;
    } vkGetPhysicalDeviceQueueFamilyProperties;
    struct
    {
        VkPhysicalDevice                  physicalDevice;
        VkPhysicalDeviceMemoryProperties* pMemoryProperties;
    } vkGetPhysicalDeviceMemoryProperties;
    struct
    {
        VkPhysicalDevice             physicalDevice;
        const VkDeviceCreateInfo*    pCreateInfo;
        const VkAllocationCallbacks* pAllocator;
        VkDevice*                    pDevice;
    } vkCreateDevice;
    struct
    {
        VkDevice                     device;
        const VkAllocationCallbacks* pAllocator;
    } vkDestroyDevice;
    struct
    {
        const char*            pLayerName;
        uint32_t*              pPropertyCount;
        VkExtensionProperties* pProperties;
    } vkEnumerateInstanceExtensionProperties;
    struct
    {
        VkPhysicalDevice       physicalDevice;
        const char*            pLayerName;
        uint32_t*              pPropertyCount;
        VkExtensionProperties* pProperties;
    } vkEnumerateDeviceExtensionProperties;
    struct
    {
        uint32_t*          pPropertyCount;
        VkLayerProperties* pProperties;
    } vkEnumerateInstanceLayerProperties;
    struct
    {
        VkPhysicalDevice   physicalDevice;
        uint32_t*          pPropertyCount;
        VkLayerProperties* pProperties;
    } vkEnumerateDeviceLayerProperties;
    struct
    {
        VkDevice device;
        uint32_t queueFamilyIndex;
        uint32_t queueIndex;
        VkQueue* pQueue;
    } vkGetDeviceQueue;
    struct
    {
        VkQueue             queue;
        uint32_t            submitCount;
        const VkSubmitInfo* pSubmits;
        VkFence             fence;
    } vkQueueSubmit;
    struct
    {
        VkQueue queue;
    } vkQueueWaitIdle;
    struct
    {
        VkDevice device;
    } vkDeviceWaitIdle;
    struct
    {
        VkDevice                     device;
        const VkMemoryAllocateInfo*  pAllocateInfo;
        const VkAllocationCallbacks* pAllocator;
        VkDeviceMemory*              pMemory;
    } vkAllocateMemory;
    struct
    {
        VkDevice                     device;
        VkDeviceMemory               memory;
        const VkAllocationCallbacks* pAllocator;
    } vkFreeMemory;
    struct
    {
        VkDevice         device;
        VkDeviceMemory   memory;
        VkDeviceSize     offset;
        VkDeviceSize     size;
        VkMemoryMapFlags flags;
        void**           ppData;
    } vkMapMemory;
    struct
    {
        VkDevice       device;
        VkDeviceMemory memory;
    } vkUnmapMemory;
    struct
    {
        VkDevice                   device;
        uint32_t                   memoryRangeCount;
        const VkMappedMemoryRange* pMemoryRanges;
    } vkFlushMappedMemoryRanges;
    struct
    {
        VkDevice                   device;
        uint32_t                   memoryRangeCount;
        const VkMappedMemoryRange* pMemoryRanges;
    } vkInvalidateMappedMemoryRanges;
    struct
    {
        VkDevice       device;
        VkDeviceMemory memory;
        VkDeviceSize*  pCommittedMemoryInBytes;
    } vkGetDeviceMemoryCommitment;
    struct
    {
        VkDevice       device;
        VkBuffer       buffer;
        VkDeviceMemory memory;
        VkDeviceSize   memoryOffset;
    } vkBindBufferMemory;
    struct
    {
        VkDevice       device;
        VkImage        image;
        VkDeviceMemory memory;
        VkDeviceSize   memoryOffset;
    } vkBindImageMemory;
    struct
    {
        VkDevice              device;
        VkBuffer              buffer;
        VkMemoryRequirements* pMemoryRequirements;
    } vkGetBufferMemoryRequirements;
    struct
    {
        VkDevice              device;
        VkImage               image;
        VkMemoryRequirements* pMemoryRequirements;
    } vkGetImageMemoryRequirements;
    struct
    {
        VkDevice                         device;
        VkImage                          image;
        uint32_t*                        pSparseMemoryRequirementCount;
        VkSparseImageMemoryRequirements* pSparseMemoryRequirements;
    } vkGetImageSparseMemoryRequirements;
    struct
    {
        VkPhysicalDevice               physicalDevice;
        VkFormat                       format;
        VkImageType                    type;
        VkSampleCountFlagBits          samples;
        VkImageUsageFlags              usage;
        VkImageTiling                  tiling;
        uint32_t*                      pPropertyCount;
        VkSparseImageFormatProperties* pProperties;
    } vkGetPhysicalDeviceSparseImageFormatProperties;
    struct
    {
        VkQueue                 queue;
        uint32_t                bindInfoCount;
        const VkBindSparseInfo* pBindInfo;
        VkFence                 fence;
    } vkQueueBindSparse;
    struct
    {
        VkDevice                     device;
        const VkFenceCreateInfo*     pCreateInfo;
        const VkAllocationCallbacks* pAllocator;
        VkFence*                     pFence;
    } vkCreateFence;
    struct
    {
        VkDevice                     device;
        VkFence                      fence;
        const VkAllocationCallbacks* pAllocator;
    } vkDestroyFence;
    struct
    {
        VkDevice       device;
        uint32_t       fenceCount;
        const VkFence* pFences;
    } vkResetFences;
    struct
    {
        VkDevice device;
        VkFence  fence;
    } vkGetFenceStatus;
    struct
    {
        VkDevice       device;
        uint32_t       fenceCount;
        const VkFence* pFences;
        VkBool32       waitAll;
        uint64_t       timeout;
    } vkWaitForFences;
    struct
    {
        VkDevice                     device;
        const VkSemaphoreCreateInfo* pCreateInfo;
        const VkAllocationCallbacks* pAllocator;
        VkSemaphore*                 pSemaphore;
    } vkCreateSemaphore;
    struct
    {
        VkDevice                     device;
        VkSemaphore                  semaphore;
        const VkAllocationCallbacks* pAllocator;
    } vkDestroySemaphore;
    struct
    {
        VkDevice                     device;
        const VkQueryPoolCreateInfo* pCreateInfo;
        const VkAllocationCallbacks* pAllocator;
        VkQueryPool*                 pQueryPool;
    } vkCreateQueryPool;
    struct
    {
        VkDevice                     device;
        VkQueryPool                  queryPool;
        const VkAllocationCallbacks* pAllocator;
    } vkDestroyQueryPool;
    struct
    {
        VkDevice           device;
        VkQueryPool        queryPool;
        uint32_t           firstQuery;
        uint32_t           queryCount;
        size_t             dataSize;
        void*              pData;
        VkDeviceSize       stride;
        VkQueryResultFlags flags;
    } vkGetQueryPoolResults;
    struct
    {
        VkDevice                     device;
        const VkBufferCreateInfo*    pCreateInfo;
        const VkAllocationCallbacks* pAllocator;
        VkBuffer*                    pBuffer;
    } vkCreateBuffer;
    struct
    {
        VkDevice                     device;
        VkBuffer                     buffer;
        const VkAllocationCallbacks* pAllocator;
    } vkDestroyBuffer;
    struct
    {
        VkDevice                     device;
        const VkImageCreateInfo*     pCreateInfo;
        const VkAllocationCallbacks* pAllocator;
        VkImage*                     pImage;
    } vkCreateImage;
    struct
    {
        VkDevice                     device;
        VkImage                      image;
        const VkAllocationCallbacks* pAllocator;
    } vkDestroyImage;
    struct
    {
        VkDevice                  device;
        VkImage                   image;
        const VkImageSubresource* pSubresource;
        VkSubresourceLayout*      pLayout;
    } vkGetImageSubresourceLayout;
    struct
    {
        VkDevice                     device;
        const VkImageViewCreateInfo* pCreateInfo;
        const VkAllocationCallbacks* pAllocator;
        VkImageView*                 pView;
    } vkCreateImageView;
    struct
    {
        VkDevice                     device;
        VkImageView                  imageView;
        const VkAllocationCallbacks* pAllocator;
    } vkDestroyImageView;
    struct
    {
        VkDevice                       device;
        const VkCommandPoolCreateInfo* pCreateInfo;
        const VkAllocationCallbacks*   pAllocator;
        VkCommandPool*                 pCommandPool;
    } vkCreateCommandPool;
    struct
    {
        VkDevice                     device;
        VkCommandPool                commandPool;
        const VkAllocationCallbacks* pAllocator;
    } vkDestroyCommandPool;
    struct
    {
        VkDevice                device;
        VkCommandPool           commandPool;
        VkCommandPoolResetFlags flags;
    } vkResetCommandPool;
    struct
    {
        VkDevice                           device;
        const VkCommandBufferAllocateInfo* pAllocateInfo;
        VkCommandBuffer*                   pCommandBuffers;
    } vkAllocateCommandBuffers;
    struct
    {
        VkDevice               device;
        VkCommandPool          commandPool;
        uint32_t               commandBufferCount;
        const VkCommandBuffer* pCommandBuffers;
    } vkFreeCommandBuffers;
    struct
    {
        VkCommandBuffer                 commandBuffer;
        const VkCommandBufferBeginInfo* pBeginInfo;
    } vkBeginCommandBuffer;
    struct
    {
        VkCommandBuffer commandBuffer;
    } vkEndCommandBuffer;
    struct
    {
        VkCommandBuffer           commandBuffer;
        VkCommandBufferResetFlags flags;
    } vkResetCommandBuffer;
    struct
    {
        VkCommandBuffer     commandBuffer;
        VkBuffer            srcBuffer;
        VkBuffer            dstBuffer;
        uint32_t            regionCount;
        const VkBufferCopy* pRegions;
    } vkCmdCopyBuffer;
    struct
    {
        VkCommandBuffer    commandBuffer;
        VkImage            srcImage;
        VkImageLayout      srcImageLayout;
        VkImage            dstImage;
        VkImageLayout      dstImageLayout;
        uint32_t           regionCount;
        const VkImageCopy* pRegions;
    } vkCmdCopyImage;
    struct
    {
        VkCommandBuffer          commandBuffer;
        VkBuffer                 srcBuffer;
        VkImage                  dstImage;
        VkImageLayout            dstImageLayout;
        uint32_t                 regionCount;
        const VkBufferImageCopy* pRegions;
    } vkCmdCopyBufferToImage;
    struct
    {
        VkCommandBuffer          commandBuffer;
        VkImage                  srcImage;
        VkImageLayout            srcImageLayout;
        VkBuffer                 dstBuffer;
        uint32_t                 regionCount;
        const VkBufferImageCopy* pRegions;
    } vkCmdCopyImageToBuffer;
    struct
    {
        VkCommandBuffer commandBuffer;
        VkBuffer        dstBuffer;
        VkDeviceSize    dstOffset;
        VkDeviceSize    dataSize;
        const void*     pData;
    } vkCmdUpdateBuffer;
    struct
    {
        VkCommandBuffer commandBuffer;
        VkBuffer        dstBuffer;
        VkDeviceSize    dstOffset;
        VkDeviceSize    size;
        uint32_t        data;
    } vkCmdFillBuffer;
    struct
    {
        VkCommandBuffer              commandBuffer;
        VkPipelineStageFlags         srcStageMask;
        VkPipelineStageFlags         dstStageMask;
        VkDependencyFlags            dependencyFlags;
        uint32_t                     memoryBarrierCount;
        const VkMemoryBarrier*       pMemoryBarriers;
        uint32_t                     bufferMemoryBarrierCount;
        const VkBufferMemoryBarrier* pBufferMemoryBarriers;
        uint32_t                     imageMemoryBarrierCount;
        const VkImageMemoryBarrier*  pImageMemoryBarriers;
    } vkCmdPipelineBarrier;
    struct
    {
        VkCommandBuffer     commandBuffer;
        VkQueryPool         queryPool;
        uint32_t            query;
        VkQueryControlFlags flags;
    } vkCmdBeginQuery;
    struct
    {
        VkCommandBuffer commandBuffer;
        VkQueryPool     queryPool;
        uint32_t        query;
    } vkCmdEndQuery;
    struct
    {
        VkCommandBuffer commandBuffer;
        VkQueryPool     queryPool;
        uint32_t        firstQuery;
        uint32_t        queryCount;
    } vkCmdResetQueryPool;
    struct
    {
        VkCommandBuffer         commandBuffer;
        VkPipelineStageFlagBits pipelineStage;
        VkQueryPool             queryPool;
        uint32_t                query;
    } vkCmdWriteTimestamp;
    struct
    {
        VkCommandBuffer    commandBuffer;
        VkQueryPool        queryPool;
        uint32_t           firstQuery;
        uint32_t           queryCount;
        VkBuffer           dstBuffer;
        VkDeviceSize       dstOffset;
        VkDeviceSize       stride;
        VkQueryResultFlags flags;
    } vkCmdCopyQueryPoolResults;
    struct
    {
        VkCommandBuffer        commandBuffer;
        uint32_t               commandBufferCount;
        const VkCommandBuffer* pCommandBuffers;
    } vkCmdExecuteCommands;
    struct
    {
        VkDevice                     device;
        const VkEventCreateInfo*     pCreateInfo;
        const VkAllocationCallbacks* pAllocator;
        VkEvent*                     pEvent;
    } vkCreateEvent;
    struct
    {
        VkDevice                     device;
        VkEvent                      event;
        const VkAllocationCallbacks* pAllocator;
    } vkDestroyEvent;
    struct
    {
        VkDevice device;
        VkEvent  event;
    } vkGetEventStatus;
    struct
    {
        VkDevice device;
        VkEvent  event;
    } vkSetEvent;
    struct
    {
        VkDevice device;
        VkEvent  event;
    } vkResetEvent;
    struct
    {
        VkDevice                      device;
        const VkBufferViewCreateInfo* pCreateInfo;
        const VkAllocationCallbacks*  pAllocator;
        VkBufferView*                 pView;
    } vkCreateBufferView;
    struct
    {
        VkDevice                     device;
        VkBufferView                 bufferView;
        const VkAllocationCallbacks* pAllocator;
    } vkDestroyBufferView;
    struct
    {
        VkDevice                        device;
        const VkShaderModuleCreateInfo* pCreateInfo;
        const VkAllocationCallbacks*    pAllocator;
        VkShaderModule*                 pShaderModule;
    } vkCreateShaderModule;
    struct
    {
        VkDevice                     device;
        VkShaderModule               shaderModule;
        const VkAllocationCallbacks* pAllocator;
    } vkDestroyShaderModule;
    struct
    {
        VkDevice                         device;
        const VkPipelineCacheCreateInfo* pCreateInfo;
        const VkAllocationCallbacks*     pAllocator;
        VkPipelineCache*                 pPipelineCache;
    } vkCreatePipelineCache;
    struct
    {
        VkDevice                     device;
        VkPipelineCache              pipelineCache;
        const VkAllocationCallbacks* pAllocator;
    } vkDestroyPipelineCache;
    struct
    {
        VkDevice        device;
        VkPipelineCache pipelineCache;
        size_t*         pDataSize;
        void*           pData;
    } vkGetPipelineCacheData;
    struct
    {
        VkDevice               device;
        VkPipelineCache        dstCache;
        uint32_t               srcCacheCount;
        const VkPipelineCache* pSrcCaches;
    } vkMergePipelineCaches;
    struct
    {
        VkDevice                           device;
        VkPipelineCache                    pipelineCache;
        uint32_t                           createInfoCount;
        const VkComputePipelineCreateInfo* pCreateInfos;
        const VkAllocationCallbacks*       pAllocator;
        VkPipeline*                        pPipelines;
    } vkCreateComputePipelines;
    struct
    {
        VkDevice                     device;
        VkPipeline                   pipeline;
        const VkAllocationCallbacks* pAllocator;
    } vkDestroyPipeline;
    struct
    {
        VkDevice                          device;
        const VkPipelineLayoutCreateInfo* pCreateInfo;
        const VkAllocationCallbacks*      pAllocator;
        VkPipelineLayout*                 pPipelineLayout;
    } vkCreatePipelineLayout;
    struct
    {
        VkDevice                     device;
        VkPipelineLayout             pipelineLayout;
        const VkAllocationCallbacks* pAllocator;
    } vkDestroyPipelineLayout;
    struct
    {
        VkDevice                     device;
        const VkSamplerCreateInfo*   pCreateInfo;
        const VkAllocationCallbacks* pAllocator;
        VkSampler*                   pSampler;
    } vkCreateSampler;
    struct
    {
        VkDevice                     device;
        VkSampler                    sampler;
        const VkAllocationCallbacks* pAllocator;
    } vkDestroySampler;
    struct
    {
        VkDevice                               device;
        const VkDescriptorSetLayoutCreateInfo* pCreateInfo;
        const VkAllocationCallbacks*           pAllocator;
        VkDescriptorSetLayout*                 pSetLayout;
    } vkCreateDescriptorSetLayout;
    struct
    {
        VkDevice                     device;
        VkDescriptorSetLayout        descriptorSetLayout;
        const VkAllocationCallbacks* pAllocator;
    } vkDestroyDescriptorSetLayout;
    struct
    {
        VkDevice                          device;
        const VkDescriptorPoolCreateInfo* pCreateInfo;
        const VkAllocationCallbacks*      pAllocator;
        VkDescriptorPool*                 pDescriptorPool;
    } vkCreateDescriptorPool;
    struct
    {
        VkDevice                     device;
        VkDescriptorPool             descriptorPool;
        const VkAllocationCallbacks* pAllocator;
    } vkDestroyDescriptorPool;
    struct
    {
        VkDevice                   device;
        VkDescriptorPool           descriptorPool;
        VkDescriptorPoolResetFlags flags;
    } vkResetDescriptorPool;
    struct
    {
        VkDevice                           device;
        const VkDescriptorSetAllocateInfo* pAllocateInfo;
        VkDescriptorSet*                   pDescriptorSets;
    } vkAllocateDescriptorSets;
    struct
    {
        VkDevice               device;
        VkDescriptorPool       descriptorPool;
        uint32_t               descriptorSetCount;
        const VkDescriptorSet* pDescriptorSets;
    } vkFreeDescriptorSets;
    struct
    {
        VkDevice                    device;
        uint32_t                    descriptorWriteCount;
        const VkWriteDescriptorSet* pDescriptorWrites;
        uint32_t                    descriptorCopyCount;
        const VkCopyDescriptorSet*  pDescriptorCopies;
    } vkUpdateDescriptorSets;
    struct
    {
        VkCommandBuffer     commandBuffer;
        VkPipelineBindPoint pipelineBindPoint;
        VkPipeline          pipeline;
    } vkCmdBindPipeline;
    struct
    {
        VkCommandBuffer        commandBuffer;
        VkPipelineBindPoint    pipelineBindPoint;
        VkPipelineLayout       layout;
        uint32_t               firstSet;
        uint32_t               descriptorSetCount;
        const VkDescriptorSet* pDescriptorSets;
        uint32_t               dynamicOffsetCount;
        const uint32_t*        pDynamicOffsets;
    } vkCmdBindDescriptorSets;
    struct
    {
        VkCommandBuffer                commandBuffer;
        VkImage                        image;
        VkImageLayout                  imageLayout;
        const VkClearColorValue*       pColor;
        uint32_t                       rangeCount;
        const VkImageSubresourceRange* pRanges;
    } vkCmdClearColorImage;
    struct
    {
        VkCommandBuffer commandBuffer;
        uint32_t        groupCountX;
        uint32_t        groupCountY;
        uint32_t        groupCountZ;
    } vkCmdDispatch;
    struct
    {
        VkCommandBuffer commandBuffer;
        VkBuffer        buffer;
        VkDeviceSize    offset;
    } vkCmdDispatchIndirect;
    struct
    {
        VkCommandBuffer      commandBuffer;
        VkEvent              event;
        VkPipelineStageFlags stageMask;
    } vkCmdSetEvent;
    struct
    {
        VkCommandBuffer      commandBuffer;
        VkEvent              event;
        VkPipelineStageFlags stageMask;
    } vkCmdResetEvent;
    struct
    {
        VkCommandBuffer              commandBuffer;
        uint32_t                     eventCount;
        const VkEvent*               pEvents;
        VkPipelineStageFlags         srcStageMask;
        VkPipelineStageFlags         dstStageMask;
        uint32_t                     memoryBarrierCount;
        const VkMemoryBarrier*       pMemoryBarriers;
        uint32_t                     bufferMemoryBarrierCount;
        const VkBufferMemoryBarrier* pBufferMemoryBarriers;
        uint32_t                     imageMemoryBarrierCount;
        const VkImageMemoryBarrier*  pImageMemoryBarriers;
    } vkCmdWaitEvents;
    struct
    {
        VkCommandBuffer    commandBuffer;
        VkPipelineLayout   layout;
        VkShaderStageFlags stageFlags;
        uint32_t           offset;
        uint32_t           size;
        const void*        pValues;
    } vkCmdPushConstants;
    struct
    {
        VkDevice                            device;
        VkPipelineCache                     pipelineCache;
        uint32_t                            createInfoCount;
        const VkGraphicsPipelineCreateInfo* pCreateInfos;
        const VkAllocationCallbacks*        pAllocator;
        VkPipeline*                         pPipelines;
    } vkCreateGraphicsPipelines;
    struct
    {
        VkDevice                       device;
        const VkFramebufferCreateInfo* pCreateInfo;
        const VkAllocationCallbacks*   pAllocator;
        VkFramebuffer*                 pFramebuffer;
    } vkCreateFramebuffer;
    struct
    {
        VkDevice                     device;
        VkFramebuffer                framebuffer;
        const VkAllocationCallbacks* pAllocator;
    } vkDestroyFramebuffer;
    struct
    {
        VkDevice                      device;
        const VkRenderPassCreateInfo* pCreateInfo;
        const VkAllocationCallbacks*  pAllocator;
        VkRenderPass*                 pRenderPass;
    } vkCreateRenderPass;
    struct
    {
        VkDevice                     device;
        VkRenderPass                 renderPass;
        const VkAllocationCallbacks* pAllocator;
    } vkDestroyRenderPass;
    struct
    {
        VkDevice     device;
        VkRenderPass renderPass;
        VkExtent2D*  pGranularity;
    } vkGetRenderAreaGranularity;
    struct
    {
        VkCommandBuffer   commandBuffer;
        uint32_t          firstViewport;
        uint32_t          viewportCount;
        const VkViewport* pViewports;
    } vkCmdSetViewport;
    struct
    {
        VkCommandBuffer commandBuffer;
        uint32_t        firstScissor;
        uint32_t        scissorCount;
        const VkRect2D* pScissors;
    } vkCmdSetScissor;
    struct
    {
        VkCommandBuffer commandBuffer;
        float           lineWidth;
    } vkCmdSetLineWidth;
    struct
    {
        VkCommandBuffer commandBuffer;
        float           depthBiasConstantFactor;
        float           depthBiasClamp;
        float           depthBiasSlopeFactor;
    } vkCmdSetDepthBias;
    struct
    {
        VkCommandBuffer commandBuffer;
        float           minDepthBounds;
        float           maxDepthBounds;
    } vkCmdSetDepthBounds;
    struct
    {
        VkCommandBuffer    commandBuffer;
        VkStencilFaceFlags faceMask;
        uint32_t           compareMask;
    } vkCmdSetStencilCompareMask;
    struct
    {
        VkCommandBuffer    commandBuffer;
        VkStencilFaceFlags faceMask;
        uint32_t           writeMask;
    } vkCmdSetStencilWriteMask;
    struct
    {
        VkCommandBuffer    commandBuffer;
        VkStencilFaceFlags faceMask;
        uint32_t           reference;
    } vkCmdSetStencilReference;
    struct
    {
        VkCommandBuffer commandBuffer;
        VkBuffer        buffer;
        VkDeviceSize    offset;
        VkIndexType     indexType;
    } vkCmdBindIndexBuffer;
    struct
    {
        VkCommandBuffer     commandBuffer;
        uint32_t            firstBinding;
        uint32_t            bindingCount;
        const VkBuffer*     pBuffers;
        const VkDeviceSize* pOffsets;
    } vkCmdBindVertexBuffers;
    struct
    {
        VkCommandBuffer commandBuffer;
        uint32_t        vertexCount;
        uint32_t        instanceCount;
        uint32_t        firstVertex;
        uint32_t        firstInstance;
    } vkCmdDraw;
    struct
    {
        VkCommandBuffer commandBuffer;
        uint32_t        indexCount;
        uint32_t        instanceCount;
        uint32_t        firstIndex;
        int32_t         vertexOffset;
        uint32_t        firstInstance;
    } vkCmdDrawIndexed;
    struct
    {
        VkCommandBuffer commandBuffer;
        VkBuffer        buffer;
        VkDeviceSize    offset;
        uint32_t        drawCount;
        uint32_t        stride;
    } vkCmdDrawIndirect;
    struct
    {
        VkCommandBuffer commandBuffer;
        VkBuffer        buffer;
        VkDeviceSize    offset;
        uint32_t        drawCount;
        uint32_t        stride;
    } vkCmdDrawIndexedIndirect;
    struct
    {
        VkCommandBuffer    commandBuffer;
        VkImage            srcImage;
        VkImageLayout      srcImageLayout;
        VkImage            dstImage;
        VkImageLayout      dstImageLayout;
        uint32_t           regionCount;
        const VkImageBlit* pRegions;
        VkFilter           filter;
    } vkCmdBlitImage;
    struct
    {
        VkCommandBuffer                 commandBuffer;
        VkImage                         image;
        VkImageLayout                   imageLayout;
        const VkClearDepthStencilValue* pDepthStencil;
        uint32_t                        rangeCount;
        const VkImageSubresourceRange*  pRanges;
    } vkCmdClearDepthStencilImage;
    struct
    {
        VkCommandBuffer          commandBuffer;
        uint32_t                 attachmentCount;
        const VkClearAttachment* pAttachments;
        uint32_t                 rectCount;
        const VkClearRect*       pRects;
    } vkCmdClearAttachments;
    struct
    {
        VkCommandBuffer       commandBuffer;
        VkImage               srcImage;
        VkImageLayout         srcImageLayout;
        VkImage               dstImage;
        VkImageLayout         dstImageLayout;
        uint32_t              regionCount;
        const VkImageResolve* pRegions;
    } vkCmdResolveImage;
    struct
    {
        VkCommandBuffer              commandBuffer;
        const VkRenderPassBeginInfo* pRenderPassBegin;
        VkSubpassContents            contents;
    } vkCmdBeginRenderPass;
    struct
    {
        VkCommandBuffer   commandBuffer;
        VkSubpassContents contents;
    } vkCmdNextSubpass;
    struct
    {
        VkCommandBuffer commandBuffer;
    } vkCmdEndRenderPass;
    struct
    {
        VkDevice               device;
        VkCommandPool          commandPool;
        VkCommandPoolTrimFlags flags;
    } vkTrimCommandPool;
    struct
    {
        VkDevice                     device;
        VkSwapchainKHR               swapchain;
        const VkAllocationCallbacks* pAllocator;
    } vkDestroySwapchainKHR;
    struct
    {
        VkDevice                                    device;
        const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo;
        const VkAllocationCallbacks*                pAllocator;
        VkDescriptorUpdateTemplate*                 pDescriptorUpdateTemplate;
    } vkCreateDescriptorUpdateTemplate;
    struct
    {
        VkDevice                     device;
        VkDescriptorUpdateTemplate   descriptorUpdateTemplate;
        const VkAllocationCallbacks* pAllocator;
    } vkDestroyDescriptorUpdateTemplate;
    struct
    {
        VkDevice                   device;
        VkDescriptorSet            descriptorSet;
        VkDescriptorUpdateTemplate descriptorUpdateTemplate;
        const void*                pData;
    } vkUpdateDescriptorSetWithTemplate;
    struct
    {
        VkCommandBuffer            commandBuffer;
        VkDescriptorUpdateTemplate descriptorUpdateTemplate;
        VkPipelineLayout           layout;
        uint32_t                   set;
        const void*                pData;
    } vkCmdPushDescriptorSetWithTemplate;
    struct
    {
        VkCommandBuffer                            commandBuffer;
        const VkPushDescriptorSetWithTemplateInfo* pPushDescriptorSetWithTemplateInfo;
    } vkCmdPushDescriptorSetWithTemplate2;
    struct
    {
        VkPhysicalDevice                              physicalDevice;
        const VkPhysicalDeviceSparseImageFormatInfo2* pFormatInfo;
        uint32_t*                                     pPropertyCount;
        VkSparseImageFormatProperties2*               pProperties;
    } vkGetPhysicalDeviceSparseImageFormatProperties2;
    struct
    {
        VkDevice                                    device;
        const VkImageSparseMemoryRequirementsInfo2* pInfo;
        uint32_t*                                   pSparseMemoryRequirementCount;
        VkSparseImageMemoryRequirements2*           pSparseMemoryRequirements;
    } vkGetImageSparseMemoryRequirements2;
    struct
    {
        uint32_t* pApiVersion;
    } vkEnumerateInstanceVersion;
    struct
    {
        VkDevice                      device;
        uint32_t                      bindInfoCount;
        const VkBindBufferMemoryInfo* pBindInfos;
    } vkBindBufferMemory2;
    struct
    {
        VkDevice                     device;
        uint32_t                     bindInfoCount;
        const VkBindImageMemoryInfo* pBindInfos;
    } vkBindImageMemory2;
    struct
    {
        VkDevice                  device;
        uint32_t                  heapIndex;
        uint32_t                  localDeviceIndex;
        uint32_t                  remoteDeviceIndex;
        VkPeerMemoryFeatureFlags* pPeerMemoryFeatures;
    } vkGetDeviceGroupPeerMemoryFeatures;
    struct
    {
        VkCommandBuffer commandBuffer;
        uint32_t        deviceMask;
    } vkCmdSetDeviceMask;
    struct
    {
        VkInstance                       instance;
        uint32_t*                        pPhysicalDeviceGroupCount;
        VkPhysicalDeviceGroupProperties* pPhysicalDeviceGroupProperties;
    } vkEnumeratePhysicalDeviceGroups;
    struct
    {
        VkDevice                              device;
        const VkImageMemoryRequirementsInfo2* pInfo;
        VkMemoryRequirements2*                pMemoryRequirements;
    } vkGetImageMemoryRequirements2;
    struct
    {
        VkDevice                               device;
        const VkBufferMemoryRequirementsInfo2* pInfo;
        VkMemoryRequirements2*                 pMemoryRequirements;
    } vkGetBufferMemoryRequirements2;
    struct
    {
        VkPhysicalDevice           physicalDevice;
        VkPhysicalDeviceFeatures2* pFeatures;
    } vkGetPhysicalDeviceFeatures2;
    struct
    {
        VkPhysicalDevice             physicalDevice;
        VkPhysicalDeviceProperties2* pProperties;
    } vkGetPhysicalDeviceProperties2;
    struct
    {
        VkPhysicalDevice     physicalDevice;
        VkFormat             format;
        VkFormatProperties2* pFormatProperties;
    } vkGetPhysicalDeviceFormatProperties2;
    struct
    {
        VkPhysicalDevice                        physicalDevice;
        const VkPhysicalDeviceImageFormatInfo2* pImageFormatInfo;
        VkImageFormatProperties2*               pImageFormatProperties;
    } vkGetPhysicalDeviceImageFormatProperties2;
    struct
    {
        VkPhysicalDevice          physicalDevice;
        uint32_t*                 pQueueFamilyPropertyCount;
        VkQueueFamilyProperties2* pQueueFamilyProperties;
    } vkGetPhysicalDeviceQueueFamilyProperties2;
    struct
    {
        VkPhysicalDevice                   physicalDevice;
        VkPhysicalDeviceMemoryProperties2* pMemoryProperties;
    } vkGetPhysicalDeviceMemoryProperties2;
    struct
    {
        VkDevice                  device;
        const VkDeviceQueueInfo2* pQueueInfo;
        VkQueue*                  pQueue;
    } vkGetDeviceQueue2;
    struct
    {
        VkPhysicalDevice                          physicalDevice;
        const VkPhysicalDeviceExternalBufferInfo* pExternalBufferInfo;
        VkExternalBufferProperties*               pExternalBufferProperties;
    } vkGetPhysicalDeviceExternalBufferProperties;
    struct
    {
        VkPhysicalDevice                         physicalDevice;
        const VkPhysicalDeviceExternalFenceInfo* pExternalFenceInfo;
        VkExternalFenceProperties*               pExternalFenceProperties;
    } vkGetPhysicalDeviceExternalFenceProperties;
    struct
    {
        VkPhysicalDevice                             physicalDevice;
        const VkPhysicalDeviceExternalSemaphoreInfo* pExternalSemaphoreInfo;
        VkExternalSemaphoreProperties*               pExternalSemaphoreProperties;
    } vkGetPhysicalDeviceExternalSemaphoreProperties;
    struct
    {
        VkCommandBuffer commandBuffer;
        uint32_t        baseGroupX;
        uint32_t        baseGroupY;
        uint32_t        baseGroupZ;
        uint32_t        groupCountX;
        uint32_t        groupCountY;
        uint32_t        groupCountZ;
    } vkCmdDispatchBase;
    struct
    {
        VkDevice                               device;
        const VkDescriptorSetLayoutCreateInfo* pCreateInfo;
        VkDescriptorSetLayoutSupport*          pSupport;
    } vkGetDescriptorSetLayoutSupport;
    struct
    {
        VkDevice                                  device;
        const VkSamplerYcbcrConversionCreateInfo* pCreateInfo;
        const VkAllocationCallbacks*              pAllocator;
        VkSamplerYcbcrConversion*                 pYcbcrConversion;
    } vkCreateSamplerYcbcrConversion;
    struct
    {
        VkDevice                     device;
        VkSamplerYcbcrConversion     ycbcrConversion;
        const VkAllocationCallbacks* pAllocator;
    } vkDestroySamplerYcbcrConversion;
    struct
    {
        VkDevice    device;
        VkQueryPool queryPool;
        uint32_t    firstQuery;
        uint32_t    queryCount;
    } vkResetQueryPool;
    struct
    {
        VkDevice    device;
        VkSemaphore semaphore;
        uint64_t*   pValue;
    } vkGetSemaphoreCounterValue;
    struct
    {
        VkDevice                   device;
        const VkSemaphoreWaitInfo* pWaitInfo;
        uint64_t                   timeout;
    } vkWaitSemaphores;
    struct
    {
        VkDevice                     device;
        const VkSemaphoreSignalInfo* pSignalInfo;
    } vkSignalSemaphore;
    struct
    {
        VkDevice                         device;
        const VkBufferDeviceAddressInfo* pInfo;
    } vkGetBufferDeviceAddress;
    struct
    {
        VkDevice                         device;
        const VkBufferDeviceAddressInfo* pInfo;
    } vkGetBufferOpaqueCaptureAddress;
    struct
    {
        VkDevice                                      device;
        const VkDeviceMemoryOpaqueCaptureAddressInfo* pInfo;
    } vkGetDeviceMemoryOpaqueCaptureAddress;
    struct
    {
        VkCommandBuffer commandBuffer;
        VkBuffer        buffer;
        VkDeviceSize    offset;
        VkBuffer        countBuffer;
        VkDeviceSize    countBufferOffset;
        uint32_t        maxDrawCount;
        uint32_t        stride;
    } vkCmdDrawIndirectCount;
    struct
    {
        VkCommandBuffer commandBuffer;
        VkBuffer        buffer;
        VkDeviceSize    offset;
        VkBuffer        countBuffer;
        VkDeviceSize    countBufferOffset;
        uint32_t        maxDrawCount;
        uint32_t        stride;
    } vkCmdDrawIndexedIndirectCount;
    struct
    {
        VkDevice                       device;
        const VkRenderPassCreateInfo2* pCreateInfo;
        const VkAllocationCallbacks*   pAllocator;
        VkRenderPass*                  pRenderPass;
    } vkCreateRenderPass2;
    struct
    {
        VkCommandBuffer              commandBuffer;
        const VkRenderPassBeginInfo* pRenderPassBegin;
        const VkSubpassBeginInfo*    pSubpassBeginInfo;
    } vkCmdBeginRenderPass2;
    struct
    {
        VkCommandBuffer           commandBuffer;
        const VkSubpassBeginInfo* pSubpassBeginInfo;
        const VkSubpassEndInfo*   pSubpassEndInfo;
    } vkCmdNextSubpass2;
    struct
    {
        VkCommandBuffer         commandBuffer;
        const VkSubpassEndInfo* pSubpassEndInfo;
    } vkCmdEndRenderPass2;
    struct
    {
        VkPhysicalDevice                physicalDevice;
        uint32_t*                       pToolCount;
        VkPhysicalDeviceToolProperties* pToolProperties;
    } vkGetPhysicalDeviceToolProperties;
    struct
    {
        VkDevice                           device;
        const VkPrivateDataSlotCreateInfo* pCreateInfo;
        const VkAllocationCallbacks*       pAllocator;
        VkPrivateDataSlot*                 pPrivateDataSlot;
    } vkCreatePrivateDataSlot;
    struct
    {
        VkDevice                     device;
        VkPrivateDataSlot            privateDataSlot;
        const VkAllocationCallbacks* pAllocator;
    } vkDestroyPrivateDataSlot;
    struct
    {
        VkDevice          device;
        VkObjectType      objectType;
        uint64_t          objectHandle;
        VkPrivateDataSlot privateDataSlot;
        uint64_t          data;
    } vkSetPrivateData;
    struct
    {
        VkDevice          device;
        VkObjectType      objectType;
        uint64_t          objectHandle;
        VkPrivateDataSlot privateDataSlot;
        uint64_t*         pData;
    } vkGetPrivateData;
    struct
    {
        VkCommandBuffer         commandBuffer;
        const VkDependencyInfo* pDependencyInfo;
    } vkCmdPipelineBarrier2;
    struct
    {
        VkCommandBuffer       commandBuffer;
        VkPipelineStageFlags2 stage;
        VkQueryPool           queryPool;
        uint32_t              query;
    } vkCmdWriteTimestamp2;
    struct
    {
        VkQueue              queue;
        uint32_t             submitCount;
        const VkSubmitInfo2* pSubmits;
        VkFence              fence;
    } vkQueueSubmit2;
    struct
    {
        VkCommandBuffer          commandBuffer;
        const VkCopyBufferInfo2* pCopyBufferInfo;
    } vkCmdCopyBuffer2;
    struct
    {
        VkCommandBuffer         commandBuffer;
        const VkCopyImageInfo2* pCopyImageInfo;
    } vkCmdCopyImage2;
    struct
    {
        VkCommandBuffer                 commandBuffer;
        const VkCopyBufferToImageInfo2* pCopyBufferToImageInfo;
    } vkCmdCopyBufferToImage2;
    struct
    {
        VkCommandBuffer                 commandBuffer;
        const VkCopyImageToBufferInfo2* pCopyImageToBufferInfo;
    } vkCmdCopyImageToBuffer2;
    struct
    {
        VkDevice                                device;
        const VkDeviceBufferMemoryRequirements* pInfo;
        VkMemoryRequirements2*                  pMemoryRequirements;
    } vkGetDeviceBufferMemoryRequirements;
    struct
    {
        VkDevice                               device;
        const VkDeviceImageMemoryRequirements* pInfo;
        VkMemoryRequirements2*                 pMemoryRequirements;
    } vkGetDeviceImageMemoryRequirements;
    struct
    {
        VkDevice                               device;
        const VkDeviceImageMemoryRequirements* pInfo;
        uint32_t*                              pSparseMemoryRequirementCount;
        VkSparseImageMemoryRequirements2*      pSparseMemoryRequirements;
    } vkGetDeviceImageSparseMemoryRequirements;
    struct
    {
        VkCommandBuffer         commandBuffer;
        VkEvent                 event;
        const VkDependencyInfo* pDependencyInfo;
    } vkCmdSetEvent2;
    struct
    {
        VkCommandBuffer       commandBuffer;
        VkEvent               event;
        VkPipelineStageFlags2 stageMask;
    } vkCmdResetEvent2;
    struct
    {
        VkCommandBuffer         commandBuffer;
        uint32_t                eventCount;
        const VkEvent*          pEvents;
        const VkDependencyInfo* pDependencyInfos;
    } vkCmdWaitEvents2;
    struct
    {
        VkCommandBuffer         commandBuffer;
        const VkBlitImageInfo2* pBlitImageInfo;
    } vkCmdBlitImage2;
    struct
    {
        VkCommandBuffer            commandBuffer;
        const VkResolveImageInfo2* pResolveImageInfo;
    } vkCmdResolveImage2;
    struct
    {
        VkCommandBuffer        commandBuffer;
        const VkRenderingInfo* pRenderingInfo;
    } vkCmdBeginRendering;
    struct
    {
        VkCommandBuffer commandBuffer;
    } vkCmdEndRendering;
    struct
    {
        VkCommandBuffer commandBuffer;
        VkCullModeFlags cullMode;
    } vkCmdSetCullMode;
    struct
    {
        VkCommandBuffer commandBuffer;
        VkFrontFace     frontFace;
    } vkCmdSetFrontFace;
    struct
    {
        VkCommandBuffer     commandBuffer;
        VkPrimitiveTopology primitiveTopology;
    } vkCmdSetPrimitiveTopology;
    struct
    {
        VkCommandBuffer   commandBuffer;
        uint32_t          viewportCount;
        const VkViewport* pViewports;
    } vkCmdSetViewportWithCount;
    struct
    {
        VkCommandBuffer commandBuffer;
        uint32_t        scissorCount;
        const VkRect2D* pScissors;
    } vkCmdSetScissorWithCount;
    struct
    {
        VkCommandBuffer     commandBuffer;
        uint32_t            firstBinding;
        uint32_t            bindingCount;
        const VkBuffer*     pBuffers;
        const VkDeviceSize* pOffsets;
        const VkDeviceSize* pSizes;
        const VkDeviceSize* pStrides;
    } vkCmdBindVertexBuffers2;
    struct
    {
        VkCommandBuffer commandBuffer;
        VkBool32        depthTestEnable;
    } vkCmdSetDepthTestEnable;
    struct
    {
        VkCommandBuffer commandBuffer;
        VkBool32        depthWriteEnable;
    } vkCmdSetDepthWriteEnable;
    struct
    {
        VkCommandBuffer commandBuffer;
        VkCompareOp     depthCompareOp;
    } vkCmdSetDepthCompareOp;
    struct
    {
        VkCommandBuffer commandBuffer;
        VkBool32        depthBoundsTestEnable;
    } vkCmdSetDepthBoundsTestEnable;
    struct
    {
        VkCommandBuffer commandBuffer;
        VkBool32        stencilTestEnable;
    } vkCmdSetStencilTestEnable;
    struct
    {
        VkCommandBuffer    commandBuffer;
        VkStencilFaceFlags faceMask;
        VkStencilOp        failOp;
        VkStencilOp        passOp;
        VkStencilOp        depthFailOp;
        VkCompareOp        compareOp;
    } vkCmdSetStencilOp;
    struct
    {
        VkCommandBuffer commandBuffer;
        VkBool32        rasterizerDiscardEnable;
    } vkCmdSetRasterizerDiscardEnable;
    struct
    {
        VkCommandBuffer commandBuffer;
        VkBool32        depthBiasEnable;
    } vkCmdSetDepthBiasEnable;
    struct
    {
        VkCommandBuffer commandBuffer;
        VkBool32        primitiveRestartEnable;
    } vkCmdSetPrimitiveRestartEnable;
    struct
    {
        VkDevice               device;
        const VkMemoryMapInfo* pMemoryMapInfo;
        void**                 ppData;
    } vkMapMemory2;
    struct
    {
        VkDevice                 device;
        const VkMemoryUnmapInfo* pMemoryUnmapInfo;
    } vkUnmapMemory2;
    struct
    {
        VkDevice                            device;
        const VkDeviceImageSubresourceInfo* pInfo;
        VkSubresourceLayout2*               pLayout;
    } vkGetDeviceImageSubresourceLayout;
    struct
    {
        VkDevice                   device;
        VkImage                    image;
        const VkImageSubresource2* pSubresource;
        VkSubresourceLayout2*      pLayout;
    } vkGetImageSubresourceLayout2;
    struct
    {
        VkDevice                       device;
        const VkCopyMemoryToImageInfo* pCopyMemoryToImageInfo;
    } vkCopyMemoryToImage;
    struct
    {
        VkDevice                       device;
        const VkCopyImageToMemoryInfo* pCopyImageToMemoryInfo;
    } vkCopyImageToMemory;
    struct
    {
        VkDevice                      device;
        const VkCopyImageToImageInfo* pCopyImageToImageInfo;
    } vkCopyImageToImage;
    struct
    {
        VkDevice                               device;
        uint32_t                               transitionCount;
        const VkHostImageLayoutTransitionInfo* pTransitions;
    } vkTransitionImageLayout;
    struct
    {
        VkCommandBuffer             commandBuffer;
        VkPipelineBindPoint         pipelineBindPoint;
        VkPipelineLayout            layout;
        uint32_t                    set;
        uint32_t                    descriptorWriteCount;
        const VkWriteDescriptorSet* pDescriptorWrites;
    } vkCmdPushDescriptorSet;
    struct
    {
        VkCommandBuffer                 commandBuffer;
        const VkBindDescriptorSetsInfo* pBindDescriptorSetsInfo;
    } vkCmdBindDescriptorSets2;
    struct
    {
        VkCommandBuffer            commandBuffer;
        const VkPushConstantsInfo* pPushConstantsInfo;
    } vkCmdPushConstants2;
    struct
    {
        VkCommandBuffer                commandBuffer;
        const VkPushDescriptorSetInfo* pPushDescriptorSetInfo;
    } vkCmdPushDescriptorSet2;
    struct
    {
        VkCommandBuffer commandBuffer;
        uint32_t        lineStippleFactor;
        uint16_t        lineStipplePattern;
    } vkCmdSetLineStipple;
    struct
    {
        VkCommandBuffer commandBuffer;
        VkBuffer        buffer;
        VkDeviceSize    offset;
        VkDeviceSize    size;
        VkIndexType     indexType;
    } vkCmdBindIndexBuffer2;
    struct
    {
        VkDevice                   device;
        const VkRenderingAreaInfo* pRenderingAreaInfo;
        VkExtent2D*                pGranularity;
    } vkGetRenderingAreaGranularity;
    struct
    {
        VkCommandBuffer                          commandBuffer;
        const VkRenderingAttachmentLocationInfo* pLocationInfo;
    } vkCmdSetRenderingAttachmentLocations;
    struct
    {
        VkCommandBuffer                            commandBuffer;
        const VkRenderingInputAttachmentIndexInfo* pInputAttachmentIndexInfo;
    } vkCmdSetRenderingInputAttachmentIndices;

} rocprofiler_vulkan_api_args_t;

ROCPROFILER_EXTERN_C_FINI
