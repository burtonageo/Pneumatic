/**
 * This file is part of the pneu game engine
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

#ifndef PNEUMATIC_SHAPE_HPP
#define PNEUMATIC_SHAPE_HPP

#include "pneu/graphics/RenderObject.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_CXX11
#include <glm/glm.hpp>

namespace pneu {

namespace graphics {

class Shape final : public pneu::graphics::RenderObject {
public:
  static auto generateRect(const glm::vec2& position     = glm::vec2(0.0f, 0.0f),
                           const glm::vec2& scale        = glm::vec2(1.0f, 1.0f)  -> Shape;
  static auto generateTri(const glm::vec2& position      = glm::vec2(0.0f, 0.0f),
                          const glm::vec2& scale         = glm::vec2(1.0f, 1.0f)  -> Shape;
  static auto generateEllipse(const glm::vec2& position  = glm::vec2(0.0f, 0.0f),
                              const glm::vec2& scale     = glm::vec2(1.0f, 1.0f)  -> Shape;

private:

}

} // namespace graphics

} // namespace pneu

#endif // PNEUMATIC_SHAPE_HPP
