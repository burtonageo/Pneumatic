/**
 * This file is part of the Pneumatic game engine
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

#ifndef PNEUMATIC_CAMERA_HPP
#define PNEUMATIC_CAMERA_HPP

#include <glm/glm.hpp>

namespace Pneumatic {

namespace Graphics {

class GlRenderer;
class Camera final {
public:
  Camera(float fov                      = 45.0f,
         float zoom                     = 1.0f,
         float near_clip                = 0.1f,
         float far_clip                 = 100.0f,
         const glm::vec3& cam_position  = glm::vec3(1.0f),
         const glm::vec3& targ_position = glm::vec3(0.0f));
  ~Camera(void) = default;

  auto getWidth(void) const                          -> int;
  auto getHeight(void) const                         -> int;

  auto getPosition(void) const                       -> glm::vec2;
  auto setPosition(const glm::vec3& new_pos)         -> void;

  auto getFieldOfView(void) const                    -> float;
  auto setFieldOfView(float fov)                     -> void;

  auto getZoom(void) const                           -> float;
  auto setZoom(float zoom)                           -> void;
  auto zoomInBy(float zoom)                          -> void;
  auto zoomOutBy(float zoom)                         -> void;

  auto getNearClip(void) const                       -> float;
  auto setNearClip(float near_clip)                  -> void;

  auto getFarClip(void) const                        -> float;
  auto setFarClip(float far_clip)                    -> void;

  auto getRenderSize(void) const                     -> glm::uvec2;
  auto getAspectRatio(void) const                    -> float;
  auto getZoomedFieldOfView(void) const              -> float;

  auto pan(const glm::vec2& direction)               -> void;

private:
  auto _getPosition3d(void) const                    -> glm::vec3;
  auto _getDirection(void) const                     -> glm::vec3;

  auto _getTargetPosition(void) const                -> glm::vec3;
  auto _setTargetPosition(const glm::vec3& new_targ) -> void;

  friend class Pneumatic::Graphics::GlRenderer;

  float fFov, fZoom, fNearClip, fFarClip;
  glm::uvec2 fCameraSize;
  glm::vec3 fCameraPosition, fCameraTarget;
};

} // namespace Graphics

} // namespace Pneumatic

#endif // PNEUMATIC_CAMERA_HPP
