/**
 * CSC3223 Graphics for Games
 * Coursework 2
 * Name: George Burton
 * Student Number: 110204567
 * File: ResourceLoader.hpp
 */

#pragma once

#ifndef RESOURCE_LOADER_HPP
#define RESOURCE_LOADER_HPP

#include <string>

#include <GLFW/glfw3.h>

namespace ResourceLoader {
  auto LoadTextFile(std::string const &) -> const std::string;
};

#endif // RESOURCE_LOADER_HPP
