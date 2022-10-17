#pragma once
#include "VkUtility/Misc/File.h"
#include "VkUtility/Handle/UsingHandle.h"
#include "VkUtility/Misc/CreateInfo.h"

namespace VkUtility::Shader {

[[nodiscard]] inline VkShaderModuleHandle load(const std::string& path, VkDevice device) {
  std::string full_path{path};
#ifdef SHADER_PATH
  full_path = std::string{SHADER_PATH} + path;
#endif
  const auto file_data = File::read(full_path);
  const auto info = CreateInfo::vk_shader_module_create_info(file_data);
  return VkShaderModuleHandle{info, device};
}

}  // namespace VkUtility::Shader
