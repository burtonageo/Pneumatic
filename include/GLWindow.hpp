/**
 * CSC3223 Graphics for Games
 * Coursework 2
 * Name: George Burton
 * Student Number: 110204567
 * File: GLWindow.hpp
 */

#pragma once

#ifndef GL_WINDOW_HPP
#define GL_WINDOW_HPP

#include <exception>
#include <GLFW/glfw3.h>

class GLWindow final {
public:
  GLWindow();
  ~GLWindow();
  void RunMainLoop();
private:
  GLFWwindow *window = nullptr;
  int width = 600, height = 800;

  static void ErrorCallback(int, const char*);
  static void KeyCallback(GLFWwindow*,
                          int key,
                          int scanCode,
                          int action,
                          int mods);
};

#endif // GL_WINDOW_HPP
