#pragma once
#include <exception>

namespace VkUtility::Exceptions {

class VkStartupException final : public std::exception {
 public:
  [[nodiscard]] const char* what() const noexcept override {
    return "VkUtility failed";
  }
};

}  // namespace VkUtility::Exceptions
