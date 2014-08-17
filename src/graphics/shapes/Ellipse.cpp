#include "pneu/graphics/shapes/Ellipse.hpp"

pneu::graphics::shapes::Ellipse::Ellipse(const glm::vec2& position,
                                         const Color<>& color,
                                         float radius)
  :
  Shape(),
  fPosition(position),
  fColor(color),
  fRadius(radius)
{
  
}

auto
pneu::graphics::shapes::Ellipse::draw() -> void
{
  
}

auto
pneu::graphics::shapes::Ellipse::update(double dt) -> void
{
  
}

