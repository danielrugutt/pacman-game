#include "PlayingState.hpp"

#include <SFML/Graphics.hpp>

#include "Resources.hpp"
#include "PacMan.hpp"
#include "Directions.hpp"
#include "Ghost.hpp"
#include "Player.hpp"
#include "Engine.hpp"

#include <cmath>
#include <random>
#include <cstdlib>
#include <assert.h>
#include <iostream>

using namespace sf;

void PlayingState::init() {
	console = new Console("PlayingState");

	labyrinth = new Labyrinth();

	pacman = new PacMan();
	blinky = new Ghost(13, 14, 3, 4);
	pinky = new Ghost(13, 17, 23, 4);
	inky = new Ghost(11, 17, 26, 32);
	clyde = new Ghost(15, 17, 1, 32);

	blinky->teleport(13, 14);

	console->writeLine("Finish initializing playing state");

	console->writeLine("Init done");

	waitTime = 0;
	
	// Open a textbox to input name
	this->paused = false;

	Window window;
	std::string name;

	window.setKeyRepeatEnabled(false);

	while (window.isOpen()) {
		window.display();
		Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
				case (Event::Closed):
				window.close();
				break;
				case (Event::TextEntered):
				if (event.text.unicode >= 33 && event.text.unicode <= 126) {
					assert(name.size() <= 3/*, "Enter only 3 characters"*/);
					name += (char)event.text.unicode;
				} else if (event.text.unicode == 8) {
					name = name.substr(0, name.length() - 1);
				}
			}
		}
		
	}
}

void PlayingState::loop() {
	if (pacmanCanMove() && !pacman->isDead()) {
		pacman->move();
	} else {
		pacman->stop();
	}
		
	if (labyrinth->isIntersection(pacman->getTileX(), pacman->getTileY())) {
		pacman->stop();
	}
		
	labyrinth->removeDot(pacman, blinky, pinky, inky, clyde);

	if (!pacman->getDirections().empty()) {
		if (!blinky->isScattering()) {
			blinky->setDestination(pacman->getTileX(), pacman->getTileY());
		}
			
		if (!pinky->isScattering()) {
			switch (pacman->getDirections().front()) {
			case Direction::Up:
				pinky->setDestination(pacman->getTileX(), pacman->getTileY() - 4);
				break;
			case Direction::Down:
				pinky->setDestination(pacman->getTileX(), pacman->getTileY() + 4);
				break;
			case Direction::Left:
				pinky->setDestination(pacman->getTileX() - 4, pacman->getTileY());
				break;
			case Direction::Right:
				pinky->setDestination(pacman->getTileX() + 4, pacman->getTileY());
				break;
			}
		}
		
		if(!inky->isScattering()) {
			inky->setDestination(pacman->getTileX() + (blinky->getTileX() - pacman->getTileX()), pacman->getTileY() + (blinky->getTileY() - pacman->getTileY()));	
		}
		
		if (!clyde->isScattering()) {
			if (sqrt(pow((clyde->getTileX() - (pacman->getTileX())), 2) + pow((clyde->getTileY() - (pacman->getTileY())), 2)) < 9) {
				clyde->setDestination(pacman->getTileX(), pacman->getTileY());
			} else {
				clyde->setDestination(1, 32);
			}
		}
	}
	
	handleGhostMovement(blinky);
	handleGhostMovement(pinky);
	handleGhostMovement(inky);
	handleGhostMovement(clyde);

	//teleports ghosts depending on how many dots the pacman has ate
	if(pacman->getDotsEaten() == 5)
		pinky->teleport(13, 14);
	if (pacman->getDotsEaten() == 50)
		inky->teleport(13, 14);
	if (pacman->getDotsEaten() == 100)
		clyde->teleport(13, 14);

	teleportTunnels(pacman);
	teleportTunnels(blinky);
	teleportTunnels(pinky);
	teleportTunnels(inky);
	teleportTunnels(clyde);

	handleGhostFrightening(blinky);
	handleGhostFrightening(pinky);
	handleGhostFrightening(inky);
	handleGhostFrightening(clyde);

	if (pacman->getDotsEaten() == 240) { //end of round
		blinky->teleport(-2, -2);
		pinky->teleport(-2, -2);
		inky->teleport(-2, -2);
		clyde->teleport(-2, -2);
		waitTime++;
	}

	if (pacman->isDead()) {
		waitTime++;
	}
		
	if (waitTime == 200) {
		if (pacman->isDead()) {
			if (blinky->isOutOfCage())  blinky->teleport(13, 14);
			if (pinky->isOutOfCage()) pinky->teleport(13, 14);
			if (inky->isOutOfCage()) inky->teleport(13, 14);
			if (clyde->isOutOfCage()) clyde->teleport(13, 14);
			pacman->teleport(13, 26);
			pacman->setDead(false);
			int lives = pacman->getLives();
			lives--;
			pacman->setLives(lives);
			waitTime = 0;
		} else {
			PlayingState::init();
			waitTime = 0;
		}
	}
	if (pacman->getLives() == 0) {
		console->writeLine("Game over :(");
		Engine::scoreboard(pacman->getDotsEaten());
		pacman->setLives(3);
		pacman->setDead(false);
		PlayingState::init();
		waitTime = 0;
	}
}

