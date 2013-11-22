#include <exception>
#include <iostream>

#include <GLFW/glfw3.h>

#include "GLWindow.hpp"

GLWindow::GLWindow()
{
  const std::string badConstructMessage = 
    "GLFW cannot be initialised";

  glfwSetErrorCallback(ErrorCallback);

  try {
    bool succ = glfwInit();
    if (!succ) {
      throw std::runtime_error(badConstructMessage);
    }
  
    window = glfwCreateWindow(width, height, "glCube", NULL, NULL);
    if (!window) {
      delete this;
      throw std::runtime_error(badConstructMessage);
    }
  } catch (std::runtime_error &e) {
    throw e;
  }

  glfwSetKeyCallback(window, KeyCallback);
}

GLWindow::~GLWindow()
{
  if (window != nullptr) {
    glfwDestroyWindow(window);
  }
  glfwTerminate();
}

void
GLWindow::RunMainLoop()
{
  while(!glfwWindowShouldClose(window)) {
    // do nothing
  }
}

void
GLWindow::ErrorCallback(int err, const char *desc)
{
  std::cout << desc << ", " << std::endl;
}

void
GLWindow::KeyCallback(GLFWwindow*,
                      int key,
                      int scanCode,
                      int action,
                      int mods)
{
  
}
