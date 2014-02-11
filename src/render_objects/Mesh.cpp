/**
 * CSC3223 Graphics for Games
 * Coursework 2
 * Name: George Burton
 * Student Number: 110204567
 * File: Mesh.cpp
 */

#include "Mesh.hpp"

#include <algorithm>
#include <iostream>
#include <fstream>

#include <glm/glm.hpp>

#include "Config.hpp"

#include "ResourceLoader.hpp"
#include "Shader.hpp"

#include "make_unique.hpp"

using namespace std;
using namespace glm;

Pneumatic::Mesh::Mesh(int numVerts)
  :
  fNumVertices(numVerts),
  fVertices(unique_ptr<vector<vec3>>(nullptr)),
  fNormals(unique_ptr<vector<vec3>>(nullptr)),
  fColors(unique_ptr<vector<vec4>>(nullptr)),
  fTexCoords(unique_ptr<vector<vec2>>(nullptr)),
  fVao(0),
  fType(GL_TRIANGLES)
{

}

Pneumatic::Mesh::~Mesh()
{

}

auto
Pneumatic::Mesh::GenerateTriangle() -> std::shared_ptr<Mesh>
{
  std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(3);

  using namespace glm;

  mesh->fVertices = make_unique<vector<vec3>>(
  vector<vec3> {
    vec3(-1.0f, -1.0f, 0.0f),
    vec3( 1.0f, -1.0f, 0.0f),
    vec3( 0.0f,  1.0f, 0.0f)
  });

  mesh->fColors = make_unique<vector<vec4>>(
  vector<vec4> {
    vec4(1.0f, 0.0f, 0.0f, 1.0f),
    vec4(0.0f, 1.0f, 0.0f, 1.0f),
    vec4(0.0f, 0.0f, 1.0f, 1.0f),  
  });

  mesh->fTexCoords = make_unique<vector<vec2>>(
  vector<vec2> {
    vec2(1.0f, 1.0f),
    vec2(0.0f, 1.0f),
    vec2(1.0f, 0.0f)
  });

  mesh->_BufferData();

  return mesh;
}

auto
Pneumatic::Mesh::GenerateCube() -> std::shared_ptr<Mesh>
{
  std::shared_ptr<Mesh> mesh = _LoadFromFile("cube");
  mesh->_GenerateNormals();
  mesh->_BufferData();
  return mesh;
}

auto
Pneumatic::Mesh::NewFromObjFile(std::string const &fname) -> std::shared_ptr<Mesh>
{
  std::shared_ptr<Mesh> mesh = _LoadFromFile(fname);
  return mesh;
}

auto
Pneumatic::Mesh::_LoadFromFile(std::string const &fileName) -> std::shared_ptr<Mesh>
{
  std::string filePath = Config::kMeshResDir + fileName + ".mesh";
  std::ifstream fs(filePath);
  if (!fs) {
    return nullptr;
  }

  std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
  mesh->fType = GL_TRIANGLES;
  fs >> mesh->fNumVertices;

  int hasTex = 0;
  int hasColour = 0;
  fs >> hasColour;
  fs >> hasTex;

  mesh->fVertices = make_unique<vector<glm::vec3>>(mesh->fNumVertices);
  mesh->fColors = make_unique<vector<glm::vec4>>(mesh->fNumVertices);
  mesh->fTexCoords = make_unique<vector<glm::vec2>>(mesh->fNumVertices);
  
  for (int i = 0; i < mesh->fNumVertices; i++) {
    fs >> (*(mesh->fVertices))[i].x;
    fs >> (*(mesh->fVertices))[i].y;
    fs >> (*(mesh->fVertices))[i].z;
  }

  if (hasColour) {
    for (int i = 0; i < mesh->fNumVertices; i++) {
      fs >> (*(mesh->fColors))[i].r;
      fs >> (*(mesh->fColors))[i].g;
      fs >> (*(mesh->fColors))[i].b;
      fs >> (*(mesh->fColors))[i].a;
    }
  } else {
      mesh->fColors = nullptr;
  }

  if (hasTex) {
    for (int i = 0; i < mesh->fNumVertices; i++) {
      fs >> (*(mesh->fTexCoords))[i].x;
      fs >> (*(mesh->fTexCoords))[i].y;
    }
  }

  return mesh;
}

auto
Pneumatic::Mesh::_GenerateNormals() -> void
{
  using namespace glm;
  fNormals = make_unique<vector<glm::vec3>>(fNumVertices);
  for (int i = 0; i < fNumVertices; i+=3) {
    vec3 &a = (*fVertices)[i];
    vec3 &b = (*fVertices)[i+1];
    vec3 &c = (*fVertices)[i+2];
    vec3 normal = cross(b - a, c - a);
    normalize(normal);
    (*fNormals)[i] = normal;
    (*fNormals)[i+1] = normal;
    (*fNormals)[i+2] = normal;
  }
}

auto
Pneumatic::Mesh::Draw() -> void
{
  glBindVertexArray(fVao);
  glDrawElements(fType, fNumVertices, GL_UNSIGNED_INT, 0);
  glDrawArrays(fType, 0, fNumVertices * sizeof(glm::vec3));
  glBindVertexArray(0);
}

auto
Pneumatic::Mesh::_BufferData() -> void
{
  GLuint positionVBO;
  GLuint colorVBO;
  GLuint textureVBO;
  GLuint normalsVBO;

  glGenVertexArrays(1, &fVao);
  glBindVertexArray(fVao);

  glGenBuffers(1, &positionVBO);
  glBindBuffer(GL_ARRAY_BUFFER, positionVBO);

  int index = 0;

  glBufferData(GL_ARRAY_BUFFER, fNumVertices * sizeof(glm::vec3),
               &(fVertices.get())[0], GL_STATIC_DRAW);
  glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(index);

  index++;
  if (fColors) {
    glGenBuffers(1, &colorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);

    glBufferData(GL_ARRAY_BUFFER, fNumVertices * sizeof(glm::vec4),
                 &(fColors.get())[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, 4, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
  index++;
  if (fTexCoords) {
    glGenBuffers(1, &textureVBO);
    glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
    glBufferData(GL_ARRAY_BUFFER, fNumVertices * sizeof(glm::vec2),
                 &(fTexCoords.get())[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
  index++;
  if (fNormals) {
    glGenBuffers(1, &normalsVBO);
    glBindBuffer(GL_ARRAY_BUFFER, normalsVBO);
    glBufferData(GL_ARRAY_BUFFER, fNumVertices * sizeof(glm::vec3),
                 &(fNormals.get())[0], GL_STATIC_DRAW );
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
  glBindVertexArray(0);
}
