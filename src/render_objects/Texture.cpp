/**
 * CSC3223 Graphics for Games
 * Coursework 2
 * Name: George Burton
 * Student Number: 110204567
 * File: Texture.cpp
 */

#include <cstdlib>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <SOIL.h>

#include "Config.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

Texture::Texture(std::string fileName) :
  _object(0)
{
  std::string filePath = Config::GetImgResDir() + fileName;
  glGenTextures(1, &_object);
  glBindTexture(GL_TEXTURE_2D, _object);

  int width;
  int height;
  int channels;
  
  unsigned char *texData = SOIL_load_image(filePath.c_str(),
                                           &width, &height, &channels, 0);
  if (texData == NULL) {
    glDeleteTextures(1, &_object);
    glBindTexture(GL_TEXTURE_2D, 0);
    return;
  }

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, channels == 4 ? GL_RGBA8 : GL_RGB8,
               width, height, 0, channels == 4 ? GL_RGBA  : GL_RGB,
               GL_UNSIGNED_BYTE, texData);
  glBindTexture(GL_TEXTURE_2D, 0);
  free(texData);
}

Texture::~Texture()
{
  glDeleteTextures(1, &_object);
}

auto
Texture::Bind(Shader *shader) -> void
{
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, _object);
  GLuint sampler = glGetUniformLocation(shader->GetShaderProgram(), "texSampler");
  glUniform1i(sampler, 0);
}

auto
Texture::Unbind(void) -> void
{
  glBindTexture(GL_TEXTURE_2D, 0);
}
