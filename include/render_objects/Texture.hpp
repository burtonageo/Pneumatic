/**
 * CSC3223 Graphics for Games
 * Coursework 2
 * Name: George Burton
 * Student Number: 110204567
 * File: Texture.hpp
 */

#pragma once

#ifndef PNEUMATIC_TEXTURE_HPP
#define PNEUMATIC_TEXTURE_HPP

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Pneumatic {
class Shader;

class Texture final {
public:
  Texture(std::string file);
  ~Texture();
  auto Bind(Shader*)            -> void;
  auto Unbind()                 -> void;
  inline auto GetObject() const -> GLuint {return fObject;};
private:
  GLuint fObject;
};

} // namespace Pneumatic

#endif // PNEUMATIC_TEXTURE_HPP
