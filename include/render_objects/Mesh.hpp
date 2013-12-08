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

#include <glm/glm>
#include <GLFW/glfw3.h>

class Shader;
class Mesh final {
public:
  static auto GenerateTriangle(void) -> Mesh*;
  static auto GenerateCube(void) -> Mesh*;
  static auto LoadFromFile(std::string file) -> Mesh*;

  auto Draw(void) -> void;
  auto BufferData(void) -> void;

private:
  std::vector<Shader*> shaders;
  GLfloat *vertices;
};

#endif // MESH_HPP
