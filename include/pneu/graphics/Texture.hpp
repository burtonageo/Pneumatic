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

#define GLEW_STATIC
#include <GL/glew.h>

#define GLFW_INCLUDE_GL3
#define GLFW_NO_GLU
#include <GLFW/glfw3.h>

#include "pneu/core/MethodResult.hpp"

typedef GLuint TextureId;

namespace pneu {

namespace graphics {

class Shader;

class Texture final {
public:
  Texture();
  Texture(const Texture& other) = delete;
  ~Texture();

  auto init(const std::string& file)        -> pneu::core::MethodResult;

  auto bind(std::shared_ptr<Shader> shader) -> void;
  auto unbind()                             -> void;
  inline auto getObject() const             -> TextureId {return fObject;}

private:
  TextureId fObject;
};

} // namespace graphics

} // namespace pneu

#endif // PNEUMATIC_TEXTURE_HPP
