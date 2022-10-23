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

}  // namespace VkUtility::CreateInfo
