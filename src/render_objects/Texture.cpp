/**
 * CSC3223 Graphics for Games
 * Coursework 2
 * Name: George Burton
 * Student Number: 110204567
 * File: Texture.cpp
 */

#include <cstdlib>
#include <string>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <SOIL.h>

#include "Config.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

Pneumatic::Texture::Texture(std::string fileName)
  :
  fObject(0)
{
  std::string filePath = Config::GetImgResDir() + fileName;
  glGenTextures(1, &fObject);
  glBindTexture(GL_TEXTURE_2D, fObject);

  int width;
  int height;
  int channels;
  
  unsigned char *texData = SOIL_load_image(filePath.c_str(),
                                           &width, &height, &channels, 0);
  if (texData == NULL) {
    glDeleteTextures(1, &fObject);
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
  SOIL_free_image_data(texData);
}

Pneumatic::Texture::~Texture()
{
  glDeleteTextures(1, &fObject);
}

auto
Pneumatic::Texture::Bind(Shader *shader) -> void
{
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, fObject);
  GLuint sampler = glGetUniformLocation(shader->GetShaderProgram(), "texSampler");
  glUniform1i(sampler, 0);
}

auto
Pneumatic::Texture::Unbind(void) -> void
{
  glBindTexture(GL_TEXTURE_2D, 0);
}
