#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

#include "Config.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "RenderObject.hpp"

RenderObject::RenderObject(Mesh *m) :
  currentShaderIndex(0),
  mesh(m),
  shaders(new std::vector<Shader*>()),
  textures(new std::vector<Texture*>()),
  shaderUpdaters(new std::vector<___hidden___::ShaderUpdateMixin*>()),
  modelMatrix(glm::mat4(1.0))
{

}

RenderObject::~RenderObject()
{
  delete mesh;
  delete shaders;
  if (textures != nullptr) {
    delete textures;
  }
}

auto
RenderObject::Update(double delta) -> void
{ 
  shaderUpdaters->at(currentShaderIndex)->Update(delta);
}

auto
RenderObject::AddTexture(std::string texFile) -> void
{
  textures->push_back(new Texture(texFile));
}

auto
RenderObject::UseShader() -> void
{
  glUseProgram(shaders->at(currentShaderIndex)->GetShaderProgram());
}

auto
RenderObject::Draw() -> void
{
  auto *currShader = shaders->at(currentShaderIndex);
  auto *currTexture = textures->at(currentShaderIndex); 
  if (currTexture != nullptr) {
    currTexture->Bind(currShader);
  }
  mesh->Draw();
  if (currTexture != nullptr) {
    currTexture->Unbind();
  }
}
