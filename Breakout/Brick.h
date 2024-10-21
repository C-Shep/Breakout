#pragma once
#include <SFML/Graphics.hpp>
#include "Debris.h"

class Brick {
public:
    Brick(float x, float y, float width, float height);
    void render(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition();

private:
    sf::RectangleShape _shape;
    bool _isDestroyed;
};