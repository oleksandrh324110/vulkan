#pragma once

#include "vulkan/vulkan.h"
#include "window/window.h"
#include <vulkan/vulkan.h>

typedef struct App {
  Vulkan vulkan;
  Window window;
} App;

App appCreate(void);
void appDestroy(App *app);
void appRun(App *app);
