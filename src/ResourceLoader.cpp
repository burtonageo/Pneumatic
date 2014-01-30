/**
 * CSC3223 Graphics for Games
 * Coursework 2
 * Name: George Burton
 * Student Number: 110204567
 * File: ResourceLoader.cpp
 */

#include "ResourceLoader.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Config.hpp"
#include "Mesh.hpp"

auto
Pneumatic::ResourceLoader::LoadTextFile(std::string const &path) -> const std::string
{
  std::string fileContents;
  std::ifstream fileStream(path, std::ios::in);
  if (fileStream.is_open()) {
    std::string line = "";
    while (getline(fileStream, line)) {
        fileContents += '\n' + line;
    }
    fileStream.close();
  }
  return fileContents;
}
