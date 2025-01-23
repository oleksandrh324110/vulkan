#pragma once

#include <stdbool.h>
#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"
#include <vulkan/vulkan.h>

typedef struct {
  GLFWwindow *window;
  VkInstance vkInstance;
} Engine;

Engine engineCreate(void);
void engineDestroy(Engine *engink);
bool engineIsRunning(Engine *engine);
void engineUpdate(Engine *engine);
