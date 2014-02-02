/**
 * CSC3223 Graphics for Games
 * Coursework 2
 * Name: George Burton
 * Student Number: 110204567
 * File: ResourceLoader.hpp
 */

#pragma once

#ifndef PNEUMATIC_RESOURCE_LOADER_HPP
#define PNEUMATIC_RESOURCE_LOADER_HPP

#include <string>
#include <utility>

namespace Pneumatic {
namespace ResourceLoader {

auto LoadTextFile(std::string const &) -> const std::string;

} // namespace ResourceLoader
} // namespace Pneumatic

#endif // PNEUMATIC_RESOURCE_LOADER_HPP
