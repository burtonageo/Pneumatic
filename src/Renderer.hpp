/**
 * This file is part of the Pneumatic game engine
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

#ifndef PNEUMATIC_GL_RENDERER_HPP
#define PNEUMATIC_GL_RENDERER_HPP

#include <memory>
#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/fwd.hpp>

#include "GlInclude.hpp"

namespace Pneumatic {

namespace Graphics {

class RenderObject;

class Renderer final {
public:
  explicit Renderer(void);

  Renderer(const Renderer&)                                         = delete;
  Renderer(Renderer&&)                                              = delete;
  auto operator=(const Renderer&)                      -> Renderer& = delete;

  ~Renderer(void);

  auto init(GLFWwindow*)                               -> bool;

  auto addRenderObject(std::weak_ptr<RenderObject>)    -> void;

  auto updateScene(double delta_time)                  -> void;
  auto renderScene(void)                               -> void;
  auto viewportDidResize(int w, int h)                 -> void;
  auto keyWasPressed(int key,
                     int scan_code,
                     int action,
                     int mods)                         -> void;
  auto quitWasRequested(void)                          -> bool;

private:
  auto _updateShaderMatrices(GLuint, const glm::mat4&,
                                     const glm::mat4&,
                                     const glm::mat4&) -> void;

  static bool sGlewInitialized;
  struct RendererImpl;
  std::unique_ptr<RendererImpl> fRenImpl;
};

} // namespace Graphics

} // namespace Pneumatic

#endif // PNEUMATIC_GL_RENDERER_HPP
