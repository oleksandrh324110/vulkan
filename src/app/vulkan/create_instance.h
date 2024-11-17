#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <vulkan/vulkan.h>

void create_instance();
bool check_validation_layer_support();
const char **get_required_extensions(uint32_t *extensionCount);
