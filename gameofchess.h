/*
 * gameofchess.h
 *
 *  Created on: Apr 2, 2015
 *      Author: shamann
 */

#ifndef GAMEOFCHESS_H_
#define GAMEOFCHESS_H_
#include "chesspiece.h"
#include <vector>
#include <string>
#include <set>
using namespace std;

class GameOfChess{
private:
	vector<ChessPiece*>* board;
	char CurrentPlayer;
	void alternatePlayers();
	void promoteTo(char promo);
	bool castle(int from, int to);
	int gameresult;
	int counter50;
	string positionToString();
	multiset<string> positionhistory;
public:
	GameOfChess(char (*promoQuestion)());
	~GameOfChess();
	void move(int from, int to);
	bool isGameOver();
	bool isPromotionNeeded();
	string getResult();
	ChessPiece* getPieceAtLocation(int loc);
	char (*promoQ)();
};



#endif /* GAMEOFCHESS_H_ */
