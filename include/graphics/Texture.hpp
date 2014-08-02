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

#include "core/MethResult.hpp"

namespace Pneumatic {

namespace Graphics {

class Shader;

class Texture final {
public:
  Texture(void);
  Texture(const Texture& other) = delete;
  ~Texture(void);

  auto init(const std::string& file)        -> Pneumatic::Core::MethResult;

  auto bind(std::shared_ptr<Shader> shader) -> void;
  auto unbind(void)                         -> void;
  inline auto getObject(void) const         -> GLuint {return fObject;}

private:
  GLuint fObject;
};

} // namespace Graphics

} // namespace Pneumatic

#endif // PNEUMATIC_TEXTURE_HPP
