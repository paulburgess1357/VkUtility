#pragma once
#include <vulkan/vulkan.h>
#include "VkUtility/Misc/Exceptions.h"
#include "VkShared/Macros.h"

namespace VkUtility {

class CreateDestroyCommandPool {
 public:
  void create() {
    handle = VK_NULL_HANDLE;
  }
  void create(const VkCommandPoolCreateInfo& info, VkDevice vk_device) {
    VkCheck(vkCreateCommandPool(vk_device, &info, nullptr, &handle), Exceptions::VkUtilityException());
    m_device = vk_device;
  }
  void destroy() const {
    if (handle && m_device) {
      vkDestroyCommandPool(m_device, handle, nullptr);
    }
  }
  VkCommandPool handle{VK_NULL_HANDLE};

 private:
  VkDevice m_device{VK_NULL_HANDLE};
};

}  // namespace VkUtility
