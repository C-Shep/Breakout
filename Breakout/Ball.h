#pragma once
#include <SFML/Graphics.hpp>
#include "Debris.h"
#include "Trail.h"

class GameManager;  // forward declaration



class Ball {
public:
    Ball(sf::RenderWindow* window, float velocity, GameManager* gameManager);
    ~Ball();
    void update(float dt);
    void render();
    void setVelocity(float coeff, float duration);
    void setFireBall(float duration);
    void setRadius(float newRadius, float duration);

private:
    sf::CircleShape _sprite;
    sf::Vector2f _direction;
    sf::RenderWindow* _window;
    float _velocity;
    bool _isAlive;
    bool _isFireBall;
    float _timeWithPowerupEffect;

    float trailTimerMax = 0.5f;
    float trailTimer = trailTimerMax;
    std::vector<Trail*> _trails;

    GameManager* _gameManager;  // Reference to the GameManager

    static constexpr float RADIUS = 10.0f;      
    static constexpr float VELOCITY = 350.0f;   // for reference.
};

