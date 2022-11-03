#pragma once
#include "VkUtility/Handle/UsingHandle.h"
#include "VkUtility/Misc/CreateInfo.h"
#include "VkUtility/Submit/ImmediateSubmit.h"
#include "VkShared/MemAlloc.h"
#include <cstring>
#include <vulkan/vulkan.h>

namespace VkUtility::Image {

[[nodiscard]] inline VMAImageHandle allocate_cpu_image(const VkImageCreateInfo& image_info, VmaAllocator allocator) {
}

}  // namespace VkUtility::Image
