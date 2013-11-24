/**
 * CSC3223 Graphics for Games
 * Coursework 2
 * Name: George Burton
 * Student Number: 110204567
 * File: GLWindow.hpp.cmake
 */

#pragma once

#ifndef GL_WINDOW_HPP
#define GL_WINDOW_HPP

#include <exception>

#include <GLFW/glfw3.h>

#include "GLContext.hpp"

class GLWindow final {
public:
  static GLWindow* GetInstance();
  static void DestroyInstance();
  
  void RunMainLoop();
  bool WindowShouldClose() const {return _shouldClose;}
  GLContext *GetContext() const {return _pContext;}

  const char* GetProgramName() const {return "@PROJECT_NAME@";}
  const int GetProgramVersionMajor() const {return @PROJECT_VERSION_MAJOR@;}
  const int GetProgramVersionMinor() const {return @PROJECT_VERSION_MINOR@;}

private:
  GLWindow();
  ~GLWindow();

  GLFWwindow *_pGLFWWindow;
  GLContext *_pContext;
  static GLWindow *_pWindowInstance;
  bool _shouldClose = false;
  const int _StartWidth = 800, _StartHeight = 600;

  void InitGLFW();
  static void DrawCallback(GLFWwindow*);
  static void ErrorCallback(int, const char *);
  static void CloseCallback(GLFWwindow*);
  static void ResizeCallback(GLFWwindow*, int width, int height);
  static void KeyCallback(GLFWwindow*,
                          int key,
                          int scanCode,
                          int action,
                          int mods);
};

#endif // GL_WINDOW_HPP
