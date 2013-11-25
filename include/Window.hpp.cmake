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

class Window final {
public:
  static Window* GetInstance();
  static void DestroyInstance();
  
  void RunMainLoop();
  bool WindowShouldClose() const {return _shouldClose;}
  GLContext *GetContext() const {return _pContext;}

  const char* GetProgramName() const {return "@PROJECT_NAME@";}
  const int GetProgramVersionMajor() const {return @PROJECT_VERSION_MAJOR@;}
  const int GetProgramVersionMinor() const {return @PROJECT_VERSION_MINOR@;}

private:
  Window();
  ~Window();

  static Window *_pWindowInstance;
  GLFWwindow *_pGLWindow;
  GLContext *_pContext;
  bool _shouldClose = false;
  const int _StartWidth = 800, _StartHeight = 600;

  void InitGLFW();
  static void DrawCallback(GLFWwindow*);
  static void ErrorCallback(int, const char *);
  static void CloseCallback(GLFWwindow*);
  static void ViewportResizeCallback(GLFWwindow*, int width, int height);
  static void KeyCallback(GLFWwindow*,
                          int key,
                          int scanCode,
                          int action,
                          int mods);
};

#endif // GL_WINDOW_HPP
