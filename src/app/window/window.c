#include "window.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

Window windowCreate() {
  if (glfwInit() == GLFW_FALSE) {
    fprintf(stderr, "Failed to initialize GLFW\n");
    exit(1);
  }

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

  GLFWwindow *handle = glfwCreateWindow(800, 600, "Vulkan", NULL, NULL);
  if (handle == NULL) {
    fprintf(stderr, "Failed to create GLFW window\n");
    exit(1);
  }

  Window window = {handle, 800, 600, "Vulkan"};

  return window;
}

void windowDestroy(Window *window) { glfwDestroyWindow(window->handle); }

bool windowShouldClose(Window *window) {
  return glfwWindowShouldClose(window->handle);
}
