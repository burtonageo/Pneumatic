#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

#include "Texture.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "TriObject.hpp"

TriObject::TriObject(void) :
  RenderObject(Mesh::GenerateTriangle(),
               new Shader("tri", "tri"))
{
  SetTexture("noise.png");
}

auto
TriObject::Update(double delta) -> void
{

}
