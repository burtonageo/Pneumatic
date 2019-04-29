#include <string>
#include <iostream>

#include "pneu/graphics/Color.hpp"
#include "pneu/graphics/Window.hpp"
#include "pneu/graphics/Renderer.hpp"
#include "pneu/core/FuncResult.hpp"

int main(int argc, const char** argv) {
  // declare window
  pneu::graphics::Window window("hello-world", 800, 600, 80, 60);

  // initialise it, handling any errors
  window.init().onError([](const std::string& error) {
                          std::cout << error << std::endl;
                          exit(EXIT_FAILURE);
                        });

  // set window background to a nice shade of blue
  window.getRenderer().setBackgroundColor(
                         pneu::graphics::Color(0.2f, 0.3f, 0.7f));

  // main event loop
  while (window.isRunning()) {
    window.pollEvents();
    window.update();
    window.renderFrame();
  }

  return EXIT_SUCCESS;
}
