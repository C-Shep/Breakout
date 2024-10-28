#include "Trail.h"
#include "CONSTANTS.h"

Trail::Trail(float x, float y, sf::RenderWindow* window)
{
    _window = window;

    trailRadius = 5.f;
    alpha = 255;
    fadeSpeed = 500.5f;

    trailColour = sf::Color(255,255,255,alpha);

    sprite.setRadius(trailRadius);
    sprite.setFillColor(trailColour);
    sprite.setPosition(x, y);
    
}

Trail::~Trail()
{

}

void Trail::update(float dt)
{
    if (alpha >= 0)
    {
        alpha -= fadeSpeed * dt;
    }
    
    trailColour = sf::Color(255, 255, 255, (int)alpha);
    sprite.setFillColor(trailColour);
}

int Trail::getAlpha()
{
    return alpha;
}

void Trail::render()
{
    _window->draw(sprite);
}