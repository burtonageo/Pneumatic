/**
* CSC3223 Graphics for Games
* Coursework 2
* Name: George Burton
* Student Number: 110204567
* File: GLWindow.cpp
*/

#include <GLFW/glfw3.h>

#include "Mesh.hpp"

Mesh::Mesh() :
  vertices(nullptr)
{

}

Mesh*
Mesh::GenerateTriangle()
{
  Mesh *mesh = new Mesh();

  mesh->vertices = new GLfloat[] {
   -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f,  1.0f, 0.0f
  };

  return mesh;
}

Mesh*
Mesh::GenerateCube()
{
  
}

Mesh*
Mesh::LoadFromFile(std::string file)
{
  
}

void
Mesh::Draw()
{
  
}

void
Mesh::BufferData()
{
  
}
