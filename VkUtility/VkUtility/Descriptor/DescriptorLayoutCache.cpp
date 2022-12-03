#include "VkUtility/Descriptor/DescriptorLayoutCache.h"
#include "VkShared/Macros.h"
#include <ranges>
#include <algorithm>
#include <functional>

namespace VkUtility::Descriptor {

// ==================== VkDescriptorSetLayoutCreateInfoKey =======================
bool DescriptorLayoutCache::VkDescriptorSetLayoutCreateInfoKey::operator==(
    const VkDescriptorSetLayoutCreateInfoKey& other) const {
  if (other.bindings.size() != bindings.size()) {
    return false;
  }

  for (size_t i = 0; i < other.bindings.size(); i++) {
    // For each binding, compare binding type, info, flags, etc.
    if (const bool binding_equal = other.bindings[i].binding == bindings[i].binding &&
                                   other.bindings[i].descriptorType == bindings[i].descriptorType &&
                                   other.bindings[i].descriptorCount == bindings[i].descriptorCount &&
                                   other.bindings[i].stageFlags == bindings[i].stageFlags;
        !binding_equal) {
      return false;
    }
  }

  return true;
}

size_t DescriptorLayoutCache::VkDescriptorSetLayoutCreateInfoKey::hash() const {
  size_t result = std::hash<size_t>()(bindings.size());
  for (const auto& [binding, descriptorType, descriptorCount, stageFlags, pImmutableSamplers] : bindings) {
    size_t binding_hash = binding | descriptorType << 8 | descriptorCount << 16 | stageFlags << 24;
    result ^= std::hash<size_t>()(binding_hash);
  }
  return result;
}

// ============================ DescriptorLayoutCache ============================
DescriptorLayoutCache::DescriptorLayoutCache(VkDevice device) : m_device{device} {
}

VkDescriptorSetLayout DescriptorLayoutCache::layout(const VkDescriptorSetLayoutCreateInfo& info) {
  VkDescriptorSetLayoutCreateInfoKey layout_key;
  layout_key.bindings.reserve(info.bindingCount);

  for (uint32_t i = 0; i < info.bindingCount; i++) {
    layout_key.bindings.push_back(info.pBindings[i]);
  }

  // Sort each layout info by binding location  (for key creation, NOT for shader use)
  std::ranges::sort(layout_key.bindings,
                    [](const VkDescriptorSetLayoutBinding& b1, const VkDescriptorSetLayoutBinding& b2) {
                      return b1.binding < b2.binding;
                    });

  if (!m_layouts.contains(layout_key)) {
    // Layout does not exist in cache; Load new layout
    VkTrace("Loading descriptor set layout into cache");
    m_layouts[layout_key] = VkDescriptorSetLayoutHandle{info, m_device};
  }

  return m_layouts.at(layout_key)();
}

}  // namespace VkUtility::Descriptor