int PlayingState::getPacManPoints() {
	return pacman->getDotsEaten();
}

// void PlayingState::SaveData(std::string& name, int& score) {
// 	Player player;
// 	player.name = name;
// 	player.score = score;
// }

void PlayingState::render(RenderWindow* window)
{
	Sprite pacmanSprite;
	Sprite blinkySprite;
	Sprite pinkySprite;
	Sprite inkySprite;
	Sprite clydeSprite;

	if (pacman->getDirections().empty()) {
		pacmanSprite = *Resources::get(Resources::PacMan, false, Direction::Unset);
	} else {
		pacmanSprite = *Resources::get(Resources::PacMan, true, pacman->getDirections().front());
	}
		
	if (pacman->isDead()) {
		pacmanSprite = *Resources::get(Resources::DeadPacMan, true, Direction::Unset);
	}
		
	if (!blinky->isFrightened()) {
		blinkySprite = *Resources::get(Resources::Blinky, blinky->isOutOfCage(), blinky->getDirection());
	} else {
		blinkySprite = *Resources::get(Resources::FrightenedGhost, blinky->isOutOfCage(), blinky->getDirection());
	}
		
	if (!pinky->isFrightened()) {
		pinkySprite = *Resources::get(Resources::Pinky, pinky->isOutOfCage(), pinky->getDirection());
	} else {
		pinkySprite = *Resources::get(Resources::FrightenedGhost, pinky->isOutOfCage(), pinky->getDirection());
	}
		
	if (!inky->isFrightened()) {
		inkySprite = *Resources::get(Resources::Inky, inky->isOutOfCage(), inky->getDirection());
	} else {
		inkySprite = *Resources::get(Resources::FrightenedGhost, inky->isOutOfCage(), inky->getDirection());
	}
		
	if(!clyde->isFrightened()) {
		clydeSprite = *Resources::get(Resources::Clyde, clyde->isOutOfCage(), clyde->getDirection());
	} else {
		clydeSprite = *Resources::get(Resources::FrightenedGhost, clyde->isOutOfCage(), clyde->getDirection());
	}
		
	pacmanSprite.setPosition(pacman->getScreenPosX(), pacman->getScreenPosY());
	blinkySprite.setPosition(blinky->getScreenPosX(), blinky->getScreenPosY());
	pinkySprite.setPosition(pinky->getScreenPosX(), pinky->getScreenPosY());
	inkySprite.setPosition(inky->getScreenPosX(), inky->getScreenPosY());
	clydeSprite.setPosition(clyde->getScreenPosX(), clyde->getScreenPosY());

	for (int i = 0; i < Labyrinth::SizeX; i++) {
		for (int j = 0; j < Labyrinth::SizeY; j++) {
			Resources::LabyrinthPieces[labyrinth->getTileCode(i, j)]->setPosition(i * 16.0f, j * 16.0f);
			window->draw(*Resources::LabyrinthPieces[labyrinth->getTileCode(i, j)]);
		}
	}

	window->draw(pacmanSprite);
	window->draw(blinkySprite);
	window->draw(pinkySprite);
	window->draw(inkySprite);
	window->draw(clydeSprite);
}


void PlayingState::keyPressed(int code)
{
	switch (code)
	{
	case Keyboard::Up:
		pacman->queueDirection(Direction::Up);
		break;
	case Keyboard::Down:
		pacman->queueDirection(Direction::Down);
		break;
	case Keyboard::Left:
		pacman->queueDirection(Direction::Left);
		break;
	case Keyboard::Right:
		pacman->queueDirection(Direction::Right);
		break;
	// case Keyboard::P:
	// 	if (!paused) {
	// 		PlayingState::ghostCanMove();
	// 		PlayingState::pacmanCanMove();
	// 		break;
	// 	}
	// 	!PlayingState::ghostCanMove();
	// 	!PlayingState::pacmanCanMove();
	// 	paused = true;
	}
}

