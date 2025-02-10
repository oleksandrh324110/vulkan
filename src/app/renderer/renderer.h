#pragma once

#include <vulkan/vulkan_core.h>

typedef struct Renderer {
  VkInstance vkInstance;
} Renderer;

Renderer rendererCreate();
void rendererDestroy(Renderer *renderer);

VkInstance vulkanCreateInstance();
void setupDebugMessenger(Renderer *renderer);
