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

#ifndef PNEUMATIC_CAMERA_HPP
#define PNEUMATIC_CAMERA_HPP

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#pragma clang diagnostic ignored "-Wundefined-reinterpret-cast"
#pragma clang diagnostic ignored "-Wundef"
#pragma clang diagnostic ignored "-Wshadow"
#pragma clang diagnostic ignored "-Wold-style-cast"
#pragma clang diagnostic ignored "-Wdeprecated"
#pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#include "pneu/core/Angle.hpp"
#include "pneu/core/MathUtil.hpp"

namespace pneu {

namespace graphics {

class GlRenderer;

/**
 * A camera for navigating a Renderer. This provides a convenient
 * interface for manipulating the viewpoint of a window.
 */
class Camera final {
public:
    /**
     * Default constuctor.
     *
     * @param fov Field of view in degrees. Default is 45.
     * @param zoom Camera zoom. Default is 1.0 (no zoom).
     * @param near_clip Minimum distance from the camera for objects to be drawn. Default is 0.1.
     * @param far_clip Maximum distance from the camera for objects to be drawn. Default is 100.0.
     * @param cam_size Size of the camera frame. Default is (600, 800).
     * @param cam_position Position of the camera in 3d space. Default is [1.0, 1.0, 1.0].
     * @param targ_position Point for camera to look at. Default is [0.0, 0.0, 0.0].
     */
    Camera(const pneu::core::Degrees<float>& fov = pneu::core::Degrees<float>(45.0f),
           float zoom                                                        = 1.0f,
           float near_clip                                             = 0.1f,
           float far_clip                                                = 100.0f,
           const glm::uvec2& cam_size                        = glm::uvec2(800, 600),
           const glm::vec3& cam_position                 = glm::vec3(1.0f),
           const glm::vec3& targ_position                = glm::vec3(0.0f));

    /**
     * Constructor for defining the fov in radians.
     *
     * @param fov Field of view in radians.
     * @param zoom Camera zoom. Default is 1.0 (no zoom).
     * @param near_clip Minimum distance from the camera for objects to be drawn. Default is 0.1.
     * @param far_clip Maximum distance from the camera for objects to be drawn. Default is 100.0.
     * @param cam_size Size of the camera frame. Default is (600, 800).
     * @param cam_position Position of the camera in 3d space. Default is [1.0, 1.0, 1.0].
     * @param targ_position Point for camera to look at. Default is [0.0, 0.0, 0.0].
     */
    Camera(const pneu::core::Radians<float>& fov,
           float zoom                                    = 1.0f,
           float near_clip                               = 0.1f,
           float far_clip                                = 100.0f,
           const glm::uvec2& cam_size                    = glm::uvec2(800, 600),
           const glm::vec3& cam_position                 = glm::vec3(1.0f),
           const glm::vec3& targ_position                = glm::vec3(0.0f));

    /**
     * Get the width of the camera view frame.
     *
     * @return Width of frame.
     */
    auto getWidth() const -> unsigned int;

    /**
     * Get the height of the camera view frame.
     *
     * @return height of frame.
     */
    auto getHeight() const -> unsigned int;

    /**
     * Get the position of the camera view frame.
     *
     * @return Position of the camera in 3d space.
     */
    auto getPosition() const -> glm::vec2;

    /**
     * Set the position of the camera.
     *
     * @param new_pos Position to move the camera to.
     */
    auto setPosition(const glm::vec3& new_pos) -> void;

    /**
     * Get the field of view in the default angle type.
     *
     * @return Field of view.
     * @note Internally the field of view is stored in Radians, so if the
     *       default angle type is set to degrees, this value must
     *       be calculated.
     */
    auto getFieldOfView() const -> pneu::core::Angle<float>;

    /**
     * Get the field of view in radians.
     *
     * @return Field of view.
     * @note Internally the field of view is stored in Radians, so no conversion
     *       calculation has to be performed when retrieving this value.
     */
    auto getFieldOfViewRadians() const -> pneu::core::Radians<float>;

    /**
     * Get the field of view in degrees.
     *
     * @return Field of view.
     * @note Internally the field of view is stored in Radians, so this
     *             value must be calculated.
     */
    auto getFieldOfViewDegrees() const -> pneu::core::Degrees<float>;

    /**
     * Set the field of view in degrees.
     *
     * @param fov_degrees Field of view.
     * @note Internally the field of view is stored in Radians, so this
     *       value must be converted before it is set.
     */
    auto setFieldOfView(const pneu::core::Degrees<float>& fov_degrees) -> void;

    /**
     * Set the field of view in radians.
     *
     * @param fov_radians Field of view.
     */
    auto setFieldOfView(const pneu::core::Radians<float>& fov_radians) -> void;

    /**
     * Get the zoom of the camera.
     *
     * @return Current zoom level.
     */
    auto getZoom() const -> float;

    /**
     * Set the zoom of the camera
     *
     * @param zoom New zoom amount.
     */
    auto setZoom(float zoom) -> void;

    /**
     * Zoom the camera in. Is essentially (current_zoom - zoom_parameter).
     *
     * @param zoom Amount to zoom in by. If it is negative, the camera will
     *             zoom out.
     */
    auto zoomInBy(float zoom) -> void;

    /**
     * Zoom the camera out. Is essentially (current_zoom + zoom_parameter).
     *
     * @param zoom Amount to zoom out by. If it is negative, the camera will
     *             zoom in.
     */
    auto zoomOutBy(float zoom) -> void;

    /**
     * Get the near clip of the camera.
     *
     * @return Near clip.
     */
    auto getNearClip() const -> float;

    /**
     * Set the near clip of the camera.
     *
     * @param near_clip The new near clipping distance.
     */
    auto setNearClip(float near_clip) -> void;

    /**
     * Get the far clip of the camera.
     *
     * @return Far clip.
     */
    auto getFarClip() const -> float;

    /**
     * Set the far clip of the camera
     *
     * @param far_clip The new far clipping distance.
     */
    auto setFarClip(float far_clip) -> void;

    /**
     * Get the size of the camera viewport as a 2D vector.
     *
     * @return The camera viewport size.
     */
    auto getRenderSize() const -> glm::uvec2;

    /**
     * Get the aspect ratio of the camera. This is calculated by the camera
     * width / camera height.
     *
     * @return The aspect ratio.
     */
    auto getAspectRatio() const -> float;

    /**
     * Get the zoomed field of view. This is calculated by fov * zoom
     *
     * @return Zoomed field of view.
     */
    auto getZoomedFieldOfView() const -> float;

    /**
     * Pan the camera across the screen.
     *
     * @param direction Direction in x and y to pan by.
     */
    auto pan(const glm::vec2& direction) -> void;

private:
    auto _getPosition3d() const -> glm::vec3;
    auto _getDirection() const -> glm::vec3;

    auto _getTargetPosition() const -> glm::vec3;
    auto _setTargetPosition(const glm::vec3& new_targ) -> void;

    friend class pneu::graphics::GlRenderer;

    pneu::core::Radians<float> fFov;
    float fZoom, fNearClip, fFarClip;
    glm::uvec2 fCameraSize;
    glm::vec3 fCameraPosition, fCameraTarget;
};

} // namespace graphics

} // namespace pneu

#endif // PNEUMATIC_CAMERA_HPP
