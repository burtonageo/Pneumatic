/**
 * CSC3223 Graphics for Games
 * Coursework 2
 * Name: George Burton
 * Student Number: 110204567
 * File: CubeObject.hpp
 */

#pragma once

#ifndef PNEUMATIC_CUBE_OBJECT_HPP
#define PNEUMATIC_CUBE_OBJECT_HPP

#include "Shader.hpp"
#include "RenderObject.hpp"

namespace Pneumatic {
namespace ___hidden___ {

class CubeShaderUpdate1 : public ShaderUpdateMixin {
// TODO: friendship not working
public:
    friend class CubeObject;
    CubeShaderUpdate1(Shader *s) : ShaderUpdateMixin(s) {}
    auto Update(double ms) -> void;
};

class CubeShaderUpdate2 : public ShaderUpdateMixin {
// TODO: friendship not working
public:
    friend class CubeObject;
    CubeShaderUpdate2(Shader *s) : Pneumatic::___hidden___::ShaderUpdateMixin(s) {}
    auto Update(double ms) -> void;
};

class CubeShaderUpdate3 : public ShaderUpdateMixin {
// TODO: friendship not working
public:
  friend class CubeObject;
  CubeShaderUpdate3(Pneumatic::Shader *s) : ShaderUpdateMixin(s) {}
  auto Update(double ms) -> void;
};

} // namespace ___hidden___

class CubeObject : public Pneumatic::RenderObject {
public:
  CubeObject();
  ~CubeObject();
};

} // namespace Pneumatic

#endif // PNEUMATIC_CUBE_OBJECT_HPP
