/**
 * CSC3223 Graphics for Games
 * Coursework 2
 * Name: George Burton
 * Student Number: 110204567
 * File: Renderer.cpp
 */

#include "iostream"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ResourceLoader.hpp"
#include "RenderObject.hpp"
#include "TriObject.hpp"
#include "CubeObject.hpp"
#include "Shader.hpp"
#include "Window.hpp"

#include "Renderer.hpp"

bool Renderer::_glewInitialized = false;

Renderer::Renderer(Window *window) :
  _pWindow(window),
  _width(0),
  _height(0),
  _viewMatrix(glm::mat4(1.0f)),
  _projectionMatrix(glm::mat4(1.0f)),
  _textureMatrix(glm::mat4(1.0f)),
  _modelMatrix(glm::mat4(1.0f)),
  _objects(std::vector<RenderObject*>()),
  _cameraPos(glm::vec3(4.0f, 0.0f, 4.0f))
{
  glfwSetWindowUserPointer(_pWindow->_pGLWindow, this);
  glfwSwapInterval(1);
  glfwMakeContextCurrent(_pWindow->_pGLWindow);

  if (!_glewInitialized) {
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
      throw new std::runtime_error("GLEW not initialized");
    }
    _glewInitialized = true;
    glGetError();
  }

  glfwSetKeyCallback(_pWindow->_pGLWindow, StaticRendererKeypressCallback);
  glfwSetWindowCloseCallback(_pWindow->_pGLWindow, StaticRendererQuitRequestedCallback);
  glfwSetFramebufferSizeCallback(_pWindow->_pGLWindow, StaticRendererResizeCallback);
  glfwSetWindowRefreshCallback(_pWindow->_pGLWindow, StaticRendererRefreshCallback);

  glEnable(GL_MULTISAMPLE);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  SetupContext();
  _pWindow->_pRenderer = this;
  _width = _pWindow->_width;
  _height = _pWindow->_height;

  RenderObject *tri = new CubeObject();
  _objects.push_back(tri);
}

auto
Renderer::UpdateShaderMatrices(GLuint program) -> void
{
  glm::mat4 mvp = _modelMatrix * _projectionMatrix * _viewMatrix;
  GLuint mvpUniform = glGetUniformLocation(program, "MVP");
  glUniformMatrix4fv(mvpUniform, 1, GL_FALSE, &mvp[0][0]);
}

auto
Renderer::Begin(void) -> void
{

}

auto
Renderer::UpdateScene(double ms) -> void
{
  float fov = 45.0f;
  float ratio = _width/static_cast<float>(_height);
  float nearClip = 0.01f;
  float farClip = 1000.0f;
  _projectionMatrix = glm::perspective(fov, ratio, nearClip, farClip);
  _viewMatrix = glm::lookAt(
    _cameraPos,
    glm::vec3(0.0f, 0.0f, 0.0f) - _cameraPos, // camera looks at
    glm::vec3(0.0f, 1.0f, 0.0f)  // up vector
  );
  std::for_each(_objects.begin(),
                _objects.end(),
                [&](RenderObject *r) {
                  r->Update(ms);
                  _modelMatrix = r->GetModelMatrix();
                  UpdateShaderMatrices(r->GetShader()->GetShaderProgram());
                });
}

auto
Renderer::RenderScene(void) -> void
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
  std::for_each(_objects.begin(),
                _objects.end(),
                [&](RenderObject *r) {
                  r->UseShader();
                  r->Draw();});

  glfwSwapBuffers(_pWindow->_pGLWindow);
}

auto
Renderer::ViewportDidResize(int width, int height) -> void
{
  glMatrixMode(GL_PROJECTION);
  glViewport(0, 0, (GLsizei)width, (GLsizei)height);
  glMatrixMode(GL_MODELVIEW);
}

auto
Renderer::KeyWasPressed(int key,
                        int scanCode,
                        int action,
                        int mods) -> void
{
  float moveFactor = 0.7;
  switch(key) {
    case GLFW_KEY_W:
      if (_cameraPos.z > 2.0f) {
        _cameraPos.z -= 0.7f * moveFactor;
      }
      break;
    case GLFW_KEY_S:
      if (_cameraPos.z < 20.0f) {
        _cameraPos.z += 0.7f * moveFactor;
      }
      break;
    case GLFW_KEY_Q:
      if (_cameraPos.y < 2.0f) {
        _cameraPos.y += 0.7f * moveFactor;
      }
      break;
    case GLFW_KEY_E:
      if (_cameraPos.y > -2.0f) {
        _cameraPos.y -= 0.7f * moveFactor;
      }
      break;
    case GLFW_KEY_X:
      if (action == GLFW_RELEASE) {
        std::for_each(_objects.begin(),
                      _objects.end(),
                      [&](RenderObject *r) {
                        r->ChangeShaders();});
      }
      break;
    default:
      //std::cout << key << std::endl;
      break;
  }
}

auto
Renderer::QuitWasRequested(void) -> bool
{
  return false;
}

auto
Renderer::SetupContext(void) -> void
{
  glfwSetTime(0.0);
}


