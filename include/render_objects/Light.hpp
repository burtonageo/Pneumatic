#pragma once

#ifndef PNEUMATIC_LIGHT_HPP
#define PNEUMATIC_LIGHT_HPP

#include <glm/glm.hpp>

namespace Pneumatic {
  class Light final {
  public:
    Light(glm::vec4 color, glm::vec4 position, glm::vec4 direction, float radius);
    ~Light();

    inline auto GetColor(void) const        -> glm::vec4 {return fColor;}
    inline auto SetColor(glm::vec4 col)     -> void      {fColor = col;}

    inline auto GetDirection(void) const    -> glm::vec3 {return fDirection;}
    inline auto SetDirection(glm::vec3 dir) -> void      {fDirection = dir;}

    inline auto GetRadius(void) const       -> float     {return fRadius;}
    inline auto SetRadius(float rad)        -> void      {fRadius = rad;}
  private:
    glm::vec4 fColor;
    glm::vec4 fPosition;
    glm::vec3 fDirection;
    float fRadius;
  };
}

#endif // PNEUMATIC_LIGHT_HPP
