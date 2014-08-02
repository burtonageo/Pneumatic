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

#ifndef PNEUMATIC_RENDEROBJECT_HPP
#define PNEUMATIC_RENDEROBJECT_HPP

#include <iostream>
#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#define GLEW_STATIC
#include <GL/glew.h>

#define GLFW_INCLUDE_GL3
#define GLFW_NO_GLU
#include <GLFW/glfw3.h>

namespace Pneumatic {

namespace Graphics {

class Light;
class Mesh;
class Shader;
class ShaderUpdateMixin;
class Texture;

class RenderObject {
public:
  explicit RenderObject(std::shared_ptr<Mesh> mesh = nullptr);
  RenderObject(const RenderObject&) = delete;
  RenderObject(RenderObject&&)      = delete;
  ~RenderObject(void);

  auto update(double delta_time)                 -> void;
  virtual auto draw(void)                        -> void;

  auto changeShaders(void)                       -> void;
  auto setShaderLight(const Light& light)        -> void;

  auto addTexture(const std::string& tex_file)   -> void;

  auto getMesh(void) const                       -> std::shared_ptr<Mesh>;
  auto setMesh(std::shared_ptr<Mesh> mesh)       -> void;

  auto getShader(void) const                     -> std::shared_ptr<Shader>;
  auto addShader(std::shared_ptr<Shader> shader) -> void;

  auto getModelMatrix(void) const                -> glm::mat4;
  auto setModelMatrix(const glm::mat4& matrix)   -> void;

protected:
  std::shared_ptr<Mesh> fMesh;
  glm::mat4 fModelMatrix;

  std::vector<std::shared_ptr<Shader>> fShaders;
  std::vector<std::shared_ptr<Texture>> fTextures;
  std::vector<std::shared_ptr<ShaderUpdateMixin>> fShaderUpdaters;

private:
  unsigned int fCurrentShaderIndex;
};

} // namespace Graphics

} // namespace Pneumatic

#endif // PNEUMATIC_RENDEROBJECT_HPP
