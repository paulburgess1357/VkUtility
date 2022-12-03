#pragma once
#include "VkUtility/Handle/CreateDestroy.h"
#include "VkShared/THandle.h"

namespace VkUtility {
using VkCommandPoolHandle = VkShared::THandle<CreateDestroyCommandPool>;
using VkSemaphoreHandle = VkShared::THandle<CreateDestroySemaphore>;
using VkFenceHandle = VkShared::THandle<CreateDestroyFence>;
using VkShaderModuleHandle = VkShared::THandle<CreateDestroyShaderModule>;
using VMABufferHandle = VkShared::THandle<CreateDestroyVMABuffer>;
using VMAImageHandle = VkShared::THandle<CreateDestroyVMAImage>;
using VKImageViewHandle = VkShared::THandle<CreateDestroyImageView>;
using VkDescriptorPoolHandle = VkShared::THandle<CreateDestroyDescriptorPool>;
using VkDescriptorSetLayoutHandle = VkShared::THandle<CreateDestroyDescriptorLayout>;

struct VkImageWrapped {
  [[nodiscard]] const VkImage& image() const {
    return image_handle().handle;
  }
  [[nodiscard]] const VkImageView& image_view() const {
    return view_handle();
  }
  VMAImageHandle image_handle{};
  VKImageViewHandle view_handle{};
};

struct VkBufferWrapped {
  [[nodiscard]] const VkBuffer& operator()() const {
    return handle().handle;
  }
  [[nodiscard]] VmaAllocation allocation() const {
    return handle().allocation;
  }
  VMABufferHandle handle{};
};

}  // namespace VkUtility
