/**
 * CSC3223 Graphics for Games
 * Coursework 2
 * Name: George Burton
 * Student Number: 110204567
 * File: ResourceLoader.hpp
 */

#include <GLFW/glfw3.h>

#include "Mesh.hpp"
#include "Shader.hpp"
#include "RenderObject.hpp"
#include "CubeObject.hpp"

CubeObject::CubeObject() :
  RenderObject(Mesh::GenerateCube(),
               new Shader("cube", "cube"))
{
  SetTexture("smiley.png");
}

CubeObject::~CubeObject()
{

}

auto
CubeObject::Update(double delta) -> void
{
  GLint rotRef = glGetUniformLocation(shader->GetShaderProgram(), "rotAngle");
  glUniform1f(rotRef, delta);
}
