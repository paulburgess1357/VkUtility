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
template <typename T>
void write_to_cpu_buffer(VmaAllocator allocator, VmaAllocation allocation, std::vector<T>& source) {
  // Fill buffer starting at the beginning
  write_to_cpu_buffer(allocator, allocation, source.data(), source.size() * sizeof(T), 0);
}

inline void write_to_cpu_buffer(VmaAllocator allocator, VmaAllocation allocation, const void* source,
                                const VkDeviceSize source_size, const VkDeviceSize dest_offset = 0) {
  // Fill portion of buffer
  void* destination{nullptr};
  vmaMapMemory(allocator, allocation, &destination);
  destination = static_cast<char*>(destination) + dest_offset;
  memcpy(destination, source, source_size);
  vmaUnmapMemory(allocator, allocation);
}

}  // namespace VkUtility::Memory
