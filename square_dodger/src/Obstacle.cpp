#include "Obstacle.h"

Obstacle::Obstacle() {
  shape.setSize({40, 40});
  shape.setFillColor(sf::Color::Blue);
  shape.setPosition({800, 290});
}

void Obstacle::update() {
  shape.move({-5, 0});

  if (shape.getPosition().x < -50) {
    shape.setPosition({800, 290});
  }
}

sf::RectangleShape Obstacle::getShape() { return shape; }

sf::FloatRect Obstacle::getBounds() { return shape.getGlobalBounds(); }