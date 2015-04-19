/*
 * main.cpp
 *
 *  Created on: Feb 25, 2015
 *      Author: shamann
 */
#include <iostream>
#include "gamepresenter.h"

int main() {
	GamePresenter* presenter = new GamePresenter;
	presenter->startGame();
	delete presenter;
	return 0;
}
