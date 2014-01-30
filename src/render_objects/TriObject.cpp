/**
 * CSC3223 Graphics for Games
 * Coursework 2
 * Name: George Burton
 * Student Number: 110204567
 * File: TriObject.cpp
 */

#include "TriObject.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "Texture.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"

Pneumatic::TriObject::TriObject(void)
  :
  RenderObject(Pneumatic::Mesh::GenerateTriangle())
{
  fShaders->push_back(new Pneumatic::Shader("tri", "tri"));
  AddTexture("noise.png");
}

auto
Pneumatic::TriObject::Update(double delta) -> void
{

}
