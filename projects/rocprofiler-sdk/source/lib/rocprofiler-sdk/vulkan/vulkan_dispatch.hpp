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

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>
#include <unordered_map>

namespace rocprofiler
{
namespace vulkan
{
struct dispatch_table;

struct core_api_table_t
{
    size_t                    size{sizeof(core_api_table_t)};
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr_fn{};
    PFN_vkGetDeviceProcAddr   vkGetDeviceProcAddr_fn{};

    PFN_vkCreateInstance                         vkCreateInstance_fn{};
    PFN_vkDestroyInstance                        vkDestroyInstance_fn{};
    PFN_vkEnumeratePhysicalDevices               vkEnumeratePhysicalDevices_fn{};
    PFN_vkGetPhysicalDeviceFeatures              vkGetPhysicalDeviceFeatures_fn{};
    PFN_vkGetPhysicalDeviceFormatProperties      vkGetPhysicalDeviceFormatProperties_fn{};
    PFN_vkGetPhysicalDeviceImageFormatProperties vkGetPhysicalDeviceImageFormatProperties_fn{};
    PFN_vkGetPhysicalDeviceProperties            vkGetPhysicalDeviceProperties_fn{};
    PFN_vkGetPhysicalDeviceQueueFamilyProperties vkGetPhysicalDeviceQueueFamilyProperties_fn{};
    PFN_vkGetPhysicalDeviceMemoryProperties      vkGetPhysicalDeviceMemoryProperties_fn{};
    PFN_vkCreateDevice                           vkCreateDevice_fn{};
    PFN_vkDestroyDevice                          vkDestroyDevice_fn{};
    PFN_vkEnumerateInstanceExtensionProperties   vkEnumerateInstanceExtensionProperties_fn{};
    PFN_vkEnumerateDeviceExtensionProperties     vkEnumerateDeviceExtensionProperties_fn{};
    PFN_vkEnumerateInstanceLayerProperties       vkEnumerateInstanceLayerProperties_fn{};
    PFN_vkEnumerateDeviceLayerProperties         vkEnumerateDeviceLayerProperties_fn{};
    PFN_vkGetDeviceQueue                         vkGetDeviceQueue_fn{};
    PFN_vkQueueSubmit                            vkQueueSubmit_fn{};
    PFN_vkQueueWaitIdle                          vkQueueWaitIdle_fn{};
    PFN_vkDeviceWaitIdle                         vkDeviceWaitIdle_fn{};
    PFN_vkAllocateMemory                         vkAllocateMemory_fn{};
    PFN_vkFreeMemory                             vkFreeMemory_fn{};
    PFN_vkMapMemory                              vkMapMemory_fn{};
    PFN_vkUnmapMemory                            vkUnmapMemory_fn{};
    PFN_vkFlushMappedMemoryRanges                vkFlushMappedMemoryRanges_fn{};
    PFN_vkInvalidateMappedMemoryRanges           vkInvalidateMappedMemoryRanges_fn{};
    PFN_vkGetDeviceMemoryCommitment              vkGetDeviceMemoryCommitment_fn{};
    PFN_vkBindBufferMemory                       vkBindBufferMemory_fn{};
    PFN_vkBindImageMemory                        vkBindImageMemory_fn{};
    PFN_vkGetBufferMemoryRequirements            vkGetBufferMemoryRequirements_fn{};
    PFN_vkGetImageMemoryRequirements             vkGetImageMemoryRequirements_fn{};
    PFN_vkGetImageSparseMemoryRequirements       vkGetImageSparseMemoryRequirements_fn{};
    PFN_vkGetPhysicalDeviceSparseImageFormatProperties
                                            vkGetPhysicalDeviceSparseImageFormatProperties_fn{};
    PFN_vkQueueBindSparse                   vkQueueBindSparse_fn{};
    PFN_vkCreateFence                       vkCreateFence_fn{};
    PFN_vkDestroyFence                      vkDestroyFence_fn{};
    PFN_vkResetFences                       vkResetFences_fn{};
    PFN_vkGetFenceStatus                    vkGetFenceStatus_fn{};
    PFN_vkWaitForFences                     vkWaitForFences_fn{};
    PFN_vkCreateSemaphore                   vkCreateSemaphore_fn{};
    PFN_vkDestroySemaphore                  vkDestroySemaphore_fn{};
    PFN_vkCreateQueryPool                   vkCreateQueryPool_fn{};
    PFN_vkDestroyQueryPool                  vkDestroyQueryPool_fn{};
    PFN_vkGetQueryPoolResults               vkGetQueryPoolResults_fn{};
    PFN_vkCreateBuffer                      vkCreateBuffer_fn{};
    PFN_vkDestroyBuffer                     vkDestroyBuffer_fn{};
    PFN_vkCreateImage                       vkCreateImage_fn{};
    PFN_vkDestroyImage                      vkDestroyImage_fn{};
    PFN_vkGetImageSubresourceLayout         vkGetImageSubresourceLayout_fn{};
    PFN_vkCreateImageView                   vkCreateImageView_fn{};
    PFN_vkDestroyImageView                  vkDestroyImageView_fn{};
    PFN_vkCreateCommandPool                 vkCreateCommandPool_fn{};
    PFN_vkDestroyCommandPool                vkDestroyCommandPool_fn{};
    PFN_vkResetCommandPool                  vkResetCommandPool_fn{};
    PFN_vkAllocateCommandBuffers            vkAllocateCommandBuffers_fn{};
    PFN_vkFreeCommandBuffers                vkFreeCommandBuffers_fn{};
    PFN_vkBeginCommandBuffer                vkBeginCommandBuffer_fn{};
    PFN_vkEndCommandBuffer                  vkEndCommandBuffer_fn{};
    PFN_vkResetCommandBuffer                vkResetCommandBuffer_fn{};
    PFN_vkCmdCopyBuffer                     vkCmdCopyBuffer_fn{};
    PFN_vkCmdCopyImage                      vkCmdCopyImage_fn{};
    PFN_vkCmdCopyBufferToImage              vkCmdCopyBufferToImage_fn{};
    PFN_vkCmdCopyImageToBuffer              vkCmdCopyImageToBuffer_fn{};
    PFN_vkCmdUpdateBuffer                   vkCmdUpdateBuffer_fn{};
    PFN_vkCmdFillBuffer                     vkCmdFillBuffer_fn{};
    PFN_vkCmdPipelineBarrier                vkCmdPipelineBarrier_fn{};
    PFN_vkCmdBeginQuery                     vkCmdBeginQuery_fn{};
    PFN_vkCmdEndQuery                       vkCmdEndQuery_fn{};
    PFN_vkCmdResetQueryPool                 vkCmdResetQueryPool_fn{};
    PFN_vkCmdWriteTimestamp                 vkCmdWriteTimestamp_fn{};
    PFN_vkCmdCopyQueryPoolResults           vkCmdCopyQueryPoolResults_fn{};
    PFN_vkCmdExecuteCommands                vkCmdExecuteCommands_fn{};
    PFN_vkCreateEvent                       vkCreateEvent_fn{};
    PFN_vkDestroyEvent                      vkDestroyEvent_fn{};
    PFN_vkGetEventStatus                    vkGetEventStatus_fn{};
    PFN_vkSetEvent                          vkSetEvent_fn{};
    PFN_vkResetEvent                        vkResetEvent_fn{};
    PFN_vkCreateBufferView                  vkCreateBufferView_fn{};
    PFN_vkDestroyBufferView                 vkDestroyBufferView_fn{};
    PFN_vkCreateShaderModule                vkCreateShaderModule_fn{};
    PFN_vkDestroyShaderModule               vkDestroyShaderModule_fn{};
    PFN_vkCreatePipelineCache               vkCreatePipelineCache_fn{};
    PFN_vkDestroyPipelineCache              vkDestroyPipelineCache_fn{};
    PFN_vkGetPipelineCacheData              vkGetPipelineCacheData_fn{};
    PFN_vkMergePipelineCaches               vkMergePipelineCaches_fn{};
    PFN_vkCreateComputePipelines            vkCreateComputePipelines_fn{};
    PFN_vkDestroyPipeline                   vkDestroyPipeline_fn{};
    PFN_vkCreatePipelineLayout              vkCreatePipelineLayout_fn{};
    PFN_vkDestroyPipelineLayout             vkDestroyPipelineLayout_fn{};
    PFN_vkCreateSampler                     vkCreateSampler_fn{};
    PFN_vkDestroySampler                    vkDestroySampler_fn{};
    PFN_vkCreateDescriptorSetLayout         vkCreateDescriptorSetLayout_fn{};
    PFN_vkDestroyDescriptorSetLayout        vkDestroyDescriptorSetLayout_fn{};
    PFN_vkCreateDescriptorPool              vkCreateDescriptorPool_fn{};
    PFN_vkDestroyDescriptorPool             vkDestroyDescriptorPool_fn{};
    PFN_vkResetDescriptorPool               vkResetDescriptorPool_fn{};
    PFN_vkAllocateDescriptorSets            vkAllocateDescriptorSets_fn{};
    PFN_vkFreeDescriptorSets                vkFreeDescriptorSets_fn{};
    PFN_vkUpdateDescriptorSets              vkUpdateDescriptorSets_fn{};
    PFN_vkCmdBindPipeline                   vkCmdBindPipeline_fn{};
    PFN_vkCmdBindDescriptorSets             vkCmdBindDescriptorSets_fn{};
    PFN_vkCmdClearColorImage                vkCmdClearColorImage_fn{};
    PFN_vkCmdDispatch                       vkCmdDispatch_fn{};
    PFN_vkCmdDispatchIndirect               vkCmdDispatchIndirect_fn{};
    PFN_vkCmdSetEvent                       vkCmdSetEvent_fn{};
    PFN_vkCmdResetEvent                     vkCmdResetEvent_fn{};
    PFN_vkCmdWaitEvents                     vkCmdWaitEvents_fn{};
    PFN_vkCmdPushConstants                  vkCmdPushConstants_fn{};
    PFN_vkCreateGraphicsPipelines           vkCreateGraphicsPipelines_fn{};
    PFN_vkCreateFramebuffer                 vkCreateFramebuffer_fn{};
    PFN_vkDestroyFramebuffer                vkDestroyFramebuffer_fn{};
    PFN_vkCreateRenderPass                  vkCreateRenderPass_fn{};
    PFN_vkDestroyRenderPass                 vkDestroyRenderPass_fn{};
    PFN_vkGetRenderAreaGranularity          vkGetRenderAreaGranularity_fn{};
    PFN_vkCmdSetViewport                    vkCmdSetViewport_fn{};
    PFN_vkCmdSetScissor                     vkCmdSetScissor_fn{};
    PFN_vkCmdSetLineWidth                   vkCmdSetLineWidth_fn{};
    PFN_vkCmdSetDepthBias                   vkCmdSetDepthBias_fn{};
    PFN_vkCmdSetDepthBounds                 vkCmdSetDepthBounds_fn{};
    PFN_vkCmdSetStencilCompareMask          vkCmdSetStencilCompareMask_fn{};
    PFN_vkCmdSetStencilWriteMask            vkCmdSetStencilWriteMask_fn{};
    PFN_vkCmdSetStencilReference            vkCmdSetStencilReference_fn{};
    PFN_vkCmdBindIndexBuffer                vkCmdBindIndexBuffer_fn{};
    PFN_vkCmdBindVertexBuffers              vkCmdBindVertexBuffers_fn{};
    PFN_vkCmdDraw                           vkCmdDraw_fn{};
    PFN_vkCmdDrawIndexed                    vkCmdDrawIndexed_fn{};
    PFN_vkCmdDrawIndirect                   vkCmdDrawIndirect_fn{};
    PFN_vkCmdDrawIndexedIndirect            vkCmdDrawIndexedIndirect_fn{};
    PFN_vkCmdBlitImage                      vkCmdBlitImage_fn{};
    PFN_vkCmdClearDepthStencilImage         vkCmdClearDepthStencilImage_fn{};
    PFN_vkCmdClearAttachments               vkCmdClearAttachments_fn{};
    PFN_vkCmdResolveImage                   vkCmdResolveImage_fn{};
    PFN_vkCmdBeginRenderPass                vkCmdBeginRenderPass_fn{};
    PFN_vkCmdNextSubpass                    vkCmdNextSubpass_fn{};
    PFN_vkCmdEndRenderPass                  vkCmdEndRenderPass_fn{};
    PFN_vkTrimCommandPool                   vkTrimCommandPool_fn{};
    PFN_vkDestroySwapchainKHR               vkDestroySwapchainKHR_fn{};
    PFN_vkCreateDescriptorUpdateTemplate    vkCreateDescriptorUpdateTemplate_fn{};
    PFN_vkDestroyDescriptorUpdateTemplate   vkDestroyDescriptorUpdateTemplate_fn{};
    PFN_vkUpdateDescriptorSetWithTemplate   vkUpdateDescriptorSetWithTemplate_fn{};
    PFN_vkCmdPushDescriptorSetWithTemplate  vkCmdPushDescriptorSetWithTemplate_fn{};
    PFN_vkCmdPushDescriptorSetWithTemplate2 vkCmdPushDescriptorSetWithTemplate2_fn{};
    PFN_vkGetPhysicalDeviceSparseImageFormatProperties2
                                             vkGetPhysicalDeviceSparseImageFormatProperties2_fn{};
    PFN_vkGetImageSparseMemoryRequirements2  vkGetImageSparseMemoryRequirements2_fn{};
    PFN_vkEnumerateInstanceVersion           vkEnumerateInstanceVersion_fn{};
    PFN_vkBindBufferMemory2                  vkBindBufferMemory2_fn{};
    PFN_vkBindImageMemory2                   vkBindImageMemory2_fn{};
    PFN_vkGetDeviceGroupPeerMemoryFeatures   vkGetDeviceGroupPeerMemoryFeatures_fn{};
    PFN_vkCmdSetDeviceMask                   vkCmdSetDeviceMask_fn{};
    PFN_vkEnumeratePhysicalDeviceGroups      vkEnumeratePhysicalDeviceGroups_fn{};
    PFN_vkGetImageMemoryRequirements2        vkGetImageMemoryRequirements2_fn{};
    PFN_vkGetBufferMemoryRequirements2       vkGetBufferMemoryRequirements2_fn{};
    PFN_vkGetPhysicalDeviceFeatures2         vkGetPhysicalDeviceFeatures2_fn{};
    PFN_vkGetPhysicalDeviceProperties2       vkGetPhysicalDeviceProperties2_fn{};
    PFN_vkGetPhysicalDeviceFormatProperties2 vkGetPhysicalDeviceFormatProperties2_fn{};
    PFN_vkGetPhysicalDeviceImageFormatProperties2 vkGetPhysicalDeviceImageFormatProperties2_fn{};
    PFN_vkGetPhysicalDeviceQueueFamilyProperties2 vkGetPhysicalDeviceQueueFamilyProperties2_fn{};
    PFN_vkGetPhysicalDeviceMemoryProperties2      vkGetPhysicalDeviceMemoryProperties2_fn{};
    PFN_vkGetDeviceQueue2                         vkGetDeviceQueue2_fn{};
    PFN_vkGetPhysicalDeviceExternalBufferProperties
                                                   vkGetPhysicalDeviceExternalBufferProperties_fn{};
    PFN_vkGetPhysicalDeviceExternalFenceProperties vkGetPhysicalDeviceExternalFenceProperties_fn{};
    PFN_vkGetPhysicalDeviceExternalSemaphoreProperties
                                              vkGetPhysicalDeviceExternalSemaphoreProperties_fn{};
    PFN_vkCmdDispatchBase                     vkCmdDispatchBase_fn{};
    PFN_vkGetDescriptorSetLayoutSupport       vkGetDescriptorSetLayoutSupport_fn{};
    PFN_vkCreateSamplerYcbcrConversion        vkCreateSamplerYcbcrConversion_fn{};
    PFN_vkDestroySamplerYcbcrConversion       vkDestroySamplerYcbcrConversion_fn{};
    PFN_vkResetQueryPool                      vkResetQueryPool_fn{};
    PFN_vkGetSemaphoreCounterValue            vkGetSemaphoreCounterValue_fn{};
    PFN_vkWaitSemaphores                      vkWaitSemaphores_fn{};
    PFN_vkSignalSemaphore                     vkSignalSemaphore_fn{};
    PFN_vkGetBufferDeviceAddress              vkGetBufferDeviceAddress_fn{};
    PFN_vkGetBufferOpaqueCaptureAddress       vkGetBufferOpaqueCaptureAddress_fn{};
    PFN_vkGetDeviceMemoryOpaqueCaptureAddress vkGetDeviceMemoryOpaqueCaptureAddress_fn{};
    PFN_vkCmdDrawIndirectCount                vkCmdDrawIndirectCount_fn{};
    PFN_vkCmdDrawIndexedIndirectCount         vkCmdDrawIndexedIndirectCount_fn{};
    PFN_vkCreateRenderPass2                   vkCreateRenderPass2_fn{};
    PFN_vkCmdBeginRenderPass2                 vkCmdBeginRenderPass2_fn{};
    PFN_vkCmdNextSubpass2                     vkCmdNextSubpass2_fn{};
    PFN_vkCmdEndRenderPass2                   vkCmdEndRenderPass2_fn{};
    PFN_vkGetPhysicalDeviceToolProperties     vkGetPhysicalDeviceToolProperties_fn{};
    PFN_vkCreatePrivateDataSlot               vkCreatePrivateDataSlot_fn{};
    PFN_vkDestroyPrivateDataSlot              vkDestroyPrivateDataSlot_fn{};
    PFN_vkSetPrivateData                      vkSetPrivateData_fn{};
    PFN_vkGetPrivateData                      vkGetPrivateData_fn{};
    PFN_vkCmdPipelineBarrier2                 vkCmdPipelineBarrier2_fn{};
    PFN_vkCmdWriteTimestamp2                  vkCmdWriteTimestamp2_fn{};
    PFN_vkQueueSubmit2                        vkQueueSubmit2_fn{};
    PFN_vkCmdCopyBuffer2                      vkCmdCopyBuffer2_fn{};
    PFN_vkCmdCopyImage2                       vkCmdCopyImage2_fn{};
    PFN_vkCmdCopyBufferToImage2               vkCmdCopyBufferToImage2_fn{};
    PFN_vkCmdCopyImageToBuffer2               vkCmdCopyImageToBuffer2_fn{};
    PFN_vkGetDeviceBufferMemoryRequirements   vkGetDeviceBufferMemoryRequirements_fn{};
    PFN_vkGetDeviceImageMemoryRequirements    vkGetDeviceImageMemoryRequirements_fn{};
    PFN_vkGetDeviceImageSparseMemoryRequirements vkGetDeviceImageSparseMemoryRequirements_fn{};
    PFN_vkCmdSetEvent2                           vkCmdSetEvent2_fn{};
    PFN_vkCmdResetEvent2                         vkCmdResetEvent2_fn{};
    PFN_vkCmdWaitEvents2                         vkCmdWaitEvents2_fn{};
    PFN_vkCmdBlitImage2                          vkCmdBlitImage2_fn{};
    PFN_vkCmdResolveImage2                       vkCmdResolveImage2_fn{};
    PFN_vkCmdBeginRendering                      vkCmdBeginRendering_fn{};
    PFN_vkCmdEndRendering                        vkCmdEndRendering_fn{};
    PFN_vkCmdSetCullMode                         vkCmdSetCullMode_fn{};
    PFN_vkCmdSetFrontFace                        vkCmdSetFrontFace_fn{};
    PFN_vkCmdSetPrimitiveTopology                vkCmdSetPrimitiveTopology_fn{};
    PFN_vkCmdSetViewportWithCount                vkCmdSetViewportWithCount_fn{};
    PFN_vkCmdSetScissorWithCount                 vkCmdSetScissorWithCount_fn{};
    PFN_vkCmdBindVertexBuffers2                  vkCmdBindVertexBuffers2_fn{};
    PFN_vkCmdSetDepthTestEnable                  vkCmdSetDepthTestEnable_fn{};
    PFN_vkCmdSetDepthWriteEnable                 vkCmdSetDepthWriteEnable_fn{};
    PFN_vkCmdSetDepthCompareOp                   vkCmdSetDepthCompareOp_fn{};
    PFN_vkCmdSetDepthBoundsTestEnable            vkCmdSetDepthBoundsTestEnable_fn{};
    PFN_vkCmdSetStencilTestEnable                vkCmdSetStencilTestEnable_fn{};
    PFN_vkCmdSetStencilOp                        vkCmdSetStencilOp_fn{};
    PFN_vkCmdSetRasterizerDiscardEnable          vkCmdSetRasterizerDiscardEnable_fn{};
    PFN_vkCmdSetDepthBiasEnable                  vkCmdSetDepthBiasEnable_fn{};
    PFN_vkCmdSetPrimitiveRestartEnable           vkCmdSetPrimitiveRestartEnable_fn{};
    PFN_vkMapMemory2                             vkMapMemory2_fn{};
    PFN_vkUnmapMemory2                           vkUnmapMemory2_fn{};
    PFN_vkGetDeviceImageSubresourceLayout        vkGetDeviceImageSubresourceLayout_fn{};
    PFN_vkGetImageSubresourceLayout2             vkGetImageSubresourceLayout2_fn{};
    PFN_vkCopyMemoryToImage                      vkCopyMemoryToImage_fn{};
    PFN_vkCopyImageToMemory                      vkCopyImageToMemory_fn{};
    PFN_vkCopyImageToImage                       vkCopyImageToImage_fn{};
    PFN_vkTransitionImageLayout                  vkTransitionImageLayout_fn{};
    PFN_vkCmdPushDescriptorSet                   vkCmdPushDescriptorSet_fn{};
    PFN_vkCmdBindDescriptorSets2                 vkCmdBindDescriptorSets2_fn{};
    PFN_vkCmdPushConstants2                      vkCmdPushConstants2_fn{};
    PFN_vkCmdPushDescriptorSet2                  vkCmdPushDescriptorSet2_fn{};
    PFN_vkCmdSetLineStipple                      vkCmdSetLineStipple_fn{};
    PFN_vkCmdBindIndexBuffer2                    vkCmdBindIndexBuffer2_fn{};
    PFN_vkGetRenderingAreaGranularity            vkGetRenderingAreaGranularity_fn{};
    PFN_vkCmdSetRenderingAttachmentLocations     vkCmdSetRenderingAttachmentLocations_fn{};
    PFN_vkCmdSetRenderingInputAttachmentIndices  vkCmdSetRenderingInputAttachmentIndices_fn{};
};

}  // namespace vulkan
}  // namespace rocprofiler
