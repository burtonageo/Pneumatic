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
#include "RenderObject.hpp"
#include "TriObject.hpp"
#include "Window.hpp"

#include "Renderer.hpp"

bool Renderer::_glewInitialized = false;

Renderer::Renderer(Window *window) :
  _pWindow(window),
  _width(0),
  _height(0),
  _objects(std::vector<RenderObject*>())
{
  glfwSetWindowUserPointer(_pWindow->_pGLWindow, this);
  glfwSwapInterval(1);
  glfwMakeContextCurrent(_pWindow->_pGLWindow);

  if (!_glewInitialized) {
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
      throw new std::runtime_error("GLEW not initialized");
    }
    _glewInitialized = true;
  }

  if (glewIsSupported("GL_VERSION_3_3"))
      std::cout << "Ready for OpenGL 3.3\n";
  else {
      std::cout << "OpenGL 3.3 not supported\n";
  }

  glfwSetKeyCallback(_pWindow->_pGLWindow, StaticRendererKeypressCallback);
  glfwSetWindowCloseCallback(_pWindow->_pGLWindow, StaticRendererQuitRequestedCallback);
  glfwSetFramebufferSizeCallback(_pWindow->_pGLWindow, StaticRendererResizeCallback);
  glfwSetWindowRefreshCallback(_pWindow->_pGLWindow, StaticRendererRefreshCallback);

  glEnable(GL_MULTISAMPLE);
  SetupContext();
  _pWindow->_pRenderer = this;
  _width = _pWindow->_width;
  _height = _pWindow->_height;

  RenderObject *tri = new TriObject();
  _objects.push_back(tri);
}

auto
Renderer::Begin(void) -> void
{

}

auto
Renderer::UpdateScene(double ms) -> void
{
 
}

auto
Renderer::RenderScene(void) -> void
{
  float ratio = _width/static_cast<float>(_height);

  glLoadIdentity();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.3f, 0.3f, 0.3f, 0.0f);

  std::for_each(_objects.begin(),
                _objects.end(),
                [](RenderObject *r) {r->Draw();});

  glfwSwapBuffers(_pWindow->_pGLWindow);
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
  glfwSetTime(0.0);
}


