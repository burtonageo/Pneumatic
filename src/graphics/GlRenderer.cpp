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

#include "GlRenderer.hpp"

#include "pneu/core/Angle.hpp"
#include "pneu/core/ResourceLoader.hpp"

#include "pneu/graphics/Color.hpp"
#include "pneu/graphics/RenderObject.hpp"
#include "pneu/graphics/Shader.hpp"
#include "pneu/graphics/Window.hpp"

#include <algorithm>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"

#include <glm/gtc/matrix_transform.hpp>

#pragma clang diagnostic pop

static auto _updateShaderMatrices(GLuint program,
                                  const glm::mat4& model_matrix,
                                  const glm::mat4& projection_matrix,
                                  const glm::mat4& view_matrix) -> void
{
  glm::mat4 mvp = model_matrix *
                  projection_matrix *
                  view_matrix;
  GLint mvp_uniform = glGetUniformLocation(program, "MVP");
  glUniformMatrix4fv(mvp_uniform, 1, GL_FALSE, &mvp[0][0]);
}

static auto _initGlew() -> pneu::core::MethodResult
{
   glewExperimental = GL_TRUE;

   GLenum err = glewInit();
   if (err != GLEW_OK) {
     const size_t max_buf_len = 80;
     char err_buf[max_buf_len];
     snprintf(err_buf, max_buf_len, "GLEW not initialized: %s", glewGetErrorString(err));

     return pneu::core::MethodResult::error(std::string(err_buf));
   }

   glGetError(); // clear out errors
   return pneu::core::MethodResult::ok();
}

bool pneu::graphics::GlRenderer::sGlewInitialized = false;

pneu::graphics::GlRenderer::GlRenderer()
  :
  width(0),
  height(0),
  backgroundColor(),
  camera(),
  objects()
{

}

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
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glfwSwapInterval(1);
  glfwSetTime(0.0);

  glfwGetFramebufferSize(win_ptr, &width, &height);
  camera.fCameraSize = glm::uvec2(width, height);

  camera.setPosition(glm::vec3(4.0f, 0.0f, 4.0f));
  camera._setTargetPosition(glm::vec3(0.0f));

  return pneu::core::MethodResult::ok();
}

auto
pneu::graphics::GlRenderer::addRenderObject(std::weak_ptr<RenderObject> object) -> void
{
  if (auto owned = object.lock()) {
    objects.push_back(owned);
  }
}

auto
pneu::graphics::GlRenderer::setBackgroundColor(const Color<>& color) -> void
{
  backgroundColor = color.toVector4();
}

auto
pneu::graphics::GlRenderer::updateScene(double ms) -> void
{
  const auto& cam = camera;
  const auto projection_matrix = glm::perspective(cam.getFieldOfViewRadians().value(),
                                                  cam.getAspectRatio(),
                                                  cam.getNearClip(),
                                                  cam.getFarClip());

  const auto view_matrix = glm::lookAt(cam._getPosition3d(),
                                       cam._getDirection(),
                                       glm::vec3(0.0f, 1.0f, 0.0f));

  std::for_each(objects.begin(),
                objects.end(),
                [&](std::shared_ptr<pneu::graphics::RenderObject> r) {
                  r->update(ms);
                  _updateShaderMatrices(r->getCurrentShader()->getShaderProgram(),
                                        r->getModelMatrix(),
                                        projection_matrix,
                                        view_matrix);
                });
}

auto
pneu::graphics::GlRenderer::renderScene() -> void
{
  const auto bg_color = backgroundColor;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(bg_color.r, bg_color.g, bg_color.b, bg_color.a);
  std::for_each(objects.begin(),
                objects.end(),
                [&](std::shared_ptr<pneu::graphics::RenderObject> r) {
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

  const auto last_width = width;
  const auto last_height = height = height;

  width = width;
  height = height;
  camera.fCameraSize.x += (static_cast<unsigned int>(width - last_width) / 3);
  camera.fCameraSize.y += (static_cast<unsigned int>(height - last_height) / 3);
}

auto
pneu::graphics::GlRenderer::quitWasRequested() -> bool
{
  return false;
}
