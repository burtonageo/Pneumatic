#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

#include "Config.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "RenderObject.hpp"

RenderObject::RenderObject(Mesh *m,
                           Shader *s,
                           Texture *tex) :
  mesh(m),
  shader(s),
  texture(tex),
  modelMatrix(glm::mat4(1.0))
{

}

RenderObject::~RenderObject()
{
  delete mesh;
  delete shader;
  if (texture != nullptr) {
    delete texture;
  }
}

auto
RenderObject::SetTexture(std::string texFile) -> void
{
  texture = new Texture(texFile);
}

auto
RenderObject::UseShader() -> void
{
  glUseProgram(shader->programID);
}

auto
RenderObject::Draw() -> void
{
  if (texture != nullptr) {
    texture->Bind(shader);
  }
  mesh->Draw();
  if (texture != nullptr) {
    texture->Unbind();
  }
}
