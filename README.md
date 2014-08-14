Pneumatic
=========

  This is an in-progress 2D game engine written in C++. The only external dependencies
to use it is the [glm](http://glm.g-truc.net/0.9.5/index.html) library; everything else
is submoduled in the `thirdparty` directory. Right now, it is very basic, and has virtually no
functionality. Features currently in development:

  - Reorganisation of project to modularise everything
  - Sprite system
  - Freetype
  - Physics
  - Audio
  - Input keymap
  - ...

Building
========

```
git submodule init && git submodule update;
mkdir -p build && cd build;
cmake .. && make
```

Creating a window
=================

```c++
#include <string>
#include <iostream>

#include "pneu/graphics/Color.hpp"
#include "pneu/graphics/Window.hpp"
#include "pneu/graphics/Renderer.hpp"
#include "pneu/core/MethodResult.hpp"

#define GLM_FORCE_CXX11
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

int main(int argc, const char** argv) {
  // declare window
  pneu::graphics::Window window("hello-world", 800, 600, 80, 60);

  // initialise it, handling any errors
  window.init().onError([](const std::string& error) {
                          std::cout << error << std::endl;
                          exit(EXIT_FAILURE);
                        });

  // set window background to a nice shade of blue
  window.getRenderer().setBackgroundColor(pneu::graphics::Color3(0.2f, 0.3f, 0.7f));

  // main event loop
  while (window.isRunning()) {
    window.pollEvents();
    window.update();
    window.renderFrame();
  }

  return EXIT_SUCCESS;
}
```
