#include <SDL.h>

#include "app.h"

VkInstance instance;
SDL_Window *window;

void app_run() {
  window_init();
  vulkan_init();
  main_loop();
  clean();
}

void window_init() {
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Vulkan_LoadLibrary(NULL);

  window =
      SDL_CreateWindow("Vulkan", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       720, 480, SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE);
}
void vulkan_init() { create_instance(); }

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

void clean() { vkDestroyInstance(instance, NULL); }
