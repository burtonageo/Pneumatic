#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Light.hpp"

Pneumatic::Light::Light(glm::vec4 col,
                        glm::vec4 pos,
                        glm::vec4 dir,
                        float rad)
  :
  fColor(col),
  fPosition(pos),
  fDirection(dir),
  fRadius(rad) 
{
  
}

Pneumatic::Light::~Light()
{
  
}
