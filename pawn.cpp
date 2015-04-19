/*
 * pawn.cpp
 *
 *  Created on: Feb 27, 2015
 *      Author: shamann
 */
#include "pawn.h"
using namespace std;
//TODO en-passant

Pawn::Pawn(char clr, int loc, vector<ChessPiece*> *chessboard): ChessPiece(clr, 'P', loc, chessboard) {}


bool Pawn::canReach(int DestPosition) {
	if (! ChessPiece::canReach(DestPosition))
		return false;
	int SrcRow = getLocation() / 8;
	int SrcCol = getLocation() % 8;
	int DestRow = DestPosition / 8;
	int DestCol = DestPosition % 8;
	ChessPiece* pieceAtDestination = myboard->at(DestPosition);
	if (pieceAtDestination == 0) {
		// Destination square is unoccupied
		if (SrcCol == DestCol) {
			if (GetColor() == 'W') {
				if (DestRow == SrcRow + 1) {
					return true;
				}
				//charge
				if (SrcRow == 1 && DestRow == 3 && myboard->at(16+DestCol) == 0 ){
					return true;
				}
			} else {
				if (DestRow == SrcRow - 1) {
					return true;
				}
				//charge
				if (SrcRow == 6 && DestRow == 4 && myboard->at(40+DestCol) == 0 ){
					return true;
				}
			}
		}
	} else {
		// Destination holds piece of opposite color
		if ((SrcCol == DestCol + 1) || (SrcCol == DestCol - 1)) {
			if (GetColor() == 'W') {
				if (DestRow == SrcRow + 1) {
					return true;
				}
			} else {
				if (DestRow == SrcRow - 1) {
					return true;
				}
			}
		}
	}
	return false;
}



