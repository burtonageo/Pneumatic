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

#include <GLFW/glfw3.h>
#include <GL/glew.h>

class GLContext final {
public:
  GLContext(GLFWwindow*);
  void RenderContext();
private:
  GLuint VertexArrayID;
  GLfloat VertexBufferData*;
}

#endif // GL_CONTEXT_HPP
 