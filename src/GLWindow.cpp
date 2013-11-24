/**
 * CSC3223 Graphics for Games
 * Coursework 2
 * Name: George Burton
 * Student Number: 110204567
 * File: GLWindow.cpp
 */

#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "GLContext.hpp"
#include "GLWindow.hpp"

GLWindow *GLWindow::_pWindowInstance = nullptr;

GLWindow*
GLWindow::GetInstance()
{
  if (!_pWindowInstance) {
    _pWindowInstance = new GLWindow();
  }
  return _pWindowInstance;
}

void
GLWindow::DestroyInstance()
{
  if (_pWindowInstance) {
    delete _pWindowInstance;
  }
}

GLWindow::GLWindow()
{
  glfwSetErrorCallback(ErrorCallback);

  try {
    InitGLFW();
    _pContext = new GLContext(_pGLFWWindow, _StartWidth, _StartHeight);
  } catch (std::runtime_error &e) {
    throw e;
  }
}

GLWindow::~GLWindow()
{
  if (_pGLFWWindow != NULL) {
    glfwDestroyWindow(_pGLFWWindow);
  }
  glfwTerminate();
}

void
GLWindow::RunMainLoop()
{
  while(!glfwWindowShouldClose(_pGLFWWindow)) {
    glfwPollEvents();
  }
}

void
GLWindow::InitGLFW()
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

    _pGLFWWindow = glfwCreateWindow(_StartWidth,
                                    _StartHeight,
                                    GetProgramName(), 
                                    NULL, 
                                    NULL);
    if (!_pGLFWWindow) {
      delete this;
      throw std::runtime_error(badInitMsg);
    }

    glfwSetKeyCallback(_pGLFWWindow, KeyCallback);
    glfwSetWindowCloseCallback(_pGLFWWindow, CloseCallback);
    glfwSetFramebufferSizeCallback(_pGLFWWindow, ResizeCallback);
    glfwSetWindowRefreshCallback(_pGLFWWindow, DrawCallback);
  } catch (std::runtime_error &e) {
    throw e;
  }
}

void
GLWindow::DrawCallback(GLFWwindow*)
{
  GetInstance()->GetContext()->RenderContext();
}

void
GLWindow::ResizeCallback(GLFWwindow *window,
                         int width,
                         int height)
{
  glfwSetWindowSize(window, width, height);
  GLWindow::GetInstance()->GetContext()->ViewportDidResize(width, height);
}

void
GLWindow::CloseCallback(GLFWwindow *window)
{
  if (GLWindow::GetInstance()->WindowShouldClose()) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
}

void
GLWindow::ErrorCallback(int err, const char *desc)
{
  std::cout << desc << std::endl;
}

void
GLWindow::KeyCallback(GLFWwindow* window,
                      int key,
                      int scanCode,
                      int action,
                      int mods)
{
  if (action == GLFW_PRESS) {
    switch (key) {
      case GLFW_KEY_ESCAPE:
        glfwSetWindowShouldClose(window, GL_TRUE);
        break;
      default:
        GetInstance()->GetContext()->KeyWasPressed(key, scanCode, action, mods);
        break;
    }
  } 
}
