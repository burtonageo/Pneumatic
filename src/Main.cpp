/**
 * CSC3223 Graphics for Games
 * Coursework 2
 * Name: George Burton
 * Student Number: 110204567
 * File: Main.cpp
 */

#include <exception>
#include <iostream>

#include <gl/glew.h>
#define GLFW_INCLUDE_GL3
#define GLFW_NO_GLU
#include <GLFW/glfw3.h>

#include "Renderer.hpp"
#include "Window.hpp"

int main(int argc, char **argv) {
  try {
    Window *win = new Window();
    Renderer *r = new Renderer(win);
    while (win->IsRunning()) {
      win->UpdateWindow();
      glfwPollEvents();
    }
    return EXIT_SUCCESS;
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
    return EXIT_FAILURE;
  }
}
