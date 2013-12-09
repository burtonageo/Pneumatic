

#pragma once

#ifndef TRI_OBJECT_HPP
#define TRI_OBJECT_HPP

#include "RenderObject.hpp"

class TriObject : public RenderObject {
public:
  TriObject(void);
  ~TriObject();
  auto Update(double delta) -> void;
};

#endif // TRI_OBJECT_HPP
