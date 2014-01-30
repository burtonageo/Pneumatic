/**
 * CSC3223 Graphics for Games
 * Coursework 2
 * Name: George Burton
 * Student Number: 110204567
 * File: Mesh.hpp
 */

#pragma once

#ifndef PNEUMATIC_MESH_HPP
#define PNEUMATIC_MESH_HPP

#include <string>
#include <vector>

#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS
#include <glm/fwd.hpp>

namespace Pneumatic {

class Mesh final {
public:
  Mesh(int numVerts = 0,
       glm::vec3 *vertices = nullptr);
  ~Mesh();

  static auto GenerateTriangle(void)                   -> Mesh*;
  static auto GenerateCube(void)                       -> Mesh*;
  static auto NewFromObjFile(std::string const &fname) -> Mesh*;

  auto Draw(void)                                      -> void;

private:
  static auto _LoadFromFile(std::string const &file)   -> Mesh*;

  auto _GenerateNormals(void)                          -> void;
  auto _BufferData(void)                               -> void;

  class RenderObject;
  friend class RenderObject;

  int fNumVertices;

  glm::vec3 *fVertices;
  glm::vec3 *fNormals;
  glm::vec4 *fColors;
  glm::vec2 *fTexCoords;

  GLuint fVao;
  GLuint fType;
};

} // namespace Pneumatic

#endif // PNEUMATIC_MESH_HPP
