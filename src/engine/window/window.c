#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

#include "window.h"

void windowCreate(Engine *engine) {
  if (glfwInit() == GLFW_FALSE) {
    fprintf(stderr, "Failed to initialize GLFW\n");
    exit(1);
  }

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

  GLFWwindow *window = glfwCreateWindow(800, 600, "Vulkan", NULL, NULL);
  if (window == NULL) {
    fprintf(stderr, "Failed to create GLFW window\n");
    exit(1);
  }

  engine->window = window;
}

void windowDestroy(GLFWwindow *window) { glfwDestroyWindow(window); }
