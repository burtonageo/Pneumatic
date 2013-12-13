/**
 * CSC3223 Graphics for Games
 * Coursework 2
 * Name: George Burton
 * Student Number: 110204567
 * File: Texture.hpp
 */

#pragma once

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Shader;
class Texture final {
public:
  Texture(std::string file);
  ~Texture();
  auto Bind(Shader*) -> void;
  auto Unbind() -> void;
  inline auto GetObject() -> GLuint const {return _object;};
private:
  GLuint _id;
  GLuint _object;
};

#endif // TEXTURE_HPP
