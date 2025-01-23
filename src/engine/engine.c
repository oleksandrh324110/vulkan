#include <GLFW/glfw3.h>
#include <stdbool.h>

#include "engine.h"
#include "vulkan/vulkan.h"
#include "window/window.h"

Engine engineCreate(void) {
  Engine engine;

  windowCreate(&engine);
  vulkanInit(&engine);

  return engine;
}

void engineDestroy(Engine *engine) {
  vkDestroyInstance(engine->vkInstance, NULL);
  glfwTerminate();
}

bool engineIsRunning(Engine *engine) {
  return !glfwWindowShouldClose(engine->window);
}

void engineUpdate(Engine *engine) { glfwPollEvents(); }
