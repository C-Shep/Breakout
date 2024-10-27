#include "Trail.h"
#include "CONSTANTS.h"

Trail::Trail(float x, float y, sf::RenderWindow* window)
{
    trailRadius = 5.f;
    alpha = 255.f;
    fadeSpeed = 0.5f;
    trailColour = sf::Color(255,255,255, alpha);

    sprite.setRadius(trailRadius);
    sprite.setFillColor(trailColour);
    sprite.setPosition(x, y);
}

Trail::~Trail()
{

}

void Trail::update(float dt)
{
    //fly through air and gravity
    alpha -= fadeSpeed * dt;
    sprite.setFillColor(trailColour);

    if ()
    {

    }
}

int Trail::getAlpha()
{
    return alpha;
}

void Trail::render()
{
    _window->draw(sprite);
}