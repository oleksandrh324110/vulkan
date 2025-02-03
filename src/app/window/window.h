#pragma once

#include "../app.h"
#include <stdbool.h>

void windowCreate(App *app);
void windowDestroy(App *app);

bool windowShouldClose(App *app);
