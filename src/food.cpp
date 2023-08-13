#include <algorithm>
#include <iostream>
#include <vector>
#include "ncurses.h"
#include "game.h"
#include "snake.h"
#include "food.h"

void Food::draw() {
	attron(COLOR_PAIR(3));
	mvaddch(this->pos.y, this->pos.x, this->display_character);
	attroff(COLOR_PAIR(3));
}

void Food::pickLocation(rectangle window_area, Snake &s) {
	mvaddch(this->pos.y, this->pos.x, ' ');
	do {
		this->pos.x = std::clamp(std::abs(rand() % 100 - (99 - window_area.bounds.x)), 1, 78);
		this->pos.y = std::clamp(std::abs(rand() % 100 - (99 - window_area.bounds.y)), 1, 22);
	} while (s.checkBodyCollision(pos));

	Food::draw();
}

coord Food::getPos() { return this->pos; }
int Food::getPosX() { return this->pos.x; }
int Food::getPosY() { return this->pos.y; }
