#pragma once

#include <SFML/Graphics.hpp>

#include "Directions.hpp"
#include "Console.hpp"
#include "Animation.hpp"

#include <map>

class Resources {
public:
	static void load();
	static sf::Sprite* get(int value, bool animated, Direction facing);

	static sf::Sprite* LabyrinthPieces[];

	static const int PacMan;
	static const int Blinky;
	static const int Pinky;
	static const int Inky;
	static const int Clyde;
	static const int FrightenedGhost;
	static const int DeadPacMan;

private:
	static sf::Texture theObjects;
	static sf::Texture Labyrinth;
	static Console console;

	static std::map<int, sf::Sprite*> sprites;
	static std::map<int, Animation> animations;

	static void loadSprite(int value, int rect1, int rect2, int animationframes);

	static const int PacManDown;
	static const int PacManLeft;
	static const int PacManRight;
	static const int BlinkyDown;
	static const int BlinkyLeft;
	static const int BlinkyRight;
	static const int PinkyDown;
	static const int PinkyLeft;
	static const int PinkyRight;
	static const int InkyDown;
	static const int InkyLeft;
	static const int InkyRight;
	static const int ClydeDown;
	static const int ClydeLeft;
	static const int ClydeRight;
};