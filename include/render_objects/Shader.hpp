/**
 * CSC3223 Graphics for Games
 * Coursework 2
 * Name: George Burton
 * Student Number: 110204567
 * File: Shader.hdpp
 */

#pragma once

#ifndef PNEUMATIC_SHADER_HPP
#define PNEUMATIC_SHADER_HPP

#include <string>
#include <vector>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace Pneumatic {
  namespace ___hidden___ {
    class ShaderUpdateMixin;
  }

  class Shader {
  public:
    Shader(std::string const &vertFile, std::string const &fragFile,
           std::string const &geomFile = "",
           std::string const &tcsFile = "",
           std::string const &tesFile = "");
    Shader(Shader const &);
    ~Shader();

    inline auto GetShaderProgram(void) const -> GLuint {return fProgramID;}
    auto Update(double ms)                   -> void;
  private:
    class Mesh;
    class RenderObject;

    friend class Mesh;
    friend class RenderObject;
    friend class ___hidden___::ShaderUpdateMixin;

    static auto _CompileShader(GLuint shaderID, const char *sourcePtr,
                              GLint result, int infoLogLength,
                              std::vector<char> errorVec)             -> void;
    auto _SetDefaultAttributes()                                      -> void;

    GLuint fProgramID;
  };
}
#endif // PNEUMATIC_SHADER_HPP
