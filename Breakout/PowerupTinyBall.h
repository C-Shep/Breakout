#pragma once

#include "PowerupBase.h"

class PowerupTinyBall : public PowerupBase
{
public:
    PowerupTinyBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball);
    ~PowerupTinyBall();

    std::pair<POWERUPS, float> applyEffect() override; // Method to apply the power-up effect
};
