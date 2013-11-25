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

#include "GLContext.hpp"
#include "Window.hpp"

Window *Window::_pWindowInstance = nullptr;

Window*
Window::GetInstance()
{
  if (!_pWindowInstance) {
    _pWindowInstance = new Window();
  }
  return _pWindowInstance;
}

void
Window::DestroyInstance()
{
  if (_pWindowInstance) {
    delete _pWindowInstance;
  }
}

Window::Window()
{
  glfwSetErrorCallback(ErrorCallback);

  try {
    InitGLFW();
    _pContext = new GLContext(_pGLWindow, _StartWidth, _StartHeight);
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

void
Window::RunMainLoop()
{
  while(!glfwWindowShouldClose(_pGLWindow)) {
    GetInstance()->GetContext()->RenderContext();
    glfwPollEvents();
  }
}

void
Window::InitGLFW()
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

    _pGLWindow = glfwCreateWindow(_StartWidth,
                                  _StartHeight,
                                  GetProgramName(), 
                                  NULL, 
                                  NULL);
    if (!_pGLWindow) {
      delete this;
      throw std::runtime_error(badInitMsg);
    }

    glfwSetKeyCallback(_pGLWindow, KeyCallback);
    glfwSetWindowCloseCallback(_pGLWindow, CloseCallback);
    glfwSetFramebufferSizeCallback(_pGLWindow, ViewportResizeCallback);
    glfwSetWindowRefreshCallback(_pGLWindow, DrawCallback);
  } catch (std::runtime_error &e) {
    throw e;
  }
}

void
Window::DrawCallback(GLFWwindow *window)
{
  GetInstance()->GetContext()->RenderContext();
}

void
Window::ViewportResizeCallback(GLFWwindow *Window,
                         int width,
                         int height)
{
  Window::GetInstance()->GetContext()->ViewportDidResize(width, height);
}

void
Window::CloseCallback(GLFWwindow *Window)
{
  if (Window::GetInstance()->WindowShouldClose()) {
    glfwSetWindowShouldClose(Window, GL_TRUE);
  }
}

void
Window::ErrorCallback(int err, const char *desc)
{
  std::cout << desc << std::endl;
}

void
Window::KeyCallback(GLFWwindow* Window,
                    int key,
                    int scanCode,
                    int action,
                    int mods)
{
  if (action == GLFW_PRESS) {
    switch (key) {
      case GLFW_KEY_ESCAPE:
        glfwSetWindowShouldClose(Window, GL_TRUE);
        break;
      default:
        GetInstance()->GetContext()->KeyWasPressed(key, scanCode, action, mods);
        break;
    }
  } 
}
