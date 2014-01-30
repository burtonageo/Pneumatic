/**
 * CSC3223 Graphics for Games
 * Coursework 2
 * Name: George Burton
 * Student Number: 110204567
 * File: ResourceLoader.hpp
 */

#include "CubeObject.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>

#include "Mesh.hpp"
#include "Shader.hpp"
#include "RenderObject.hpp"

Pneumatic::CubeObject::CubeObject() :
  RenderObject(Mesh::GenerateCube())
{
  Shader *s1 = new Shader("cube1", "cube1", "cube1");
  Shader *s2 = new Shader("cube2", "cube2", "cube2");
  fShaders->push_back(s1);
  fShaders->push_back(s2);
  auto sUpdt1 = new ___hidden___::CubeShaderUpdate1(s1);
  auto sUpdt2 = new ___hidden___::CubeShaderUpdate2(s2);
  fShaderUpdaters->push_back(sUpdt1);
  fShaderUpdaters->push_back(sUpdt2);
  AddTexture("smiley.png");
  AddTexture("noise.png");
}

Pneumatic::CubeObject::~CubeObject()
{

}

auto
Pneumatic::___hidden___::CubeShaderUpdate1::Update(double delta) -> void
{
  GLuint program = shader->GetShaderProgram();
  GLint rotRef = glGetUniformLocation(program, "rotAngle");
  glUniform1f(rotRef, static_cast<float>(delta));
  GLint timeRef = glGetUniformLocation(program, "time");
  glUniform1f(timeRef, static_cast<float>(delta));
}


auto
Pneumatic::___hidden___::CubeShaderUpdate2::Update(double delta) -> void
{
  GLuint program = shader->GetShaderProgram();
  GLint timeRef = glGetUniformLocation(program, "time");
  glUniform1f(timeRef, delta);
  GLint alphaRef = glGetUniformLocation(program, "alphaValue");
  glUniform1f(alphaRef, delta);
}

auto
Pneumatic::___hidden___::CubeShaderUpdate3::Update(double delta) -> void
{
  GLint rotRef = glGetUniformLocation(shader->GetShaderProgram(), "rotAngle");
  glUniform1f(rotRef, delta);
  GLint timeRef = glGetUniformLocation(shader->GetShaderProgram(), "time");
  glUniform1f(timeRef, static_cast<float>(delta));
  glm::mat4 texRotMat(1.0f);
  texRotMat = glm::translate(texRotMat, glm::vec3(0.5f, 0.5f, 0.0f));
  texRotMat = glm::rotate(texRotMat, 5.0f, glm::vec3(0.0f, 0.0f, 1.0f));
  texRotMat = glm::translate(texRotMat, glm::vec3(-0.5f, -0.5f, 0.0f));
  GLint texRotRef = glGetUniformLocation(shader->GetShaderProgram(), "texRotAngle");
  glUniformMatrix4fv(texRotRef, 1, GL_FALSE, &texRotMat[0][0]);
}  
