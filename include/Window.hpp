/**
 * CSC3223 Graphics for Games
 * Coursework 2
 * Name: George Burton
 * Student Number: 110204567
 * File: Window.hpp
 */

#pragma once

#ifndef PNEUMATIC_WINDOW_HPP
#define PNEUMATIC_WINDOW_HPP

#include <exception>
#include <string>

#define GLFW_INCLUDE_GL3
#define GLFW_NO_GLU
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Config.hpp"

namespace Pneumatic {
class Renderer;

class Window final {
public:
  Window(std::string const &title = Config::kProgramName,
         int width = 800,
         int height = 600);

  ~Window(void);
  auto UpdateWindow(void)                  -> void;
  auto PollEvents(void)                    -> void;
  auto IsRunning(void) const               -> bool;
private:
  auto _InitGLFW(std::string const &)      -> void;

  friend class Renderer;

  int         fWidth;
  int         fHeight;
  GLFWwindow *fGlWindow;
  Renderer   *fRenderer;
};
} // namespace Pneumatic

#endif // PNEUMATIC_WINDOW_HPP
