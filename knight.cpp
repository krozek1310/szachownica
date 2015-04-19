/*
 * knight.cpp
 *
 *  Created on: Feb 27, 2015
 *      Author: shamann
 */
#include <cmath>
#include "chesspiece.h"
#include "knight.h"
using namespace std;

Knight::Knight(char clr, int loc, vector<ChessPiece*> *chessboard): ChessPiece(clr, 'N', loc, chessboard) {}


bool Knight::canReach(int DestPosition) {
	if (! ChessPiece::canReach(DestPosition))
			return false;
	int SrcRow = getLocation() / 8;
	int SrcCol = getLocation() % 8;
	int DestRow = DestPosition / 8;
	int DestCol = DestPosition % 8;
	int coldiff = abs(SrcCol - DestCol);
	int rowdiff = abs(SrcRow - DestRow);
	if (coldiff == 1 && rowdiff == 2) {
			return true;
	}
	if (coldiff == 2 && rowdiff == 1) {
			return true;
	}
	return false;
}




