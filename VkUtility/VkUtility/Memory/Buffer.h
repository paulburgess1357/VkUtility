#pragma once
#include "VkUtility/Handle/UsingHandle.h"
#include "VkUtility/Misc/CreateInfo.h"
#include "VkUtility/Submit/ImmediateSubmit.h"
#include "VkShared/MemAlloc.h"
#include <cstring>
#include <vulkan/vulkan.h>

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

inline void write_to_cpu_buffer(VmaAllocator allocator, VmaAllocation allocation, const void* source,
                                const VkDeviceSize source_size, const VkDeviceSize dest_offset = 0) {
  // Fill portion of buffer
  void* destination{nullptr};
  vmaMapMemory(allocator, allocation, &destination);
  destination = static_cast<char*>(destination) + dest_offset;
  memcpy(destination, source, source_size);
  vmaUnmapMemory(allocator, allocation);
}

[[nodiscard]] inline VMABufferHandle create_and_write_to_gpu_buffer(const ImmediateSubmit& submit,
                                                                    VmaAllocator allocator, const void* source,
                                                                    const VkDeviceSize source_size,
                                                                    const VkBufferUsageFlags gpu_usage) {
  // Write to staging buffer
  const auto staging_info = CreateInfo::vk_buffer_create_info(source_size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT);
  const auto staging_buffer = allocate_cpu_buffer(staging_info, allocator);
  write_to_cpu_buffer(allocator, staging_buffer().allocation, source, source_size, 0);

  // Create gpu buffer
  const auto gpu_info = CreateInfo::vk_buffer_create_info(source_size, gpu_usage | VK_BUFFER_USAGE_TRANSFER_DST_BIT);
  auto gpu_buffer = allocate_gpu_buffer(gpu_info, allocator);

  // Copy to gpu buffer
  submit.submit([&](VkCommandBuffer cmd) {
    VkBufferCopy copy;
    copy.dstOffset = 0;
    copy.srcOffset = 0;
    copy.size = source_size;
    vkCmdCopyBuffer(cmd, staging_buffer().handle, gpu_buffer().handle, 1, &copy);
  });

  return gpu_buffer;
}

}  // namespace VkUtility::Memory
