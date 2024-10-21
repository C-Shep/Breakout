#include "Debris.h"
#include <iostream>
#include "CONSTANTS.h"
Debris::Debris(float x, float y, sf::RenderWindow* window)
{
    _window = window;

    //init vars
    gravity = 9.8f;
    debrisRadius = 5.f;
    velocity = 400.f;
    sprite.setRadius(debrisRadius);
    sprite.setFillColor(sf::Color::Red);
    sprite.setPosition(x, y);

    //fly in random compass direction
    float randXdir = 0.f;
    float randYdir = 0.f;

    //make sure they both arent 0 (theyd stay still if they were)
    while (randXdir == 0 && randYdir == 0)
    {
        randXdir = (rand() % 3) - 1;
        randYdir = (rand() % 3) - 1;
    }

    direction.x = randXdir;
    direction.y = randYdir;
}

Debris::~Debris()
{
    
}

void Debris::update(float dt)
{
    //fly through air and gravity
    direction.y += gravity * dt;
    sprite.move(direction * velocity * dt);
}

sf::Vector2f Debris::getPosition()
{
    return sprite.getPosition();
}

void Debris::render()
{
    _window->draw(sprite);
}