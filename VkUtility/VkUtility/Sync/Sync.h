#pragma once
#include "VkUtility/Handle/UsingHandle.h"
#include "VkUtility/Misc/CreateInfo.h"
#include <vulkan/vulkan.h>

namespace VkUtility::Sync {

[[nodiscard]] inline VkSemaphoreHandle create_semaphore(VkDevice device, const VkSemaphoreCreateFlags flags = 0) {
  const auto info = CreateInfo::vk_semaphore_create_info(flags);
  return VkSemaphoreHandle{info, device};
}

[[nodiscard]] inline VkFenceHandle create_fence(VkDevice device, const VkFenceCreateFlags flags = 0) {
  const auto info = CreateInfo::vk_fence_create_info(flags);
  return VkFenceHandle{info, device};
}

}  // namespace VkUtility::Sync
