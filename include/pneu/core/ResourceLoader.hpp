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

#ifndef PNEUMATIC_CORE_RESOURCE_LOADER_HPP
#define PNEUMATIC_CORE_RESOURCE_LOADER_HPP

#include <string>

#include "pneu/core/FuncResult.hpp"

namespace pneu {

namespace core {

namespace ResourceLoader {
  
/**
 * Loads a text file from the path and
 * @param path The path to the text file
 * @return The result is valid if the text file was opened and parsed properly.
 *         If there was an error (e.g. file doesn't exist, file is corrupt,
 *         then the result will be an error.
 */
auto loadTextFile(const std::string& path) -> pneu::core::FuncResult<std::string>;

}

} // namespace core

} // namespace pneu

#endif // PNEUMATIC_CORE_RESOURCE_LOADER_HPP
