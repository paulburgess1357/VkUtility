#pragma once
#include "VkUtility/Handle/UsingHandle.h"
#include "VkUtility/Misc/CreateInfo.h"
#include "VkShared/MemAlloc.h"

namespace VkUtility::Memory {

[[nodiscard]] inline VMABufferHandle allocate_cpu_buffer(const VkBufferCreateInfo& buffer_info,
                                                         VmaAllocator allocator) {
  const auto info = CreateInfo::vma_allocation_create_info(
      VMA_MEMORY_USAGE_AUTO_PREFER_HOST, VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT,
      VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, 0);
  return VMABufferHandle{buffer_info, info, allocator};
}

[[nodiscard]] inline VMABufferHandle allocate_gpu_buffer(const VkBufferCreateInfo& buffer_info,
                                                         VmaAllocator allocator) {
  const auto info = CreateInfo::vma_allocation_create_info(VMA_MEMORY_USAGE_AUTO_PREFER_DEVICE, 0,
                                                           VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, 0);
  return VMABufferHandle{buffer_info, info, allocator};
}

// TODO left off on writting map memory functions.

}  // namespace VkUtility::Memory
