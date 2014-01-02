#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Config.hpp"
#include "Light.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "RenderObject.hpp"

Pneumatic::RenderObject::RenderObject(Pneumatic::Mesh *m)
  :
  fMesh(m),
  fModelMatrix(glm::mat4(1.0)),
  shaders(new std::vector<Shader*>()),
  textures(new std::vector<Texture*>()),
  shaderUpdaters(new std::vector<___hidden___::ShaderUpdateMixin*>()),
  fCurrentShaderIndex(0)
{

}

Pneumatic::RenderObject::~RenderObject()
{
  delete fMesh;
  delete shaders;
  if (textures != nullptr) {
    delete textures;
  }
}

auto
Pneumatic::RenderObject::Update(double delta) -> void
{ 
  shaderUpdaters->at(fCurrentShaderIndex)->Update(delta);
}

auto
Pneumatic::RenderObject::AddTexture(std::string const &texFile) -> void
{
  textures->push_back(new Texture(texFile));
}

auto
Pneumatic::RenderObject::SetShaderLight(Light *light) -> void
{

}

auto
Pneumatic::RenderObject::UseShader() -> void
{
  glUseProgram(shaders->at(fCurrentShaderIndex)->GetShaderProgram());
}

auto
Pneumatic::RenderObject::Draw() -> void
{
  auto *currShader = shaders->at(fCurrentShaderIndex);
  auto *currTexture = textures->at(fCurrentShaderIndex); 
  if (currTexture != nullptr) {
    currTexture->Bind(currShader);
  }
  fMesh->Draw();
  if (currTexture != nullptr) {
    currTexture->Unbind();
  }
}
