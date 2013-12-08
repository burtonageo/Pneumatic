/**
 * CSC3223 Graphics for Games
 * Coursework 2
 * Name: George Burton
 * Student Number: 110204567
 * File: Window.hpp
 */

#pragma once

#ifndef GL_WINDOW_HPP
#define GL_WINDOW_HPP

#include <exception>
#include <string>

#include <GLFW/glfw3.h>

#include "Config.hpp"

class Renderer;
class Window final {
public:
  Window(std::string title = Config::GetProgramName(),
         int width = 800,
         int height = 600);

  ~Window(void);
  auto UpdateWindow(void) -> void;
  auto IsRunning(void) -> bool;
private:
  bool running;
  GLFWwindow *_pGLWindow;
  int _width, _height;
  friend class Renderer;

  auto InitGLFW(std::string title) -> void;
};

#endif // GL_WINDOW_HPP
