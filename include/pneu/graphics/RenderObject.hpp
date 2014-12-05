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

#ifndef PNEUMATIC_RENDEROBJECT_HPP
#define PNEUMATIC_RENDEROBJECT_HPP

#include "pneu/core/Forward.hpp"

#include <iostream>
#include <vector>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated"
#pragma clang diagnostic ignored "-Wdocumentation"
#pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#pragma clang diagnostic ignored "-Wold-style-cast"
#pragma clang diagnostic ignored "-Wshadow"
#pragma clang diagnostic ignored "-Wundef"
#pragma clang diagnostic ignored "-Wundefined-reinterpret-cast"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#pragma clang diagnostic pop

namespace pneu {

namespace graphics {

class Light;
class Shader;
class ShaderUpdateMixin;
class Texture;

/**
 * An abstract object which can be drawn in a renderer. Is made
 * up of a mesh and a collection of shaders and textures.
 *
 * @note textures and shaders can be shared among multiple RenderObjects
 */
class RenderObject {
public:
  /**
   * constructor
   */
  RenderObject();

  /**
   * destructor
   */
  virtual ~RenderObject();

  virtual auto update(double delta_time)         -> void = 0;
  virtual auto draw()                            -> void = 0;

  auto changeShaders()                           -> void;
  auto setShaderLight(const Light& light)        -> void;

  auto getCurrentTexture() const                 -> std::shared_ptr<Texture>;
  auto addTexture(const std::string& tex_file)   -> pneu::core::MethodResult;

  auto getCurrentShader() const                  -> std::shared_ptr<Shader>;
  auto addShader(std::shared_ptr<Shader> shader) -> pneu::core::MethodResult;

  auto getModelMatrix() const                    -> glm::mat4;
  auto setModelMatrix(const glm::mat4& matrix)   -> void;

protected:
  auto bindCurrentShader()                       -> void;
  auto bindCurrentTexture()                      -> void;

  auto unBindCurrentShader()                     -> void;
  auto unBindCurrentTexture()                    -> void;

private:
  unsigned int fCurrentShaderIndex;
  glm::mat4 fModelMatrix;

  std::vector<std::shared_ptr<Shader>> fShaders;
  std::vector<std::shared_ptr<Texture>> fTextures;
  std::vector<std::shared_ptr<ShaderUpdateMixin>> fShaderUpdaters;
};

RenderObject::~RenderObject() = default;

} // namespace graphics

} // namespace pneu

#endif // PNEUMATIC_RENDEROBJECT_HPP
