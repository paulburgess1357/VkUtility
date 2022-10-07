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

class CreateDestroySemaphore {
 public:
  void create() {
    handle = VK_NULL_HANDLE;
  }
  void create(const VkSemaphoreCreateInfo& info, VkDevice vk_device) {
    VkCheck(vkCreateSemaphore(vk_device, &info, nullptr, &handle), Exceptions::VkUtilityException());
    m_device = vk_device;
  }
  void destroy() const {
    if (handle && m_device) {
      vkDestroySemaphore(m_device, handle, nullptr);
    }
  }
  VkSemaphore handle{VK_NULL_HANDLE};

 private:
  VkDevice m_device{VK_NULL_HANDLE};
};

class CreateDestroyFence {
 public:
  void create() {
    handle = VK_NULL_HANDLE;
  }
  void create(const VkFenceCreateInfo& info, VkDevice vk_device) {
    VkCheck(vkCreateFence(vk_device, &info, nullptr, &handle), Exceptions::VkUtilityException());
    m_device = vk_device;
  }
  void destroy() const {
    if (handle && m_device) {
      vkDestroyFence(m_device, handle, nullptr);
    }
  }
  VkFence handle{VK_NULL_HANDLE};

 private:
  VkDevice m_device{VK_NULL_HANDLE};
};

class CreateDestroyShaderModule {
 public:
  void create() {
    handle = VK_NULL_HANDLE;
  }
  void create(const VkShaderModuleCreateInfo& info, VkDevice vk_device) {
    VkCheck(vkCreateShaderModule(vk_device, &info, nullptr, &handle), Exceptions::VkUtilityException());
    m_device = vk_device;
  }
  void destroy() const {
    if (handle && m_device) {
      vkDestroyShaderModule(m_device, handle, nullptr);
    }
  }
  VkShaderModule handle{VK_NULL_HANDLE};

 private:
  VkDevice m_device{VK_NULL_HANDLE};
};

}  // namespace VkUtility
