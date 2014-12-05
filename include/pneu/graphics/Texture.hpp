/**
 * This file is part of the pneumatic game engine
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

#pragma once

#ifndef PNEUMATIC_TEXTURE_HPP
#define PNEUMATIC_TEXTURE_HPP

#include <memory>
#include <string>
#include <utility>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#pragma clang diagnostic pop

#include "pneu/core/Forward.hpp"

typedef GLuint TextureId;

namespace pneu {

namespace graphics {

class Shader;

/**
 * Represents a texture resource available on the GPU. Currently
 * only supports textures from files (no procedural textures).
 */
class Texture final {
public:
  /**
   * Constructs an uninitialised texture. To create a GPU texture, call
   * the init() method.
   */
  Texture();

  /**
   * Textures cannot be copied.
   */
  Texture(const Texture& other) = delete;

  /**
   * Deletes the texture from the GPU.
   */
  ~Texture();

  /**
   * Loads a texture from a file. Valid formats are:
   *   - BMP
   *   - PNG
   *   - JPG
   *   - TGA
   *   - DDS
   *   - PSD
   *   - HDR
   *
   * @param file Path to the texture file.
   *
   * @return Whether the load operation was successful.
   */
  auto init(const std::string& file)        -> pneu::core::MethodResult;

  /**
   * Binds a texture so that it is in use on the GPU.
   *
   * @param shader Shader to bind the texture to.
   */
  auto bind(std::shared_ptr<Shader> shader) -> void;

  /**
   * Unbinds a texture.
   */
  auto unbind()                             -> void;

  /**
   * Returns handle to texture object on the GPU.
   */
  auto getObject() const                    -> TextureId {return fObject;}

private:
  TextureId fObject;
};

} // namespace graphics

} // namespace pneu

#endif // PNEUMATIC_TEXTURE_HPP
