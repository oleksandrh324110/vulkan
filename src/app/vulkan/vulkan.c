#include "vulkan.h"
#include <GLFW/glfw3.h>
#include <stdint.h>
#include <vulkan/vulkan.h>

Vulkan vulkanCreate() { return (Vulkan){.instance = vulkanCreateInstance()}; }

void vulkanDestroy(Vulkan *vulkan) {
  vkDestroyInstance(vulkan->instance, NULL);
}
