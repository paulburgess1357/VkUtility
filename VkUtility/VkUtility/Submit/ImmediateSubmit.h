#pragma once
#include "VkUtility/Handle/UsingHandle.h"
#include <functional>

namespace VkUtility {

struct UploadContext {
  UploadContext(VkDevice device, VkQueue queue, const uint32_t queue_family_idx);
  VkCommandPoolHandle cmd_pool;
  VkCommandBuffer cmd_buffer{VK_NULL_HANDLE};
  VkFenceHandle upload_fence;
  VkQueue queue{VK_NULL_HANDLE};
};

class ImmediateSubmit {
 public:
  ImmediateSubmit(VkDevice device, VkQueue queue, const uint32_t queue_family_idx);
  void submit(std::function<void(VkCommandBuffer cmd)>&& function) const;

 private:
  UploadContext upload_ctx;
  VkDevice m_device{VK_NULL_HANDLE};
};

}  // namespace VkUtility
