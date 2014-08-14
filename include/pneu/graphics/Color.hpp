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

#ifndef PNEUMATIC_COLOR_HPP
#define PNEUMATIC_COLOR_HPP

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

template<typename T>
class Color4t;

template<typename T>
class Color3t {
public:
  Color3t(T r, T g, T b)
    :
    r(r),
    g(g),
    b(b) { }

  auto toVector() -> glm::tvec3
  {
    return glm::tvec3<T>(r, g, b);
  }

  auto toColor4(T alpha = static_cast<T>(1.0)) const -> Color4t;

  T r, g, b;
}

template<typename T>
class Color4t {
public:
  Color4t(T r, T g, T b, T a)
    :
    r(r),
    g(g),
    b(b),
    a(a) { }

  auto toVector() const -> glm::tvec4<T>
  {
    return glm::tvec4<T>(r, g, b, a);
  }

  auto toColor3() const -> Color3t;

  T r, g, b, a;
};

template<typename T>
auto
pneu::graphics::Color3::toColor4(T alpha) const -> Color4t
{
  return Color4t<T>(fColVec.r, fColVec.g, fColVec.b, alpha);
}

template<typename T>
auto
pneu::graphics::Color4::toColor3() const -> Color3t
{
  return Color4t<T>(fColVec.r, fColVec.g, fColVec.b);
}

typedef Color3  Color3t<float>;
typedef Color3d Color3t<double>;
typedef Color4  Color4t<float>;
typedef Color4d Color4t<double>;

#endif // PNEUMATIC_COLOR_HPP
