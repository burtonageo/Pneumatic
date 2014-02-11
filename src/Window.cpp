/**
 * CSC3223 Graphics for Games
 * Coursework 2
 * Name: George Burton
 * Student Number: 110204567
 * File: Window.cpp
 */

#include "Window.hpp"

#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "Renderer.hpp"

#include "make_unique.hpp"

using namespace std;

Pneumatic::Window::Window(std::string const &title,
                          int width,
                          int height)
  try :
  fWidth(width),
  fHeight(height),
  fGlWindow(),
  fRenderer(nullptr)
{
  _InitGLFW(title);
  fRenderer = make_unique<Renderer>(this);
} catch (runtime_error &e) {
  throw e;
}

auto
Pneumatic::Window::UpdateWindow() -> void
{
  double delta = glfwGetTime();
  fRenderer->UpdateScene(delta);
  fRenderer->RenderScene();
}

auto
Pneumatic::Window::PollEvents() -> void
{
  glfwPollEvents();
}

auto
Pneumatic::Window::IsRunning(void) const  -> bool
{
  return !glfwWindowShouldClose(fGlWindow.get());
}

auto
Pneumatic::Window::_InitGLFW(std::string const &title) -> void
{
  const std::string badInitMsg =
    "GLFW window cannot be created";
  try {
    bool succ = glfwInit();
    if (!succ) {
      throw std::runtime_error(badInitMsg);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    fGlWindow = unique_ptr<GLFWwindow,
                           WindowDeleter>(glfwCreateWindow(fWidth,
                                                           fHeight,
                                                           title.c_str(),
                                                           NULL,
                                                           NULL));

    if (!fGlWindow) {
      throw std::runtime_error(badInitMsg);
    }
  } catch (std::runtime_error &e) {
    throw e;
  }
}
