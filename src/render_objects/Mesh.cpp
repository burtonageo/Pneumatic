/**
 * This file is part of the Pneumatic game engine
 *
 * Copyright (c) 2014 George Burton
 * 
 * THIS SOFTWARE IS PROVIDED 'AS-IS', WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTY. IN NO EVENT WILL THE AUTHORS BE HELD LIABLE FOR ANY DAMAGES
 * ARISING FROM THE USE OF THIS SOFTWARE.
 * 
 * Permission is granted to anyone to use this software for any purpose,  
 * including commercial applications, and to alter it and redistribute it  
 * freely, subject to the following restrictions:
 * 
 *    1. The origin of this software must not be misrepresented; you must not  
 *       claim that you wrote the original software. If you use this software  
 *       in a product, an acknowledgment in the product documentation would be  
 *       appreciated but is not required.
 * 
 *    2. Altered source versions must be plainly marked as such, and must not be  
 *       misrepresented as being the original software.
 * 
 *    3. This notice may not be removed or altered from any source  
 *       distribution.
 *
 **/

#include "Mesh.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <fstream>

#include "Config.hpp"
#include "GlInclude.hpp"
#include "ResourceLoader.hpp"
#include "Shader.hpp"

using namespace glm;
using namespace std;

Pneumatic::Graphics::Mesh::Mesh(int num_verts)
  :
  fVertices(),
  fNormals(),
  fColors(),
  fTexCoords(),
  fNumVertices(num_verts),
  fVao(0),
  fType(GL_TRIANGLES)
{

}

Pneumatic::Graphics::Mesh::~Mesh() = default;

auto
Pneumatic::Graphics::Mesh::generateTriangle() -> std::shared_ptr<Mesh>
{
  auto mesh = make_shared<Mesh>(3);
  mesh->_reserveArrays();

  mesh->fVertices = {
    vec3(-1.0f, -1.0f, 0.0f),
    vec3( 1.0f, -1.0f, 0.0f),
    vec3( 0.0f,  1.0f, 0.0f),
  };

  mesh->fColors = {
    vec4(1.0f, 0.0f, 0.0f, 1.0f),
    vec4(0.0f, 1.0f, 0.0f, 1.0f),
    vec4(0.0f, 0.0f, 1.0f, 1.0f),
  };

  mesh->fTexCoords = {
    vec2(1.0f, 1.0f),
    vec2(0.0f, 1.0f),
    vec2(1.0f, 0.0f),
  };

  mesh->_bufferData();
  return mesh;
}

auto
Pneumatic::Graphics::Mesh::generateCube() -> std::shared_ptr<Mesh>
{
  auto mesh = _loadFromFile("cube");
  mesh->_generateNormals();
  mesh->_bufferData();
  return mesh;
}

auto
Pneumatic::Graphics::Mesh::generateSphere() -> std::shared_ptr<Mesh>
{
  return nullptr;
}

auto
Pneumatic::Graphics::Mesh::loadFromObjFile(const std::string& file_name) -> std::shared_ptr<Mesh>
{
  return nullptr;
}

auto
Pneumatic::Graphics::Mesh::_loadFromFile(const std::string& file_name) -> std::shared_ptr<Mesh>
{
  // TODO: ake file paths work good
  string file_path = file_name + ".mesh";
  ifstream fs(file_path);

  if (!fs) {
    return nullptr;
  }

  auto mesh = make_shared<Mesh>();
  mesh->fType = GL_TRIANGLES;
  fs >> mesh->fNumVertices;

  mesh->_reserveArrays();

  int has_tex = 0, has_color = 0;
  fs >> has_tex;
  fs >> has_color;

  for (int i = 0; i < mesh->fNumVertices; i++) {
    fs >> mesh->fVertices[i].x;
    fs >> mesh->fVertices[i].y;
    fs >> mesh->fVertices[i].z;
  }
  mesh->fVertices.shrink_to_fit();

  if (has_color) {
    for (int i = 0; i < mesh->fNumVertices; i++) {
      fs >> mesh->fColors[i].r;
      fs >> mesh->fColors[i].g;
      fs >> mesh->fColors[i].b;
      fs >> mesh->fColors[i].a;
    }
  }
  mesh->fColors.shrink_to_fit();

  if (has_tex) {
    for (int i = 0; i < mesh->fNumVertices; i++) {
      fs >> mesh->fTexCoords[i].x;
      fs >> mesh->fTexCoords[i].y;
    }
  }
  mesh->fTexCoords.shrink_to_fit();

  return mesh;
}

auto
Pneumatic::Graphics::Mesh::draw() -> void
{
  glBindVertexArray(fVao);
  glDrawElements(fType, fNumVertices, GL_UNSIGNED_INT, 0);
  glDrawArrays(fType, 0, fNumVertices * sizeof(glm::vec3));
  glBindVertexArray(0);
}

auto
Pneumatic::Graphics::Mesh::_generateNormals() -> void
{
  for (int i = 0; i < fNumVertices; i+=3) {
    vec3& a = fVertices[i];
    vec3& b = fVertices[i+1];
    vec3& c = fVertices[i+2];

    vec3 normal = glm::cross(b - a, c - a);
    glm::normalize(normal);

    fNormals[i]   = normal;
    fNormals[i+1] = normal;
    fNormals[i+2] = normal;
  }
  fNormals.shrink_to_fit();
}

auto
Pneumatic::Graphics::Mesh::_bufferData() -> void
{
  glGenVertexArrays(1, &fVao);
  glBindVertexArray(fVao);

  _bufferVertices();
  _bufferColors();
  _bufferTexCoords();
  _bufferNormals();

  glBindVertexArray(0);
}

auto
Pneumatic::Graphics::Mesh::_reserveArrays() -> void
{
  fVertices  = std::vector<glm::vec3>(fNumVertices, glm::vec3());
  fNormals   = std::vector<glm::vec3>(fNumVertices, glm::vec3());
  fColors    = std::vector<glm::vec4>(fNumVertices, glm::vec4());
  fTexCoords = std::vector<glm::vec2>(fNumVertices, glm::vec2());
}

#define MESH_BUFFER_DATA_METH_DECL(meth_name, member_arr, idx, vec_tp, vec_num_elems) \
  auto \
  Pneumatic::Graphics::Mesh::meth_name() -> void \
  { \
    if (member_arr.empty()) { \
      return; \
    } \
    \
    GLuint vbo; \
    \
    glGenBuffers(1, &vbo); \
    glBindBuffer(GL_ARRAY_BUFFER, vbo); \
    \
    glBufferData(GL_ARRAY_BUFFER, \
                 fNumVertices * sizeof(vec_tp), \
                 member_arr.data(),  GL_STATIC_DRAW); \
    glVertexAttribPointer(idx, vec_num_elems, GL_FLOAT, GL_FALSE, 0, 0); \
    glEnableVertexAttribArray(idx); \
  }

MESH_BUFFER_DATA_METH_DECL(_bufferVertices,  fVertices,  0, glm::vec3, 3)
MESH_BUFFER_DATA_METH_DECL(_bufferColors,    fColors,    1, glm::vec4, 4)
MESH_BUFFER_DATA_METH_DECL(_bufferTexCoords, fTexCoords, 2, glm::vec2, 2)
MESH_BUFFER_DATA_METH_DECL(_bufferNormals,   fNormals,   3, glm::vec3, 3)

#undef MESH_BUFFER_DATA_METH_DECL
