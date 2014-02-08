/**
 * CSC3223 Graphics for Games
 * Coursework 2
 * Name: George Burton
 * Student Number: 110204567
 * File: Light.cpp
 */

#include "Light.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

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
