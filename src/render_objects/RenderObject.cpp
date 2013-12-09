#include <glm/glm.hpp>

#include <iostream>

#include "Mesh.hpp"
#include "Shader.hpp"
#include "RenderObject.hpp"

RenderObject::RenderObject(Mesh *m,
                           Shader *s,
                           GLuint tex) :
  mesh(m),
  shader(s),
  texture(tex),
  modelMatrix(glm::mat4(1.0f))
{
  
}

RenderObject::~RenderObject()
{
  delete mesh;
  delete shader;
}

auto
RenderObject::Draw() -> void
{
  glUseProgram(shader->programID);
  mesh->Draw();
}
