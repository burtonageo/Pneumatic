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

#ifndef PNEU_CORE_FORWARD_HPP
#define PNEU_CORE_FORWARD_HPP

namespace pneu {

namespace core {

/**
 * A strongly-typed Radian value
 *
 * In Pneumatic, angle measurements are strongly typed to
 * ensure that developers know which units they are using.
 *
 * @tparam T Internal numerical representation
 *
 * @note The internal angle type used in Pneumatic is radians.
 *
 */
template<typename T = float>
struct Radians;

/**
 * A strongly-typed Degree value
 *
 * In Pneumatic, angle measurements are strongly typed to
 * ensure that developers know which units they are using.
 *
 * @tparam T Internal numerical representation
 *
 * @note The internal angle type used in Pneumatic is radians.
 *
 */
template<typename T = float>
struct Degrees;

/**
 * A default angle value configurable at compile time. By
 * default, it is set to degrees, but can be overridden by
 * defining the macro constant PNEU_DEFAULT_ANGLE_RADIANS.
 *
 */
#if defined PNEU_DEFAULT_ANGLE_RADIANS

template<typename T = float>
using Angle = typename pneu::core::Radians<T>;

#else

template<typename T = float>
using Angle = typename pneu::core::Degrees<T>;

#endif

/**
 * A result from an operation which may fail
 *
 */
template<typename T>
class FuncResult;

/**
 * An alternative name for a void FuncResult to
 * indicate that this class may be used for methods
 * and functions which mutate state, but do not return
 * a value.
 *
 */
using MethodResult = FuncResult<void>;

} // namespace core

} // namespace pneu

#endif // PNEU_CORE_FORWARD_HPP
