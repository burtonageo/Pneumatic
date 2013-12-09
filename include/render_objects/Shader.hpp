/**
 * CSC3223 Graphics for Games
 * Coursework 2
 * Name: George Burton
 * Student Number: 110204567
 * File: Shader.cpp
 */

#pragma once

#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <vector>
#include <GLFW/glfw3.h>

class Shader final {
public:
  Shader(std::string const &vertFile, std::string const &fragFile,
         std::string const &geomFile = "",
         std::string const &tcsFile = "",
         std::string const &tesFile = "");
  ~Shader();
  inline auto GetShaderProgram(void) -> GLuint const {return programID;}
  auto SetDefaultAttributes() -> void;
private:
  friend class Mesh;
  friend class RenderObject;
  static auto CompileShader(GLuint shaderID, const char *sourcePtr,
                            GLint result, int infoLogLength,
                            std::vector<char> errorVec) -> void;
  GLuint programID;
};

#endif // SHADER_HPP
