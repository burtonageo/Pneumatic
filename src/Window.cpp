/**
 * CSC3223 Graphics for Games
 * Coursework 2
 * Name: George Burton
 * Student Number: 110204567
 * File: Window.cpp
 */

#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Config.hpp"
#include "Window.hpp"

Window::Window(std::string title, int width, int height)
{
  //glfwSetErrorCallback(ErrorCallback);

  try {
    _width = width;
    _height = height;
    InitGLFW(title);
  } catch (std::runtime_error &e) {
    throw e;
  }
}

Window::~Window()
{
  if (_pGLWindow != NULL) {
    glfwDestroyWindow(_pGLWindow);
  }
  glfwTerminate();
}

auto
Window::UpdateWindow() -> void
{

}

auto
Window::InitGLFW(std::string title) -> void
{
  const std::string badInitMsg = 
    "GLFW cannot be initialised";
  try {
    bool succ = glfwInit();
    if (!succ) {
      throw std::runtime_error(badInitMsg);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _pGLWindow = glfwCreateWindow(_width,
                                  _height,
                                  title.c_str(), 
                                  NULL, 
                                  NULL);
    if (!_pGLWindow) {
      delete this;
      throw std::runtime_error(badInitMsg);
    }
  } catch (std::runtime_error &e) {
    throw e;
  }
}

auto
Window::IsRunning() -> bool
{
  return !glfwWindowShouldClose(_pGLWindow);
}
