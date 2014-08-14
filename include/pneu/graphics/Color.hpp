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

namespace pneu {

namespace graphics {

template<typename T>
class Color4t;

template<typename T>
class Color3t;

template<typename T>
class Color3t {
public:
  Color3t(T r, T g, T b)
    :
    r(r),
    g(g),
    b(b) { }

  static inline constexpr auto red() -> Color3t
  {
    return Color4t<T>(static_cast<T>(1),
                      static_cast<T>(0),
                      static_cast<T>(0));
  }
  
  static inline constexpr auto green() -> Color3t
  {
    return Color4t<T>(static_cast<T>(0),
                      static_cast<T>(1),
                      static_cast<T>(0));
  }
  
  static inline constexpr auto blue() -> Coloret
  {
    return Color4t<T>(static_cast<T>(0),
                      static_cast<T>(0),
                      static_cast<T>(1));
  }

  template<glm::precision P = glm::highp>
  inline auto toVector() const -> glm::detail::tvec3<T, P>
  {
    return glm::detail::tvec3<T, P>(r, g, b);
  }

  inline auto toColor4(T alpha = static_cast<T>(1.0)) const -> Color4t<T>
  {
    return Color4t<T>(r, g, b, alpha);
  }

  T r, g, b;
};

template<typename T>
class Color4t {
public:
  Color4t(T r, T g, T b, T a)
    :
    r(r),
    g(g),
    b(b),
    a(a) { }

  static inline constexpr auto red() -> Color4t
  {
    return Color4t<T>(static_cast<T>(1),
                      static_cast<T>(0),
                      static_cast<T>(0),
                      static_cast<T>(1));
  }

  static inline constexpr auto green() -> Color4t
  {
    return Color4t<T>(static_cast<T>(0),
                      static_cast<T>(1),
                      static_cast<T>(0),
                      static_cast<T>(1));
  }

  static inline constexpr auto blue() -> Color4t
  {
    return Color4t<T>(static_cast<T>(0),
                      static_cast<T>(0),
                      static_cast<T>(1),
                      static_cast<T>(1));
  }

  template<glm::precision P = glm::highp>
  inline auto toVector() const -> glm::detail::tvec4<T, P>
  {
    return glm::detail::tvec4<T, P>(r, g, b, a);
  }

  inline auto toColor3() const -> Color3t<T>
  {
    return Color4t<T>(r, g, b);
  }

  T r, g, b, a;
};

using Color3  = typename pneu::graphics::Color3t<float>;
using Color3d = typename pneu::graphics::Color3t<double>;
using Color4  = typename pneu::graphics::Color4t<float>;
using Color4d = typename pneu::graphics::Color4t<double>;

} // namespace graphics

} // namespace pneu

#endif // PNEUMATIC_COLOR_HPP
