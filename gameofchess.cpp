/*
 * gameofchess.cpp
 *
 *  Created on: Apr 2, 2015
 *      Author: shamann
 */
#include "gameofchess.h"
#include "chesspiece.h"
#include "pawn.h"
#include "knight.h"
#include "bishop.h"
#include "rook.h"
#include "queen.h"
#include "king.h"
#include <iostream>
using namespace std;


GameOfChess::GameOfChess(char (*promoQuestion)()) {
	CurrentPlayer = 'W';
	//empty the board
		board = new vector<ChessPiece*>(64,NULL);
		// Allocate and place black pieces
		for (int col = 0; col < 8; ++col) {
			board->at(48 +col) = new Pawn('B', 48 + col, board);
		}
		board->at(56) = new Rook('B', 56, board);
		board->at(57) = new Knight('B', 57,board);
		board->at(58) = new Bishop('B', 58, board);
		board->at(59) = new Queen('B', 59, board);
		board->at(60) = new King('B', 60, board);
		board->at(61) = new Bishop('B', 61, board);
		board->at(62) = new Knight('B', 62, board);
		board->at(63) = new Rook('B', 63, board);
		// Allocate and place white pieces
		for (int col = 0; col < 8; ++col) {
			board->at(8+col) = new Pawn('W', 8 + col, board);
		}
		board->at(0) = new Rook('W', 0, board);
		board->at(1) = new Knight('W', 1, board);
		board->at(2) = new Bishop('W', 2, board);
		board->at(3) = new Queen('W', 3, board);
		board->at(4) = new King('W', 4, board);
		board->at(5) = new Bishop('W', 5, board);
		board->at(6) = new Knight('W', 6, board);
		board->at(7) = new Rook('W', 7, board);
		promoQ = promoQuestion;
		gameresult=1000;
		counter50=0;
		positionhistory.clear();
}

void GameOfChess::move(int from, int to) {
	if ( board->at(from) == 0 || isGameOver())
		return;

	bool countsTowards50rule = false;
	if (board->at(from)->GetType() == 'P')
		countsTowards50rule = true;
	if (board->at(to) != NULL)
		countsTowards50rule = true;

	if ( board->at(from)->GetColor() == CurrentPlayer){
		if ( board->at(from)->move(to) ){
			if (isPromotionNeeded()){
				char promotion = promoQ();
				promoteTo(promotion);
			}
			//move is valid, further actions;
			if (countsTowards50rule){
				counter50 = 0;
				positionhistory.clear();
			}
			else{
				counter50++;
				positionhistory.insert(positionToString());
			}
			alternatePlayers();
		}
		else if (board->at(from)->GetType() == 'K') { //CASTLING
			if ( castle(from, to) )
				alternatePlayers();
		}
	}
	else{
		cout<<"GameofChess: It is not your turn to move"<<endl;
	}
	if (isGameOver()){
		cout<<"Game over"<<endl;
		cout<<getResult()<<endl;
	}
}

bool GameOfChess::isGameOver() {
	//Check if current player can move
	bool movepossible = false;
	for (vector<ChessPiece*>::iterator it = board->begin() ; it != board->end(); ++it){
		if ( (*it) != NULL && (*it)->GetColor() == CurrentPlayer && (*it)->hasLegalMove() ){
			movepossible = true;
			break;
		}
	}
	//check if current player is in check
	bool incheck;
	for (int loc=0; loc < board->size(); loc++){
		if ( board->at(loc) != NULL && board->at(loc)->GetColor() == CurrentPlayer ){
			incheck = board->at(loc)->myKingInCheck();
			break;
		}
	}
	if (!movepossible){
		if (incheck)
			gameresult=(CurrentPlayer=='W')? -1 : 1;
		else
			gameresult=0;
		return true;
	}
	//check if 50 moves since last take or pawn movement
	if (counter50>=100){
		gameresult=0;
		return true;
	}
	//check if triple repetition
	if (positionhistory.count(positionToString()) >=3 ){
		gameresult=0;
		return true;
	}
	return false;
}

void GameOfChess::alternatePlayers() {
	if (CurrentPlayer == 'W')
		CurrentPlayer = 'B';
	else
		CurrentPlayer = 'W';
}

