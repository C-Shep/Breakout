#pragma once
#include <SFML/Graphics.hpp>

class Trail
{
public:
	Trail(float x, float y, sf::RenderWindow* window);
	~Trail();

	void update(float dt);
	void render();
	int getAlpha();

private:

	sf::CircleShape sprite;
	sf::RenderWindow* _window;

	float trailRadius;
	float alpha;
	float fadeSpeed;
	sf::Color trailColour;

	int startAlpha = 255;
	int endAlpha = 0;
};

