/**
 * CSC3223 Graphics for Games
 * Coursework 2
 * Name: George Burton
 * Student Number: 110204567
 * File: GLWindow.cpp
 */

#include <algorithm>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Shader.hpp"
#include "Mesh.hpp"

Mesh::Mesh(int numVerts, glm::vec3 *vertices) :
  numVertices(numVerts),
  vertices(vertices),
  colors(nullptr),
  type(GL_TRIANGLES),
  vao(0)
{

}

Mesh::~Mesh()
{
  delete[] vertices;
  delete[] colors;
  delete[] texCoords;
}

auto
Mesh::GenerateTriangle() -> Mesh*
{
  Mesh *mesh = new Mesh(3);

  using namespace glm;
  mesh->vertices = new vec3[mesh->numVertices] {
   vec3(-1.0f, -1.0f, 0.0f),
   vec3( 1.0f, -1.0f, 0.0f),
   vec3( 0.0f,  1.0f, 0.0f)
  };

  mesh->BufferData();
  return mesh;
}

auto
Mesh::GenerateCube() -> Mesh*
{
  Mesh *mesh = new Mesh(12);

  using namespace glm;
  mesh->vertices = new vec3[mesh->numVertices] {
    vec3(-1.0f,-1.0f,-1.0f),
    vec3(-1.0f,-1.0f, 1.0f),
    vec3(-1.0f, 1.0f, 1.0f),
    vec3( 1.0f, 1.0f,-1.0f),
    vec3(-1.0f,-1.0f,-1.0f),
    vec3(-1.0f, 1.0f,-1.0f),
    vec3( 1.0f,-1.0f, 1.0f),
    vec3(-1.0f,-1.0f,-1.0f),
    vec3( 1.0f,-1.0f,-1.0f),
    vec3( 1.0f, 1.0f,-1.0f),
    vec3( 1.0f,-1.0f,-1.0f),
    vec3(-1.0f,-1.0f,-1.0f),
    vec3(-1.0f,-1.0f,-1.0f),
    vec3(-1.0f, 1.0f, 1.0f),
    vec3(-1.0f, 1.0f,-1.0f),
    vec3( 1.0f,-1.0f, 1.0f),
    vec3(-1.0f,-1.0f, 1.0f),
    vec3(-1.0f,-1.0f,-1.0f),
    vec3(-1.0f, 1.0f, 1.0f),
    vec3(-1.0f,-1.0f, 1.0f),
    vec3( 1.0f,-1.0f, 1.0f),
    vec3( 1.0f, 1.0f, 1.0f),
    vec3( 1.0f,-1.0f,-1.0f),
    vec3( 1.0f, 1.0f,-1.0f),
    vec3( 1.0f,-1.0f,-1.0f),
    vec3( 1.0f, 1.0f, 1.0f),
    vec3( 1.0f,-1.0f, 1.0f),
    vec3( 1.0f, 1.0f, 1.0f),
    vec3( 1.0f, 1.0f,-1.0f),
    vec3(-1.0f, 1.0f,-1.0f),
    vec3( 1.0f, 1.0f, 1.0f),
    vec3(-1.0f, 1.0f,-1.0f),
    vec3(-1.0f, 1.0f, 1.0f),
    vec3( 1.0f, 1.0f, 1.0f),
    vec3(-1.0f, 1.0f, 1.0f),
    vec3( 1.0f,-1.0f, 1.0f)
  };
}

auto
Mesh::LoadFromFile(std::string file) -> Mesh*
{
  
}

auto
Mesh::Draw() -> void
{
  glBindVertexArray(vao);
  glDrawArrays(type, 0, numVertices * sizeof(glm::vec3));
  glBindVertexArray(0);
}

auto
Mesh::BufferData() -> void
{
  GLuint positionVBO;
  GLuint colorVBO;

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(1, &positionVBO);
  glBindBuffer(GL_ARRAY_BUFFER, positionVBO);

  int index = 0;

  glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(glm::vec3),
               &vertices[0], GL_STATIC_DRAW);
  glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(index);

  index++;

  if (colors) {
    glGenBuffers(1, &colorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);

    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(glm::vec4),
                 &colors[0], GL_STATIC_DRAW);
    glVertexAttribPointer(index, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(index);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }
}
