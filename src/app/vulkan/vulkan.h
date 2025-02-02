#pragma once

#include "../app.h"

void vulkanInit(App *app);
void vulkanCreateInstance(App *app);
void setupDebugMessenger(App *app);
void vulkanDestroy(App *app);
