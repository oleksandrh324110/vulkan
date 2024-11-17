#include "./create_instance.h"
#include "./setup_debug_messenger.h"

#include <SDL_vulkan.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

const char *validation_layers[] = {"VK_LAYER_KHRONOS_validation"};
const uint32_t validation_layer_count =
    sizeof(validation_layers) / sizeof(validation_layers[0]);

extern const bool enable_validation_layers;

extern VkInstance instance;

void create_instance() {
  if (enable_validation_layers && !check_validation_layer_support()) {
    fprintf(stderr, "validation layers requested, but not available!\n");
    exit(1);
  }

  VkApplicationInfo app_info = {.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
                                .pApplicationName = "Hello Triangle",
                                .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
                                .pEngineName = "No Engine",
                                .engineVersion = VK_MAKE_VERSION(1, 0, 0),
                                .apiVersion = VK_API_VERSION_1_0};

  uint32_t extension_count;
  const char **extensions = get_required_extensions(&extension_count);

  VkInstanceCreateInfo create_info = {
      .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
      .pApplicationInfo = &app_info,
      .enabledExtensionCount = extension_count,
      .ppEnabledExtensionNames = extensions,
      .enabledLayerCount = 0,
      .pNext = NULL};

  VkDebugUtilsMessengerCreateInfoEXT debug_create_info;
  if (enable_validation_layers) {
    create_info.enabledLayerCount = validation_layer_count;
    create_info.ppEnabledLayerNames = validation_layers;

    populate_debug_messenger_create_info(&debug_create_info);
    create_info.pNext =
        (VkDebugUtilsMessengerCreateInfoEXT *)&debug_create_info;
  }
  create_info.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;

  if (vkCreateInstance(&create_info, NULL, &instance) != VK_SUCCESS) {
    fprintf(stderr, "failed to create VkInstance!\n");
    exit(1);
  }

  free(extensions);
}

bool check_validation_layer_support() {
  uint32_t layer_count;
  vkEnumerateInstanceLayerProperties(&layer_count, NULL);
  VkLayerProperties available_layers[layer_count];
  vkEnumerateInstanceLayerProperties(&layer_count, available_layers);

  for (size_t i = 0; i < validation_layer_count; i++) {
    bool found = false;
    for (size_t j = 0; j < layer_count; j++) {
      if (!strcmp(validation_layers[i], available_layers[j].layerName)) {
        found = true;
        break;
      }
    }
    if (!found)
      return false;
  }

  return true;
}

const char **get_required_extensions(uint32_t *extension_count) {
  uint32_t sdl_extension_count;
  SDL_Vulkan_GetInstanceExtensions(NULL, &sdl_extension_count, NULL);
  sdl_extension_count++;
  if (enable_validation_layers)
    sdl_extension_count += validation_layer_count;

  const char **extensions = malloc(sdl_extension_count * sizeof(char *));
  SDL_Vulkan_GetInstanceExtensions(NULL, &sdl_extension_count, extensions);
  extensions[sdl_extension_count++] =
      VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME;
  if (enable_validation_layers)
    sdl_extension_count += validation_layer_count;

  if (enable_validation_layers)
    extensions[sdl_extension_count - 1] = VK_EXT_DEBUG_UTILS_EXTENSION_NAME;

  *extension_count = sdl_extension_count;
  return extensions;
}
