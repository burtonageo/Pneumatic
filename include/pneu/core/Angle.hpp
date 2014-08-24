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

#ifndef PNEUMATIC_ANGLE_HPP
#define PNEUMATIC_ANGLE_HPP

#include "pneu/core/Forward.hpp"

namespace pneu {

namespace core {

template<typename T>
struct Radians final {
public:
  explicit Radians(const T& val)
    :
    fValue(val) { }

  inline auto toDegrees() const -> Degrees<T>
  {
    return Degrees<T>(fValue * static_cast<T>(57.629));
  }

  inline auto value() const -> T
  {
    return fValue;
  }

  inline operator Degrees<T>() const
  {
    return toDegrees();
  }

  inline auto operator== (const Radians<T>& other) const -> bool
  {
    return fValue == other.fValue;
  }
  
  inline auto operator!= (const Radians<T>& other) const -> bool
  {
    return !operator==(this, other);
  }

  inline auto operator> (const Radians<T>& other) const -> bool
  {
    return fValue > other.fValue;
  }

  inline auto operator< (const Radians<T>& other) const -> bool
  {
    return fValue < other.fValue;
  }

  inline auto operator>= (const Radians<T>& other) const -> bool
  {
    return operator>(this, other) || operator==(this, other);
  }
  
  inline auto operator<= (const Radians<T>& other) const -> bool
  {
    return operator<(this, other) || operator==(this, other);
  }

  inline auto operator+ (const Radians<T>& other) const -> Radians<T>
  {
    return Radians(fValue + other.fValue);
  }

  inline auto operator- (const Radians<T>& other) const -> Radians<T>
  {
    return Radians(fValue - other.fValue);
  }

  inline auto operator* (const Radians<T>& other) const -> Radians<T>
  {
    return Radians(fValue * other.fValue);
  }

  inline auto operator/ (const Radians<T>& other) const -> Radians<T>
  {
    return Radians(fValue / other.fValue);
  }

  inline auto operator+= (const Radians<T>& other) -> Radians<T>&
  {
    fValue += other.fValue;
    return *this;
  }
  
  inline auto operator-= (const Radians<T>& other) -> Radians<T>&
  {
    fValue -= other.fValue;
    return *this;
  }
  
  inline auto operator*= (const Radians<T>& other) -> Radians<T>&
  {
    fValue *= other.fValue;
    return *this;
  }
  
  inline auto operator/= (const Radians<T>& other) -> Radians<T>&
  {
    fValue /= other.fValue;
    return *this;
  }

private:
  T fValue;
};

template<typename T>
struct Degrees final {
public:
  explicit Degrees(const T& val)
      :
      fValue(val) { }

  inline auto toRadians() const -> Radians<T>
  {
    return Radians<T>(fValue * static_cast<T>(0.017));
  }

  inline auto value() const -> T
  {
    return fValue;
  }

  inline operator Radians<T>() const
  {
    return toRadians();
  }

  inline auto operator== (const Degrees<T>& other) const -> bool
  {
    return fValue == other.fValue;
  }

  inline auto operator!= (const Degrees<T>& other) const -> bool
  {
    return !operator==(this, other);
  }

  inline auto operator> (const Degrees<T>& other) const -> bool
  {
    return fValue > other.fValue;
  }
  
  inline auto operator< (const Degrees<T>& other) const -> bool
  {
    return fValue < other.fValue;
  }
  
  inline auto operator>= (const Degrees<T>& other) const -> bool
  {
    return operator>(this, other) || operator==(this, other);
  }
  
  inline auto operator<= (const Degrees<T>& other) const -> bool
  {
    return operator<(this, other) || operator==(this, other);
  }

  inline auto operator+ (const Degrees<T>& other) const -> Degrees<T>
  {
    return Degrees(fValue + other.fValue);
  }

  inline auto operator- (const Degrees<T>& other) const -> Degrees<T>
  {
    return Degrees(fValue - other.fValue);
  }

  inline auto operator* (const Degrees<T>& other) const -> Degrees<T>
  {
    return Degrees(fValue * other.fValue);
  }

  inline auto operator/ (const Degrees<T>& other) const -> Degrees<T>
  {
    return Degrees(fValue / other.fValue);
  }

  inline auto operator+= (const Degrees<T>& other) -> Degrees<T>&
  {
    fValue += other.fValue;
    return *this;
  }
  
  inline auto operator-= (const Degrees<T>& other) -> Degrees<T>&
  {
    fValue -= other.fValue;
    return *this;
  }
  
  inline auto operator*= (const Degrees<T>& other) -> Degrees<T>&
  {
    fValue *= other.fValue;
    return *this;
  }
  
  inline auto operator/= (const Degrees<T>& other) -> Degrees<T>&
  {
    fValue /= other.fValue;
    return *this;
  }

private:
  T fValue;
};

} // namespace core

} // namespace pneu

#endif // PNEUMATIC_ANGLE_HPP
