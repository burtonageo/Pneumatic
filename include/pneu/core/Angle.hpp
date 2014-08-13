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

template<typename T>
struct Radians;

template<typename T>
struct Degrees;

template<typename T>
struct Radians {
public:
  explicit Radians(const T& val)
    :
    fValue(val) { }

  inline auto toDegrees() -> Degrees<T>
  {
    return Degrees<T>(fValue * static_cast<T>(57.629));
  }

  inline auto value() -> T
  {
    return fValue;
  }

  auto operator+ (const Radians<T>& other) -> Radians<T>
  {
    return Radians(value + other.value);
  }

  auto operator- (const Radians<T>& other) -> Radians<T>
  {
    return Radians(value - other.value);
  }

  auto operator* (const Radians<T>& other) -> Radians<T>
  {
    return Radians(value * other.value);
  }

  auto operator/ (const Radians<T>& other) -> Radians<T>
  {
    return Radians(value / other.value);
  }


private:
  T fValue;
};

template<typename T>
struct Degrees {
public:
  explicit Degrees(const T& val)
      :
      fValue(val) { }

  inline auto toRadians() -> Radians<T>
  {
    return Radians<T>(fValue * static_cast<T>(0.017));
  }

  inline auto value() -> T
  {
    return fValue;
  }

  auto operator+ (const Degrees<T>& other) -> Degrees<T>
  {
    return Degrees(value + other.value);
  }

  auto operator- (const Degrees<T>& other) -> Degrees<T>
  {
    return Degrees(value - other.value);
  }

  auto operator* (const Degrees<T>& other) -> Degrees<T>
  {
    return Degrees(value * other.value);
  }

  auto operator/ (const Degrees<T>& other) -> Degrees<T>
  {
    return Degrees(value / other.value);
  }

private:
  T fValue;
};

#endif // PNEUMATIC_ANGLE_HPP
