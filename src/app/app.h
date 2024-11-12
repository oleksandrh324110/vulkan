#include <stdbool.h>

#include <SDL_vulkan.h>
#include <vulkan/vulkan.h>

extern VkInstance instance;
extern SDL_Window *window;

#include "./vulkan/create_instance.h"

void app_run();
void window_init();
void vulkan_init();
void main_loop();
void clean();
