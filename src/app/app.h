#pragma once

#include "GLFW/glfw3.h"
#include <vulkan/vulkan.h>

typedef struct App {
  VkInstance vkInstance;
  GLFWwindow *window;
} App;

App appCreate(void);
void appDestroy(App *app);
void appRun(App *app);
