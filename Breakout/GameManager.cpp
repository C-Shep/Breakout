#include "GameManager.h"
#include "Ball.h"
#include "PowerupManager.h"
#include <iostream>

GameManager::GameManager(sf::RenderWindow* window)
    : _window(window), _paddle(nullptr), _ball(nullptr), _brickManager(nullptr), _powerupManager(nullptr),
    _messagingSystem(nullptr), _ui(nullptr), _pause(false), _time(0.f), _lives(3), _pauseHold(0.f), _levelComplete(false),
    _powerupInEffect({ none,0.f }), _timeLastPowerupSpawned(0.f)
{
    _font.loadFromFile("font/montS.ttf");
    _masterText.setFont(_font);
    _masterText.setPosition(50, 400);
    _masterText.setCharacterSize(48);
    _masterText.setFillColor(sf::Color::Yellow);

    view.reset(sf::FloatRect(0.f, 0.f, _window->getSize().x, _window->getSize().y));
    viewBaseCentre = view.getCenter();
    view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

    //screenshake vars
    maxShakeTime = .1f;
    shakeTime = 0.f;
    maxShakeAmount = sf::Vector2f(1.f, 1.f);
    shakeAmount = maxShakeAmount;
}

void GameManager::initialize()
{
    //randomize seed
    srand(time(NULL));

    _paddle = new Paddle(_window);
    _brickManager = new BrickManager(_window, this);
    _messagingSystem = new MessagingSystem(_window);
    _ball = new Ball(_window, 400.0f, this); 
    _powerupManager = new PowerupManager(_window, _paddle, _ball);
    _ui = new UI(_window, _lives, this);

    // Create bricks
    _brickManager->createBricks(5, 10, 80.0f, 30.0f, 5.0f);

}

void GameManager::update(float dt)
{
    _powerupInEffect = _powerupManager->getPowerupInEffect();
    _ui->updatePowerupText(_powerupInEffect);
    _powerupInEffect.second -= dt;
    

    if (_lives <= 0)
    {
        _masterText.setString("Game over.");
        return;
    } else if (_levelComplete)
    {
        _masterText.setString("Level completed.");
        return;
    }
    // pause and pause handling
    if (_pauseHold > 0.f) _pauseHold -= dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
    {
        if (!_pause && _pauseHold <= 0.f)
        {
            _pause = true;
            _masterText.setString("paused.");
            _pauseHold = PAUSE_TIME_BUFFER;
        }
        if (_pause && _pauseHold <= 0.f)
        {
            _pause = false;
            _masterText.setString("");
            _pauseHold = PAUSE_TIME_BUFFER;
        }
    }
    if (_pause)
    {
        return;
    }

    // timer.
    _time += dt;

    //powerup spawning
    powerupSpawnTime = _timeLastPowerupSpawned + POWERUP_FREQUENCY;
    if (_time > powerupSpawnTime && rand() % powerupRandomSpawnChance == 0)    
    {
        _powerupManager->spawnPowerup();
        _timeLastPowerupSpawned = _time;
    }

    // move paddle
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) _paddle->moveRight(dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) _paddle->moveLeft(dt);

   
    if (shakeTime>0)
    {
        screenshake(dt);
    }
    else {
        view.setCenter(viewBaseCentre);
        shakeAmount = maxShakeAmount;
    }

    // update everything 
    _paddle->update(dt);
    _ball->update(dt);
    _powerupManager->update(dt);
}

void GameManager::loseLife()
{
    //Reduce life
    _lives--;
    _ui->lifeLost(_lives);

    //Turn screenshake on
    shakeTime = maxShakeTime;
}

void GameManager::screenshake(float dt)
{
    //coinflip on if to reverse shake
    int xxReverse = (rand() % 2) + 1;
    int yyReverse = (rand() % 2) + 1;

    //x reverse and lerp and tend towards 0
    if (xxReverse == 1)  shakeAmount.x *= -1;

    //y reverse and tend towards 0
    if (yyReverse == 1) shakeAmount.y *= -1;

    //clamp shake amount
    if (shakeAmount.x > maxShakeAmount.x) shakeAmount.x = maxShakeAmount.x;
    if (shakeAmount.y > maxShakeAmount.y) shakeAmount.y = maxShakeAmount.y;

    //Set the views now shaken position
    view.setCenter(view.getCenter().x + shakeAmount.x, view.getCenter().y + shakeAmount.y);

    //tick down shake time
    shakeTime -= dt;
}

void GameManager::render()
{
    _window->setView(view);
    _paddle->render();
    _ball->render();
    _brickManager->render();
    _powerupManager->render();
    _window->draw(_masterText);
    _ui->render();
}

void GameManager::levelComplete()
{
    _levelComplete = true;
}

sf::RenderWindow* GameManager::getWindow() const { return _window; }
UI* GameManager::getUI() const { return _ui; }
Paddle* GameManager::getPaddle() const { return _paddle; }
BrickManager* GameManager::getBrickManager() const { return _brickManager; }
PowerupManager* GameManager::getPowerupManager() const { return _powerupManager; }
