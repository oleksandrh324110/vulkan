#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>
#include <SDL_vulkan.h>

#include "./engine/vulkan/vulkan_init.h"

void main_loop() {}

int main(int argc, char *argv[]) {
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Vulkan_LoadLibrary(NULL);

  SDL_Window *window = SDL_CreateWindow(
      "Hello, Vulkan!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 720,
      480, SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE);

  vulkan_init(window);

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

    main_loop();
  }

  SDL_Quit();
  return 0;
}
