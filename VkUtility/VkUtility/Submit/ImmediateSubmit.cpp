#include "VkUtility/Submit/ImmediateSubmit.h"
#include "VkUtility/Command/Command.h"
#include "VkUtility/Sync/Sync.h"
#include "VkUtility/Misc/Exceptions.h"
#include "VkShared/Macros.h"
#include <vulkan/vulkan.h>

namespace VkUtility {

// clang-format off
UploadContext::UploadContext(VkDevice device, VkQueue queue, const uint32_t queue_family_idx)
    : cmd_pool{Command::create_command_pool(device, queue_family_idx)},
      cmd_buffer{Command::create_command_buffer(device, cmd_pool())},
      upload_fence{Sync::create_fence(device)},
      queue{queue} {
}
// clang-format on

ImmediateSubmit::ImmediateSubmit(VkDevice device, VkQueue queue, const uint32_t queue_family_idx)
    : upload_ctx{device, queue, queue_family_idx}, m_device{device} {
}

void ImmediateSubmit::submit(std::function<void(VkCommandBuffer cmd)>&& function) const {
  // Record command buffer
  const auto cmd_info = CreateInfo::vk_command_buffer_begin_info(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);
  VkCheck(vkBeginCommandBuffer(upload_ctx.cmd_buffer, &cmd_info), Exceptions::ImmediateSubmitException());

  // Run submission function
  function(upload_ctx.cmd_buffer);

  VkCheck(vkEndCommandBuffer(upload_ctx.cmd_buffer), Exceptions::ImmediateSubmitException());

  // Submit command buffer
  constexpr auto wait_stage{VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT};
  const auto submit_info = CreateInfo::vk_submit_info(wait_stage, upload_ctx.cmd_buffer);
  VkCheck(vkQueueSubmit(upload_ctx.queue, 1, &submit_info, upload_ctx.upload_fence()),
          Exceptions::ImmediateSubmitException());

  // Wait for execution
  vkWaitForFences(m_device, 1, &upload_ctx.upload_fence(), VK_TRUE, UINT64_MAX);
  VkCheck(vkResetFences(m_device, 1, &upload_ctx.upload_fence()), Exceptions::ImmediateSubmitException());

  // Reset command buffer
  vkResetCommandPool(m_device, upload_ctx.cmd_pool(), 0);
}

}  // namespace VkUtility
