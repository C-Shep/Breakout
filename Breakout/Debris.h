#pragma once
#include <SFML/Graphics.hpp>

class Debris
{
public:
	Debris(float x, float y, sf::RenderWindow* window);
	~Debris();

	void update(float dt);
	void render();
	sf::Vector2f getPosition();
private:

	sf::CircleShape sprite;
	sf::Vector2f direction;
	sf::RenderWindow* _window;

	float debrisRadius;
	float velocity;
	float gravity;
};

