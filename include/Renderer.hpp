/**
 * CSC3223 Graphics for Games
 * Coursework 2
 * Name: George Burton
 * Student Number: 110204567
 * File: Renderer.hpp
 */

#pragma once

#ifndef PNEUMATIC_RENDERER_HPP
#define PNEUMATIC_RENDERER_HPP

#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace Pneumatic {
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
    auto _SetupContext(void) -> void;

    static bool sGlewInitialized;
    int fWidth, fHeight;

    Window *fWindow;

    glm::mat4 fViewMatrix;
    glm::mat4 fProjectionMatrix;
    glm::mat4 fTextureMatrix;
    glm::mat4 fModelMatrix;
    glm::vec3 fCameraPos;

    std::vector<RenderObject*> fObjects;

    inline static auto StaticRendererResizeCallback(GLFWwindow* win,
                                                    int w,
                                                    int h)                  -> void
    {
      Renderer *r = static_cast<Renderer*>(
        glfwGetWindowUserPointer(win));
      r->ViewportDidResize(w, h);
    }

    inline static auto StaticRendererRefreshCallback(GLFWwindow *win)       -> void
    {
      Renderer *r = static_cast<Renderer*>(
        glfwGetWindowUserPointer(win));
      r->RenderScene();
    }

    inline static auto StaticRendererKeypressCallback(GLFWwindow *win,
                                                      int key,
                                                      int scanCode,
                                                      int action,
                                                      int mods)             -> void
    {
      Renderer *r = static_cast<Renderer*>(
        glfwGetWindowUserPointer(win));
      r->KeyWasPressed(key, scanCode, action, mods);
    }

    inline static auto StaticRendererQuitRequestedCallback(GLFWwindow *win) -> void
    {
      Renderer *r = static_cast<Renderer*>(
        glfwGetWindowUserPointer(win));
      r->QuitWasRequested();
    }
  };
}
#endif // PNEUMATIC_RENDERER_HPP
