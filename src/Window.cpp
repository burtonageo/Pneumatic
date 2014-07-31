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

#include "Window.hpp"

#include <cstdlib>
#include <iostream>

#include "GlInclude.hpp"
#include "MethResult.hpp"
#include "Renderer.hpp"
#include "RenderObject.hpp"

namespace Pneumatic {

namespace Graphics {

struct Window::WindowImpl final {
private:
  struct WindowDeleter final {
    auto operator()(GLFWwindow* win_ptr)
    {
      glfwDestroyWindow(win_ptr);
    }
  };

public:
  WindowImpl(int w, int h, int mw, int mh)
    :
    width(w),
    height(h),
    min_width(mw),
    min_height(mh),
    glWindow(),
    renderer() { }

    ~WindowImpl() = default;

  auto init(void)
  {
    renderer = std::make_shared<Renderer>();
    return renderer->init(glWindow.get());
  }

  friend class Pneumatic::Graphics::Window;

  int width, height;
  const int min_width, min_height;

  std::unique_ptr<GLFWwindow, WindowDeleter> glWindow;
  std::shared_ptr<Renderer> renderer;
};

} // namespace Graphics

} // namespace Pneumatic

using namespace std;

Pneumatic::Graphics::Window::Window(const std::string& title, int w, int h, int mw, int mh)
  :
  fWinImpl(make_unique<Pneumatic::Graphics::Window::WindowImpl>(w, h, mw, mh)),
  fWinTitle(title)
{

}

Pneumatic::Graphics::Window::~Window() = default;

auto
Pneumatic::Graphics::Window::init() -> Pneumatic::Core::MethResult
{
  if (!_initGlfw(fWinTitle)) {
    return Pneumatic::Core::MethResult::error("Could not initialise glfw");
  }

  if (!fWinImpl->init()) {
    return Pneumatic::Core::MethResult::error("Could not initialise renderer");
  }
  return Pneumatic::Core::MethResult::ok();
}

auto
Pneumatic::Graphics::Window::updateWindow() -> void
{
  double delta = glfwGetTime();

  auto* ren_ptr = fWinImpl->renderer.get();
  ren_ptr->updateScene(delta);
  ren_ptr->renderScene();
  glfwSwapBuffers(fWinImpl->glWindow.get());
}

auto
Pneumatic::Graphics::Window::pollEvents() -> void
{
  glfwPollEvents();
}

auto
Pneumatic::Graphics::Window::isRunning() -> bool
{
  return !glfwWindowShouldClose(fWinImpl->glWindow.get());
}

auto
Pneumatic::Graphics::Window::addRenderObject(std::weak_ptr<RenderObject> object) -> void
{
  fWinImpl->renderer->addRenderObject(object);
}

auto
Pneumatic::Graphics::Window::_initGlfw(const std::string& title) -> bool
{
  bool glfw_success = glfwInit();
  if (!glfw_success) {
    return false;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  auto* win_ptr = glfwCreateWindow(fWinImpl->width,
                                   fWinImpl->height,
                                   title.c_str(),
                                   NULL,
                                   NULL);

  if (!win_ptr) {
    return false;
  }

  glfwSetWindowUserPointer(win_ptr, this);

  glfwSetWindowSizeCallback(win_ptr, _windowResizeCallback);
  glfwSetFramebufferSizeCallback(win_ptr, _viewportResizeCallback);

  glfwSetWindowPosCallback(win_ptr, _windowMoveCallback);
  glfwSetWindowRefreshCallback(win_ptr, _refreshCallback);
  glfwSetKeyCallback(win_ptr, _keypressCallback);
  glfwSetWindowCloseCallback(win_ptr, _quitRequestedCallback);
  glfwSetWindowFocusCallback(win_ptr, _windowFocusChangeCallback);

  fWinImpl->glWindow = std::unique_ptr<GLFWwindow, WindowImpl::WindowDeleter>(win_ptr);
  return true;
}

auto
Pneumatic::Graphics::Window::_handleKeypress(int key, int scan_code, int action, int mods)  -> void
{
  fWinImpl->renderer->keyWasPressed(key, scan_code, action, mods);
}

auto
Pneumatic::Graphics::Window::_handleRefresh() -> void
{
  fWinImpl->renderer->renderScene();
}

auto
Pneumatic::Graphics::Window::_handleQuitRequested() -> void
{
  
}

auto
Pneumatic::Graphics::Window::_handleWindowResize(int w, int h) -> void
{
  int resize_width = max(w, fWinImpl->min_width);
  int resize_height = max(h, fWinImpl->min_height);

  glfwSetWindowSize(fWinImpl->glWindow.get(), resize_width, resize_height);
}

auto
Pneumatic::Graphics::Window::_handleWindowMove(int new_x_pos, int new_y_pos) -> void
{

}

auto
Pneumatic::Graphics::Window::_handleViewportResize(int w, int h) -> void
{
  fWinImpl->renderer->viewportDidResize(w, h);
}

auto
Pneumatic::Graphics::Window::_handleFocusLost() -> void
{
  
}

auto
Pneumatic::Graphics::Window::_handleFocusGained() -> void
{
  
}

auto
Pneumatic::Graphics::Window::_windowResizeCallback(GLFWwindow* win,
                                         int w,
                                         int h) -> void
{
  auto* pneu_win = static_cast<Pneumatic::Graphics::Window*>(glfwGetWindowUserPointer(win));
  pneu_win->_handleWindowResize(w, h);
}

auto
Pneumatic::Graphics::Window::_viewportResizeCallback(GLFWwindow* win, int w, int h) -> void
{
  auto* pneu_win = static_cast<Pneumatic::Graphics::Window*>(glfwGetWindowUserPointer(win));
  pneu_win->_handleViewportResize(w, h);
}

auto
Pneumatic::Graphics::Window::_windowMoveCallback(GLFWwindow* win, int x, int y) -> void
{
  auto* pneu_win = static_cast<Pneumatic::Graphics::Window*>(glfwGetWindowUserPointer(win));
  pneu_win->_handleWindowMove(x, y);
}

auto
Pneumatic::Graphics::Window::_refreshCallback(GLFWwindow* win) -> void
{
  auto* pneu_win = static_cast<Pneumatic::Graphics::Window*>(glfwGetWindowUserPointer(win));
  pneu_win->_handleRefresh();
}

auto
Pneumatic::Graphics::Window::_keypressCallback(GLFWwindow* win,
                                               int key,
                                               int scan_code,
                                               int action,
                                               int mods) -> void
{
  auto* pneu_win = static_cast<Pneumatic::Graphics::Window*>(glfwGetWindowUserPointer(win));
  pneu_win->_handleKeypress(key, scan_code, action, mods);
}

auto
Pneumatic::Graphics::Window::_quitRequestedCallback(GLFWwindow* win) -> void
{
  auto* pneu_win = static_cast<Pneumatic::Graphics::Window*>(glfwGetWindowUserPointer(win));
  return pneu_win->_handleQuitRequested();
}

auto
Pneumatic::Graphics::Window::_windowFocusChangeCallback(GLFWwindow* win, int focus) -> void
{
  auto* pneu_win = static_cast<Pneumatic::Graphics::Window*>(glfwGetWindowUserPointer(win));
  if (focus == GL_TRUE) {
    pneu_win->_handleFocusGained();
  } else {
    pneu_win->_handleFocusLost();
  }
}