void PlayingState::keyReleased(int code)
{
	
}

bool PlayingState::pacmanCanMove() {
	if (!pacman->getDirections().empty()) {
		switch (pacman->getDirections().front()) {
			case Direction::Up:
				return !labyrinth->tileBlocksEntity(pacman->getTileX(), pacman->getTileY() - 1);
				break;
			case Direction::Down:
				return !labyrinth->tileBlocksEntity(pacman->getTileX(), pacman->getTileY() + 1);
				break;
			case Direction::Left:
				return !labyrinth->tileBlocksEntity(pacman->getTileX() - 1, pacman->getTileY());
				break;
			case Direction::Right:
				return !labyrinth->tileBlocksEntity(pacman->getTileX() + 1, pacman->getTileY());
				break;
		}
	}
	return true;
}

void PlayingState::handleGhostMovement(Ghost* ghost) {
	if (ghost->isScattering()) {
		if (ghost->getTileX() == ghost->getDestX() && ghost->getTileY() == ghost->getDestY()) {
			ghost->setScattering(false);
		}
	}

	if (labyrinth->isIntersection(ghost->getTileX(), ghost->getTileY())) {
		if (ghost->shouldTakeDecision()) {
			float dirRight = calculateDistance(ghost, 1, 0);
			float dirLeft = calculateDistance(ghost, -1, 0);
			float dirUp = calculateDistance(ghost, 0, -1);
			float dirDown = calculateDistance(ghost, 0, 1);

			if (dirRight < dirLeft && dirRight < dirUp && dirRight < dirDown) {
				ghost->setDirection(Direction::Right);
			} else if (dirLeft < dirRight && dirLeft < dirUp && dirLeft < dirDown) {
				ghost->setDirection(Direction::Left);
			} else if (dirUp < dirLeft && dirUp < dirRight && dirUp < dirDown) {
				ghost->setDirection(Direction::Up);
			} else if (dirDown < dirLeft && dirDown < dirUp && dirDown < dirRight) {
				ghost->setDirection(Direction::Down);
			}
		}
		ghost->setTakeDecision(false);
	} else {
		ghost->setTakeDecision(true);
	}
	if (ghostCanMove(ghost) && ghost->isOutOfCage()) {
		ghost->move();
	} else {
		ghost->setTakeDecision(true);
	}	
}

bool PlayingState::ghostCanMove(Ghost* ghost) {
	switch (ghost->getDirection()) {
		case Direction::Up:
			return !labyrinth->tileBlocksEntity(ghost->getTileX(), ghost->getTileY() - 1);
			break;
		case Direction::Down:
			return !labyrinth->tileBlocksEntity(ghost->getTileX(), ghost->getTileY() + 1);
			break;
		case Direction::Left:
			return !labyrinth->tileBlocksEntity(ghost->getTileX() - 1, ghost->getTileY());
			break;
		case Direction::Right:
			return !labyrinth->tileBlocksEntity(ghost->getTileX() + 1, ghost->getTileY());
			break;
		default:
			return false;
	}
}

float PlayingState::calculateDistance(Ghost* ghost, int addX, int addY) {
	float distance = 1000000.0f;
	if (!labyrinth->tileBlocksEntity(ghost->getTileX() + addX, ghost->getTileY() + addY)) {
		distance = (float) sqrt(pow((ghost->getDestX() - (ghost->getTileX() + addX)), 2) + pow((ghost->getDestY() - (ghost->getTileY() + addY)), 2));
	}
	return distance;
}

void PlayingState::teleportTunnels(Entity* entity) {
	if (entity->getTileX() == 0 && entity->getTileY() == 17) {
		entity->teleport(26, 17);
	} else if (entity->getTileX() == 27 && entity->getTileY() == 17) {
		entity->teleport(1, 17);
	}	
}

void PlayingState::handleGhostFrightening(Ghost* ghost) {
	if (pacman->getTileX() == ghost->getTileX() && pacman->getTileY() == ghost->getTileY()) {
		if (ghost->isFrightened()) {
			ghost->teleport(13, 14);
			ghost->setFrightened(false);
		} else {
			pacman->setDead(true);
			blinky->teleport(-2, -2);
			pinky->teleport(-2, -2);
			inky->teleport(-2, -2);
			clyde->teleport(-2, -2);
		}
	}
}
