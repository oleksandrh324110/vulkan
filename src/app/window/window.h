#pragma once

#include <GLFW/glfw3.h>
#include <stdbool.h>

typedef struct Window {
  GLFWwindow *handle;
  int width;
  int height;
  const char *title;

  void (*onResize)(struct Window *window, int width, int height);
  void (*onKey)(struct Window *window, int key, int scancode, int action,
                int mods);
  void (*onMouseButton)(struct Window *window, int button, int action,
                        int mods);
  void (*onMouseMove)(struct Window *window, double x, double y);
  void (*onMouseScroll)(struct Window *window, double x, double y);
  void (*onUpdate)(struct Window *window, float deltaTime);
  void (*onRender)(struct Window *window);
  void (*onDestroy)(struct Window *window);
} Window;

Window windowCreate();
void windowDestroy(Window *window);
bool windowShouldClose(Window *window);
