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

#ifndef PNEUMATIC_SHADERUNIFORM_HPP
#define PNEUMATIC_SHADERUNIFORM_HPP

#include <functional>
#include <memory>
#include <string>

namespace pneu {

namespace graphics {

class Shader;

template<typename T>
class ShaderUniform final {
public:
  ShaderUniform(std::shared_ptr<Shader> shader,
                const std::string& variable_name)
    :
    fShader(shader),
    fVariableName(variable_name) { }

  auto update(const T& uniform_value)                           -> void;

  template<typename... Args>
  auto update(std::function<T (Args&&...)> f, Args&&... args)   -> void
  {
    T value = f(args...);
    update(value);
  }

private:
  std::shared_ptr<Shader> fShader;
  std::string fVariableName;
};

} // namespace pneu

} // namespace graphics

#endif // PNEUMATIC_SHADERUNIFORM_HPP
