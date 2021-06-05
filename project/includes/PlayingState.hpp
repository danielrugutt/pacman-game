#pragma once

#include "GameState.hpp"

#include "Console.hpp"
#include "Labyrinth.hpp"
#include "Entity.hpp"
#include "PacMan.hpp"
#include "Ghost.hpp"

class PlayingState :
	public GameState
{
private:
	Console* console;
	Labyrinth* labyrinth;
	PacMan* pacman;
	Ghost* blinky;
	Ghost* pinky;
	Ghost* inky;
	Ghost* clyde;

	int waitTime;
	bool paused;

	bool pacmanCanMove();
	void handleGhostMovement(Ghost* ghost);
	bool ghostCanMove(Ghost* ghost);
	float calculateDistance(Ghost* ghost, int addX, int addY);
	void teleportTunnels(Entity* entity);
	void handleGhostFrightening(Ghost* ghost);

public:
	void init();
	void loop();
	void render(sf::RenderWindow* window);
	void keyPressed(int code);
	void keyReleased(int code);
	void saveData(std::string name, int score);
	int getPacManPoints();
};