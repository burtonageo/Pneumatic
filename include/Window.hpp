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
#include <memory>
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

  auto UpdateWindow(void)                  -> void;
  auto PollEvents(void)                    -> void;
  auto IsRunning(void) const               -> bool;
private:
  auto _InitGLFW(std::string const &)      -> void;

  friend class Renderer;

  int fWidth;
  int fHeight;

  struct WindowDeleter {
    void operator()(GLFWwindow *window) {
      glfwDestroyWindow(window);
    }
  };
  std::unique_ptr<GLFWwindow, WindowDeleter> fGlWindow;
  std::unique_ptr<Renderer> fRenderer;
};
} // namespace Pneumatic

#endif // PNEUMATIC_WINDOW_HPP
