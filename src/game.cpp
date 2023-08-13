#include <string>
#include <cmath>
#include <vector>
#include "ncurses.h"
#include "time.h"
#include "unistd.h"

#include "game.h"

WINDOW* wnd;
rectangle window_area = { {0, 0}, {80, 24} };
int screen_height, screen_width;




class Snake {
	private:
		std::vector<coord> body;
		coord startPosition = {5, 5};
		// start speed
		coord speed = {1, 0};
		int display_character = 'o';
	public:
		// constructor adds a head on first position

		Snake() {
			this->body.push_back(this->startPosition);
		}

		int getHeadX() {
			return this->body[0].x;
		}
		int getHeadY() {
			return this->body[0].y;
		}
		coord getHead() {
			return this->body[0];
		}
		void setHeadX(int x) {
			this->body[0].x = x; 
		}
		void setHeadY(int y) {
			this->body[0].y = y;
		}

		void update() {
			mvaddch(this->body.back().y, this->body.back().x, ' ');
			for (int i = this->body.size() - 1; i > 0; i--) {
				this->body[i] = this->body[i-1];
			}
			this->body[0].x = this->body[0].x + this->speed.x;
			this->body[0].y = this->body[0].y + this->speed.y;
			/*
			this->body[0].x = constrain(this->body[0].x, window_area.left() + 1, window_area.right() - 2);
			this->body[0].y = constrain(this->body[0].y, window_area.top() + 1, window_area.bottom() - 2);
			*/
		}

		void show() {
			attron(COLOR_PAIR(2));
			mvaddch(this->body[0].y, this->body[0].x, this->display_character);
			for (size_t i = 1; i < this->body.size(); i++) {
				mvaddch(this->body[i].y, this->body[i].x, this->display_character);
			}
			attroff(COLOR_PAIR(2));
		}

		coord getSpeed() {
			return this->speed;
		}

		void dir(int x, int y) {
			this->speed.x = x;
			this->speed.y = y;
		}

		bool eat(coord food) {
			if (this->body[0].x == food.x && this->body[0].y == food.y) {
				this->body.push_back(this->body.back());
				return true;
			}
			return false;
		}

		bool checkBodyCollision(coord pos) {
			for (size_t i=2; i<body.size(); i++) {
				if (pos.x == body[i].x && pos.y == body[i].y) {
					return true;
				}
			}
			return false;
		}

		void growTail() {
			this->body.push_back(this->body.back());
		}

}s;


class Food {
	public:
		coord pos;
		int display_character = '*';
		void pickLocation() {
			mvaddch(this->pos.y, this->pos.x, ' ');

			do {
			this->pos.x = constrain(abs(rand() % 100 - (99 - window_area.bounds.x)), 1, 78);
			this->pos.y = constrain(abs(rand() % 100 - (99 - window_area.bounds.y)), 1, 22);
			} while (s.checkBodyCollision(pos));

			attron(COLOR_PAIR(3));
			mvaddch(this->pos.y, this->pos.x, this->display_character);
			attroff(COLOR_PAIR(3));
		}
}f;



void init_ncurses() {
	srand(time(0));
	initscr();
	//window_area.bounds = {80, 24};
	wnd = newwin(window_area.bounds.y, window_area.bounds.x, 0, 0);
	cbreak();
	noecho();
	clear();
	refresh();
	keypad(wnd, true);
	nodelay(wnd, true);
	curs_set(0);
}

void makeCanvas() {
	if(!has_colors()) {
        	endwin();
        	printf("ERROR: Terminal does not support color.\n");
        	exit(1);
	}
	
	start_color();



	//getmaxyx(wnd, screen_height, screen_width);

	//window_area.bounds = {screen_width, screen_height};



	//makes a box around the terminal in bold font
	attron(A_BOLD);
	box(wnd, 0, 0);
	attroff(A_BOLD);
	//changes color scheme to black and white

    	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
    	//wbkgd(wnd, COLOR_PAIR(1));
}

void redrawCanvas() {
	//init_pair(1, COLOR_WHITE, COLOR_BLACK);
    	// wbkgd(wnd, COLOR_PAIR(1));
}

void changeDirection(int in_char, bool &exit_requested, Snake &s) {
	switch (in_char) {
			case 'q':
				exit_requested = true;
				break;
			case 'f':
				s.growTail();
				break;
			case KEY_UP:
			case 'w':
				s.dir(0, -1);
				break;
			case KEY_DOWN:
			case 's':
				s.dir(0, 1);
				break;
			case KEY_LEFT:
			case 'a':
				s.dir(-1, 0);
				break;
			case KEY_RIGHT:
			case 'd':
				s.dir(1, 0);
				break;
			default:
				break;
	}
}


void checkOutOfBounds(Snake &s) {
		if (window_area.topCollision(s.getHead())) {
			s.setHeadY(window_area.bottom() - 2);
		}
		if (window_area.rightCollision(s.getHead())) {
			s.setHeadX(window_area.left() + 1);
		}
		if (window_area.bottomCollision(s.getHead())) {
			s.setHeadY(window_area.top() + 1);
		}
		if (window_area.leftCollision(s.getHead())) {
			s.setHeadX(window_area.right() - 2);
		}
}


int init() {
	init_ncurses();
	makeCanvas();

	refresh();

	f.pickLocation();

	return 0;
};



void run() {
	int in_char;

	bool exit_requested = false;

	while(1) {
		in_char = wgetch(wnd);
		
		redrawCanvas();	

		s.update();

		checkOutOfBounds(s);

		changeDirection(in_char, exit_requested, s);

		s.show();

		if (s.eat(f.pos)) {
			f.pickLocation();
		}

		refresh();

		if (exit_requested || s.checkBodyCollision(s.getHead())) break;

		usleep(80000);
	}
}



void close() {
	endwin();
}


int constrain(int x, int a, int b) {
	if (a < x && x < b) {
		return x;
	}
	if (x <= a) {
		return a;
	}
	return b;
}

int abs(int n) {
	if (n >= 0) {
		return n;
	}
	return n * -1;
}


