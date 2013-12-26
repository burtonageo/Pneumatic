#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Texture.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "TriObject.hpp"

TriObject::TriObject(void) :
  RenderObject(Mesh::GenerateTriangle())
{
  shaders->push_back(new Shader("tri", "tri"));
  AddTexture("noise.png");
}

auto
TriObject::Update(double delta) -> void
{

}
