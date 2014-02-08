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
#include <memory>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/fwd.hpp>

namespace Pneumatic {

class Mesh final {
public:
  Mesh(int numVerts = 0);
  ~Mesh();

  static auto GenerateTriangle(void)                   -> std::shared_ptr<Mesh>;
  static auto GenerateCube(void)                       -> std::shared_ptr<Mesh>;
  static auto NewFromObjFile(std::string const &fname) -> std::shared_ptr<Mesh>;

  auto Draw(void)                                      -> void;

private:
  static auto _LoadFromFile(std::string const &file)   -> std::shared_ptr<Mesh>;

  auto _GenerateNormals(void)                          -> void;
  auto _BufferData(void)                               -> void;

  class RenderObject;
  friend class RenderObject;

  int fNumVertices;

  std::unique_ptr<std::vector<glm::vec3>> fVertices;
  std::unique_ptr<std::vector<glm::vec3>> fNormals;
  std::unique_ptr<std::vector<glm::vec4>> fColors;
  std::unique_ptr<std::vector<glm::vec2>> fTexCoords;

  GLuint fVao;
  GLuint fType;
};

} // namespace Pneumatic

#endif // PNEUMATIC_MESH_HPP
