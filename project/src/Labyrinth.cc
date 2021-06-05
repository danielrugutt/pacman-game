#include "Labyrinth.hpp"

Labyrinth::Labyrinth() : tiles{ {30, 30, 30,  0, 13, 13, 13, 13, 13, 13, 13, 13,  1, 30, 30, 30,  8, 30,  9, 30, 30, 30,  0, 13, 13, 13, 13, 17, 28, 13, 13, 13, 13,  1, 30, 30},
								{30, 30, 30,  8, 26, 26, 27, 26, 26, 26, 26, 26,  9, 30, 30, 30,  8, 30,  9, 30, 30, 30,  8, 26, 26, 26, 27, 11, 10, 26, 26, 26, 26,  9, 30, 30},
								{30, 30, 30,  8, 26,  2, 14,  3, 26,  2,  3, 26,  9, 30, 30, 30,  8, 30,  9, 30, 30, 30,  8, 26,  2,  3, 26,  6,  7, 26,  2,  3, 26,  9, 30, 30},
								{30, 30, 30,  8, 26, 11, 30, 10, 26, 11, 10, 26,  9, 30, 30, 30,  8, 30,  9, 30, 30, 30,  8, 26, 11, 10, 26, 26, 26, 26, 11, 10, 26,  9, 30, 30},
								{30, 30, 30,  8, 26, 11, 30, 10, 26, 11, 10, 26,  9, 30, 30, 30,  8, 30,  9, 30, 30, 30,  8, 26, 11,  6, 14, 14,  3, 26, 11, 10, 26,  9, 30, 30},
								{30, 30, 30,  8, 26,  6, 15,  7, 26,  6,  7, 26,  6, 13, 13, 13,  7, 30,  6, 13, 13, 13,  7, 26,  6, 15, 15, 15,  7, 26, 11, 10, 26,  9, 30, 30},
								{30, 30, 30,  8, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 11, 10, 26,  9, 30, 30},
								{30, 30, 30,  8, 26,  2, 14,  3, 26,  2, 14, 14, 14, 14, 14, 14,  3, 30,  2, 14, 14, 14,  3, 26,  2,  3, 26,  2, 14, 14,  7, 10, 26,  9, 30, 30},
								{30, 30, 30,  8, 26, 11, 30, 10, 26,  6, 15, 15,  3,  2, 15, 15,  7, 30,  6, 15, 15, 15,  7, 26, 11, 10, 26,  6, 15, 15,  3, 10, 26,  9, 30, 30},
								{30, 30, 30,  8, 26, 11, 30, 10, 26, 26, 26, 26, 11, 10, 30, 30, 30, 30, 30, 30, 30, 30, 30, 26, 11, 10, 26, 26, 26, 26, 11, 10, 26,  9, 30, 30},
								{30, 30, 30,  8, 26, 11, 30, 10, 26,  2,  3, 26, 11, 10, 30, 18, 12, 12, 12, 19, 30,  2,  3, 26, 11, 10, 26,  2,  3, 26, 11, 10, 26,  9, 30, 30},
								{30, 30, 30,  8, 26,  6, 15,  7, 26, 11, 10, 26,  6,  7, 30,  9, 30, 30, 30,  8, 30, 11, 10, 26,  6,  7, 26, 11, 10, 26,  6,  7, 26,  9, 30, 30},
								{30, 30, 30,  8, 26, 26, 26, 26, 26, 11, 10, 26, 30, 30, 30,  9, 30, 30, 30,  8, 30, 11, 10, 26, 26, 26, 26, 11, 10, 26, 26, 26, 26,  9, 30, 30},
								{30, 30, 30, 24, 14, 14, 14,  3, 26, 11,  6, 14, 14,  3, 30, 31, 30, 30, 30,  8, 30, 11,  6, 14, 14,  3, 30, 11,  6, 14, 14,  3, 26,  9, 30, 30},
								{30, 30, 30, 16, 15, 15, 15,  7, 26, 11,  2, 15, 15,  7, 30, 31, 30, 30, 30,  8, 30, 11,  2, 15, 15,  7, 30, 11,  2, 15, 15,  7, 26,  9, 30, 30},
								{30, 30, 30,  8, 26, 26, 26, 26, 26, 11, 10, 26, 30, 30, 30,  9, 30, 30, 30,  8, 30, 11, 10, 26, 26, 26, 26, 11, 10, 26, 26, 26, 26,  9, 30, 30},
								{30, 30, 30,  8, 26,  2, 14,  3, 26, 11, 10, 26,  2,  3, 30,  9, 30, 30, 30,  8, 30, 11, 10, 26,  2,  3, 26, 11, 10, 26,  2,  3, 26,  9, 30, 30},
								{30, 30, 30,  8, 26, 11, 30, 10, 26,  6,  7, 26, 11, 10, 30, 22, 13, 13, 13, 23, 30,  6,  7, 26, 11, 10, 26,  6,  7, 26, 11, 10, 26,  9, 30, 30},
								{30, 30, 30,  8, 26, 11, 30, 10, 26, 26, 26, 26, 11, 10, 30, 30, 30, 30, 30, 30, 30, 30, 30, 26, 11, 10, 26, 26, 26, 26, 11, 10, 26,  9, 30, 30},
								{30, 30, 30,  8, 26, 11, 30, 10, 26,  2, 14, 14,  7,  6, 14, 14,  3, 30,  2, 14, 14, 14,  3, 26, 11, 10, 26,  2, 14, 14,  7, 10, 26,  9, 30, 30},
								{30, 30, 30,  8, 26,  6, 15,  7, 26,  6, 15, 15, 15, 15, 15, 15,  7, 30,  6, 15, 15, 15,  7, 26,  6,  7, 26,  6, 15, 15,  3, 10, 26,  9, 30, 30},
								{30, 30, 30,  8, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 11, 10, 26,  9, 30, 30},
								{30, 30, 30,  8, 26,  2, 14,  3, 26,  2,  3, 26,  2, 12, 12, 12,  3, 30,  2, 12, 12, 12,  3, 26,  2, 14, 14, 14,  3, 26, 11, 10, 26,  9, 30, 30},
								{30, 30, 30,  8, 26, 11, 30, 10, 26, 11, 10, 26,  9, 30, 30, 30,  8, 30,  9, 30, 30, 30,  8, 26, 11,  2, 15, 15,  7, 26, 11, 10, 26,  9, 30, 30},
								{30, 30, 30,  8, 26, 11, 30, 10, 26, 11, 10, 26,  9, 30, 30, 30,  8, 30,  9, 30, 30, 30,  8, 26, 11, 10, 26, 26, 26, 26, 11, 10, 26,  9, 30, 30},
								{30, 30, 30,  8, 26,  6, 15,  7, 26,  6,  7, 26,  9, 30, 30, 30,  8, 30,  9, 30, 30, 30,  8, 26,  6,  7, 26,  2,  3, 26,  6,  7, 26,  9, 30, 30},
								{30, 30, 30,  8, 26, 26, 27, 26, 26, 26, 26, 26,  9, 30, 30, 30,  8, 30,  9, 30, 30, 30,  8, 26, 26, 26, 27, 11, 10, 26, 26, 26, 26,  9, 30, 30},
								{30, 30, 30,  4, 12, 12, 12, 12, 12, 12, 12, 12,  5, 30, 30, 30,  8, 30,  9, 30, 30, 30,  4, 12, 12, 12, 12, 25, 20, 12, 12, 12, 12,  5, 30, 30} } {} //setup tiles based on labrinth png

