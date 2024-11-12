#include "./create_instance.h"

#include <SDL_vulkan.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vulkan/vulkan.h>

void create_instance() {
  VkApplicationInfo app_info = {.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
                                .pApplicationName = "Hello Triangle",
                                .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
                                .pEngineName = "No Engine",
                                .engineVersion = VK_MAKE_VERSION(1, 0, 0),
                                .apiVersion = VK_API_VERSION_1_0};

  uint32_t sdl_extension_count;
  SDL_Vulkan_GetInstanceExtensions(NULL, &sdl_extension_count, NULL);
  const char **sdl_extensions = malloc(++sdl_extension_count * sizeof(char *));
  SDL_Vulkan_GetInstanceExtensions(NULL, &sdl_extension_count, sdl_extensions);
  sdl_extensions[sdl_extension_count++] =
      VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME;

  for (size_t i = 0; i < sdl_extension_count; i++)
    printf("%s\n", sdl_extensions[i]);
  printf("\n");

  uint32_t extension_count;
  vkEnumerateInstanceExtensionProperties(NULL, &extension_count, NULL);
  VkExtensionProperties extensions[extension_count];
  vkEnumerateInstanceExtensionProperties(NULL, &extension_count, extensions);

  for (size_t i = 0; i < extension_count; i++)
    printf("%s\n", extensions[i].extensionName);
  printf("\n");

  for (size_t i = 0; i < sdl_extension_count; i++) {
    bool found = false;
    for (size_t j = 0; j < extension_count; j++) {
      if (!strcmp(sdl_extensions[i], extensions[j].extensionName)) {
        found = true;
        break;
      }
    }
    if (!found) {
      fprintf(stderr, "extension %s wasn't found\n", sdl_extensions[i]);
      exit(1);
    }
  }

  VkInstanceCreateInfo create_info = {
      .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
      .pApplicationInfo = &app_info,
      .enabledExtensionCount = sdl_extension_count,
      .ppEnabledExtensionNames = sdl_extensions,
      .enabledLayerCount = 0};
  create_info.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;

  if (vkCreateInstance(&create_info, NULL, &instance) != VK_SUCCESS) {
    fprintf(stderr, "failed to create instance!\n");
    exit(1);
  }

  free(sdl_extensions);
}
