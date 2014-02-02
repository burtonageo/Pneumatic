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

static const std::string kFragmentDir = "@FRAGMENT_DIR@/";
static const std::string kVertexDir   = "@VERTEX_DIR@/";
static const std::string kGeometryDir = "@GEOMETRY_DIR@/";
static const std::string kTessEvalDir = "@TESS_EVAL_DIR@/";
static const std::string kTessCtrlDir = "@TESS_CONTROL_DIR@/";
static const std::string kMeshResDir  = "@RES_MESH_DIR@/";
static const std::string kImgResDir   = "@RES_IMG_DIR@/";
static const std::string kProgramName = "@PROJECT_NAME@";

static const int kProgramVersionMajor = @PROJECT_VERSION_MAJOR@;
static const int kProgramVersionMinor = @PROJECT_VERSION_MINOR@;

} // namespace Config
} // namespace Pneumatic

#endif // CONFIG_HPP
