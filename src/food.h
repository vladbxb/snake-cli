#ifndef FOOD_H
#define FOOD_H

class Food {
	private:
		coord pos;
		int display_character = '*';
	public:
		void draw();
		void pickLocation(rectangle window_area, Snake &s);
		coord getPos();
		int getPosX();
		int getPosY();
};

#endif
