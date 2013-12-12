/**
 * CSC3223 Graphics for Games
 * Coursework 2
 * Name: George Burton
 * Student Number: 110204567
 * File: GLWindow.cpp
 */

#include <algorithm>
#include <iostream>
#include <fstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Config.hpp"

#include "ResourceLoader.hpp"
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

  mesh->colors = new vec4[mesh->numVertices] {
    vec4(1.0f, 0.0f, 0.0f, 1.0f),
    vec4(0.0f, 1.0f, 0.0f, 1.0f),
    vec4(0.0f, 0.0f, 1.0f, 1.0f),  
  };

  mesh->texCoords = new vec2[mesh->numVertices] {
    vec2(1.0f, 1.0f),
    vec2(0.0f, 1.0f),
    vec2(1.0f, 0.0f)
  };
  mesh->BufferData();

  return mesh;
}

auto
Mesh::GenerateCube() -> Mesh*
{
  Mesh *mesh = LoadFromFile("cube");
  mesh->BufferData();
  return mesh;
}

auto
Mesh::LoadFromFile(std::string fileName) -> Mesh*
{
  std::string filePath = Config::GetMeshResDir() + fileName + ".mesh";
  std::ifstream fs(filePath);
  if (!fs) {
    return NULL;
  }

  Mesh *mesh = new Mesh();
  mesh->type = GL_TRIANGLES;
  fs >> mesh->numVertices;

  int hasTex = 0; int hasColour = 0;
  fs >> hasTex;
  fs >> hasColour;

  mesh->vertices = new glm::vec3[mesh->numVertices]; 
  mesh->colors = new glm::vec4[mesh->numVertices];
  mesh->texCoords = new glm::vec2[mesh->numVertices];
  
  for (int i = 0; i < mesh->numVertices; i++) {
    fs >> mesh->vertices[i].x;
    fs >> mesh->vertices[i].y;
    fs >> mesh->vertices[i].z;
  }

  if (hasColour) {
    for (int i = 0; i < mesh->numVertices; i++) {
      fs >> mesh->colors[i].r;
      fs >> mesh->colors[i].g;
      fs >> mesh->colors[i].b;
      fs >> mesh->colors[i].a;
    }
  } else {
      mesh->colors = nullptr;
  }

  if (hasTex) {
    for (int i = 0; i < mesh->numVertices; i++) {
      fs >> mesh->texCoords[i].x;
      fs >> mesh->texCoords[i].y;
    }
  } else {
    mesh->texCoords = nullptr;
  }

  return mesh;
}

auto
Mesh::Draw() -> void
{
  glBindVertexArray(vao);
  glDrawElements(type , numVertices , GL_UNSIGNED_INT , 0);
  glDrawArrays(type, 0, numVertices * sizeof(glm::vec3));
  glBindVertexArray(0);
}

auto
Mesh::BufferData() -> void
{
  GLuint positionVBO;
  GLuint colorVBO;
  GLuint textureVBO;
  GLuint indexBufferID;

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
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, 4, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
  index++;
  if (texCoords) {
    glGenBuffers(1, &textureVBO);
    glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(glm::vec2),
                 &texCoords[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
  glBindVertexArray(0);
}
