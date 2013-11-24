/**
 * CSC3223 Graphics for Games
 * Coursework 2
 * Name: George Burton
 * Student Number: 110204567
 * File: GLContext.hpp
 */

#pragma once

#ifndef GL_CONTEXT_HPP
#define GL_CONTEXT_HPP

#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ResourceLoader.hpp"

class GLContext final {
public:
  GLContext(GLFWwindow*, int, int);
  void RenderContext();
  void ViewportDidResize(int w, int h);
  void KeyWasPressed(int key,
                     int scanCode,
                     int action,
                     int mods);
private:
  void SetupContext();

  GLFWwindow *_pWindow;
  int _width, _height;

  std::vector<GLuint> *programs;

  GLuint _VertexArrayID;
  GLuint _VertexBuffer;
};

#endif // GL_CONTEXT_HPP
