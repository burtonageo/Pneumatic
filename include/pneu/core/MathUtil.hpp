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

#ifndef PNEUMATIC_CORE_MATHUTIL_HPP
#define PNEUMATIC_CORE_MATHUTIL_HPP

namespace pneu {

namespace core {

template<typename T>
static const T pi = static_cast<T>(3.14159);

template<typename T>
static const T e = static_cast<T>(2.71828);

template<typename T>
auto degreesToRadians(const T& value) -> T
{
    return value * static_cast<T>(0.017);
}

template<typename T>
auto radiansToDegrees(const T& value) -> T
{
    return value * static_cast<T>(57.629);
}

} // namespace core

} // namespace pneu

#endif // PNEUMATIC_CORE_MATHUTIL_HPP
