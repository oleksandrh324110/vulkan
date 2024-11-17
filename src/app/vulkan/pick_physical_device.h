#pragma once

#include <stdbool.h>
#include <vulkan/vulkan.h>

typedef struct {
  uint32_t graphics_family;
} QueueFamilyIndices;

void pick_physical_device();
bool is_device_suitable(VkPhysicalDevice *device);
QueueFamilyIndices find_queue_families(VkPhysicalDevice *device);
bool is_queue_family_indices_complete(QueueFamilyIndices *indices);
