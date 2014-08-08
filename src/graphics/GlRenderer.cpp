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

#include "GlRenderer.hpp"

#define GLEW_STATIC
#include <GL/glew.h>

#define GLFW_INCLUDE_GL3
#define GLFW_NO_GLU
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "core/MethodResult.hpp"
#include "core/ResourceLoader.hpp"

#include "graphics/Camera.hpp"
#include "graphics/RenderObject.hpp"
#include "graphics/Shader.hpp"
#include "graphics/Window.hpp"

namespace pneu {

namespace graphics {

struct GlRenderer::GlRendererImpl final {
public:
  GlRendererImpl(int w,
                 int h)
    :
    width(w),
    height(h),
    camera(),
    objects() { }

  int width, height;

  pneu::graphics::Camera camera;
  std::vector<std::shared_ptr<RenderObject>> objects;
};

} // namespace graphics

} // namespace pneu

using namespace std;
using namespace pneu::core;

static auto _updateShaderMatrices(GLuint program,
                                  const glm::mat4& model_matrix,
                                  const glm::mat4& projection_matrix,
                                  const glm::mat4& view_matrix) -> void
{
  glm::mat4 mvp = model_matrix *
                  projection_matrix *
                  view_matrix;
  GLuint mvp_uniform = glGetUniformLocation(program, "MVP");
  glUniformMatrix4fv(mvp_uniform, 1, GL_FALSE, &mvp[0][0]);
}

static auto _initGlew(void) -> pneu::core::MethodResult
{
   glewExperimental = GL_TRUE;
 
   GLenum err = glewInit();
   if (err != GLEW_OK) {
     const size_t max_buf_len = 80;
     char err_buf[max_buf_len];
     snprintf(err_buf, max_buf_len, "GLEW not initialized: %s", glewGetErrorString(err));

     return MethodResult::error(string(err_buf));
   }

   glGetError(); // clear out errors
   return MethodResult::ok();  
}

bool pneu::graphics::GlRenderer::sGlewInitialized = false;

pneu::graphics::GlRenderer::GlRenderer()
  :
  fRenImpl(make_unique<pneu::graphics::GlRenderer::GlRendererImpl>(0, 0)) { }

pneu::graphics::GlRenderer::~GlRenderer() = default;

auto
pneu::graphics::GlRenderer::init(GLFWwindow* win_ptr) -> pneu::core::MethodResult
{
  glfwMakeContextCurrent(win_ptr);

  if (!sGlewInitialized) {
    PNEU_TRY_METHOD(_initGlew());
    sGlewInitialized = true;
  }

  glEnable(GL_MULTISAMPLE);
  //glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glfwSwapInterval(1);
  glfwSetTime(0.0);

  glfwGetFramebufferSize(win_ptr, &fRenImpl->width, &fRenImpl->height);
  fRenImpl->camera.fCameraSize = glm::uvec2(fRenImpl->width,
                                            fRenImpl->height);

  fRenImpl->camera.setPosition(glm::vec3(4.0f, 0.0f, 4.0f));
  fRenImpl->camera._setTargetPosition(glm::vec3(0.0f));

  return MethodResult::ok();
}

auto
pneu::graphics::GlRenderer::addRenderObject(std::weak_ptr<RenderObject> object) -> void
{
  if (auto owned = object.lock()) {
    fRenImpl->objects.push_back(owned);
  }
}

auto
pneu::graphics::GlRenderer::updateScene(double ms) -> void
{
  const auto& cam = fRenImpl->camera;
  const auto projection_matrix = glm::perspective(cam.getFieldOfView(),
                                                  cam.getAspectRatio(),
                                                  cam.getNearClip(),
                                                  cam.getFarClip());

  const auto view_matrix = glm::lookAt(cam._getPosition3d(),
                                       cam._getDirection(),
                                       glm::vec3(0.0f, 1.0f, 0.0f));

  for_each(fRenImpl->objects.begin(),
           fRenImpl->objects.end(),
           [&](shared_ptr<pneu::graphics::RenderObject> r) {
             r->update(ms);
             _updateShaderMatrices(r->getShader()->getShaderProgram(),
                                   r->getModelMatrix(),
                                   projection_matrix,
                                   view_matrix);
           });
}

auto
pneu::graphics::GlRenderer::renderScene() -> void
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
  for_each(fRenImpl->objects.begin(),
           fRenImpl->objects.end(),
           [&](shared_ptr<pneu::graphics::RenderObject> r) {
             r->draw();
           });
}

auto
pneu::graphics::GlRenderer::viewportDidResize(int width, int height) -> void
{
  glMatrixMode(GL_PROJECTION);
  glViewport(0, 0, static_cast<GLsizei>(width),
                   static_cast<GLsizei>(height));
  glMatrixMode(GL_MODELVIEW);

  const auto last_width = fRenImpl->width;
  const auto last_height = fRenImpl->height = height;

  fRenImpl->width = width;
  fRenImpl->height = height;
  fRenImpl->camera.fCameraSize.x += ((width - last_width) / 3);
  fRenImpl->camera.fCameraSize.y += ((height - last_height) / 3);
}

auto
pneu::graphics::GlRenderer::quitWasRequested() -> bool
{
  return false;
}
