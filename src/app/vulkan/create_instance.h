#pragma once

#include <stdbool.h>
#include <stdint.h>

void create_instance();
bool checkValidationLayerSupport();
const char **getRequiredExtensions(uint32_t *extensionsCount);
