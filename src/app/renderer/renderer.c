#include "renderer.h"
#include <GLFW/glfw3.h>
#include <stdint.h>
#include <vulkan/vulkan.h>

Renderer rendererCreate() {
  return (Renderer){.vkInstance = vulkanCreateInstance()};
}

void rendererDestroy(Renderer *renderer) {
  vkDestroyInstance(renderer->vkInstance, NULL);
}
