/**
 * CSC3223 Graphics for Games
 * Coursework 2
 * Name: George Burton
 * Student Number: 110204567
 * File: Config.hpp.cmake
 */

#pragma once

#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>

namespace Config {
  inline std::string GetFragmentDir() {return "@FRAGMENT_DIR@/";}
  inline std::string GetVertexDir() {return "@VERTEX_DIR@/";}
  inline std::string GetProgramName() {return "@PROJECT_NAME@";}
  
  inline int GetProgramVersionMajor() {return @PROJECT_VERSION_MAJOR@;}
  inline int GetProgramVersionMinor() {return @PROJECT_VERSION_MINOR@;}
}

#endif // CONFIG_HPP
