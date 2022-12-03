#include "VkUtility/Descriptor/DescriptorAllocator.h"
#include "VkUtility/Misc/CreateInfo.h"

namespace VkUtility::Descriptor {

DescriptorAllocator::DescriptorAllocator(VkDevice device) : m_device{device} {
}

void DescriptorAllocator::allocate(VkDescriptorSetLayout layout, VkDescriptorSet* handle) {
  if (!m_current_pool()) {
    m_current_pool = pool(1000, 1000, 0);
  }
  auto info = CreateInfo::vk_descriptor_alloc_info(layout, m_current_pool());

  switch (vkAllocateDescriptorSets(m_device, &info, handle)) {  // NOLINT(clang-diagnostic-switch-enum)
    case VK_SUCCESS:
      break;
    case VK_ERROR_FRAGMENTED_POOL:
    case VK_ERROR_OUT_OF_POOL_MEMORY:
      VkWarning("Existing pool is full or fragmented.  Attempting to allocate a new pool");

      // Store current pool into used pools
      m_used_pools.push(std::move(m_current_pool));

      // Create new pool or obtain a free pool
      m_current_pool = pool(1000, 1000, 0);

      // Allocate
      info = CreateInfo::vk_descriptor_alloc_info(layout, m_current_pool());
      VkCheck(vkAllocateDescriptorSets(m_device, &info, handle), Exceptions::VkUtilityException());
      break;

    default:
      VkError("Failed to allocate resources for descriptor set");
      break;
  }
}

void DescriptorAllocator::reset() {
  // Free existing pool descriptors and move into 'free pools' for future use
  while (!m_used_pools.empty()) {
    VkDescriptorPoolHandle pool = std::move(m_used_pools.front());
    m_used_pools.pop();
    vkResetDescriptorPool(m_device, pool(), 0);
    m_free_pools.push(std::move(pool));
  }

  // Free current pool resources (keep in current pool variable)
  if (m_current_pool()) {
    vkResetDescriptorPool(m_device, m_current_pool(), 0);
  }
}

VkDescriptorPoolHandle DescriptorAllocator::pool(const uint32_t ratio_multiplier, const uint32_t descriptor_set_count,
                                                 const VkDescriptorPoolCreateFlags flags) {
  // Return a free pool if it exists.  If no free pools are avaiable, create a new pool
  VkDescriptorPoolHandle pool;
  if (!m_free_pools.empty()) {
    // Grab existing free pool
    pool = std::move(m_free_pools.front());
    m_free_pools.pop();
  } else {
    // Create a new pool
    pool = create_pool(ratio_multiplier, descriptor_set_count, flags);
  }

  return pool;
}

VkDescriptorPoolHandle DescriptorAllocator::create_pool(const uint32_t ratio_multiplier,
                                                        const uint32_t descriptor_set_count,
                                                        const VkDescriptorPoolCreateFlags flags) {
  const auto descriptor_type_counts = DescriptorPoolSizes::descriptor_type_counts(ratio_multiplier);
  const auto info = CreateInfo::vk_descriptor_pool_create_info(descriptor_set_count, flags, descriptor_type_counts);

  return VkDescriptorPoolHandle{info, m_device};

  // Ratio multiplier and Descriptor Set Counts do not have to be the same number!

  // Descriptor Type Counts (ratio_multiplier = 1000):
  // VK_DESCRIPTOR_TYPE_SAMPLER; 1000 * 0.5 = 500
  // VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER 1000 * 0.4 = 400
  // VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE 1000 * .7 = 700
  // VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER 1000 * .2 = 200

  // Descriptor Set Counts (descriptor_set_count = 1000):
  // 1000 possible unique sets.  Each set can contain a number of the above resources.
  // E.g. Set 1: {
  //              2 VK_DESCRIPTOR_TYPE_SAMPLER,
  //              3 VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
  //              5 VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER
  //              }

  // E.g. Set 2: {
  //              1 VK_DESCRIPTOR_TYPE_SAMPLER,
  //              2 VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
  //              }

  // E.g. Set 1000 (max): {
  //              1 VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT
  // }

  // Totals: 3 VK_DESCRIPTOR_TYPE_SAMPLER
  //         5 VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER
  //         5 VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER
  //         1 VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT
}

}  // namespace VkUtility::Descriptor
