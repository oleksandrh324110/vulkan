#include "vulkan.h"
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vulkan/vulkan.h>

VkInstance vulkanCreateInstance() {
  VkApplicationInfo appInfo = {.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
                               .pApplicationName = "Hello Triangle",
                               .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
                               .pEngineName = "No Engine",
                               .engineVersion = VK_MAKE_VERSION(1, 0, 0),
                               .apiVersion = VK_API_VERSION_1_0};

  uint32_t glfwExtensionCount = 0;
  const char **glfwExtensions;
  glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

  for (size_t i = 0; i < glfwExtensionCount; i++)
    printf("Required extension: %s\n", glfwExtensions[i]);
  putchar('\n');

  uint32_t extensionCount = 0;
  vkEnumerateInstanceExtensionProperties(NULL, &extensionCount, NULL);
  VkExtensionProperties extensions[extensionCount];
  vkEnumerateInstanceExtensionProperties(NULL, &extensionCount, extensions);

  for (size_t i = 0; i < extensionCount; i++)
    printf("Available extension: %s\n", extensions[i].extensionName);
  putchar('\n');

  const size_t requiredExtensionsCount = glfwExtensionCount + 1;
  const char *requiredExtensions[requiredExtensionsCount];
  for (size_t i = 0; i < glfwExtensionCount; i++)
    requiredExtensions[i] = glfwExtensions[i];
  requiredExtensions[requiredExtensionsCount - 1] =
      VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME;

  for (size_t i = 0; i < requiredExtensionsCount; i++) {
    bool found = false;

    for (size_t j = 0; j < extensionCount; j++)
      if (strcmp(requiredExtensions[i], extensions[j].extensionName) == 0) {
        found = true;
        break;
      }

    if (!found) {
      fprintf(stderr, "Required extension %s not found!\n",
              requiredExtensions[i]);
      exit(1);
    }
  }

  VkInstanceCreateInfo createInfo = {
      .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
      .pApplicationInfo = &appInfo,
      .enabledExtensionCount = requiredExtensionsCount,
      .ppEnabledExtensionNames = (const char **)requiredExtensions,
      .flags = VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR,
      .enabledLayerCount = 0};

  VkInstance instance;
  if (vkCreateInstance(&createInfo, NULL, &instance) != VK_SUCCESS) {
    fprintf(stderr, "Failed to create Vulkan instance!\n");
    exit(1);
  }
  return instance;
}
