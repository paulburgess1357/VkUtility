#pragma once
#include "VkShared/MemAlloc.h"
#include <vulkan/vulkan.h>
#include <vector>
// ReSharper disable CppInitializedValueIsAlwaysRewritten

namespace VkUtility::CreateInfo {

[[nodiscard]] inline VkCommandPoolCreateInfo vk_command_pool_create_info(const uint32_t queue_family_idx,
                                                                         const VkCommandPoolCreateFlags flags = 0) {
  VkCommandPoolCreateInfo info = {};
  info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  info.queueFamilyIndex = queue_family_idx;
  info.flags = flags;
  info.pNext = nullptr;
  return info;
}

[[nodiscard]] inline VkCommandBufferAllocateInfo vk_command_buffer_allocate_info(
    VkCommandPool pool, const uint32_t buffer_count = 1,
    const VkCommandBufferLevel level = VK_COMMAND_BUFFER_LEVEL_PRIMARY) {
  VkCommandBufferAllocateInfo info = {};
  info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  info.commandPool = pool;
  info.commandBufferCount = buffer_count;
  info.level = level;
  info.pNext = nullptr;
  return info;
}

[[nodiscard]] inline VkSemaphoreCreateInfo vk_semaphore_create_info(const VkSemaphoreCreateFlags flags = 0) {
  VkSemaphoreCreateInfo info = {};
  info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
  info.flags = flags;
  info.pNext = nullptr;
  return info;
}

[[nodiscard]] inline VkFenceCreateInfo vk_fence_create_info(const VkFenceCreateFlags flags = 0) {
  VkFenceCreateInfo info = {};
  info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  info.flags = flags;
  info.pNext = nullptr;
  return info;
}

[[nodiscard]] inline VkShaderModuleCreateInfo vk_shader_module_create_info(const std::vector<char>& shader_data) {
  VkShaderModuleCreateInfo info = {};
  info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  info.codeSize = shader_data.size();
  info.pCode = reinterpret_cast<const uint32_t*>(shader_data.data());
  info.pNext = nullptr;
  return info;
}

[[nodiscard]] inline VmaAllocationCreateInfo vma_allocation_create_info(const VmaMemoryUsage vma_usage,
                                                                        const VmaAllocationCreateFlags allocation_flags,
                                                                        const VkMemoryPropertyFlags required_flags,
                                                                        const VkMemoryPropertyFlags preferred_flags) {
  VmaAllocationCreateInfo info = {};
  info.usage = vma_usage;
  info.flags = allocation_flags;
  info.requiredFlags = required_flags;
  info.preferredFlags = preferred_flags;
  return info;
}

[[nodiscard]] inline VkCommandBufferBeginInfo vk_command_buffer_begin_info(const VkCommandBufferUsageFlags flags) {
  VkCommandBufferBeginInfo info = {};
  info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  info.pInheritanceInfo = nullptr;
  info.flags = flags;
  info.pNext = nullptr;
  return info;
}

[[nodiscard]] inline VkSubmitInfo vk_submit_info(const VkPipelineStageFlags& wait_stage,
                                                 const VkCommandBuffer& cmd_buffer) {
  VkSubmitInfo info = {};
  info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  info.commandBufferCount = 1;
  info.pCommandBuffers = &cmd_buffer;
  info.waitSemaphoreCount = 0;
  info.pWaitSemaphores = nullptr;
  info.pWaitDstStageMask = &wait_stage;
  info.signalSemaphoreCount = 0;
  info.pSignalSemaphores = nullptr;
  info.pNext = nullptr;
  return info;
}

[[nodiscard]] inline VkBufferCreateInfo vk_buffer_create_info(const VkDeviceSize size, const VkBufferUsageFlags usage) {
  VkBufferCreateInfo info = {};
  info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
  info.size = size;
  info.usage = usage;
  return info;
}

[[nodiscard]] inline VkImageCreateInfo vk_image_create_info(const VkFormat format, const VkImageUsageFlags usage,
                                                            const VkExtent3D extent,
                                                            const VkSampleCountFlagBits sample_count,
                                                            const uint32_t mip_levels, const uint32_t array_layers = 1,
                                                            const VkImageType image_type = VK_IMAGE_TYPE_2D) {
  VkImageCreateInfo info = {};
  info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
  info.tiling = VK_IMAGE_TILING_OPTIMAL;

  info.imageType = image_type;
  info.arrayLayers = array_layers;
  info.format = format;
  info.extent = extent;
  info.mipLevels = mip_levels;
  info.samples = sample_count;
  info.usage = usage;
  info.pNext = nullptr;
  return info;
}

[[nodiscard]] inline VkImageViewCreateInfo vk_image_view_create_info(
    VkImage image, const VkFormat format, const VkImageAspectFlags aspect_flags,
    const VkImageViewType image_type = VK_IMAGE_VIEW_TYPE_2D) {
  VkImageViewCreateInfo info = {};
  info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;

  info.viewType = image_type;
  info.image = image;
  info.format = format;
  info.subresourceRange.baseMipLevel = 0;
  info.subresourceRange.levelCount = 1;
  info.subresourceRange.baseArrayLayer = 0;
  info.subresourceRange.layerCount = 1;
  info.subresourceRange.aspectMask = aspect_flags;
  info.pNext = nullptr;
  return info;
}

}  // namespace VkUtility::CreateInfo
