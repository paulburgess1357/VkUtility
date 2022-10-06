#pragma once
#include "VkUtility/Handle/UsingHandle.h"
#include "VkUtility/Misc/CreateInfo.h"
#include "VkUtility/Misc/Exceptions.h"
#include "VkShared/Macros.h"
#include <vulkan/vulkan.h>

namespace VkUtility::Command {

[[nodiscard]] inline VkCommandPoolHandle create_command_pool(VkDevice device, const uint32_t queue_family_idx,
                                                             const VkCommandPoolCreateFlags flags = 0) {
  const auto info = VkUtility::CreateInfo::vk_command_pool_create_info(queue_family_idx, flags);
  return VkCommandPoolHandle{info, device};
}

[[nodiscard]] inline VkCommandBuffer create_command_buffer(VkDevice device, VkCommandPool pool) {
  const auto info = CreateInfo::vk_command_buffer_allocate_info(pool);
  VkCommandBuffer cmd_buffer;
  VkCheck(vkAllocateCommandBuffers(device, &info, &cmd_buffer), Exceptions::VkUtilityException());
  return cmd_buffer;
}

}  // namespace VkUtility::Command
