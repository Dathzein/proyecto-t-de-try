#pragma once
#include <SFML/Graphics.hpp>

class Obstacle {
    public:
        Obstacle();
        void update();
        sf::RectangleShape getShape();
        sf::FloatRect getBounds();
    private:
        sf::RectangleShape shape;
};