/**
 * CSC3223 Graphics for Games
 * Coursework 2
 * Name: George Burton
 * Student Number: 110204567
 * File: TriObject.hpp
 */

#pragma once

#ifndef PNEUMATIC_TRI_OBJECT_HPP
#define PNEUMATIC_TRI_OBJECT_HPP

#include "RenderObject.hpp"

namespace Pneumatic {
  class TriObject : public RenderObject {
  public:
    TriObject(void);
    ~TriObject();
    auto Update(double delta) -> void;
  };
}
#endif // PNEUMATIC_TRI_OBJECT_HPP
