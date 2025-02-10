#include "app.h"
#include "renderer/renderer.h"
#include "window/window.h"
#include <GLFW/glfw3.h>
#include <stdbool.h>

static void keymapCallback(App *app) {
  if (glfwGetKey(app->window.handle, GLFW_KEY_Q))
    glfwSetWindowShouldClose(app->window.handle, GLFW_TRUE);
}

App appCreate(void) {
  return (App){.renderer = rendererCreate(), .window = windowCreate()};
}

void appDestroy(App *app) {
  rendererDestroy(&app->renderer);
  windowDestroy(&app->window);
}

void appRun(App *app) {
  while (!windowShouldClose(&app->window)) {
    glfwPollEvents();
    keymapCallback(app);
  }
}
