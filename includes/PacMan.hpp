#pragma once

#include "Entity.hpp"

#include <queue>
#include "Directions.hpp"

class PacMan
	: public Entity
{
private:
	std::queue<Direction> directions;
	int eatenDots;
	bool dead;

public:
	PacMan();

	void queueDirection(Direction dir);
	void move();
	std::queue<Direction> getDirections();
	void stop();

	void eatDot();
	int getDotsEaten();
	int getLives();
	void setLives(int num) {
		lives = num;
	}

	void setDead(bool d);
	bool isDead();
	int lives;
};