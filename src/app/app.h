#pragma once

#include "renderer/renderer.h"
#include "window/window.h"
#include <vulkan/vulkan.h>

typedef struct App {
  Renderer renderer;
  Window window;
} App;

App appCreate(void);
void appDestroy(App *app);
void appRun(App *app);
