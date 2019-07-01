/*
 * File: main.cpp
 * Project: Project-TE
 * Created Date: Sunday June 9th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Tuesday July 2nd 2019 1:43:20 am
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#include <iostream>
#include "Game.hpp"

int main(int argc, char *argv[])
{
	Game testGame(480, 320, "Hello, World!");
	testGame.run();
	return 0;
}