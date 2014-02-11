/**
 * CSC3223 Graphics for Games
 * Coursework 2
 * Name: George Burton
 * Student Number: 110204567
 * File: Texture.cpp
 */

#include "Texture.hpp"

#include <SOIL.h>

#include "Config.hpp"
#include "Shader.hpp"

Pneumatic::Texture::Texture(std::string fileName)
  :
  fObject(0)
{
  std::string filePath = Config::kImgResDir + fileName;
  glGenTextures(1, &fObject);
  glBindTexture(GL_TEXTURE_2D, fObject);

  int width;
  int height;
  int channels;

  const auto texData = SOIL_load_image(filePath.c_str(),
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
Pneumatic::Texture::Bind(std::shared_ptr<Shader> &shader) -> void
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
