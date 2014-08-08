Pneumatic
=========

  This is my computer science graphics project which will eventually become
a full-featured 2D game engine. Right now, it is very basic, and has virtually no
functionality. Features currently in development:

  - Reorganisation of project to modularise everything
  - Sprite system
  - Freetype
  - Physics
  - Audio
  - Input keymap
  - ...

Creating a window
=================

```c++
#include <string>
#include <iostream>

#include "pneu/graphics/Window.hpp"
#include "pneu/core/MethodResult.hpp"

int main(int argc, const char** argv) {
  pneu::graphics::Window win("testing", 800, 600, 80, 60);

  win.init().onError([](const std::string& error) {
                       std::cout << error << std::endl;
                       exit(1);
                     });

  while (win.isRunning()) {
    win.pollEvents();
    win.update();
    win.renderFrame();
  }

  return 0;
}
```
