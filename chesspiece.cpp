/*
 * chesspieces.cpp
 *
 *  Created on: Feb 25, 2015
 *      Author: shamann
 */
#include "chesspiece.h"
#include <iostream>
using namespace std;

ChessPiece::ChessPiece(char clr, char ptype, int loc, vector<ChessPiece*> *chessboard){
	color = clr;
	piecetype = ptype;
	moved = false;
	location =loc;
	myboard = chessboard;
}

char ChessPiece::GetColor() {
	return color;
}

char ChessPiece::GetType(){
	return piecetype;
}

bool ChessPiece::canReach(int DestPosition){
	if (DestPosition < 0 || DestPosition > 63)
		return false;
	if (myboard->at(DestPosition) == 0)
		return true;
	if (myboard->at(DestPosition)->GetColor() != color)
		return true;
	return false;
}


bool ChessPiece::hasMoved() {
	return moved;
}

int ChessPiece::getLocation() {
	return location;
}

bool ChessPiece::move(int DestPosition) {
	if (canReach(DestPosition)){
		ChessPiece* tmp = myboard->at(DestPosition);
		myboard->at(DestPosition) = myboard->at(location);
		myboard->at(location) = 0;
		//checking
		//revert
		if (myKingInCheck()){
			myboard->at(location) =  this;
			myboard->at(DestPosition) = tmp;
			cout<<"ChessPiece: That move would place my king in check!"<<endl;
			return false;
		}
		//move acceptance
		delete tmp;
		location = DestPosition;
		moved = true;
		return true;
	}
	cout<<"ChessPiece: This move violates piece movement restrictions"<<endl;
	return false;
}

void ChessPiece::setLocation(int loc) {
	location = loc;
}

int ChessPiece::findOwnKing() {
	int itermax = myboard->size();
	for (int loc = 0; loc < itermax; loc++){
		if (myboard->at(loc) )
			if ( myboard->at(loc)->GetType() == 'K')
				if ( myboard->at(loc)->GetColor() == color)
					return loc;
	}
	return -1; //as an error
}

bool ChessPiece::myKingInCheck() {
	int king = findOwnKing();
	return opponentCanAttack(king);
}

bool ChessPiece::opponentCanAttack(int sq) {
	for (vector<ChessPiece*>::iterator it = myboard->begin() ; it != myboard->end(); ++it){
		if (*it != NULL)
			if ( (*it)->color != color )
				if ( (*it)->canReach(sq) )
					return true;
	}
	return false;
}

void ChessPiece::markAsMoved() {
	moved = true;
}

bool ChessPiece::hasLegalMove() {
	for (int DestPosition=0; DestPosition < 64; DestPosition++ ){
		if (canReach(DestPosition)){
			ChessPiece* tmp = myboard->at(DestPosition);
			myboard->at(DestPosition) = myboard->at(location);
			myboard->at(location) = 0;
			if (!myKingInCheck()){
				myboard->at(location) =  this;
				myboard->at(DestPosition) = tmp;
				return true;
			}
			myboard->at(location) =  this;
			myboard->at(DestPosition) = tmp;
		}
	}
	return false;
}
