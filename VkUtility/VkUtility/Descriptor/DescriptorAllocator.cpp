#include "VkUtility/Descriptor/DescriptorAllocator.h"
#include "VkUtility/Misc/CreateInfo.h"

namespace VkUtility::Descriptor {

DescriptorAllocator::DescriptorAllocator(VkDevice device) : m_device{device} {
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
