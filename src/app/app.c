#include <stdbool.h>

#include "GLFW/glfw3.h"
#include "app.h"
#include "vulkan/vulkan.h"
#include "window/window.h"

static void keymapCallback(App *app) {
  if (glfwGetKey(app->window.handle, GLFW_KEY_Q))
    glfwSetWindowShouldClose(app->window.handle, GLFW_TRUE);
}

App appCreate(void) {
  return (App){.vulkan = vulkanCreate(), .window = windowCreate()};
}

void appDestroy(App *app) {
  vulkanDestroy(&app->vulkan);
  windowDestroy(&app->window);
}

void appRun(App *app) {
  while (!windowShouldClose(&app->window)) {
    glfwPollEvents();
    keymapCallback(app);
  }
}
