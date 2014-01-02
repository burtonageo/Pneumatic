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

namespace Pneumatic {
  namespace Config {
    inline auto GetFragmentDir() -> std::string {return "@FRAGMENT_DIR@/";}
    inline auto GetVertexDir()   -> std::string {return "@VERTEX_DIR@/";}
    inline auto GetGeometryDir() -> std::string {return "@GEOMETRY_DIR@/";}
    inline auto GetTessEvalDir() -> std::string {return "@TESS_EVAL_DIR@/";}
    inline auto GetTessCtrlDir() -> std::string {return "@TESS_CONTROL_DIR@/";}
    inline auto GetMeshResDir()  -> std::string {return "@RES_MESH_DIR@/";}
    inline auto GetImgResDir()   -> std::string {return "@RES_IMG_DIR@/";}
    inline auto GetProgramName() -> std::string {return "@PROJECT_NAME@";}
  
    inline auto GetProgramVersionMajor() -> int {return @PROJECT_VERSION_MAJOR@;}
    inline auto GetProgramVersionMinor() -> int {return @PROJECT_VERSION_MINOR@;}
  }
}

#endif // CONFIG_HPP
