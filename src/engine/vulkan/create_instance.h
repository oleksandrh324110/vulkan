#include <stdio.h>

#include <SDL_vulkan.h>
#include <vulkan/vulkan.h>

extern VkInstance instance;

void create_instance() {
  VkApplicationInfo app_info = {.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
                                .pApplicationName = "Hello Triangle",
                                .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
                                .pEngineName = "No Engine",
                                .engineVersion = VK_MAKE_VERSION(1, 0, 0),
                                .apiVersion = VK_API_VERSION_1_0};

  uint32_t sdl_extension_count;
  const char **sdl_extensions;
  SDL_Vulkan_GetInstanceExtensions(NULL, &sdl_extension_count, sdl_extensions);

  VkInstanceCreateInfo create_info = {
      .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
      .pApplicationInfo = &app_info,
      .enabledExtensionCount = sdl_extension_count,
      .ppEnabledExtensionNames = sdl_extensions,
      .enabledLayerCount = 0};

  if (vkCreateInstance(&create_info, NULL, &instance) != VK_SUCCESS) {
    fprintf(stderr, "failed to create instance!\n");
    exit(1);
  }
}
