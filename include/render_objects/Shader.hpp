/**
 * CSC3223 Graphics for Games
 * Coursework 2
 * Name: George Burton
 * Student Number: 110204567
 * File: Shader.hdpp
 */

#pragma once

#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <vector>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "RenderObject.hpp"

class Shader {
public:
  Shader(std::string const &vertFile, std::string const &fragFile,
         std::string const &geomFile = "",
         std::string const &tcsFile = "",
         std::string const &tesFile = "");
  Shader(Shader const &);
  ~Shader();
  inline auto GetShaderProgram(void) -> GLuint const {return programID;}
  auto SetDefaultAttributes() -> void;
  auto Update(double ms) -> void;
private:
  friend class Mesh;
  friend class RenderObject;
  friend class ___hidden___::ShaderUpdateMixin;
  
  static auto CompileShader(GLuint shaderID, const char *sourcePtr,
                            GLint result, int infoLogLength,
                            std::vector<char> errorVec) -> void;
  GLuint programID;
};

#endif // SHADER_HPP
