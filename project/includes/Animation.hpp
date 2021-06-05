#pragma once

#include <SFML/Graphics.hpp>

class Animation {
public:
	Animation(sf::IntRect* rect, int framesNumber);
	void changeFrame();
	sf::IntRect getBounds();

private:
	sf::IntRect* bounds;
	int frames;
	sf::Clock clock;
	int resetValue;
};