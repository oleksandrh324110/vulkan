#include <GLFW/glfw3.h>
#include <stdint.h>
#include <vulkan/vulkan.h>

#include "vulkan.h"

void vulkanInit(App *app) { vulkanCreateInstance(app); }
void vulkanDestroy(App *app) { vkDestroyInstance(app->vkInstance, NULL); }
