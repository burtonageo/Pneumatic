/**
 * CSC3223 Graphics for Games
 * Coursework 2
 * Name: George Burton
 * Student Number: 110204567
 * File: CubeObject.hpp
 */

#pragma once

#ifndef CUBE_OBJECT_HPP
#define CUBE_OBJECT_HPP

#include "RenderObject.hpp"

class CubeObject : public RenderObject {
public:
  CubeObject();
  ~CubeObject();
  auto Update(double delta) -> void;
};

#endif // CUBE_OBJECT_HPP
