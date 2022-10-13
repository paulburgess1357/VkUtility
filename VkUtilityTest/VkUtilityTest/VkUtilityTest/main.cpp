#include "VkStartup/Context/InitContext.h"
#include "VkUtility/Command/Command.h"

int main() {
  VkStartup::InitContextOptions options;
  options.enable_validation = true;
  VkStartup::InitContext context{std::move(options)};

  // Test command buffer creation
  auto& ctx = context.context();
  auto graphics_pool = VkUtility::Command::create_command_pool(
      ctx.device(), ctx.queues.at(VkShared::Enums::QueueFamily::Graphics).family_index,
      VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);
  if (const auto graphics_buffer = VkUtility::Command::create_command_buffer(ctx.device(), graphics_pool())) {
    return 0;
  }
  return 1;
}
