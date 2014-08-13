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

#include "pneu/graphics/Camera.hpp"


pneu::graphics::Camera::Camera(const pneu::core::Degrees<float>& fov,
                               float zoom,
                               float near_clip,
                               float far_clip,
                               const glm::uvec2& cam_size,
                               const glm::vec3& cam_position,
                               const glm::vec3& targ_position)
  :
  fFov(fov.toRadians()),
  fZoom(zoom),
  fNearClip(near_clip),
  fFarClip(far_clip),
  fCameraSize(cam_size),
  fCameraPosition(cam_position),
  fCameraTarget(targ_position)
{
  
}

pneu::graphics::Camera::Camera(const pneu::core::Radians<float>& fov,
                               float zoom,
                               float near_clip,
                               float far_clip,
                               const glm::uvec2& cam_size,
                               const glm::vec3& cam_position,
                               const glm::vec3& targ_position)
  :
  fFov(fov),
  fZoom(zoom),
  fNearClip(near_clip),
  fFarClip(far_clip),
  fCameraSize(cam_size),
  fCameraPosition(cam_position),
  fCameraTarget(targ_position)
{

}

auto
pneu::graphics::Camera::getWidth() const -> int
{
  return fCameraSize.x;
}

auto
pneu::graphics::Camera::getHeight() const -> int
{
  return fCameraSize.y;
}

auto
pneu::graphics::Camera::getPosition() const -> glm::vec2
{
  return glm::vec2(fCameraPosition.x, fCameraPosition.y);
}

auto
pneu::graphics::Camera::setPosition(const glm::vec3& new_pos) -> void
{
  fCameraPosition = new_pos;
}

auto
pneu::graphics::Camera::getFieldOfView() const -> pneu::core::Angle<float>
{
  return static_cast<pneu::core::Angle<float>>(fFov);
}

auto
pneu::graphics::Camera::getFieldOfViewRadians() const -> pneu::core::Radians<float>
{
  return fFov;
}

auto
pneu::graphics::Camera::getFieldOfViewDegrees() const -> pneu::core::Degrees<float>
{
  return fFov.toDegrees();
}

auto
pneu::graphics::Camera::setFieldOfView(const pneu::core::Degrees<float>& fov_degrees) -> void
{
  fFov = fov_degrees.toRadians();
}

auto
pneu::graphics::Camera::setFieldOfView(const pneu::core::Radians<float>& fov_degrees) -> void
{
  fFov = fov_degrees;
}

auto
pneu::graphics::Camera::getZoom() const -> float
{
  return fZoom;
}

auto
pneu::graphics::Camera::setZoom(float zoom) -> void
{
  fZoom = zoom;
}

auto
pneu::graphics::Camera::zoomInBy(float zoom) -> void
{
  fZoom -= zoom;
}

auto
pneu::graphics::Camera::zoomOutBy(float zoom) -> void
{
  fZoom += zoom;
}

auto
pneu::graphics::Camera::getNearClip() const -> float
{
  return fNearClip;
}

auto
pneu::graphics::Camera::setNearClip(float near_clip) -> void
{
  fNearClip = near_clip;
}

auto
pneu::graphics::Camera::getFarClip() const -> float
{
  return fFarClip;
}

auto
pneu::graphics::Camera::setFarClip(float far_clip) -> void
{
  fFarClip = far_clip;
}

auto
pneu::graphics::Camera::getRenderSize(void) const -> glm::uvec2
{
  return fCameraSize;
}

auto
pneu::graphics::Camera::getAspectRatio() const -> float
{
  if (fCameraSize.y == 0.0f) {
    return 0.0f;
  }
  return static_cast<float>(fCameraSize.x) /
         static_cast<float>(fCameraSize.y);
}

auto
pneu::graphics::Camera::getZoomedFieldOfView() const -> float
{
  return fFov.value() * fZoom;
}

auto
pneu::graphics::Camera::pan(const glm::vec2& direction) -> void
{
  // TODO: implement
}

auto
pneu::graphics::Camera::_getPosition3d() const -> glm::vec3
{
  return fCameraPosition;
}

auto
pneu::graphics::Camera::_getDirection() const -> glm::vec3
{
  return fCameraTarget - fCameraPosition;
}

auto
pneu::graphics::Camera::_getTargetPosition() const -> glm::vec3
{
  return fCameraTarget;
}

auto
pneu::graphics::Camera::_setTargetPosition(const glm::vec3& new_targ) -> void
{
  fCameraTarget = new_targ;
}


