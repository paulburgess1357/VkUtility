#pragma once
#include <vulkan/vulkan.h>
#include "VkUtility/Misc/Exceptions.h"
#include "VkShared/Macros.h"
#include "VkShared/MemAlloc.h"

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

struct VMAHandle {
  // ReSharper disable once CppNonExplicitConvertingConstructor
  VMAHandle(VkBuffer buffer) {
    handle = buffer;
    allocation = VK_NULL_HANDLE;
  }

  [[nodiscard]] bool operator!() const {
    return handle == VK_NULL_HANDLE;
  }

  VkBuffer handle{VK_NULL_HANDLE};
  VmaAllocation allocation{VK_NULL_HANDLE};
};

class CreateDestroyVMABuffer {
 public:
  void create() {
    handle.handle = VK_NULL_HANDLE;
    handle.allocation = VK_NULL_HANDLE;
  }
  void create(const VkBufferCreateInfo& buffer_info, const VmaAllocationCreateInfo& vma_info,
              VmaAllocator vma_allocator) {
    VkCheck(vmaCreateBuffer(vma_allocator, &buffer_info, &vma_info, &handle.handle, &handle.allocation, nullptr),
            Exceptions::VMAException());
    m_allocator = vma_allocator;
  }
  void destroy() const {
    if (handle.handle && handle.allocation && m_allocator) {
      vmaDestroyBuffer(m_allocator, handle.handle, handle.allocation);
    }
  }
  VMAHandle handle{VK_NULL_HANDLE};

 private:
  VmaAllocator m_allocator{VK_NULL_HANDLE};
};

}  // namespace VkUtility
