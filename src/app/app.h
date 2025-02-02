#pragma once

#include "GLFW/glfw3.h"
#include <vulkan/vulkan.h>

typedef struct App {
  VkInstance vkInstance;
  GLFWwindow *window;
} App;

App appCreate(void);
void appRun(App *app);
void appDestroy(App *app);
