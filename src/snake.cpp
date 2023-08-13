#include <iostream>
#include <vector>

#include "ncurses.h"
#include "game.h"
#include "snake.h"

//constructor creates the snake head

Snake::Snake() { this->body.push_back(this->startPosition); }

int Snake::getHeadX() { return this->body[0].x; }
int Snake::getHeadY() { return this->body[0].y; }
coord Snake::getHead() { return this->body[0]; }
coord Snake::getSpeed() { return this->speed; }

void Snake::setHeadX(int x) { this->body[0].x = x; }
void Snake::setHeadY(int y) { this->body[0].y = y; }

void Snake::update() {
	mvaddch(this->body.back().y, this->body.back().x, ' ');
	for (int i = this->body.size() - 1; i > 0; i--) {
		this->body[i] = this->body[i-1];
	}
	this->body[0].x = this->body[0].x + this->speed.x;
	this->body[0].y = this->body[0].y + this->speed.y;
}

void Snake::show() {
	attron(COLOR_PAIR(2));
	mvaddch(this->body[0].y, this->body[0].x, this->display_character);
	for (size_t i = 1; i < this->body.size(); i++) {
		mvaddch(this->body[i].y, this->body[i].x, this->display_character);
	}
	attroff(COLOR_PAIR(2));
}

void Snake::changeDir(int x, int y) {
	this->speed.x = x;
	this->speed.y = y;
}

int Snake::getDirX() { return this->speed.x; }
int Snake::getDirY() { return this->speed.y; }
coord Snake::getDir() { return this->speed; }


bool Snake::eat(coord food) {
	if (this->body[0].x == food.x && this->body[0].y == food.y) {
		this->body.push_back(this->body.back());
		return true;
	}
	return false;
}

bool Snake::checkBodyCollision(coord pos) {
	for (size_t i=2; i<body.size(); i++) {
		if (pos.x == body[i].x && pos.y == body[i].y) {
			return true;
		}
	}
	return false;
}

//duplic elementul de pe ultima pozitie, ca dupa sa isi dea update
//cand se apeleaza update() la impingerea fiecarui element in jos
//
void Snake::growTail() { this->body.push_back(this->body.back()); }
