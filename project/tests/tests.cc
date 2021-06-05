//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//              Final Project: PacMan Game : Student Test Cases             //
//                                                                          //
// Written By : Daniel Rugutt, AJ Jain, Ananay Mathur, Zuhair Ali           //
// Environment : VSCode                                                     //
// Date: May 5th, 2021:                         Compiler Vagrant and CLang  //
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up                             //
//////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"

//////////////////////////////////////////////////////////////////////////////
//                                 Includes                                 //
//////////////////////////////////////////////////////////////////////////////

#include "Animation.hpp"
#include "Console.hpp"
#include "Directions.hpp"
#include "Engine.hpp"
#include "Entity.hpp"
#include "GameState.hpp"
#include "Ghost.hpp"
#include "Labyrinth.hpp"
#include "PacMan.hpp"
#include "PlayingState.hpp"
#include "Resources.hpp"
#include "StateManager.hpp"
#include "TestSFML.hpp"

//////////////////////////////////////////////////////////////////////////////
//                                Test Cases                                //
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////

TEST_CASE("Setting up SFML Window and Console") {
    SECTION("Engine runs properly and window is properly launched and is open") {
        Engine::init();
        REQUIRE(Engine::isRunning());
        Engine::handleEvents();
	    Engine::render();
        REQUIRE(Engine::isRunning());
    }
    SECTION("Console properly write") {
        Console console("Test Console");
        
        std::ostringstream oss;
        std::streambuf* p_cout_streambuf = std::cout.rdbuf();
        std::cout.rdbuf(oss.rdbuf());

        console.writeLine("Writing to terminal");

        std::cout.rdbuf(p_cout_streambuf); // restore
        // test your oss content...
        REQUIRE(oss && oss.str() == "[Test Console]: Writing to terminal");
        std::cout << oss.str();
    }
    SECTION("Render window properly launches and closes with correct dimensions") {
        sf::RenderWindow test_window;
        test_window.create(sf::VideoMode(600, 900), "Test Window");
        REQUIRE(test_window.isOpen());
        sf::Vector2u test_vector;
        test_vector.x = 600;
        test_vector.y = 900;
        REQUIRE(test_window.getSize() == test_vector);
        test_window.close();
        REQUIRE_FALSE(test_window.isOpen());
    }
}

TEST_CASE( "Pacman Movement Game Mimic" ) {
    Entity entity();
    PlayingState playstate;
    PacMan pacman;
    REQUIRE(pacman.getLives() == 3);
    REQUIRE(pacman.getDotsEaten() == 0);
    REQUIRE_FALSE(pacman.isDead());
    playstate.keyPressed(0);
    REQUIRE(pacman.getScreenPosX() == 0);
    REQUIRE(pacman.getScreenPosY() == 0.4);
    playstate.keyReleased(1);
    playstate.keyPressed(1);
    Ghost ghost(0, 0, 0, 0);
    REQUIRE(pacman.getScreenPosX() == 0);
    REQUIRE(pacman.getScreenPosY() == 0);
    REQUIRE(pacman.getDotsEaten() == 1);
    ghost.setDestination(0, 0);
    REQUIRE_FALSE(pacman.isDead());
    REQUIRE(pacman.getLives() == 2);
    pacman.setDead(false);
    REQUIRE_FALSE(pacman.isDead());
    REQUIRE(pacman.getTileX() == 0);
    pacman.Teleport();
    REQUIRE(pacman.getScreenPosX() == 8);
    REQUIRE(pacman.getScreenPosY() == 8);
    playstate.keyPressed(0);
    REQUIRE(pacman.getScreenPosX() == 8);
}

TEST_CASE("Initializing level") {
    PlayingState* play = new PlayingState();
    play->init();
    REQUIRE(play->getPacManPoints() == 0);
    delete play;
}

TEST_CASE("Ghost") {
    PlayingState* play = new PlayingState();
    Ghost* ghost = new Ghost(13, 14, 3, 4);
    SECTION("Initializing ghost") {
        REQUIRE(ghost->getDestX() == 3);
        REQUIRE(ghost->getDestY() == 4);
        REQUIRE(ghost->getDirection() == Direction::Unset);
        REQUIRE_FALSE(ghost->isFrightened());
        REQUIRE_FALSE(ghost->isOutOfCage());
        REQUIRE_FALSE(ghost->isScattering());
    }

    SECTION("Moving ghost") {
        ghost->setDestination(1, 5);
        REQUIRE(ghost->getDestX() == 1);
        REQUIRE(ghost->getDestY() == 5);
        ghost->setDirection(Direction::Right);
        REQUIRE(ghost->getDirection() == Direction::Right);
        play->loop();
        REQUIRE_FALSE(ghost->getDirection() == Direction::Unset);
        REQUIRE(ghost->isOutOfCage());
    }

    SECTION("Scared ghosts") {
        ghost->setFrightened(true);
        ghost->setScattering(true);
        REQUIRE(ghost->isFrightened());
        REQUIRE(ghost->isScattering());
    }

    delete ghost;
    delete play;
}