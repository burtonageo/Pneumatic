/**
 * CSC3223 Graphics for Games
 * Coursework 2
 * Name: George Burton
 * Student Number: 110204567
 * File: Mesh.hpp
 */

#pragma once

#ifndef MESH_HPP
#define MESH_HPP

#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Shader;
class RenderObject;
class Mesh final {
public:
  Mesh(int numVerts = 0,
       glm::vec3 *vertices = nullptr);
  ~Mesh();
  static auto GenerateTriangle(void) -> Mesh*;
  static auto GenerateCube() -> Mesh*;

  auto Draw(void) -> void;
  auto BufferData() -> void;

private:
  static auto LoadFromFile(std::string file) -> Mesh*;
  friend class RenderObject;
  int numVertices;
  glm::vec3 *vertices;
  glm::vec4 *colors;
  glm::vec2 *texCoords;
  GLuint vao;
  GLuint type;
  GLuint texture;
};

#endif // MESH_HPP
