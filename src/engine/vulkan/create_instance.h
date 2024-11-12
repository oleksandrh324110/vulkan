#include <stdio.h>

#include <SDL_vulkan.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

extern VkInstance instance;
extern SDL_Window *window;

void create_instance(SDL_Window *window) {
  VkApplicationInfo app_info = {.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
                                .pApplicationName = "Hello Triangle",
                                .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
                                .pEngineName = "No Engine",
                                .engineVersion = VK_MAKE_VERSION(1, 0, 0),
                                .apiVersion = VK_API_VERSION_1_0};

  uint32_t sdl_extension_count;
  SDL_Vulkan_GetInstanceExtensions(NULL, &sdl_extension_count, NULL);
  const char **sdl_extensions =
      malloc(++sdl_extension_count * (sizeof(char *)));
  SDL_Vulkan_GetInstanceExtensions(NULL, &sdl_extension_count, sdl_extensions);
  sdl_extensions[sdl_extension_count++] =
      VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME;

  for (size_t i = 0; i < sdl_extension_count; i++)
    printf("%s\n", sdl_extensions[i]);

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
}
