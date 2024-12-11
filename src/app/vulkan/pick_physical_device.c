#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

#include "pick_physical_device.h"

extern VkInstance instance;

void pick_physical_device() {
  VkPhysicalDevice physical_device = VK_NULL_HANDLE;

  uint32_t device_count;
  vkEnumeratePhysicalDevices(instance, &device_count, NULL);

  if (device_count == 0) {
    fprintf(stderr, "failed to find GPUs with Vulkan support!\n");
    exit(1);
  }

  VkPhysicalDevice devices[device_count];
  vkEnumeratePhysicalDevices(instance, &device_count, devices);

  for (size_t i = 0; i < device_count; i++) {
    if (is_device_suitable(&devices[i])) {
      physical_device = devices[i];
      break;
    }
  }

  if (physical_device == VK_NULL_HANDLE) {
    fprintf(stderr, "failed to find a suitable GPU!\n");
    exit(1);
  }
}

bool is_device_suitable(VkPhysicalDevice *device) {
  VkPhysicalDeviceProperties device_properties;
  VkPhysicalDeviceFeatures device_features;
  vkGetPhysicalDeviceProperties(*device, &device_properties);
  vkGetPhysicalDeviceFeatures(*device, &device_features);

  QueueFamilyIndices indices = find_queue_families(device);

  return device_properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
         device_features.geometryShader &&
         is_queue_family_indices_complete(&indices);
}

QueueFamilyIndices find_queue_families(VkPhysicalDevice *device) {
  QueueFamilyIndices indices = {-1};

  uint32_t queue_family_count;
  vkGetPhysicalDeviceQueueFamilyProperties(*device, &queue_family_count, NULL);
  VkQueueFamilyProperties queue_families[queue_family_count];
  vkGetPhysicalDeviceQueueFamilyProperties(*device, &queue_family_count,
                                           queue_families);

  for (size_t i = 0; i < queue_family_count; i++) {
    if (queue_families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
      indices.graphics_family = i;
    is_queue_family_indices_complete(&indices);
  }

  return indices;
}

bool is_queue_family_indices_complete(QueueFamilyIndices *indices) {
  return indices->graphics_family != -1;
}
