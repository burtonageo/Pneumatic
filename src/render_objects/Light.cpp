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

#include "Light.hpp"

Pneumatic::Graphics::Light::Light(const glm::vec3& position,
                                  const glm::vec4& color,
                                  float radius)
  :
  fPosition(position),
  fColor(color),
  fRadius(radius)
{

}

Pneumatic::Graphics::Light::Light(const Light& other)
  :
  fPosition(other.fPosition),
  fColor(other.fColor),
  fRadius(other.fRadius)
{

}

Pneumatic::Graphics::Light::~Light() = default;

auto
Pneumatic::Graphics::Light::getPosition() const -> glm::vec3
{
  return fPosition;
}

auto
Pneumatic::Graphics::Light::setPosition(const glm::vec3& new_pos) -> void
{
  fPosition = new_pos;
}

auto
Pneumatic::Graphics::Light::getColor() const -> glm::vec4
{
  return fColor;
}

auto
Pneumatic::Graphics::Light::setColor(const glm::vec4& new_col) -> void
{
  fColor = new_col;
}

auto
Pneumatic::Graphics::Light::getRadius() const -> float
{
  return fRadius;
}

auto
Pneumatic::Graphics::Light::setRadius(float new_radius) -> void
{
  fRadius = new_radius;
}
