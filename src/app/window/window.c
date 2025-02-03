#include "window.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

void windowCreate(App *app) {
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

  app->window = window;
}

void windowDestroy(App *app) { glfwDestroyWindow(app->window); }

bool windowShouldClose(App *app) { return glfwWindowShouldClose(app->window); }
