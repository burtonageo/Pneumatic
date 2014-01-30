/**
 * CSC3223 Graphics for Games
 * Coursework 2
 * Name: George Burton
 * Student Number: 110204567
 * File: Renderer.cpp
 */

#include "Renderer.hpp"

#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>

#include "ResourceLoader.hpp"
#include "RenderObject.hpp"
#include "TriObject.hpp"
#include "CubeObject.hpp"
#include "Shader.hpp"
#include "Window.hpp"

bool Pneumatic::Renderer::sGlewInitialized = false;

Pneumatic::Renderer::Renderer(Window *window)
  :
  fWidth(0),
  fHeight(0),
  fWindow(window),
  fFov(45.0f),
  fNearClip(0.1f),
  fFarClip(100.0f),
  fViewMatrix(glm::mat4(1.0f)),
  fProjectionMatrix(glm::mat4(1.0f)),
  fTextureMatrix(glm::mat4(1.0f)),
  fModelMatrix(glm::mat4(1.0f)),
  fCameraPos(glm::vec3(4.0f, 0.0f, 4.0f)),
  fObjects(std::list<Pneumatic::RenderObject*>())
{
  glfwSetWindowUserPointer(fWindow->fGlWindow, this);
  glfwSwapInterval(1);
  glfwMakeContextCurrent(fWindow->fGlWindow);

  if (!sGlewInitialized) {
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
      throw new std::runtime_error("GLEW not initialized");
    }
    sGlewInitialized = true;
    glGetError();
  }

  glfwSetKeyCallback(fWindow->fGlWindow, StaticRendererKeypressCallback);
  glfwSetWindowCloseCallback(fWindow->fGlWindow, StaticRendererQuitRequestedCallback);
  glfwSetFramebufferSizeCallback(fWindow->fGlWindow, StaticRendererResizeCallback);
  glfwSetWindowRefreshCallback(fWindow->fGlWindow, StaticRendererRefreshCallback);

  glEnable(GL_MULTISAMPLE);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  _SetupContext();
  fWindow->fRenderer = this;
  fWidth = fWindow->fWidth;
  fHeight = fWindow->fHeight;

  Pneumatic::RenderObject *cube = new CubeObject();
  fObjects.push_back(cube);
}

auto
Pneumatic::Renderer::_UpdateShaderMatrices(GLuint program) -> void
{
  glm::mat4 mvp = fModelMatrix * fProjectionMatrix * fViewMatrix;
  GLuint mvpUniform = glGetUniformLocation(program, "MVP");
  glUniformMatrix4fv(mvpUniform, 1, GL_FALSE, &mvp[0][0]);
}

auto
Pneumatic::Renderer::UpdateScene(double ms) -> void
{
  float ratio = fWidth/static_cast<float>(fHeight);
  fProjectionMatrix = glm::perspective(fFov, ratio, fNearClip, fFarClip);
  fViewMatrix = glm::lookAt(
    fCameraPos,
    glm::vec3(0.0f, 0.0f, 0.0f) - fCameraPos, // camera looks at
    glm::vec3(0.0f, 1.0f, 0.0f)               // up vector
  );
  std::for_each(fObjects.begin(),
                fObjects.end(),
                [&](Pneumatic::RenderObject *r) {
                  r->Update(ms);
                  fModelMatrix = r->GetModelMatrix();
                  _UpdateShaderMatrices(r->GetShader()->GetShaderProgram());
                });
}

auto
Pneumatic::Renderer::RenderScene(void) -> void
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
  std::for_each(fObjects.begin(),
                fObjects.end(),
                [&](Pneumatic::RenderObject *r) {
                  r->UseShader();
                  r->Draw();});

  glfwSwapBuffers(fWindow->fGlWindow);
}

auto
Pneumatic::Renderer::ViewportDidResize(int width, int height) -> void
{
  fWidth = width;
  fHeight = height;
  glMatrixMode(GL_PROJECTION);
  glViewport(0, 0, (GLsizei)fWidth, (GLsizei)fHeight);
  glMatrixMode(GL_MODELVIEW);
}

auto
Pneumatic::Renderer::KeyWasPressed(int key,
                        int scanCode,
                        int action,
                        int mods) -> void
{
  float moveFactor = 0.7;
  switch(key) {
    case GLFW_KEY_W:
      if (fCameraPos.z > 2.0f) {
        fCameraPos.z -= 0.7f * moveFactor;
      }
      break;
    case GLFW_KEY_S:
      if (fCameraPos.z < 20.0f) {
        fCameraPos.z += 0.7f * moveFactor;
      }
      break;
    case GLFW_KEY_Q:
      if (fCameraPos.y < 2.0f) {
        fCameraPos.y += 0.7f * moveFactor;
      }
      break;
    case GLFW_KEY_E:
      if (fCameraPos.y > -2.0f) {
        fCameraPos.y -= 0.7f * moveFactor;
      }
      break;
    case GLFW_KEY_X:
      if (action == GLFW_RELEASE) {
        std::for_each(fObjects.begin(),
                      fObjects.end(),
                      [&](Pneumatic::RenderObject *r) {
                        r->ChangeShaders();});
      }
      break;
    default:

      break;
  }
}

auto
Pneumatic::Renderer::QuitWasRequested(void) -> bool
{
  return false;
}

auto
Pneumatic::Renderer::_SetupContext(void) -> void
{
  glfwSetTime(0.0);
}


