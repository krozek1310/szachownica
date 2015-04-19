/*
 * gamepresenter.cpp
 *
 *  Created on: Apr 2, 2015
 *      Author: shamann
 */

#include "gamepresenter.h"
#include "gameofchess.h"
#include <iostream>
using namespace std;

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;


int GamePresenter::getSpriteForPiece(char piecetype,char piececolor){
	int colorfix = (piececolor == 'B') ? 1 : 0;
	switch(piecetype){
		case 'P':
			return  10 + colorfix;
		case 'R':
			return  8 + colorfix;
		case 'N':
			return  6 + colorfix;
		case 'B':
			return  4 + colorfix;
		case 'Q':
			return  2 + colorfix;
		case 'K':
			return  0 + colorfix;
		}
	return 2;
}

GamePresenter::GamePresenter() {
	cout<<"calling presenter constructor"<<endl;
	currentgame = new GameOfChess(myPromoQuestion);
	SDL_Init(SDL_INIT_VIDEO);
	main_window = SDL_CreateWindow("Szachownica - Piotr Sionkowski", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	main_renderer = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	background = IMG_LoadTexture(main_renderer, "board.png");
	piecesheet = IMG_LoadTexture(main_renderer, "pieces.png");
	fullscreen.x = 0;
	fullscreen.y = 0;
	fullscreen.w = SCREEN_WIDTH;
	fullscreen.h = SCREEN_HEIGHT;
	int spriteW, spriteH;
	SDL_QueryTexture(piecesheet, NULL, NULL, &spriteW, &spriteH);
	spriteW /= 6;
	spriteH /= 2;
	for (int i = 0; i < 12; ++i){
		pieces[i].x = i / 2 * spriteW;
		pieces[i].y = i % 2 * spriteH;
		pieces[i].w = spriteW;
		pieces[i].h = spriteH;
	}
	sdlquit = false;
}

GamePresenter::~GamePresenter() {
	cout<<"calling presenter destructor"<<endl;
	delete currentgame;
	SDL_Quit();
}

void GamePresenter::startGame() {
	SDL_Event e;
	while (!sdlquit){
		//regular game
		int mouserow, mousecol, srcpos, dstpos;
		//while (!currentgame->isGameOver())
		while (SDL_PollEvent(&e)){
				if (e.type == SDL_QUIT){
					cout<<"GamePresenter: Quitting game..."<<endl;
					sdlquit = true;
				}
				if (e.type == SDL_MOUSEBUTTONDOWN){
					mouserow = 7 - e.button.y / (SCREEN_HEIGHT / 8);
					mousecol = e.button.x / (SCREEN_WIDTH / 8);
					srcpos = mouserow * 8 + mousecol;
				}
				if (e.type == SDL_MOUSEBUTTONUP){
					mouserow = 7 - e.button.y / (SCREEN_HEIGHT / 8);
					mousecol = e.button.x / (SCREEN_WIDTH / 8);
					dstpos = mouserow * 8 + mousecol;
					if (!currentgame->isGameOver())
						currentgame->move(srcpos,dstpos);
					}
				}
		drawBoard();
	}
}

void GamePresenter::drawBoard() {
	SDL_RenderClear(main_renderer);
	SDL_RenderCopy(main_renderer,background,NULL,&fullscreen);
	SDL_Rect currentField;
	currentField.h = SCREEN_HEIGHT/8;
	currentField.w = SCREEN_WIDTH/8;
	currentField.y = 0;
	for(int a = 7; a >= 0; a--){
		currentField.x = 0;
		for(int b = 0; b<8; b++){
			ChessPiece* CurrentPiece = currentgame->getPieceAtLocation(a*8 + b);
			if (CurrentPiece)
				SDL_RenderCopy(main_renderer,piecesheet,&pieces[getSpriteForPiece(CurrentPiece->GetType(),CurrentPiece->GetColor())],&currentField);
			currentField.x += currentField.w;
		}
		currentField.y += currentField.h;
	}
	if (currentgame->isGameOver()){
		SDL_SetTextureAlphaMod(piecesheet,160);
		if (currentgame->getResult() == "White wins"){
			SDL_RenderCopy(main_renderer,piecesheet,&pieces[getSpriteForPiece('K','W')],&fullscreen);

		}
		if (currentgame->getResult() == "Black wins"){
			SDL_RenderCopy(main_renderer,piecesheet,&pieces[getSpriteForPiece('K','B')],&fullscreen);
		}
		if (currentgame->getResult() == "Draw"){
			SDL_Rect lefthalf;
			lefthalf.h=SCREEN_HEIGHT;
			lefthalf.w=SCREEN_WIDTH/2;
			lefthalf.x=0;
			lefthalf.y=0;
			SDL_Rect righthalf(lefthalf);
			righthalf.x=SCREEN_WIDTH/2;
			SDL_Rect halfwhiteking=pieces[getSpriteForPiece('K','W')];
			SDL_Rect halfblackking=pieces[getSpriteForPiece('K','B')];
			halfwhiteking.w/=2;
			halfblackking.w/=2;
			halfblackking.x+=halfblackking.w;
			SDL_RenderCopy(main_renderer,piecesheet,&halfwhiteking,&lefthalf);
			SDL_RenderCopy(main_renderer,piecesheet,&halfblackking,&righthalf);
		}
		SDL_SetTextureAlphaMod(piecesheet,255);
	}
	SDL_RenderPresent(main_renderer);
}

char GamePresenter::myPromoQuestion() {
	int promoW = SCREEN_WIDTH  /2;
	int promoH = SCREEN_HEIGHT /2;
	SDL_Window* promo_window = SDL_CreateWindow("Pawn Promotion", 0, 0, promoW, promoH, SDL_WINDOW_SHOWN);
	SDL_Renderer* promo_renderer = SDL_CreateRenderer(promo_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_Texture* psheet = IMG_LoadTexture(promo_renderer, "pieces.png");
	int spriteW, spriteH;
	SDL_QueryTexture(psheet, NULL, NULL, &spriteW, &spriteH);
	spriteW /= 6;
	spriteH /= 2;
	SDL_Rect spriterect[4];
	for (int i=0; i<4;i++){
		spriterect[i].h = spriteH;
		spriterect[i].w = spriteW;
		spriterect[i].x = (i+1)*spriteW;
		spriterect[i].y = 0;
	}

	SDL_Rect dests[4];
	for (int i=0; i<4;i++){
		dests[i].h = promoH/2;
		dests[i].w = promoW/2;
		dests[i].x = (i/2) * promoW/2;
		dests[i].y = (i%2) * promoH/2;
	}

	SDL_Event e;
	char retval ='?';
	while (retval=='?'){
	while (SDL_PollEvent(&e)){
		if (e.type == SDL_MOUSEBUTTONDOWN){
			if (e.button.x > promoW/2){
				if(e.button.y > promoH/2)
					retval = 'R';
				else
					retval = 'N';
			}else {
				if(e.button.y > promoH/2)
					retval = 'B';
				else
					retval = 'Q';
			}
		}
	}
	SDL_RenderClear(promo_renderer);
	for (int i=0; i<4; i++)
		SDL_RenderCopy(promo_renderer,psheet,&spriterect[i],&dests[i]);
	SDL_RenderPresent(promo_renderer);
	}
	SDL_DestroyWindow(promo_window);
	return retval;
}
