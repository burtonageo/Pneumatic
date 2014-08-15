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

#ifndef PNEUMATIC_RENDERER_HPP
#define PNEUMATIC_RENDERER_HPP

#include <memory>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_CXX11
#include <glm/fwd.hpp>

namespace pneu {

namespace graphics {

template<typename T>
class Color;
class RenderObject;

class Renderer {
public:
  virtual ~Renderer() = 0;  

  virtual auto addRenderObject(std::weak_ptr<pneu::graphics::RenderObject>)  -> void = 0;
  virtual auto setBackgroundColor(const pneu::graphics::Color<float>& color) -> void = 0;
};

inline Renderer::~Renderer() = default;

} // namespace graphics 

} // namespace pneu

#endif // PNEUMATIC_RENDERER_HPP
