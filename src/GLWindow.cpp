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

#include "GLWindow.hpp"

GLWindow::GLWindow()
{
  glfwSetErrorCallback(ErrorCallback);

  try {
    InitGLFW();
    InitGLEW();
  } catch (std::runtime_error &e) {
    throw e;
  }
}

GLWindow::~GLWindow()
{
  if (window != nullptr) {
    glfwDestroyWindow(window);
  }
  glfwTerminate();
}

void
GLWindow::RunMainLoop()
{
  while(!glfwWindowShouldClose(window)) {
    float ratio = 0.0f;

    glfwGetFramebufferSize(window, &width, &height);
    ratio = width/static_cast<float>(height);

    if (GLEW_ARB_vertex_program)
    {
      std::cout << "Hi" << std::endl;
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}

void
GLWindow::InitGLEW()
{
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

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, "glCube", NULL, NULL);
    if (!window) {
      delete this;
      throw std::runtime_error(badInitMsg);
    }

    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, KeyCallback);
  } catch (std::runtime_error &e) {
    throw e;
  }
}

void
GLWindow::ErrorCallback(int err, const char *desc)
{
  std::cout << desc << ", " << std::endl;
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
        break;
    }
  } 
}
