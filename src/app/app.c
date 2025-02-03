#include <stdbool.h>

#include "GLFW/glfw3.h"
#include "app.h"
#include "vulkan/vulkan.h"
#include "window/window.h"

App appCreate(void) {
  App app;
  windowCreate(&app);
  vulkanInit(&app);
  return app;
}

void appDestroy(App *app) {
  vulkanDestroy(app);
  windowDestroy(app);
}

void appRun(App *app) {
  while (!windowShouldClose(app)) {
    glfwPollEvents();
  }
}
