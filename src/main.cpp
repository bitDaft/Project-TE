#include <iostream>
#include "Game.hpp"

int main(int argc, char *argv[]) {
	Game testGame(480,320,"Hello, World!");
	testGame.run();
	return 0;
}