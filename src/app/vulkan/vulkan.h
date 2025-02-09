#pragma once

#include <vulkan/vulkan_core.h>

typedef struct Vulkan {
  VkInstance instance;
} Vulkan;

Vulkan vulkanCreate();
VkInstance vulkanCreateInstance();
void setupDebugMessenger(Vulkan *this);
void vulkanDestroy(Vulkan *this);
