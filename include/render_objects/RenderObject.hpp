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

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Mesh;
class Shader;
class Texture;
class RenderObject {
public:
  RenderObject(Mesh *m = nullptr,
               Shader *s = nullptr,
               Texture *t = nullptr);
  ~RenderObject(void);
  auto UseShader(void) -> void;
  auto SetTexture(std::string texFile) -> void;
  inline auto GetMesh(void) -> Mesh* const {return mesh;}
  inline auto SetMesh(Mesh *m) -> void {mesh = m;}
  inline auto GetShader(void) -> Shader* const {return shader;}
  inline auto SetShader(Shader *s) -> void {shader = s;}
  inline auto GetModelMatrix(void) -> glm::mat4 const {return modelMatrix;}
  inline auto SetModelMatrix(glm::mat4 mat) -> void {modelMatrix = mat;}
  virtual auto Update(double delta) -> void = 0;
  virtual auto Draw(void) -> void;
protected:
  Mesh *mesh;
  Shader *shader;
  Texture *texture;
  glm::mat4 modelMatrix;  
};

#endif // RENDEROBJECT_HPP
