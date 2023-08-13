int init();
void init_ncurses();
void makeCanvas();
void run();
void close();

typedef struct {
	int x;
	int y;
}coord;


struct rectangle {
	coord offset;
	coord bounds;

	int top() {
		return offset.y;
	}

	int bottom() {
		return offset.y + bounds.y;
	}

	int left() {
		return offset.x;
	}

	int right() {
		return offset.x + bounds.x;
	}

	int width() {
		return bounds.x;
	}

	int height() {
		return bounds.y;
	}

	bool topCollision(coord pos) {
		if (pos.y <= top()) {
			return true;
		}
		return false;
	}
	
	bool rightCollision(coord pos) {
		if (pos.x >= right() - 1) {
			return true;
		}
		return false;
	}

	bool bottomCollision(coord pos) {
		if (pos.y >= bottom() - 1) {
			return true;
		}
		return false;
	}

	bool leftCollision(coord pos) {
		if (pos.x <= left()) {
			return true;
		}
		return false;
	}
};
