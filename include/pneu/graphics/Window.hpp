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

#ifndef PNEUMATIC_WINDOW_HPP
#define PNEUMATIC_WINDOW_HPP

#include <memory>
#include <string>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wundef"
#pragma clang diagnostic ignored "-Wdocumentation"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_CXX11
#include <glm/fwd.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#pragma clang diagnostic pop

#include "pneu/graphics/Renderer.hpp"

namespace pneu {

namespace core {

template<typename T>
class FuncResult;
using MethodResult = FuncResult<void>;

} // namespace core

namespace graphics {

class Renderer;
class RenderObject;
class Window final {
public:
    Window(const std::string& title,
          int width,
          int height,
          int min_width = 0,
          int min_height = 0);
    Window(const Window&) = delete;
    auto operator=(const Window&) -> Window& = delete;

    Window(Window&&);
    auto operator=(Window&&) -> Window& = default;

    ~Window();

    auto init() -> pneu::core::MethodResult;

    auto update() -> void;
    auto pollEvents() -> void;
    auto renderFrame() -> void;

    auto isRunning() -> bool;

    auto getRenderer() const -> Renderer&;

private:
    auto _initGlfw(const std::string&) -> pneu::core::MethodResult;

    auto _handleKeypress(int, int, int, int) -> void;
    auto _handleRefresh() -> void;
    auto _handleQuitRequested() -> void;

    auto _handleWindowResize(int, int) -> void;
    auto _handleWindowMove(int, int) -> void;
    auto _handleViewportResize(int, int) -> void;

    auto _handleFocusLost() -> void;
    auto _handleFocusGained() -> void;

    static auto _windowResizeCallback(GLFWwindow*, int, int) -> void;
    static auto _viewportResizeCallback(GLFWwindow*, int, int) -> void;

    static auto _windowMoveCallback(GLFWwindow*, int, int) -> void;
    static auto _refreshCallback(GLFWwindow*) -> void;
    static auto _keypressCallback(GLFWwindow*, int, int, int, int) -> void;
    static auto _quitRequestedCallback(GLFWwindow*) -> void;
    static auto _windowFocusChangeCallback(GLFWwindow*, int) -> void;

    int width, height;
    const int min_width, min_height;

    struct WindowDeleter final {
        void operator()(GLFWwindow* window) { glfwDestroyWindow(window); }
    };

    std::unique_ptr<GLFWwindow, WindowDeleter> glWindow;
    std::shared_ptr<Renderer> renderer;
    std::string fWinTitle;
};

} // namespace graphics

} // namespace pneu

#endif // PNEUMATIC_WINDOW_HPP
