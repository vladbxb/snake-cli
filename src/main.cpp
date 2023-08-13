#include "game.h"

int main() {
	int init_status = init();

	if (!init_status) {
		run();
	}

	close();

	return 0;
}
