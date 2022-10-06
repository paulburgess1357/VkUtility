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

[[nodiscard]] inline VkSemaphoreCreateInfo vk_semaphore_create_info(const VkSemaphoreCreateFlags flags = 0) {
  VkSemaphoreCreateInfo info = {};
  info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
  info.pNext = nullptr;
  info.flags = flags;
  return info;
}

[[nodiscard]] inline VkFenceCreateInfo vk_fence_create_info(const VkFenceCreateFlags flags = 0) {
  VkFenceCreateInfo info = {};
  info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  info.pNext = nullptr;
  info.flags = flags;
  return info;
}

}  // namespace VkUtility::CreateInfo
