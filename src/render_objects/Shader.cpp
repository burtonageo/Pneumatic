/**
 * CSC3223 Graphics for Games
 * Coursework 2
 * Name: George Burton
 * Student Number: 110204567
 * File: Shader.cpp
 */

#include "Shader.hpp"

#include <iostream>
#include <string>
#include <vector>
  
#include <GL/glew.h>
#include <GLFW/glfw3.h>

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
#define MAYBE_ATTATCH_SHADER(fProgramID, shaderID) { \
  if (shaderID != 0) { \
    glAttachShader(fProgramID, shaderID); \
  }}
#define MAYBE_DELETE_SHADER(shaderID) { \
  if (shaderID != 0) { \
    glDeleteShader(shaderID); \
  }}
Pneumatic::Shader::Shader(std::string const &vertFile, std::string const &fragFile,
                          std::string const &geomFile, std::string const &tcsFile,
                          std::string const &tesFile)
  :
  fProgramID(0)
{
  GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

  GLuint geometryShaderID = MAYBE_CREATE_SHADER_ID(geomFile, GL_GEOMETRY_SHADER);
  GLuint tessControlShaderID = MAYBE_CREATE_SHADER_ID(tcsFile, GL_TESS_CONTROL_SHADER);
  GLuint tessellationShaderID = MAYBE_CREATE_SHADER_ID(tesFile, GL_TESS_EVALUATION_SHADER);

  const std::string vertFileExt = ".vert_glsl";
  const std::string fragFileExt = ".frag_glsl";
  const std::string geomFileExt = ".geom_glsl";
  const std::string tcsFileExt = ".tcs_glsl";
  const std::string tesFileExt = ".tes_glsl";

  const std::string vertShaderPath = Config::GetVertexDir() + vertFile + vertFileExt;
  const std::string fragShaderPath = Config::GetFragmentDir() + fragFile + fragFileExt;
  const std::string geomShaderPath = MAYBE_CREATE_SHADER_PATH(Config::GetGeometryDir(),
                                                              geomFile,
                                                              geomFileExt);

  const std::string tctrlShaderPath = MAYBE_CREATE_SHADER_PATH(Config::GetTessCtrlDir(),
                                                               tcsFile,
                                                               tcsFileExt);

  const std::string tevalShaderPath = MAYBE_CREATE_SHADER_PATH(Config::GetTessEvalDir(),
                                                               tesFile,
                                                               tesFileExt);
  auto vertShaderCode = ResourceLoader::LoadTextFile(vertShaderPath);
  auto fragShaderCode = ResourceLoader::LoadTextFile(fragShaderPath);
  auto geomShaderCode = ResourceLoader::LoadTextFile(geomShaderPath);
  auto tctrlShaderCode = ResourceLoader::LoadTextFile(tctrlShaderPath);
  auto tevalShaderCode = ResourceLoader::LoadTextFile(tevalShaderPath);

  GLint result = GL_FALSE;
  int infoLogLength = 0;

  const char *vertexSourcePointer = vertShaderCode.c_str();
  std::vector<char> vertexShaderErrorMessage;
  _CompileShader(vertexShaderID, vertexSourcePointer, result, infoLogLength,
                 vertexShaderErrorMessage);

  const char *fragSourcePointer = fragShaderCode.c_str();
  std::vector<char> fragmentShaderErrorMessage;
  _CompileShader(fragmentShaderID, fragSourcePointer, result, infoLogLength,
                 fragmentShaderErrorMessage);

  if (geomShaderCode != "") {
    const char *geomSourcePointer = geomShaderCode.c_str();
    std::vector<char> geometryShaderErrorMessage;
    _CompileShader(geometryShaderID, geomSourcePointer, result, infoLogLength,
                   geometryShaderErrorMessage);
  }

  if (tctrlShaderCode != "") {
    const char *tctrlSourcePointer = tctrlShaderCode.c_str();
    std::vector<char> tessControlShaderErrorMessage;
    _CompileShader(tessControlShaderID, tctrlSourcePointer, result, infoLogLength,
                   tessControlShaderErrorMessage);
  }

  if (tevalShaderCode != "") {
    const char *tevalSourcePointer = tctrlShaderCode.c_str();
    std::vector<char> tessControlShaderErrorMessage;
    _CompileShader(tessControlShaderID, tevalSourcePointer, result, infoLogLength,
                   tessControlShaderErrorMessage);
  }

  fProgramID = glCreateProgram();
  glAttachShader(fProgramID, vertexShaderID);
  glAttachShader(fProgramID, fragmentShaderID);
  MAYBE_ATTATCH_SHADER(fProgramID, geometryShaderID);
  MAYBE_ATTATCH_SHADER(fProgramID, tessControlShaderID);
  MAYBE_ATTATCH_SHADER(fProgramID, tessellationShaderID);
  
  glLinkProgram(fProgramID);

  glGetProgramiv(fProgramID, GL_LINK_STATUS, &result);
  glGetProgramiv(fProgramID, GL_INFO_LOG_LENGTH, &infoLogLength);
  std::vector<char> programErrorMessage(std::max(infoLogLength, int(1)));
  glGetProgramInfoLog(fProgramID, infoLogLength, NULL, &programErrorMessage[0]);
  std::cout << std::string(programErrorMessage.begin(), programErrorMessage.end());

  glDeleteShader(vertexShaderID);
  glDeleteShader(fragmentShaderID);
  MAYBE_DELETE_SHADER(geometryShaderID);
  MAYBE_DELETE_SHADER(tessControlShaderID);
  MAYBE_DELETE_SHADER(tessellationShaderID);
  _SetDefaultAttributes();
}

Pneumatic::Shader::~Shader()
{
  glDeleteProgram(fProgramID);
}

auto
Pneumatic::Shader::_SetDefaultAttributes() -> void
{
  const GLuint VERTEX_BUFFER = 0;
  const GLuint COLOR_BUFFER = 1;
  const GLuint TEXTURE_BUFFER = 2;
  const GLuint NORMALS_BUFFER = 3;
  glBindAttribLocation(fProgramID, VERTEX_BUFFER,  "position");
  glBindAttribLocation(fProgramID, COLOR_BUFFER,   "color");
  glBindAttribLocation(fProgramID, TEXTURE_BUFFER, "texCoord");
  glBindAttribLocation(fProgramID, NORMALS_BUFFER, "normal");
}

auto
Pneumatic::Shader::_CompileShader(GLuint shaderID, const char *sourcePtr,
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
