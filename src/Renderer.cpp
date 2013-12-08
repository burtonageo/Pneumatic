/**
 * CSC3223 Graphics for Games
 * Coursework 2
 * Name: George Burton
 * Student Number: 110204567
 * File: Renderer.cpp
 */

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ResourceLoader.hpp"
#include "Window.hpp"

#include "Renderer.hpp"

Renderer::Renderer(Window *window, int width, int height) :
  _width(width),
  _height(height),
  _pWindow(window)
{
  glfwSetWindowUserPointer(_pWindow->_pGLWindow, this);
  glfwMakeContextCurrent(_pWindow->_pGLWindow);
  glfwSwapInterval(1);
  programs = new std::vector<GLuint>();
  GLuint programID = ResourceLoader::LoadAndCompileShaders("tri");
  programs->push_back(programID);

  try {
    glewExperimental = GL_TRUE; 
    GLenum err = glewInit();
    if (err != GLEW_OK) {
      std::cout << "Error: " << glewGetErrorString(err) << std::endl;
      throw std::runtime_error("GLEW not initialsed");
    }
  } catch (std::runtime_error &e) {
    throw e;
  }
  glfwSetKeyCallback(_pWindow->_pGLWindow, StaticRendererKeypressCallback);
  //glfwSetWindowCloseCallback(_pWindow->_pGLWindow, CloseCallback);
  glfwSetFramebufferSizeCallback(_pWindow->_pGLWindow, StaticRendererResizeCallback);
  glfwSetWindowRefreshCallback(_pWindow->_pGLWindow, StaticRendererRefreshCallback);

  glEnable(GL_MULTISAMPLE);
  SetupContext();
}

auto
Renderer::UpdateScene(void) -> void
{
  
}

auto
Renderer::RenderScene(void) -> void
{
  float ratio = _width/static_cast<float>(_height);

  glLoadIdentity();
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

  for (auto it = programs->begin(); it != programs->end(); ++it) {
    glUseProgram(*it);
  }

  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, _VertexBuffer);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glDrawArrays(GL_TRIANGLES, 0, 3);

  glDisableVertexAttribArray(0);
  glFlush();
  glfwSwapBuffers(_pWindow->_pGLWindow);
  glfwSetTime(0.0);
}

auto
Renderer::ViewportDidResize(int width, int height) -> void
{
  glViewport(0, 0, (GLsizei)width, (GLsizei)height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
}

auto
Renderer::KeyWasPressed(int key,
                        int scanCode,
                        int action,
                        int mods) -> void
{
  std::cout << "Pressed!\n";
}

auto
Renderer::QuitWasRequested(void) -> bool
{
  return false;
}

auto
Renderer::SetupContext(void) -> void
{
  glGenVertexArrays(1, &_VertexArrayID);
  glBindVertexArray(_VertexArrayID);

  glGenBuffers(1, &_VertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, _VertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(_VertexBufferData), _VertexBufferData, GL_STATIC_DRAW);

  glfwSetTime(0.0);
}


