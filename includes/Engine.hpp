#pragma once

#include <SFML/Graphics.hpp>
#include "Console.hpp"
#include "StateManager.hpp"
#include "Player.hpp"

class Engine
{
private:
	static sf::RenderWindow window;
	static Console console;
	static StateManager gamestates;

public:
	static void init();
	static bool isRunning();
	static void handleEvents();
	static void render();
	static void scoreboard(int score);
	void printBoard();
};

std::ostream& operator<<( std::ostream& os, const Player& player );