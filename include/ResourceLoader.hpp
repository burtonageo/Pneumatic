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

class ResourceLoader final {
public:
  static const GLuint LoadAndCompileShaders(std::string);
  static const char* LoadImage(std::string);
private:
  ResourceLoader();
};

#endif // RESOURCE_LOADER_HPP
