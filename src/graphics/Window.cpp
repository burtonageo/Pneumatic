/**
 * This file is part of the pneu game engine
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

#include "pneu/graphics/Window.hpp"

#define GLEW_STATIC
#include <GL/glew.h>

#define GLFW_INCLUDE_GL3
#define GLFW_NO_GLU
#include <GLFW/glfw3.h>

#include "pneu/core/MethodResult.hpp"
#include "pneu/graphics/RenderObject.hpp"

#include "GlRenderer.hpp"

namespace pneu {

namespace graphics {

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

  auto init(void) -> pneu::core::MethodResult
  {
    renderer = std::make_shared<GlRenderer>();
    return renderer->init(glWindow.get());
  }

  friend class pneu::graphics::Window;

  int width, height;
  const int min_width, min_height;

  std::unique_ptr<GLFWwindow, WindowDeleter> glWindow;
  std::shared_ptr<GlRenderer> renderer;
};

} // namespace graphics

} // namespace pneu

using namespace std;
using namespace pneu::core;

pneu::graphics::Window::Window(const std::string& title, int w, int h, int mw, int mh)
  :
  fWinImpl(make_unique<pneu::graphics::Window::WindowImpl>(w, h, mw, mh)),
  fWinTitle(title)
{

}

pneu::graphics::Window::~Window() = default;

auto
pneu::graphics::Window::init() -> pneu::core::MethodResult
{
  PNEU_TRY_METHOD(_initGlfw(fWinTitle));
  PNEU_TRY_METHOD(fWinImpl->init());

  return pneu::core::MethodResult::ok();
}

auto
pneu::graphics::Window::update() -> void
{
  double delta = glfwGetTime();

  fWinImpl->renderer->updateScene(delta);
}

auto
pneu::graphics::Window::pollEvents() -> void
{
  glfwPollEvents();
}

auto
pneu::graphics::Window::renderFrame() -> void
{
  fWinImpl->renderer->renderScene();
  glfwSwapBuffers(fWinImpl->glWindow.get());
}

auto
pneu::graphics::Window::isRunning() -> bool
{
  return !glfwWindowShouldClose(fWinImpl->glWindow.get());
}

auto
pneu::graphics::Window::addRenderObject(std::weak_ptr<RenderObject> object) -> void
{
  fWinImpl->renderer->addRenderObject(object);
}

auto
pneu::graphics::Window::setBackgroundColor(const glm::vec3& color) -> void
{
  fWinImpl->renderer->setBackgroundColor(color);
}

auto
pneu::graphics::Window::_initGlfw(const std::string& title) -> pneu::core::MethodResult
{
  bool glfw_success = glfwInit();
  if (!glfw_success) {
    return MethodResult::error("Failed to initialise GLFW");
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
    return MethodResult::error("Could not create GLFW window");
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
  return MethodResult::ok();
}

auto
pneu::graphics::Window::_handleKeypress(int key, int scan_code, int action, int mods)  -> void
{

}

auto
pneu::graphics::Window::_handleRefresh() -> void
{
  fWinImpl->renderer->renderScene();
}

auto
pneu::graphics::Window::_handleQuitRequested() -> void
{
  
}

auto
pneu::graphics::Window::_handleWindowResize(int w, int h) -> void
{
  int resize_width = max(w, fWinImpl->min_width);
  int resize_height = max(h, fWinImpl->min_height);

  glfwSetWindowSize(fWinImpl->glWindow.get(), resize_width, resize_height);
}

auto
pneu::graphics::Window::_handleWindowMove(int new_x_pos, int new_y_pos) -> void
{

}

auto
pneu::graphics::Window::_handleViewportResize(int w, int h) -> void
{
  fWinImpl->renderer->viewportDidResize(w, h);
}

auto
pneu::graphics::Window::_handleFocusLost() -> void
{
  
}

auto
pneu::graphics::Window::_handleFocusGained() -> void
{
  
}

auto
pneu::graphics::Window::_windowResizeCallback(GLFWwindow* win,
                                         int w,
                                         int h) -> void
{
  auto* pneu_win = static_cast<pneu::graphics::Window*>(glfwGetWindowUserPointer(win));
  pneu_win->_handleWindowResize(w, h);
}

auto
pneu::graphics::Window::_viewportResizeCallback(GLFWwindow* win, int w, int h) -> void
{
  auto* pneu_win = static_cast<pneu::graphics::Window*>(glfwGetWindowUserPointer(win));
  pneu_win->_handleViewportResize(w, h);
}

auto
pneu::graphics::Window::_windowMoveCallback(GLFWwindow* win, int x, int y) -> void
{
  auto* pneu_win = static_cast<pneu::graphics::Window*>(glfwGetWindowUserPointer(win));
  pneu_win->_handleWindowMove(x, y);
}

auto
pneu::graphics::Window::_refreshCallback(GLFWwindow* win) -> void
{
  auto* pneu_win = static_cast<pneu::graphics::Window*>(glfwGetWindowUserPointer(win));
  pneu_win->_handleRefresh();
}

auto
pneu::graphics::Window::_keypressCallback(GLFWwindow* win,
                                               int key,
                                               int scan_code,
                                               int action,
                                               int mods) -> void
{
  auto* pneu_win = static_cast<pneu::graphics::Window*>(glfwGetWindowUserPointer(win));
  pneu_win->_handleKeypress(key, scan_code, action, mods);
}

auto
pneu::graphics::Window::_quitRequestedCallback(GLFWwindow* win) -> void
{
  auto* pneu_win = static_cast<pneu::graphics::Window*>(glfwGetWindowUserPointer(win));
  return pneu_win->_handleQuitRequested();
}

auto
pneu::graphics::Window::_windowFocusChangeCallback(GLFWwindow* win, int focus) -> void
{
  auto* pneu_win = static_cast<pneu::graphics::Window*>(glfwGetWindowUserPointer(win));
  if (focus == GL_TRUE) {
    pneu_win->_handleFocusGained();
  } else {
    pneu_win->_handleFocusLost();
  }
}

