#pragma once
#include "VkUtility/Handle/UsingHandle.h"
#include <vector>
#include <utility>
#include <vulkan/vulkan.h>

// Manages allocation of descriptor sets.  New descriptor pools will automatically be created
// once existing pools are full.  All pools can be reset and reused.

namespace VkUtility::Descriptor {

class DescriptorAllocator {
 public:
  explicit DescriptorAllocator(VkDevice device);

  // void reset_pools();
  //[[nodiscard]] bool allocate(VkDescriptorSet* set, VkDescriptorSetLayout layout);

 private:
  [[nodiscard]] VkDescriptorPoolHandle create_pool(const uint32_t ratio_multiplier, const uint32_t descriptor_set_count,
                                                   const VkDescriptorPoolCreateFlags flags);

  VkDescriptorPoolHandle m_current_pool{};
  std::vector<VkDescriptorPoolHandle> m_used_pools;
  std::vector<VkDescriptorPoolHandle> m_free_pools;

  VkDevice m_device{VK_NULL_HANDLE};
};

class DescriptorPoolSizes {
 public:
  [[nodiscard]] static std::vector<VkDescriptorPoolSize> descriptor_type_counts(const uint32_t ratio_multiplier) {
    std::vector<VkDescriptorPoolSize> type_counts;
    type_counts.reserve(descriptor_type_ratios.size());

    for (auto& [descriptor_type, ratio] : descriptor_type_ratios) {
      type_counts.emplace_back(
          VkDescriptorPoolSize{.type = descriptor_type,
                               .descriptorCount = static_cast<uint32_t>(ratio * static_cast<float>(ratio_multiplier))});
    }
    return type_counts;
  }

 private:
  inline static std::vector<std::pair<VkDescriptorType, float>> descriptor_type_ratios = {
      {VK_DESCRIPTOR_TYPE_SAMPLER, 0.5f},                // e.g. 1000 (descriptor_count_per_descriptor_type) * 0.5
      {VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 4.f},  // e.g. 1000 (descriptor_count_per_descriptor_type) * 0.4
      {VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 4.f},
      {VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1.f},
      {VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1.f},
      {VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1.f},
      {VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 2.f},
      {VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 2.f},
      {VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1.f},
      {VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1.f},
      {VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 0.5f}};
};

}  // namespace VkUtility::Descriptor
