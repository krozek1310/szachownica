/*
 * king.cpp
 *
 *  Created on: Feb 27, 2015
 *      Author: shamann
 */
#include <cmath>
#include "king.h"
using namespace std;
//TODO castling

King::King(char clr, int loc, vector<ChessPiece*> *chessboard) : ChessPiece(clr, 'K', loc, chessboard) {}


bool King::canReach(int DestPosition) {
	if (! ChessPiece::canReach(DestPosition))
			return false;
	int SrcRow = getLocation() / 8;
	int SrcCol = getLocation() % 8;
	int DestRow = DestPosition / 8;
	int DestCol = DestPosition % 8;
	int RowDelta = abs(DestRow - SrcRow);
	int ColDelta = abs(DestCol - SrcCol);
	if ( RowDelta <= 1 && ColDelta <= 1 )
	{
		return true;
	}
	//Castle logic <-breaks checking
	/*if (hasMoved() == false && !myKingInCheck()){
		if(location == 4 && DestPosition == 6){//White Kingside
			return true;
		}
	}*/
	return false;
}





