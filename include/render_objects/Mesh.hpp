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

#include <GLFW/glfw3.h>

class Mesh final {
public:
  static Mesh *GenerateTriangle();
  static Mesh *GenerateCube();
  static Mesh *LoadFromFile(std::string file);

  void Draw();
  void BufferData();

private:
  GLfloat *vertices;
};

#endif // MESH_HPP
