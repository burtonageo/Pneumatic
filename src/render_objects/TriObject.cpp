#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Texture.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "TriObject.hpp"

Pneumatic::TriObject::TriObject(void)
  :
  RenderObject(Pneumatic::Mesh::GenerateTriangle())
{
  shaders->push_back(new Pneumatic::Shader("tri", "tri"));
  AddTexture("noise.png");
}

auto
Pneumatic::TriObject::Update(double delta) -> void
{

}
