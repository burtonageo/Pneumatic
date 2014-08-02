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

#include "graphics/Camera.hpp"

Pneumatic::Graphics::Camera::Camera(float fov,
                                    float zoom,
                                    float near_clip,
                                    float far_clip,
                                    const glm::vec3& cam_position,
                                    const glm::vec3& targ_position)
  :
  fFov(fov),
  fZoom(zoom),
  fNearClip(near_clip),
  fFarClip(far_clip),
  fCameraSize(glm::uvec2(0, 0)),
  fCameraPosition(cam_position),
  fCameraTarget(targ_position)
{

}

auto
Pneumatic::Graphics::Camera::getWidth() const -> int
{
  return fCameraSize.x;
}

auto
Pneumatic::Graphics::Camera::getHeight() const -> int
{
  return fCameraSize.y;
}

auto
Pneumatic::Graphics::Camera::getPosition() const -> glm::vec2
{
  return glm::vec2(fCameraPosition.x, fCameraPosition.y);
}

auto
Pneumatic::Graphics::Camera::setPosition(const glm::vec3& new_pos) -> void
{
  fCameraPosition = new_pos;
}

auto
Pneumatic::Graphics::Camera::getFieldOfView() const -> float
{
  return fFov;
}

auto
Pneumatic::Graphics::Camera::setFieldOfView(float fov) -> void
{
  fFov = fov;
}

auto
Pneumatic::Graphics::Camera::getZoom() const -> float
{
  return fZoom;
}

auto
Pneumatic::Graphics::Camera::setZoom(float zoom) -> void
{
  fZoom = zoom;
}

auto
Pneumatic::Graphics::Camera::zoomInBy(float zoom) -> void
{
  fZoom -= zoom;
}

auto
Pneumatic::Graphics::Camera::zoomOutBy(float zoom) -> void
{
  fZoom += zoom;
}

auto
Pneumatic::Graphics::Camera::getNearClip() const -> float
{
  return fNearClip;
}

auto
Pneumatic::Graphics::Camera::setNearClip(float near_clip) -> void
{
  fNearClip = near_clip;
}

auto
Pneumatic::Graphics::Camera::getFarClip() const -> float
{
  return fFarClip;
}

auto
Pneumatic::Graphics::Camera::setFarClip(float far_clip) -> void
{
  fFarClip = far_clip;
}

auto
Pneumatic::Graphics::Camera::getRenderSize(void) const -> glm::uvec2
{
  return fCameraSize;
}

auto
Pneumatic::Graphics::Camera::getAspectRatio() const -> float
{
  if (fCameraSize.y == 0.0f) {
    return 0.0f;
  }
  return static_cast<float>(fCameraSize.x) /
         static_cast<float>(fCameraSize.y);
}

auto
Pneumatic::Graphics::Camera::getZoomedFieldOfView() const -> float
{
  return fFov * fZoom;
}

auto
Pneumatic::Graphics::Camera::pan(const glm::vec2& direction) -> void
{
  // TODO: implement
}

auto
Pneumatic::Graphics::Camera::_getPosition3d() const -> glm::vec3
{
  return fCameraPosition;
}

auto
Pneumatic::Graphics::Camera::_getDirection() const -> glm::vec3
{
  return fCameraTarget - fCameraPosition;
}


auto
Pneumatic::Graphics::Camera::_getTargetPosition() const -> glm::vec3
{
  return fCameraTarget;
}

auto
Pneumatic::Graphics::Camera::_setTargetPosition(const glm::vec3& new_targ) -> void
{
  fCameraTarget = new_targ;
}