int Labyrinth::getTileCode(int x, int y) {
	return tiles[x][y];
}

bool Labyrinth::tileBlocksEntity(int x, int y) {
	return tiles[x][y] != 30 && tiles[x][y] != 26 && tiles[x][y] != 27;
}

bool Labyrinth::isIntersection(int x, int y) {
	return (x == 1 && y == 4) || (x == 6 && y == 4) || (x == 12 && y == 4) || (x == 15 && y == 4) || (x == 21 && y == 4) || (x == 26 && y == 4)
		|| (x == 1 && y == 8) || (x == 6 && y == 8) || (x == 9 && y == 8) || (x == 12 && y == 8) || (x == 15 && y == 8) || (x == 18 && y == 8) || (x == 21 && y == 8) || (x == 26 && y == 8)
		|| (x == 1 && y == 11) || (x == 6 && y == 11) || (x == 9 && y == 11) || (x == 12 && y == 11) || (x == 15 && y == 11) || (x == 18 && y == 11) || (x == 21 && y == 11) || (x == 26 && y == 11)
		|| (x == 9 && y == 14) || (x == 12 && y == 14) || (x == 15 && y == 14) || (x == 18 && y == 14)
		|| (x == 6 && y == 17) || (x == 9 && y == 17) || (x == 12 && y == 17) || (x == 15 && y == 17) || (x == 18 && y == 17) || (x == 21 && y == 17) || (x == 26 && y == 17)
		|| (x == 9 && y == 20) || (x == 18 && y == 20)
		|| (x == 1 && y == 23) || (x == 9 && y == 23) || (x == 6 && y == 23) || (x == 12 && y == 23) || (x == 15 && y == 23) || (x == 18 && y == 23) || (x == 21 && y == 23) || (x == 26 && y == 23)
		|| (x == 1 && y == 26) || (x == 3 && y == 26) || (x == 6 && y == 26) || (x == 9 && y == 26) || (x == 12 && y == 26) || (x == 15 && y == 26) || (x == 18 && y == 26) || (x == 21 && y == 26) || (x == 24 && y == 26) || (x == 26 && y == 26)
		|| (x == 1 && y == 29) || (x == 3 && y == 29) || (x == 6 && y == 29) || (x == 9 && y == 29) || (x == 12 && y == 29) || (x == 15 && y == 29) || (x == 18 && y == 29) || (x == 21 && y == 29) || (x == 24 && y == 29) || (x == 26 && y == 29)
		|| (x == 1 && y == 32) || (x == 12 && y == 32) || (x == 15 && y == 32) || (x == 26 && y == 32)
		|| (x == 13 && y == 14) || (x == 14 && y == 15); //based on board specifications -- can be improved
}

void Labyrinth::removeDot(PacMan* pacman, Ghost* ghost1, Ghost* ghost2, Ghost* ghost3, Ghost* ghost4) {
	if (tiles[pacman->getTileX()][pacman->getTileY()] == 26) {
		tiles[pacman->getTileX()][pacman->getTileY()] = 30;
		pacman->eatDot();
	} else if (tiles[pacman->getTileX()][pacman->getTileY()] == 27) {
		tiles[pacman->getTileX()][pacman->getTileY()] = 30;
		ghost1->setFrightened(true);
		ghost2->setFrightened(true);
		ghost3->setFrightened(true);
		ghost4->setFrightened(true);
	}
}