ChessPiece* GameOfChess::getPieceAtLocation(int loc) {
	if (loc > 63 || loc < 0)
		return NULL;
	return board->at(loc);
}

GameOfChess::~GameOfChess() {
	for (int pos=0;pos<64;pos++)
		delete board->at(pos);
}

bool GameOfChess::isPromotionNeeded() {
	for(int pos=0; pos<8; pos++){
		if (board->at(pos))
			if(board->at(pos)->GetType() == 'P')
				return true;
	}
	for(int pos=56; pos<64; pos++){
		if (board->at(pos))
			if(board->at(pos)->GetType() == 'P')
				return true;
	}
	return false;
}

void GameOfChess::promoteTo(char promo) {
	cout<<"Starting promotion"<<endl;
	int target=-1;
	int playerfix = (CurrentPlayer == 'B') ? 0 : 56;
	for(int pos=0+playerfix; pos<8+playerfix; pos++){
		if (board->at(pos) )
			if(board->at(pos)->GetType() == 'P')
				target = pos;
	}
	cout<<"target is at "<<target<<endl;
	delete board->at(target);
	switch(promo){
	case 'N':
		cout<<"Promoting to Knight"<<endl;
		board->at(target) = new Knight(CurrentPlayer,target,board);
		break;
	case 'B':
		cout<<"Promoting to Bishop"<<endl;
		board->at(target) = new Bishop(CurrentPlayer,target,board);
		break;
	case 'R':
		cout<<"Promoting to Rook"<<endl;
		board->at(target) = new Rook(CurrentPlayer,target,board);
		break;
	case 'Q':
		cout<<"Promoting to Queen"<<endl;
		board->at(target) = new Queen(CurrentPlayer,target,board);
		break;
	}
}

bool GameOfChess::castle(int from, int to){
	//initial condidions: KING, NOT MOVED, NOT UNDER CHECK
	if (board->at(from)->GetType() != 'K' || board->at(from)->hasMoved() || board->at(from)->myKingInCheck()){
		return false;
	}
	//target square not occupied
	if (board->at(to) != NULL)//target square occupied
		return false;
	//target square not under attack
	if (board->at(from)->opponentCanAttack(to))//target square attacked
		return false;

	if (to == from+2){//kingside
		if (board->at(from+3) == NULL)//no rook to castle with
					return false;
		if (board->at(from+3)->hasMoved())//rook has moved
			return false;
		if (board->at(from)->opponentCanAttack(from+1))//mid-square attacked
			return false;
		if (board->at(from+1) != NULL)//mid-square occupied
			return false;
		//do castle
		board->at(to) = board->at(from); //move king
		board->at(from) = NULL;
		board->at(to)->setLocation(to);
		board->at(to)->markAsMoved();
		board->at(to-1) = board->at(from+3); //move rook
		board->at(from+3) = 0;
		board->at(to-1)->setLocation(to-1);
		board->at(to-1)->markAsMoved();
		return true;

	}
	if (to == from-2){//queenside
		if (board->at(from-4) == NULL)//no rook to castle with
			return false;
		if (board->at(from-4)->hasMoved())//rook has moved
			return false;
		if (board->at(from)->opponentCanAttack(from-1))//mid-square attacked
			return false;
		if (board->at(from-1) != NULL)//mid-square occupied
			return false;
		//do castle
		board->at(to) = board->at(from); //move king
		board->at(from) = NULL;
		board->at(to)->setLocation(to);
		board->at(to)->markAsMoved();
		board->at(to+1) = board->at(from-4); //move rook
		board->at(from-4) = 0;
		board->at(to+1)->setLocation(to+1);
		board->at(to+1)->markAsMoved();
		return true;
	}
	return false;
}

string GameOfChess::getResult(){
	if (gameresult == 1)
		return "White wins";
	if (gameresult == -1)
		return "Black wins";
	if (gameresult == 0)
		return "Draw";
	return "in progress...";
}

string GameOfChess::positionToString(){
	string tmp="";
	char prepr;
	for (vector<ChessPiece*>::iterator it = board->begin() ; it != board->end(); ++it){
		if (*it == NULL){
			tmp+='_';
			continue;
		}
		prepr=(*it)->GetType();
		if( (*it)->GetColor() == 'B' )
			prepr -= ('A'-'a');
		tmp+=prepr;
	}
	return tmp;
}


