#include "app.h"

#include <SDL.h>
#include <SDL_vulkan.h>
#include <stdbool.h>
#include <vulkan/vulkan.h>

#include "./vulkan/create_instance.h"
#include "./vulkan/setup_debug_messenger.h"

#ifdef NDEBUG
const bool enable_validation_layers = false;
#else
const bool enable_validation_layers = true;
#endif

VkInstance instance;
VkDebugUtilsMessengerEXT debug_messenger;

SDL_Window *window;

void app_run() {
  window_init();
  vulkan_init();
  main_loop();
  cleanup();
}

void window_init() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Vulkan_LoadLibrary(NULL);
  window =
      SDL_CreateWindow("Vulkan", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       720, 480, SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE);
}

void vulkan_init() {
  create_instance();
  setup_debug_messenger();
  pick_physical_device();
}

void main_loop() {
  SDL_Event event;
  int running = true;
  while (running) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        running = false;
        break;
      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_q)
          running = false;
        break;
      }
    }

    // code here
  }
}

void cleanup() {
  if (enable_validation_layers)
    destroy_debug_utils_messenger_ext(instance, debug_messenger, NULL);
  vkDestroyInstance(instance, NULL);
  SDL_Quit();
}
