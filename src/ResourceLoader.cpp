/**
 * CSC3223 Graphics for Games
 * Coursework 2
 * Name: George Burton
 * Student Number: 110204567
 * File: ResourceLoader.cpp
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <GLFW/glfw3.h>

#include "Config.hpp"

#include "ResourceLoader.hpp"

// taken from http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/

const GLuint ResourceLoader::LoadAndCompileShaders(std::string shaderName)
{
  
  using namespace std;

  GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

  const string vertShader = Config::GetVertexDir() + shaderName + ".vert_glsl";
  const string fragShader = Config::GetFragmentDir() + shaderName + ".frag_glsl";

  
  string vertexShaderCode;
  ifstream vertexShaderStream(vertShader, ios::in);
  if (vertexShaderStream.is_open()) {
      string Line = "";
      while (getline(vertexShaderStream, Line)) {
        vertexShaderCode += "\n" + Line;
      }
      vertexShaderStream.close();
  }

  
  string fragmentShaderCode;
  ifstream fragmentShaderStream(fragShader, ios::in);
  if (fragmentShaderStream.is_open()) {
      string Line = "";
      while (getline(fragmentShaderStream, Line)) {
        fragmentShaderCode += "\n" + Line;
      }
      fragmentShaderStream.close();
  }

  GLint Result = GL_FALSE;
  int infoLogLength = 0;

  const char *vertexSourcePointer = vertexShaderCode.c_str();
  glShaderSource(vertexShaderID, 1, &vertexSourcePointer , NULL);
  glCompileShader(vertexShaderID);

  glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &Result);
  glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
  vector<char> vertexShaderErrorMessage(infoLogLength);
  glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
  std::cout << std::string(vertexShaderErrorMessage.begin(), vertexShaderErrorMessage.end());

  const char *fragmentSourcePointer = fragmentShaderCode.c_str();
  glShaderSource(fragmentShaderID, 1, &fragmentSourcePointer , NULL);
  glCompileShader(fragmentShaderID);

  glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &Result);
  glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
  vector<char> fragmentShaderErrorMessage(infoLogLength);
  glGetShaderInfoLog(fragmentShaderID, infoLogLength, NULL, &fragmentShaderErrorMessage[0]);

  GLuint programID = glCreateProgram();
  glAttachShader(programID, vertexShaderID);
  glAttachShader(programID, fragmentShaderID);
  glLinkProgram(programID);

  glGetProgramiv(programID, GL_LINK_STATUS, &Result);
  glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
  vector<char> programErrorMessage(max(infoLogLength, int(1)));
  glGetProgramInfoLog(programID, infoLogLength, NULL, &programErrorMessage[0]);

  glDeleteShader(vertexShaderID);
  glDeleteShader(fragmentShaderID);

  return programID;
}

auto
ResourceLoader::LoadTextFile(std::string const &path) -> const std::string
{
  std::string fileContents;
  std::ifstream fileStream(path, std::ios::in);
  if (fileStream.is_open()) {
    std::string line = "";
    while (getline(fileStream, line)) {
        fileContents += "\n" + line;
    }
    fileStream.close();
  }
  return fileContents;
}

const char* ResourceLoader::LoadImage(std::string path)
{
  
}
