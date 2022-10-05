#pragma once
#include "VkUtility/Handle/CreateDestroy.h"
#include "VkShared/THandle.h"

namespace VkUtility {
using VkCommandPoolHandle = VkShared::THandle<CreateDestroyCommandPool>;
}
