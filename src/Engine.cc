#include "Engine.hpp"

#include "PlayingState.hpp"
#include "Resources.hpp"
#include "sqlite_orm.hpp"
#include "json.hpp"

#include <string>
#include <iostream>

using namespace sqlite_orm;
using json = nlohmann::json;
using namespace sf;

RenderWindow Engine::window;
Console Engine::console("Engine");
StateManager Engine::gamestates;
//
PlayingState* play = new PlayingState();
//
void Engine::init() {
	console.writeLine("Init...");
	Resources::load();
	window.create(VideoMode(448, 596), "PacMan Game");
	console.writeLine("Created window");
	// Originally: gamestates.addState(new PlayingState);
	gamestates.addState(play);
	//
	auto storage = make_storage(
      "scoreboard.db",
      make_table("scoreboard",
                 make_column("id", &Player::id, autoincrement(), primary_key()),
                 make_column("name", &Player::name),
				 make_column("score", &Player::score))
                 );
	storage.sync_schema();
	//
}

bool Engine::isRunning() {
	return window.isOpen();
}

void Engine::handleEvents() {
	Event event;
	while (window.pollEvent(event)) {
		switch (event.type) {
			case Event::Closed:
				console.writeLine("Closing window...");
				//
				scoreboard(play->getPacManPoints());
				//
				window.close();
				break;
			case Event::KeyPressed:
				gamestates.keyPressed(event.key.code);
				break;
			case Event::KeyReleased:
				gamestates.keyReleased(event.key.code);
				break;
		}
	}
	gamestates.loop();
}

//
void Engine::scoreboard(const int score) {
	std::string name;
	std::cout << "Enter your name: ";
	std::cin >> name;
	Player player;
	player.id = -1;
	player.name = name;
	player.score = score;
	storage.insert(player);
	printBoard();
}
//
void Engine::printBoard() {
	json j_params = json::array();
    std::vector<Player> players = storage.get_all<Player>();
    for (size_t i = 0; i < players.size(); i++) {
    	json j;
        j["name"] = players.at(i).name;
        j["score"] = players.at(i).score;
        j_params.push_back({j});
		std::cout << players.at(i) << std::endl; 
    }

	std::cout << j_params << std::endl;
}
//
std::ostream& operator<<( std::ostream& os, const Player& player ) {
	os << "+--------------+" << "\n";
	os << "| " << player.name << " | " << player.score << " |" << "\n";
	os << "+--------------+" << "\n";
	return os;
}
//


void Engine::render()
{
	window.clear(Color::Black);
	gamestates.render(& window);
	window.display();
}
