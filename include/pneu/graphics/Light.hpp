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

#ifndef PNEUMATIC_LIGHT_HPP
#define PNEUMATIC_LIGHT_HPP

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

namespace pneu {

namespace graphics {

struct Light final {
public:
  Light(const glm::vec3& position,
        const glm::vec4& color,
        float radius);
  Light(const Light& other);
  ~Light(void);

  auto getPosition(void) const               -> glm::vec3;
  auto setPosition(const glm::vec3& new_pos) -> void;

  auto getColor(void) const                  -> glm::vec4;
  auto setColor(const glm::vec4& new_col)    -> void;

  auto getRadius(void) const                 -> float;
  auto setRadius(float new_radius)           -> void;

private:
  glm::vec3 fPosition;
  glm::vec4 fColor;
  float fRadius;
};

} // namespace graphics

} // namespace pneu

#endif // PNEUMATIC_LIGHT_HPP