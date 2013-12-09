/**
 * CSC3223 Graphics for Games
 * Coursework 2
 * Name: George Burton
 * Student Number: 110204567
 * File: Shader.cpp
 */

#include <iostream>
#include <string>
#include <vector>
  
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.hpp"
#include "ResourceLoader.hpp"
#include "Config.hpp"

#define MAYBE_CREATE_SHADER_ID(file, shaderType) { \
  file != "" ? \
    glCreateShader(shaderType) : \
    0}
#define MAYBE_CREATE_SHADER_PATH(dir, file, ext) { \
  file != "" ? \
    dir + file + ext : \
    ""}
#define MAYBE_ATTATCH_SHADER(shaderID) { \
  if (shaderID != 0) { \
    glAttachShader(programID, shaderID); \
  }}
#define MAYBE_DELETE_SHADER(shaderID) { \
if (shaderID != 0) { \
  glDeleteShader(shaderID); \
}}
Shader::Shader(std::string const &vertFile, std::string const &fragFile,
               std::string const &geomFile, std::string const &tcsFile,
               std::string const &tesFile)
{
  /*
  GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

  GLuint geometryShaderID = MAYBE_CREATE_SHADER_ID(geomFile, GL_GEOMETRY_SHADER);
  GLuint tessControlShaderID = MAYBE_CREATE_SHADER_ID(tcsFile, GL_TESS_CONTROL_SHADER);
  GLuint tessellationShaderID = MAYBE_CREATE_SHADER_ID(tesFile, GL_TESS_EVALUATION_SHADER);

  const std::string vertShaderPath = Config::GetVertexDir() + vertFile + ".vert_glsl";
  const std::string fragShaderPath = Config::GetFragmentDir() + fragFile + ".frag_glsl";
  const std::string geomShaderPath = MAYBE_CREATE_SHADER_PATH(Config::GetGeometryDir(),
                                                              geomFile,
                                                              ".geom_glsl");

  const std::string tctrlShaderPath = MAYBE_CREATE_SHADER_PATH(Config::GetTessCtrlDir(),
                                                               tcsFile,
                                                               ".tcs_glsl");

  const std::string tevalShaderPath = MAYBE_CREATE_SHADER_PATH(Config::GetTessEvalDir(),
                                                               tesFile,
                                                               ".tes_glsl");
  auto vertShaderCode = ResourceLoader::LoadTextFile(vertShaderPath);
  auto fragShaderCode = ResourceLoader::LoadTextFile(fragShaderPath);
  auto geomShaderCode = ResourceLoader::LoadTextFile(geomShaderPath);
  auto tctrlShaderCode = ResourceLoader::LoadTextFile(tctrlShaderPath);
  auto tevalShaderCode = ResourceLoader::LoadTextFile(tevalShaderPath);

  GLint result = GL_FALSE;
  int infoLogLength = 0;

  const char *vertexSourcePointer = vertShaderCode.c_str();
  std::vector<char> vertexShaderErrorMessage;
  CompileShader(vertexShaderID, vertexSourcePointer, result, infoLogLength,
                vertexShaderErrorMessage);

  const char *fragSourcePointer = fragShaderCode.c_str();
  std::vector<char> fragmentShaderErrorMessage;
  CompileShader(fragmentShaderID, fragSourcePointer, result, infoLogLength,
                fragmentShaderErrorMessage);

  if (geomShaderCode != "") {
    const char *geomSourcePointer = fragShaderCode.c_str();
    std::vector<char> geometryShaderErrorMessage;
    CompileShader(geometryShaderID, geomSourcePointer, result, infoLogLength,
                  geometryShaderErrorMessage);
  }

  if (tctrlShaderCode != "") {
    const char *tctrlSourcePointer = tctrlShaderCode.c_str();
    std::vector<char> tessControlShaderErrorMessage;
    CompileShader(tessControlShaderID, tctrlSourcePointer, result, infoLogLength,
                  tessControlShaderErrorMessage);
  }

  if (tevalShaderCode != "") {
    const char *tevalSourcePointer = tctrlShaderCode.c_str();
    std::vector<char> tessControlShaderErrorMessage;
    CompileShader(tessControlShaderID, tevalSourcePointer, result, infoLogLength,
                  tessControlShaderErrorMessage);
  }

  programID = glCreateProgram();
  glAttachShader(programID, vertexShaderID);
  glAttachShader(programID, fragmentShaderID);
  MAYBE_ATTATCH_SHADER(geometryShaderID);
  MAYBE_ATTATCH_SHADER(tessControlShaderID);
  MAYBE_ATTATCH_SHADER(tessellationShaderID);
  
  glLinkProgram(programID);

  glGetProgramiv(programID, GL_LINK_STATUS, &result);
  glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
  std::vector<char> programErrorMessage(std::max(infoLogLength, int(1)));
  glGetProgramInfoLog(programID, infoLogLength, NULL, &programErrorMessage[0]);
  std::cout << std::string(programErrorMessage.begin(), programErrorMessage.end());

  glDeleteShader(vertexShaderID);
  glDeleteShader(fragmentShaderID);
  MAYBE_DELETE_SHADER(geometryShaderID);
  MAYBE_DELETE_SHADER(tessControlShaderID);
  MAYBE_DELETE_SHADER(tessellationShaderID);
  */
  programID = ResourceLoader::LoadAndCompileShaders("tri");
}

Shader::~Shader()
{
  glDeleteProgram(programID);
}

auto
Shader::SetDefaultAttributes() -> void
{
  
}

auto
Shader::CompileShader(GLuint shaderID, const char *sourcePtr,
                   GLint result, int infoLogLength,
                   std::vector<char> errorVec) -> void
{
  glShaderSource(shaderID, 1, &sourcePtr , NULL);
  glCompileShader(shaderID);

  glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
  glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
  errorVec = std::vector<char>(infoLogLength);
  glGetShaderInfoLog(shaderID, infoLogLength, NULL, &errorVec[0]);
  std::cout << std::string(errorVec.begin(), errorVec.end());
}
