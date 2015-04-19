/*
 * gamepresenter.h
 *
 *  Created on: Apr 2, 2015
 *      Author: shamann
 */

#ifndef GAMEPRESENTER_H_
#define GAMEPRESENTER_H_
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "gameofchess.h"

class GamePresenter{
public:
	GamePresenter();
	~GamePresenter();
	void startGame();
	static char myPromoQuestion();
private:
	void drawBoard();
	int getSpriteForPiece(char piecetype, char piececolor);
	SDL_Window* main_window;
	SDL_Renderer* main_renderer;
	GameOfChess* currentgame;
	SDL_Texture* background;
	SDL_Texture* piecesheet;
	SDL_Rect fullscreen;
	SDL_Rect pieces[12];
	bool sdlquit;
};



#endif /* GAMEPRESENTER_H_ */
