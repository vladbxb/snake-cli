#include <string>
#include <vector>
#include "ncurses.h"
#include "time.h"
#include "unistd.h"

#include "game.h"
#include "snake.h"
#include "food.h"

WINDOW* wnd;
rectangle window_area = { {0, 0}, {80, 24} };
int screen_height, screen_width;

Snake s;

Food f;


void init_ncurses() {
	srand(time(0));
	initscr();
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
				if (s.getDirY() != 1) {
					s.changeDir(0, -1);
				}
				break;
			case KEY_DOWN:
			case 's':
				if (s.getDirY() != -1) {
					s.changeDir(0, 1);
				}
				break;
			case KEY_LEFT:
			case 'a':
				if (s.getDirX() != 1) {
					s.changeDir(-1, 0);
				}
				break;
			case KEY_RIGHT:
			case 'd':
				if (s.getDirX() != -1) {
					s.changeDir(1, 0);
				}
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

	f.pickLocation(window_area, s);

	return 0;
};



void run() {
	int in_char;

	bool exit_requested = false;

	while(1) {
		in_char = wgetch(wnd);

		s.update();

		checkOutOfBounds(s);

		changeDirection(in_char, exit_requested, s);

		s.show();
		f.draw();

		if (s.eat(f.getPos())) {
			f.pickLocation(window_area, s);
		}

		refresh();

		if (exit_requested || s.checkBodyCollision(s.getHead())) break;

		usleep(80000);
	}
}



void close() {
	endwin();
}

