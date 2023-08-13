#ifndef SNAKE_H
#define SNAKE_H

class Snake {
	private:
		std::vector<coord> body;
		coord startPosition = {5, 5};
		coord speed = {1, 0};
		int display_character = 'o';
	public:
		Snake();

		int getHeadX();
		int getHeadY();
		coord getHead();
		coord getSpeed();

		void setHeadX(int x);
		void setHeadY(int y);

		void update();

		void show();

		void changeDir(int x, int y);
		int getDirX();
		int getDirY();
		coord getDir();

		bool eat(coord food);

		bool checkBodyCollision(coord pos);

		void growTail();

};

#endif
