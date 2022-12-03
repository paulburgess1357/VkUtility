#pragma once
#include "VkUtility/Handle/UsingHandle.h"
#include <vulkan/vulkan.h>
#include <unordered_map>
#include <vector>

namespace VkUtility::Descriptor {

class DescriptorLayoutCache {
 public:
  explicit DescriptorLayoutCache(VkDevice device);
  [[nodiscard]] VkDescriptorSetLayout layout(const VkDescriptorSetLayoutCreateInfo& info);

 private:
  struct VkDescriptorSetLayoutCreateInfoKey {
    std::vector<VkDescriptorSetLayoutBinding> bindings;
    [[nodiscard]] bool operator==(const VkDescriptorSetLayoutCreateInfoKey& other) const;
    [[nodiscard]] size_t hash() const;
  };

  struct DescriptorLayoutHash {
    std::size_t operator()(const VkDescriptorSetLayoutCreateInfoKey& k) const {
      return k.hash();
    }
  };

  VkDevice m_device{VK_NULL_HANDLE};
  std::unordered_map<VkDescriptorSetLayoutCreateInfoKey, VkDescriptorSetLayoutHandle, DescriptorLayoutHash> m_layouts{};
};

}  // namespace VkUtility::Descriptor
