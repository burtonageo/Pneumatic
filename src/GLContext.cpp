/**
 * CSC3223 Graphics for Games
 * Coursework 2
 * Name: George Burton
 * Student Number: 110204567
 * File: GLContext.cpp
 */

#include <iostream>

#include <GL/glew.h>
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#undef GLFW_INCLUDE_GLU

#include "ResourceLoader.hpp"

#include "GLContext.hpp"

GLContext::GLContext(GLFWwindow *window, int width, int height) :
  _width(width),
  _height(height)
{
  _pWindow = window;
  glfwMakeContextCurrent(_pWindow);
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

  glEnable(GL_MULTISAMPLE);
  SetupContext();
}

static const GLfloat _VertexBufferData[] = {
   -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f,  1.0f, 0.0f,
};

void
GLContext::RenderContext()
{
  float ratio = _width/static_cast<float>(_height);

  double delta = glfwGetTime();

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
  glfwSwapBuffers(_pWindow);
  glfwSetTime(0.0);
}

void
GLContext::ViewportDidResize(int width, int height)
{
  glViewport(0, 0, (GLsizei)width, (GLsizei)height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
}

void
GLContext::KeyWasPressed(int key,
                         int scanCode,
                         int action,
                         int mods)
{
  std::cout << "Pressed!\n";
}

void
GLContext::SetupContext()
{
  glGenVertexArrays(1, &_VertexArrayID);
  glBindVertexArray(_VertexArrayID);

  glGenBuffers(1, &_VertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, _VertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(_VertexBufferData), _VertexBufferData, GL_STATIC_DRAW);
}

