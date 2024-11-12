#include "./create_instance.h"
#include "SDL_video.h"

VkInstance instance;

void vulkan_init(SDL_Window *window) { create_instance(window); }
