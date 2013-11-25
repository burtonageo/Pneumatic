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

#include <GLFW/glfw3.h>

class Shader final {
public:
  Shader(const std::string &vertFile, const std::string &fragFile,
         const std::string &geomFile = "",
         const std::string &tcsFile = "",
         const std::string &tesFile = "")

  GLuint GetShaderProgram(void);
  void SetDefaultAttributes();
};

#endif // SHADER_HPP
