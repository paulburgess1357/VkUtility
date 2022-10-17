#pragma once
#include "VkUtility/Misc/Exceptions.h"
#include <VkShared/Macros.h>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>

namespace VkUtility::File {

[[nodiscard]] inline std::vector<char> read(const std::string& path) {
  std::ifstream file(path, std::ios::ate | std::ios::binary);
  // if (file.is_open()) {
  //   VkError("Input file is open: " + path);
  //   throw Exceptions::FileSystemException();
  // }

  if (!std::filesystem::exists(path)) {
    VkError("File does not exist: " + path);
    throw Exceptions::FileSystemException();
  }

  const size_t file_size = file.tellg();
  std::vector<char> buffer(file_size);

  file.seekg(0);
  file.read(buffer.data(), static_cast<long long>(file_size));
  file.close();

  return buffer;
}

}  // namespace VkUtility::File
