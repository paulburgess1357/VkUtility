#pragma once
#include <exception>

namespace VkUtility::Exceptions {

class VkUtilityException final : public std::exception {
 public:
  [[nodiscard]] const char* what() const noexcept override {
    return "VkUtility failed";
  }
};

class VMAException final : public std::exception {
 public:
  [[nodiscard]] const char* what() const noexcept override {
    return "VMA failed";
  }
};

class FileSystemException final : public std::exception {
 public:
  [[nodiscard]] const char* what() const noexcept override {
    return "File is open!";
  }
};

class ImmediateSubmitException final : public std::exception {
 public:
  [[nodiscard]] const char* what() const noexcept override {
    return "Immediate submit failed";
  }
};
}  // namespace VkUtility::Exceptions
