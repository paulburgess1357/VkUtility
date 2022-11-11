#pragma once
#include "VkUtility/Handle/UsingHandle.h"
#include "VkUtility/Misc/CreateInfo.h"
#include "VkShared/MemAlloc.h"
#include <vulkan/vulkan.h>

namespace VkUtility::Image {

[[nodiscard]] inline VMAImageHandle allocate_gpu_image(const VkImageCreateInfo& image_info, VmaAllocator allocator) {
  const auto info = CreateInfo::vma_allocation_create_info(VMA_MEMORY_USAGE_AUTO_PREFER_DEVICE, 0,
                                                           VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, 0);
  return VMAImageHandle{image_info, info, allocator};
}

[[nodiscard]] inline VkImageWrapped create_gpu_image(VmaAllocator allocator, VkDevice device, const VkFormat format,
                                                     const VkImageUsageFlags usage, const VkExtent3D extent,
                                                     const VkSampleCountFlagBits sample_count,
                                                     const uint32_t mip_levels, const VkImageAspectFlags aspect_flags,
                                                     const uint32_t array_layers = 1,
                                                     const VkImageType image_type = VK_IMAGE_TYPE_2D,
                                                     const VkImageViewType image_view_type = VK_IMAGE_VIEW_TYPE_2D) {
  // Create VMA Image
  const auto image_info = CreateInfo::vk_image_create_info(format, usage, extent, sample_count, mip_levels,
                                                           array_layers, image_type);
  auto vma_image = allocate_gpu_image(image_info, allocator);

  const auto view_info = CreateInfo::vk_image_view_create_info(vma_image().handle, format, aspect_flags, array_layers,
                                                               image_view_type);
  return VkImageWrapped{std::move(vma_image), VKImageViewHandle{view_info, device}};
}

}  // namespace VkUtility::Image
