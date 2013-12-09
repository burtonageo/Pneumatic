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
#include "Renderer.hpp"
#include "Window.hpp"

Window::Window(std::string title, int width, int height) :
  _running(false),
  _pGLWindow(nullptr),
  _width(width),
  _height(height),
  _pRenderer(nullptr)
  
{
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
}

auto
Window::UpdateWindow() -> void
{
  double delta = glfwGetTime();
  _pRenderer->UpdateScene(delta);
  _pRenderer->RenderScene();
}

auto
Window::InitGLFW(std::string title) -> void
{
  const std::string badInitMsg = 
    "GLFW window cannot be created";
  try {
    bool succ = glfwInit();
    if (!succ) {
      throw std::runtime_error(badInitMsg);
    }
    _pGLWindow = glfwCreateWindow(_width,
                                  _height,
                                  title.c_str(), 
                                  NULL, 
                                  NULL);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (!_pGLWindow) {
      //delete this;
      throw std::runtime_error(badInitMsg);
    }
  } catch (std::runtime_error &e) {
    throw e;
  }
}

auto
Window::IsRunning(void) -> bool
{
  return !glfwWindowShouldClose(_pGLWindow);
}
