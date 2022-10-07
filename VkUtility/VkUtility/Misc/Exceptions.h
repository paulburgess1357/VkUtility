#pragma once
#include <exception>

namespace VkUtility::Exceptions {

class VkUtilityException final : public std::exception {
 public:
  [[nodiscard]] const char* what() const noexcept override {
    return "VkUtility failed";
  }
};

class FileSystemException final : public std::exception {
 public:
  [[nodiscard]] const char* what() const noexcept override {
    return "File is open!";
  }
};

}  // namespace VkUtility::Exceptions
