#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vulkan/vulkan.h>

#include "setup_debug_messenger.h"

extern VkDebugUtilsMessengerEXT debug_messenger;
extern VkInstance instance;
extern const bool enable_validation_layers;

static VKAPI_ATTR VkBool32 VKAPI_CALL
debug_callback(VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
               VkDebugUtilsMessageTypeFlagsEXT message_type,
               const VkDebugUtilsMessengerCallbackDataEXT *callback_data,
               void *user_data) {
  fprintf(stderr, "validation layer: severity = %d, message = %s\n",
          message_severity, callback_data->pMessage);
  return VK_FALSE;
}

void setup_debug_messenger() {
  if (!enable_validation_layers)
    return;

  VkDebugUtilsMessengerCreateInfoEXT create_info;
  populate_debug_messenger_create_info(&create_info);

  if (create_debug_utils_messenger_ext(instance, &create_info, NULL,
                                       &debug_messenger) != VK_SUCCESS) {
    fprintf(stderr, "failed to set up debug messenger!\n");
    exit(1);
  }
}

VkResult create_debug_utils_messenger_ext(
    VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *create_info,
    const VkAllocationCallbacks *allocator,
    VkDebugUtilsMessengerEXT *debug_messenger) {
  PFN_vkCreateDebugUtilsMessengerEXT func =
      (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
          instance, "vkCreateDebugUtilsMessengerEXT");

  return func ? func(instance, create_info, allocator, debug_messenger)
              : VK_ERROR_EXTENSION_NOT_PRESENT;
}

void populate_debug_messenger_create_info(
    VkDebugUtilsMessengerCreateInfoEXT *create_info) {
  memset(create_info, 0, sizeof(VkDebugUtilsMessengerCreateInfoEXT));
  create_info->sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
  create_info->messageSeverity =
      VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
      VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
      VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
  create_info->messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                             VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                             VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
  create_info->pfnUserCallback = debug_callback;
}

void destroy_debug_utils_messenger_ext(
    VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger,
    const VkAllocationCallbacks *pAllocator) {
  PFN_vkDestroyDebugUtilsMessengerEXT func =
      (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
          instance, "vkDestroyDebugUtilsMessengerEXT");
  func ? func(instance, debugMessenger, pAllocator) : NULL;
}
