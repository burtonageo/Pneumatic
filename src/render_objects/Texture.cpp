/**
 * This file is part of the Pneumatic game engine
 *
 * Copyright (c) 2014 George Burton
 *
 * THIS SOFTWARE IS PROVIDED 'AS-IS', WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTY. IN NO EVENT WILL THE AUTHORS BE HELD LIABLE FOR ANY DAMAGES
 * ARISING FROM THE USE OF THIS SOFTWARE.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *    1. The origin of this software must not be misrepresented; you must not
 *       claim that you wrote the original software. If you use this software
 *       in a product, an acknowledgment in the product documentation would be
 *       appreciated but is not required.
 *
 *    2. Altered source versions must be plainly marked as such, and must not be
 *       misrepresented as being the original software.
 *
 *    3. This notice may not be removed or altered from any source
 *       distribution.
 *
 **/

#include "Texture.hpp"

#include <SOIL.h>

#include "Shader.hpp"

using namespace std;
using namespace Pneumatic::Core;

Pneumatic::Graphics::Texture::Texture()
  :
  fObject(0)
{

}

Pneumatic::Graphics::Texture::~Texture()
{
  glDeleteTextures(1, &fObject);
}

auto
Pneumatic::Graphics::Texture::init(const std::string& file_name) -> Pneumatic::Core::MethResult
{
  const std::string k_file_path = file_name;
  int width, height, channels;

  unsigned char* tex_data = SOIL_load_image(k_file_path.c_str(),
                                            &width, &height, &channels, 0);
  if (tex_data == NULL) {
    return MethResult::error(string("Could not load texture data from file: ")
                               .append(k_file_path));
  }

  glGenTextures(1, &fObject);
  glBindTexture(GL_TEXTURE_2D, fObject);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, channels == 4 ? GL_RGBA8 : GL_RGB8,
               width, height, 0, channels == 4 ? GL_RGBA  : GL_RGB,
               GL_UNSIGNED_BYTE, tex_data);

  glBindTexture(GL_TEXTURE_2D, 0);
  SOIL_free_image_data(tex_data);

  return MethResult::ok();
}

auto
Pneumatic::Graphics::Texture::bind(std::shared_ptr<Shader> shader) -> void
{
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, fObject);
  GLuint sampler = glGetUniformLocation(shader->getShaderProgram(), "texSampler");
  glUniform1i(sampler, 0);
}

auto
Pneumatic::Graphics::Texture::unbind() -> void
{
  glBindTexture(GL_TEXTURE_2D, 0);
}
