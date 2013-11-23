/**
 * CSC3223 Graphics for Games
 * Coursework 2
 * Name: George Burton
 * Student Number: 110204567
 * File: GLWindow.cpp
 */

#include <exception>
#include <iostream>

#include "GLWindow.hpp"

int main(int argc, char **argv) {
  using namespace std;

  try {
    GLWindow *window = new GLWindow();
    window->RunMainLoop();
    delete window;
    return EXIT_SUCCESS;
  } catch (runtime_error e) {
    cout << e.what() << endl;
    return EXIT_FAILURE;
  }
}
