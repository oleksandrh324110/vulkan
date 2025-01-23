#include <GLFW/glfw3.h>
#include <stdint.h>
#include <vulkan/vulkan.h>

#include "vulkan.h"

void vulkanInit(Engine *engine) { vulkanCreateInstance(engine); }

void vulkanDestroy(Engine *engine) {
  vkDestroyInstance(engine->vkInstance, NULL);
}
