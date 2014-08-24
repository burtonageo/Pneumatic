/**
 * This file is part of the pneumatic game engine
 *
 * Copyright (c) 2014 George Burton
 * 
 * THIS SOFTWARE IS PROVIDED 'AS-IS', WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTY. IN NO EVENT WILL THE AUTHORS BE HELD LIABLE FOR ANY DAMAGES
 * ARISING FROM THE USE OF THIS SOFTWARE.
 * 
 * Permission is granted to anyone to use this software for any purpose,  
 * including commercial applications, and to alter it and redistribute it  
 * freely, subject to the following restrictions:
 * 
 *    1. The origin of this software must not be misrepresented; you must not  
 *       claim that you wrote the original software. If you use this software  
 *       in a product, an acknowledgment in the product documentation would be  
 *       appreciated but is not required.
 * 
 *    2. Altered source versions must be plainly marked as such, and must not be  
 *       misrepresented as being the original software.
 * 
 *    3. This notice may not be removed or altered from any source  
 *       distribution.
 *
 **/

#pragma once

#ifndef PNEUMATIC_SHADER_HPP
#define PNEUMATIC_SHADER_HPP

#include <string>
#include <utility>
#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#define GLEW_STATIC
#include <GL/glew.h>

#define GLFW_INCLUDE_GL3
#define GLFW_NO_GLU
#include <GLFW/glfw3.h>

#include "pneu/core/FuncResult.hpp"

typedef GLuint ShaderId;

namespace pneu {

namespace graphics {

class Shader final {
public:
  Shader();
  ~Shader();

  auto loadFromFile(const std::string& vert_file,
                    const std::string& frag_file,
                    const std::string& geom_file = "",
                    const std::string& tcs_file  = "",
                    const std::string& tes_file  = "")      -> pneu::core::MethodResult;

  auto initWithCode(const std::string& vert_source,
                    const std::string& frag_source,
                    const std::string& geom_source = "",
                    const std::string& tcs_source  = "",
                    const std::string& tes_source  = "")    -> pneu::core::MethodResult;

  auto getShaderProgram() const                             -> ShaderId;

  auto bind()                                               -> void;
  auto unbind()                                             -> void;

private:
  auto _setDefaultAttributes()                              -> void;

  auto _compileShader(GLuint, const std::string& file_path) -> pneu::core::MethodResult;
  auto _linkShaderProgram()                                 -> pneu::core::MethodResult;

  bool fBound;
  ShaderId fProgramId;
};

// Used to update shaders
class ShaderUpdateMixin {
public:
  ShaderUpdateMixin(std::shared_ptr<pneu::graphics::Shader> shader)
    :
    fShader(shader) { }
  virtual ~ShaderUpdateMixin() = default;

  virtual auto update(double delta_time) -> void = 0;
  std::shared_ptr<pneu::graphics::Shader> fShader;
};

} // namespace graphics

} // namespace pneu

#endif // PNEUMATIC_SHADER_HPP
