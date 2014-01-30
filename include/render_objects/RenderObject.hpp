/**
 * CSC3223 Graphics for Games
 * Coursework 2
 * Name: George Burton
 * Student Number: 110204567
 * File: RenderObject.hpp
 */

#pragma once

#ifndef PNEUMATIC_RENDEROBJECT_HPP
#define PNEUMATIC_RENDEROBJECT_HPP

#include <iostream>
#include <vector>

#include <GLFW/glfw3.h>
#include <glm/fwd.hpp>

namespace Pneumatic {

namespace ___hidden___ {

class ShaderUpdateMixin;

} // namespace ___hidden___

class Light;
class Mesh;
class Shader;
class Texture;

class RenderObject {
public:
  RenderObject(Pneumatic::Mesh *m = nullptr);
  ~RenderObject(void);

  auto UseShader(void)                        -> void;
  auto AddTexture(std::string const &)        -> void;

  auto Update(double delta)                   -> void;
  auto SetShaderLight(Pneumatic::Light*)      -> void;
  auto Draw(void)                             -> void;

  inline auto GetMesh(void) const             -> Mesh* {return fMesh;}
  inline auto SetMesh(Pneumatic::Mesh *m)     -> void  {fMesh = m;}

  inline auto GetShader(void) const           -> Shader* {return fShaders->at(fCurrentShaderIndex);}
  inline auto AddShader(Pneumatic::Shader *s) -> void    {fShaders->push_back(s);}

  inline auto GetModelMatrix(void) const      -> glm::mat4 {return fModelMatrix;}
  inline auto SetModelMatrix(glm::mat4 mat)   -> void      {fModelMatrix = mat;}

  inline auto ChangeShaders(void)             -> void
  {
    fCurrentShaderIndex = fCurrentShaderIndex < (fShaders->size() - 1)
      ? fCurrentShaderIndex + 1
      : 0;
  }

protected:
  Mesh     *fMesh;
  glm::mat4 fModelMatrix;

  std::vector<Shader*>  *fShaders;
  std::vector<Texture*> *fTextures;
  std::vector<___hidden___::ShaderUpdateMixin*> *fShaderUpdaters;
private:
  unsigned long fCurrentShaderIndex;
};

// Used to update shaders
namespace ___hidden___ {
class ShaderUpdateMixin {
public:
  ShaderUpdateMixin(Shader *s) : shader(s) {}
  virtual auto Update(double delta) -> void = 0;
  Shader *shader;
};

} // namespace ___hidden___

} // namespace Pneumatic

#endif // PNEUMATIC_RENDEROBJECT_HPP
