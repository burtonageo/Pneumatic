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

#include <list>
#include <memory>

#define GLFW_INCLUDE_GL3
#define GLFW_NO_GLU
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

namespace Pneumatic {
class Window;
class RenderObject;

class Renderer {
public:
  Renderer(Window*);

  auto UpdateScene(double ms)                                      -> void;
  auto RenderScene(void)                                           -> void;

  auto DrawLine(glm::vec3 from,
                glm::vec3 to,
                glm::vec4 col = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)) -> void;

  auto ViewportDidResize(int w, int h)                             -> void;
  auto KeyWasPressed(int key,
                     int scanCode,
                     int action,
                     int mods)                                     -> void;
  auto QuitWasRequested(void)                                      -> bool;

  inline auto GetFov(void) const                                   -> float {return fFov;}
  inline auto SetFov(float fov)                                    -> void  {fFov = fov;}

  inline auto GetNearClip(void) const                              -> float {return fNearClip;}
  inline auto SetNearClip(float nc)                                -> void  {fNearClip = nc;}

  inline auto GetFarClip(void) const                               -> float {return fFarClip;}
  inline auto SetFarClip(float fc)                                 -> void  {fFarClip = fc;}

  inline auto GetBackgroundColor(void) const                       -> glm::vec4 {return fBackgroundColor;}
  inline auto SetBackgroundColor(glm::vec4 color)                  -> void      {fBackgroundColor = color;}
protected:
  auto _UpdateShaderMatrices(GLuint)                               -> void;
private:
  auto _SetupContext(void)                                         -> void;

  static bool sGlewInitialized;

  int     fWidth;
  int     fHeight;
  Window *fWindow;

  float   fFov;
  float   fNearClip;
  float   fFarClip;

  glm::mat4 fViewMatrix;
  glm::mat4 fProjectionMatrix;
  glm::mat4 fTextureMatrix;
  glm::mat4 fModelMatrix;

  glm::vec4 fBackgroundColor;
  glm::vec3 fCameraPos;

  std::list<std::shared_ptr<Pneumatic::RenderObject>> fObjects;

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
} // namespace Pneumatic
#endif // PNEUMATIC_RENDERER_HPP
