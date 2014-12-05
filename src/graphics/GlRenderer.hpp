/**
 * This file is part of the pneumatic game engine
 *
 * Copyright (c) 2014 George Burton
 *
 * THIS SOFTWARE IS PROVIDED 'AS-IS', WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTY. IN NO EVENT WILL THE AUTHORS BE HELD LIABLE FOR ANY DAMAGES
 * ARISING FROM THE USE OF THIS SOFTWARE.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *    1. The origin of this software must not be misrepresented; you must not
 *       claim that you wrote the original software. If you use this software
 *       in a product, an acknowledgment in the product documentation would be
 *       appreciated but is not required.
 *
 *    2. Altered source versions must be plainly marked as such, and must not be
 *       misrepresented as being the original software.
 *
 *    3. This notice may not be removed or altered from any source
 *       distribution.
 *
 **/

#pragma once

#ifndef PNEUMATIC_GL_GlRenderer_HPP
#define PNEUMATIC_GL_GlRenderer_HPP

#include <memory>
#include <vector>

#define GLEW_STATIC
#include <GL/glew.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wundef"
#pragma clang diagnostic ignored "-Wdocumentation"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_CXX11
#include <glm/fwd.hpp>

#define GLFW_INCLUDE_GL3
#define GLFW_NO_GLU
#include <GLFW/glfw3.h>

#pragma clang diagnostic pop

#include "pneu/graphics/Renderer.hpp"

namespace pneu {

namespace core {

template<typename T>
class FuncResult;
using MethodResult = FuncResult<void>;

} // namespace core

namespace graphics {

class RenderObject;

class GlRenderer final : public pneu::graphics::Renderer {
public:
  GlRenderer();

  GlRenderer(const GlRenderer&)                                                             = delete;
  GlRenderer(GlRenderer&&)                                                                  = delete;
  auto operator=(const GlRenderer&)                                          -> GlRenderer& = delete;

  ~GlRenderer();

  auto init(GLFWwindow*)                                                     -> pneu::core::MethodResult;

  virtual auto addRenderObject(std::weak_ptr<pneu::graphics::RenderObject>)  -> void;
  virtual auto setBackgroundColor(const pneu::graphics::Color<float>& color) -> void;

  virtual auto updateScene(double delta_time)                                -> void;
  virtual auto renderScene()                                                 -> void;
  virtual auto viewportDidResize(int w, int h)                               -> void;
  virtual auto quitWasRequested()                                            -> bool;

private:
  static bool sGlewInitialized;
  struct GlRendererImpl;
  std::unique_ptr<GlRendererImpl> fRenImpl;
};

} // namespace graphics

} // namespace pneu

#endif // PNEUMATIC_GL_GlRenderer_HPP
