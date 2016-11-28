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

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#pragma clang diagnostic ignored "-Wundefined-reinterpret-cast"
#pragma clang diagnostic ignored "-Wundef"
#pragma clang diagnostic ignored "-Wshadow"
#pragma clang diagnostic ignored "-Wold-style-cast"
#pragma clang diagnostic ignored "-Wdeprecated"
#pragma clang diagnostic ignored "-Wdocumentation-unknown-command"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#pragma clang diagnostic pop

namespace pneu {

namespace graphics {

/**
 * Represents an RGBA color. The type of each component is
 * templated.
 */
template<typename T = float>
class Color final {
public:
    /**
     * Constructs a colour with a custom value for each component.
     * For floating point types, each component should take the value
     * 0 <= x <= 1.0.
     *
     * @param _r The red component.
     * @param _g The green component.
     * @param _b The blue component.
     * @param _a The alpha component.
     */
    Color(T _r, T _g, T _b, T _a = static_cast<T>(1))
        :
        r(_r),
        g(_g),
        b(_b),
        a(_a) { }

    /**
     * Creates the color red (equivelent to
     * [1, 0, 0, 1]).
     */
    static constexpr auto red() -> Color
    {
        return Color<T>(static_cast<T>(1),
                                        static_cast<T>(0),
                                        static_cast<T>(0));
    }

    /**
     * Creates the color green (equivelent to
     * [0, 1, 0, 1]).
     */
    static constexpr auto green() -> Color
    {
        return Color<T>(static_cast<T>(0),
                                        static_cast<T>(1),
                                        static_cast<T>(0));
    }

    /**
     * Creates the color blue (equivelent to
     * [0, 0, 1, 1]).
     */
    static constexpr auto blue() -> Color
    {
        return Color<T>(static_cast<T>(0),
                                        static_cast<T>(0),
                                        static_cast<T>(1));
    }

    /**
     * Returns the color as a glm::tvec4<T>, where T is
     * the templated type for the class instance.
     *
     * @return The color vector. The format is [R, G, B, A].
     */
    template<glm::precision P = glm::highp>
    auto toVector4() const -> glm::tvec4<T, P>
    {
        return glm::tvec4<T, P>(r, g, b, a);
    }

    /**
     * Returns the color as a glm::tvec3<T>, where T is
     * the templated type for the class instance.
     *
     * @return The color vector. The format is [R, G, B].
     */
    template<glm::precision P = glm::highp>
    auto toVector3() const -> glm::tvec3<T, P>
    {
        return glm::tvec4<T, P>(r, g, b);
    }

    T r, g, b, a;
};

using Colord = typename pneu::graphics::Color<double>;

} // namespace graphics

} // namespace pneu

#endif // PNEUMATIC_COLOR_HPP
