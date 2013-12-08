/**
 * CSC3223 Graphics for Games
 * Coursework 2
 * Name: George Burton
 * Student Number: 110204567
 * File: Shader.cpp
 */

#include <GLFW/glfw3.h>

#include "Shader.h"

Shader::Shader(const std::string &vertFile, const std::string &fragFile,
               const std::string &geomFile, const std::string &tcsFile,
               const std::string &tesFile)
{
  GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

  GLuint geometryShaderID = geomFile != "" ?
                                glCreateShader(GL_GEOMETRY_SHADER) :
                                NULL;
  GLuint tessellationShaderID = tesFile != "" ?
                                glCreateShader(GL_TESSELLATION_SHADER) :
                                NULL;
    
  const string vertShader = Config::GetVertexDir() + shaderName + ".vert_glsl";
}

GLuint
Shader::GetShaderProgram(void)
{
  
}

void
Shader::SetDefaultAttributes()
{
  
}
