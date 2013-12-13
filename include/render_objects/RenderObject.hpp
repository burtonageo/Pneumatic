/**
 * CSC3223 Graphics for Games
 * Coursework 2
 * Name: George Burton
 * Student Number: 110204567
 * File: RenderObject.hpp
 */

#pragma once

#ifndef RENDEROBJECT_HPP
#define RENDEROBJECT_HPP

#include <iostream>
#include <vector>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace ___hidden___{
  class ShaderUpdateMixin;
}

class Mesh;
class Texture;
class Shader;
class RenderObject {
public:
protected:
  int currentShaderIndex;
public:
  RenderObject(Mesh *m = nullptr);
  ~RenderObject(void);
  auto UseShader(void) -> void;
  auto AddTexture(std::string texFile) -> void;
  inline auto GetMesh(void) -> Mesh* const {return mesh;}
  inline auto SetMesh(Mesh *m) -> void {mesh = m;}
  inline auto GetShader(void) -> Shader* {return shaders->at(currentShaderIndex);}
  inline auto AddShader(Shader *s) -> void {shaders->push_back(s);}
  inline auto GetModelMatrix(void) -> glm::mat4 const {return modelMatrix;}
  inline auto SetModelMatrix(glm::mat4 mat) -> void {modelMatrix = mat;}
  auto Update(double delta) -> void;
  virtual auto Draw(void) -> void;
  inline auto ChangeShaders(void) -> void {currentShaderIndex++;
                                           if (currentShaderIndex == shaders->size()) {
                                             currentShaderIndex = 0;
                                           }}
protected:
  Mesh *mesh;
  std::vector<Shader*> *shaders;
  std::vector<Texture*> *textures;
  std::vector<___hidden___::ShaderUpdateMixin*> *shaderUpdaters;
  glm::mat4 modelMatrix;
};

// Used to update shaders
namespace ___hidden___ {
  class ShaderUpdateMixin {
  public:
    ShaderUpdateMixin(Shader *s) : shader(s) {}
    virtual auto Update(double delta) -> void = 0;
    Shader *shader;
  };
}

#endif // RENDEROBJECT_HPP
