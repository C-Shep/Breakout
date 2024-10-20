#pragma once
#include <SFML/Graphics.hpp>
#include "CONSTANTS.h"
#include "Paddle.h"
#include "Ball.h"
#include "BrickManager.h"
#include "PowerupManager.h"
#include "MessagingSystem.h"
#include "UI.h"



class GameManager {
public:
    GameManager(sf::RenderWindow* window);
    void initialize();
    void update(float dt);
    void loseLife();
    void render();
    void levelComplete();
    void powerupEffect(POWERUPS pu, float t);
    void screenshake(sf::Vector2f myShakeAmount, float dt);

    float lerp(float a, float b, float t);

    Paddle* getPaddle() const;
    BrickManager* getBrickManager() const;
    PowerupManager* getPowerupManager() const;
    sf::RenderWindow* getWindow() const;
    UI* getUI() const;


private:
    bool _pause;
    float _pauseHold;
    float _time;
    float _timeLastPowerupSpawned;
    int _lives;
    bool _levelComplete;
    std::pair<POWERUPS, float> _powerupInEffect;

    sf::Font _font;
    sf::Text _masterText;

    sf::RenderWindow* _window;
    Paddle* _paddle;
    Ball* _ball;
    BrickManager* _brickManager;
    PowerupManager* _powerupManager;
    MessagingSystem* _messagingSystem;
    UI* _ui;

    static constexpr float PAUSE_TIME_BUFFER = 0.5f;    // for holding the pause button down
    static constexpr float POWERUP_FREQUENCY = 7.5f;    // time between minimum powerup spawn

    //powerup vars
    float powerupSpawnTime;
    int powerupRandomSpawnChance = 700;

    //view
    sf::View view;
    sf::Vector2f viewBaseCentre;

    //screenshake
    sf::Vector2f shakeAmount;
    sf::Vector2f maxShakeAmount;
    float shakeFalloff;
    float maxShakeTime;
    float shakeTime;

};
