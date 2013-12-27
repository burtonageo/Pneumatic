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
#include <glm/glm.hpp>

class Window;
class RenderObject;
class Renderer {
public:
  Renderer(Window* win);

  auto UpdateScene(double ms) -> void;
  auto RenderScene(void) -> void;
  auto ViewportDidResize(int w, int h) -> void;
  auto KeyWasPressed(int key,
                     int scanCode,
                     int action,
                     int mods) -> void;
  auto QuitWasRequested(void) -> bool;
protected:
  auto UpdateShaderMatrices(GLuint) -> void;
private:
  auto SetupContext(void) -> void;

  int _width, _height;
  Window *_window;
  static bool _glewInitialized;
  glm::mat4 _viewMatrix;
  glm::mat4 _projectionMatrix;
  glm::mat4 _textureMatrix;
  glm::mat4 _modelMatrix;
  glm::vec3 _cameraPos;
  std::vector<RenderObject*> _objects;

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

  inline static auto StaticRendererQuitRequestedCallback(GLFWwindow *win) -> void {
                                                          Renderer *r = static_cast<Renderer*>(
                                                            glfwGetWindowUserPointer(win));
                                                          r->QuitWasRequested();
                                                        }
};

#endif // GL_CONTEXT_HPP
