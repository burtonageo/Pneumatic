/**
 * CSC3223 Graphics for Games
 * Coursework 2
 * Name: George Burton
 * Student Number: 110204567
 * File: Renderer.hpp
 */

#pragma once

#ifndef GL_CONTEXT_HPP
#define GL_CONTEXT_HPP

#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window;
class Renderer final {
public:
  Renderer(Window*, int, int);

  auto UpdateScene(double ms) -> void;
  auto RenderScene() -> void;
  auto ViewportDidResize(int w, int h) -> void;
  auto KeyWasPressed(int key,
                     int scanCode,
                     int action,
                     int mods) -> void;
  auto QuitWasRequested(void) -> bool;
private:
  void SetupContext(void);

  int _width, _height;
  GLuint _VertexArrayID;
  GLuint _VertexBuffer;

  Window *_pWindow;
  std::vector<GLuint> *programs;

  inline static auto StaticRendererResizeCallback(GLFWwindow* win,
                                                        int w,
                                                        int h) -> void {
                                                          Renderer *r = static_cast<Renderer*>(
                                                            glfwGetWindowUserPointer(win));
                                                          r->ViewportDidResize(w, h);
                                                        }

  inline static auto StaticRendererRefreshCallback(GLFWwindow *win) -> void {
                                                        Renderer *r = static_cast<Renderer*>(
                                                          glfwGetWindowUserPointer(win));
                                                        r->RenderScene();
                                                      }

  inline static auto StaticRendererKeypressCallback(GLFWwindow *win,
                                                         int key,
                                                         int scanCode,
                                                         int action,
                                                         int mods) -> void {
                                                           Renderer *r = static_cast<Renderer*>(
                                                             glfwGetWindowUserPointer(win));
                                                           r->KeyWasPressed(key, scanCode, action, mods);
                                                         }

  inline static auto StaticRendererQuitRequestedCallback(GLFWwindow *win) -> bool {
                                                          Renderer *r = static_cast<Renderer*>(
                                                            glfwGetWindowUserPointer(win));
                                                          return r->QuitWasRequested();
                                                        }
};

#endif // GL_CONTEXT_HPP
