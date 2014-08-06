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

#ifndef PNEUMATIC_WINDOW_HPP
#define PNEUMATIC_WINDOW_HPP

#include <memory>
#include <string>

struct GLFWwindow;

namespace Pneumatic {

namespace Core {

class MethodResult;

} // namespace Core

namespace Graphics {

class RenderObject;
class Window final {
public:
  Window(const std::string&, int, int, int, int);
  Window(const Window&)                                                     = delete;
  Window(Window&&)                                                          = delete;
  auto operator=(const Window&)                                  -> Window& = delete;
  ~Window(void);

  auto init(void)                                                -> Pneumatic::Core::MethodResult;

  auto update(void)                                              -> void;
  auto pollEvents(void)                                          -> void;
  auto renderFrame(void)                                         -> void;

  auto isRunning(void)                                           -> bool;

  auto addRenderObject(std::weak_ptr<RenderObject> object)       -> void;

private:  
  auto _initGlfw(const std::string&)                             -> Pneumatic::Core::MethodResult;

  auto _handleKeypress(int, int, int, int)                       -> void;
  auto _handleRefresh(void)                                      -> void;
  auto _handleQuitRequested(void)                                -> void;

  auto _handleWindowResize(int, int)                             -> void;
  auto _handleWindowMove(int, int)                               -> void;
  auto _handleViewportResize(int, int)                           -> void;

  auto _handleFocusLost(void)                                    -> void;
  auto _handleFocusGained(void)                                  -> void;

  static auto _windowResizeCallback(GLFWwindow*, int, int)       -> void;
  static auto _viewportResizeCallback(GLFWwindow*, int, int)     -> void;

  static auto _windowMoveCallback(GLFWwindow*, int, int)         -> void;
  static auto _refreshCallback(GLFWwindow*)                      -> void;
  static auto _keypressCallback(GLFWwindow*, int, int, int, int) -> void;
  static auto _quitRequestedCallback(GLFWwindow*)                -> void;
  static auto _windowFocusChangeCallback(GLFWwindow*, int)       -> void;

  struct WindowImpl;
  std::unique_ptr<WindowImpl> fWinImpl;
  std::string fWinTitle;
};

} // namespace Graphics

} // namespace Pneumatic

#endif // PNEUMATIC_WINDOW_HPP
