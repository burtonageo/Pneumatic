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

#ifndef PNEUMATIC_CORE_ANGLE_HPP
#define PNEUMATIC_CORE_ANGLE_HPP

#include "pneu/core/Forward.hpp"

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
template<typename T>
struct Radians final {
public:
    /**
     * Constructor
     *
     */
    explicit Radians(const T& val)
        :
        fValue(val) { }

    /**
     * Converts this radian value to degrees
     *
     * @return Value in degrees. This is calculated
     *                 by (current value * 57.629)
     *
     */
    auto toDegrees() const -> Degrees<T>
    {
        return Degrees<T>(fValue * static_cast<T>(57.629));
    }

    /**
     * Unwrap the underlying numerical value
     *
     * @return The current value of this radians struct.
     *
     */
    auto value() const -> T
    {
        return fValue;
    }

    /**
     * Implicit conversion operator to degrees.
     *
     */
    operator Degrees<T>() const
    {
        return toDegrees();
    }

    /**
     * Equality test between two radians. Returns true if the
     * two values are equal numerically.
     *
     * @param other Rhs of operator.
     *
     * @return rhs.value() == lhs.value().
     *
     */
    auto operator== (const Radians<T>& other) const -> bool
    {
        return fValue == other.fValue;
    }

    /**
     * Inequality test between two radians. Returns inverse of
     * operator==.
     *
     * @param other Rhs of operator.
     *
     * @return rhs.value() != lhs.value().
     *
     */
    auto operator!= (const Radians<T>& other) const -> bool
    {
        return !operator==(this, other);
    }

    /**
     * Greater than test between two radians.
     *
     * @param other Rhs of operator.
     *
     * @return rhs.value() > lhs.value().
     *
     */
    auto operator> (const Radians<T>& other) const -> bool
    {
        return fValue > other.fValue;
    }

    /**
     * Less than test between two radians.
     *
     * @param other Rhs of operator.
     *
     * @return rhs.value() < lhs.value().
     *
     */
    auto operator< (const Radians<T>& other) const -> bool
    {
        return fValue < other.fValue;
    }

    /**
     * Greater than or equal test between two radians.
     *
     * @param other Rhs of operator.
     *
     * @return rhs.value() >= lhs.value()
     *
     */
    auto operator>= (const Radians<T>& other) const -> bool
    {
        return operator>(this, other) || operator==(this, other);
    }

    /**
     * Less than or equal test between two radians.
     *
     * @param other Rhs of operator.
     *
     * @return rhs.value() <= lhs.value()
     *
     */
    auto operator<= (const Radians<T>& other) const -> bool
    {
        return operator<(this, other) || operator==(this, other);
    }

    /**
     * Plus operator on two radians.
     *
     * @param other Rhs of operator.
     *
     * @return rhs.value() + lhs.value().
     *
     */
    auto operator+ (const Radians<T>& other) const -> Radians<T>
    {
        return Radians(fValue + other.fValue);
    }

    /**
     * Minus operator on two radians.
     *
     * @param other Rhs of operator.
     *
     * @return rhs.value() - lhs.value().
     *
     */
    auto operator- (const Radians<T>& other) const -> Radians<T>
    {
        return Radians(fValue - other.fValue);
    }

    /**
     * Multiplication operator on two radians.
     *
     * @param other Rhs of operator.
     *
     * @return rhs.value() * lhs.value().
     *
     */
    auto operator* (const Radians<T>& other) const -> Radians<T>
    {
        return Radians(fValue * other.fValue);
    }

    /**
     * Division operator on two radians.
     *
     * @param other Rhs of operator.
     *
     * @return rhs.value() / lhs.value().
     *
     */
    auto operator/ (const Radians<T>& other) const -> Radians<T>
    {
        return Radians(fValue / other.fValue);
    }

    /**
     * Add-assign operator.
     *
     * @param other Rhs of operator.
     *
     * @return &(rhs.value() += lhs.value()).
     *
     */
    auto operator+= (const Radians<T>& other) -> Radians<T>&
    {
        fValue += other.fValue;
        return *this;
    }

    /**
     * Subtract-assign operator.
     *
     * @param other Rhs of operator.
     *
     * @return &(rhs.value() -= lhs.value()).
     *
     */
    auto operator-= (const Radians<T>& other) -> Radians<T>&
    {
        fValue -= other.fValue;
        return *this;
    }

    /**
     * Multiply-assign operator.
     *
     * @param other Rhs of operator.
     *
     * @return &(rhs.value() *= lhs.value()).
     *
     */
    auto operator*= (const Radians<T>& other) -> Radians<T>&
    {
        fValue *= other.fValue;
        return *this;
    }

    /**
     * Divide-assign operator.
     *
     * @param other Rhs of operator.
     *
     * @return &(rhs.value() /= lhs.value()).
     *
     */
    auto operator/= (const Radians<T>& other) -> Radians<T>&
    {
        fValue /= other.fValue;
        return *this;
    }

private:
    T fValue;
};

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
template<typename T>
struct Degrees final {
public:
    explicit Degrees(const T& val)
            :
            fValue(val) { }

    auto toRadians() const -> Radians<T>
    {
        return Radians<T>(fValue * static_cast<T>(0.017));
    }

    auto value() const -> T
    {
        return fValue;
    }

    operator Radians<T>() const
    {
        return toRadians();
    }

    auto operator== (const Degrees<T>& other) const -> bool
    {
        return fValue == other.fValue;
    }

    auto operator!= (const Degrees<T>& other) const -> bool
    {
        return !operator==(this, other);
    }

    auto operator> (const Degrees<T>& other) const -> bool
    {
        return fValue > other.fValue;
    }

    auto operator< (const Degrees<T>& other) const -> bool
    {
        return fValue < other.fValue;
    }

    auto operator>= (const Degrees<T>& other) const -> bool
    {
        return operator>(this, other) || operator==(this, other);
    }

    auto operator<= (const Degrees<T>& other) const -> bool
    {
        return operator<(this, other) || operator==(this, other);
    }

    auto operator+ (const Degrees<T>& other) const -> Degrees<T>
    {
        return Degrees(fValue + other.fValue);
    }

    auto operator- (const Degrees<T>& other) const -> Degrees<T>
    {
        return Degrees(fValue - other.fValue);
    }

    auto operator* (const Degrees<T>& other) const -> Degrees<T>
    {
        return Degrees(fValue * other.fValue);
    }

    auto operator/ (const Degrees<T>& other) const -> Degrees<T>
    {
        return Degrees(fValue / other.fValue);
    }

    auto operator+= (const Degrees<T>& other) -> Degrees<T>&
    {
        fValue += other.fValue;
        return *this;
    }

    auto operator-= (const Degrees<T>& other) -> Degrees<T>&
    {
        fValue -= other.fValue;
        return *this;
    }

    auto operator*= (const Degrees<T>& other) -> Degrees<T>&
    {
        fValue *= other.fValue;
        return *this;
    }

    auto operator/= (const Degrees<T>& other) -> Degrees<T>&
    {
        fValue /= other.fValue;
        return *this;
    }

private:
    T fValue;
};

} // namespace core

} // namespace pneu

#endif // PNEUMATIC_CORE_ANGLE_HPP
