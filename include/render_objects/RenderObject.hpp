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
#include <memory>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

namespace Pneumatic {

class Light;
class Mesh;
class Shader;
class Texture;

class RenderObject {
public:
  RenderObject(std::shared_ptr<Pneumatic::Mesh> m =
                 std::shared_ptr<Pneumatic::Mesh>(nullptr));
  ~RenderObject(void);

  auto UseShader(void)                                    -> void;
  auto AddTexture(std::string const &)                    -> void;

  auto Update(double delta)                               -> void;
  auto SetShaderLight(Pneumatic::Light*)                  -> void;
  auto Draw(void)                                         -> void;

  inline auto GetMesh(void) const                         -> std::shared_ptr<Mesh> {return fMesh;}
  inline auto SetMesh(std::shared_ptr<Pneumatic::Mesh> m) -> void  {fMesh = m;}

  inline auto GetShader(void) const                       -> std::shared_ptr<Shader>
  {
    return fShaders->at(fCurrentShaderIndex);
  }

  inline auto AddShader(std::shared_ptr<Pneumatic::Shader> s) -> void
  {
    fShaders->push_back(s);
  }

  inline auto GetModelMatrix(void) const                  -> glm::mat4 {return fModelMatrix;}
  inline auto SetModelMatrix(glm::mat4 mat)               -> void      {fModelMatrix = mat;}

  inline auto ChangeShaders(void)                         -> void
  {
    fCurrentShaderIndex = fCurrentShaderIndex < (fShaders->size() - 1)
      ? fCurrentShaderIndex + 1
      : 0;
  }

protected:
  std::shared_ptr<Mesh> fMesh;
  glm::mat4 fModelMatrix;

  std::unique_ptr<std::vector<std::shared_ptr<Shader>>>  fShaders;
  std::unique_ptr<std::vector<std::shared_ptr<Texture>>> fTextures;
private:
  unsigned long fCurrentShaderIndex;
};

} // namespace Pneumatic

#endif // PNEUMATIC_RENDEROBJECT_HPP
