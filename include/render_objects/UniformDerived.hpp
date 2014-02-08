

#pragma once

#ifndef PNEUMATIC_UNIFORMDERIVED_HPP
#define PNEUMATIC_UNIFORMDERIVED_HPP

#include "Uniform.hpp"

namespace Pneumatic {

template<typename T, int count>
class UniformDerived : public Uniform {
public:
  UniformDerived(std::string const &name, Shader *shader = nullptr)
    :
    Uniform(
      name,
      shader)
    {}

private:
  enum fAttribs {
    elementCount = count,
    elementSize  = sizeof(T)
  };

  T fElements[count];
};

typedef UniformDerived<float, 1> UniformFloat1;
typedef UniformDerived<float, 2> UniformFloatVec2;
typedef UniformDerived<float, 3> UniformFloatVec3;
typedef UniformDerived<float, 4> UniformFloatVec4;

typedef UniformDerived<float, 4> UniformFloatMat2;
typedef UniformDerived<float, 9> UniformFloatMat3;
typedef UniformDerived<float, 16> UniformFloatMat4;

typedef UniformDerived<bool, 1> UniformBool1;

} // namespace Pneumatic

#endif // PNEUMATIC_UNIFORMDERIVED_HPP