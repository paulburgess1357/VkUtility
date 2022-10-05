#pragma once
#include <vulkan/vulkan.h>
// ReSharper disable CppInitializedValueIsAlwaysRewritten

namespace VkUtility::CreateInfo {

[[nodiscard]] inline VkCommandPoolCreateInfo vk_command_pool_create_info(const uint32_t queue_family_idx,
                                                                         const VkCommandPoolCreateFlags flags = 0) {
  VkCommandPoolCreateInfo info = {};
  info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  info.pNext = nullptr;
  info.queueFamilyIndex = queue_family_idx;
  info.flags = flags;
  return info;
}

[[nodiscard]] inline VkCommandBufferAllocateInfo vk_command_buffer_allocate_info(
    VkCommandPool pool, const uint32_t buffer_count = 1,
    const VkCommandBufferLevel level = VK_COMMAND_BUFFER_LEVEL_PRIMARY) {
  VkCommandBufferAllocateInfo info = {};
  info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  info.pNext = nullptr;

  info.commandPool = pool;
  info.commandBufferCount = buffer_count;
  info.level = level;

  return info;
}

}  // namespace VkUtility::CreateInfo
