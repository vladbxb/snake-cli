CFLAGS = -std=c++17 -Wall -pedantic

bin/main: bin/main.o bin/game.o bin/snake.o bin/food.o
	g++ -g -o bin/main bin/main.o bin/game.o bin/snake.o bin/food.o $(CFLAGS) -lncurses

bin/main.o: src/main.cpp
	mkdir -p bin	
	g++ -g -c -o bin/main.o src/main.cpp $(CFLAGS) 

bin/game.o: src/game.cpp src/game.h
	mkdir -p bin	
	g++ -g -c -o bin/game.o src/game.cpp $(CFLAGS)

bin/snake.o: src/snake.cpp src/snake.h
	mkdir -p bin	
	g++ -g -c -o bin/snake.o src/snake.cpp $(CFLAGS)

bin/food.o: src/food.cpp src/food.h
	mkdir -p bin	
	g++ -g -c -o bin/food.o src/food.cpp $(CFLAGS)
