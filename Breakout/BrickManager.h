#pragma once
#include <vector>
#include "Brick.h"
#include "Debris.h"
#include <SFML/Graphics.hpp>

class GameManager;

class BrickManager {
public:
    BrickManager(sf::RenderWindow* window, GameManager* gameManager);
    void createBricks(int rows, int cols, float brickWidth, float brickHeight, float spacing);
    void render();
    void update(float dt);
    int checkCollision(sf::CircleShape& ball, sf::Vector2f& direction);

private:
    std::vector<Brick> _bricks;
    std::vector<Debris*> _debris;
    sf::RenderWindow* _window;

    static constexpr int debrisAmount = 3;

    GameManager* _gameManager;
    static constexpr float TOP_PADDING = 100.0f;
};
