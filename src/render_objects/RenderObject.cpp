/**
 * CSC3223 Graphics for Games
 * Coursework 2
 * Name: George Burton
 * Student Number: 110204567
 * File: RenderObject.cpp
 */

#include "RenderObject.hpp"

#include "Light.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

using namespace std;

Pneumatic::RenderObject::RenderObject(std::shared_ptr<Pneumatic::Mesh> m)
  :
  fMesh(m),
  fModelMatrix(glm::mat4(1.0)),
  fShaders(unique_ptr<vector<shared_ptr<Shader>>>()),
  fTextures(unique_ptr<vector<shared_ptr<Texture>>>()),
  fCurrentShaderIndex(0)
{

}

auto
Pneumatic::RenderObject::Update(double delta) -> void
{ 
  fShaders->at(fCurrentShaderIndex)->Update(delta);
}

auto
Pneumatic::RenderObject::AddTexture(std::string const &texFile) -> void
{
  fTextures->push_back(make_shared<Texture>(texFile));
}

auto
Pneumatic::RenderObject::SetShaderLight(Light *light) -> void
{

}

auto
Pneumatic::RenderObject::UseShader() -> void
{
  glUseProgram(fShaders->at(fCurrentShaderIndex)->GetShaderProgram());
}

auto
Pneumatic::RenderObject::Draw() -> void
{
  auto currShader = fShaders->at(fCurrentShaderIndex);
  auto currTexture = fTextures->at(fCurrentShaderIndex); 
  if (currTexture != nullptr) {
    currTexture->Bind(&*currShader);
  }
  fMesh->Draw();
  if (currTexture != nullptr) {
    currTexture->Unbind();
  }
}
