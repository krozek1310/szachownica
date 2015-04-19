/*
 * bishop.cpp
 *
 *  Created on: Feb 27, 2015
 *      Author: shamann
 */
#include <cmath>
#include "chesspiece.h"
#include "bishop.h"
using namespace std;

Bishop::Bishop(char clr, int loc, vector<ChessPiece*> *chessboard): ChessPiece(clr, 'B', loc, chessboard) {}


bool Bishop::canReach(int DestPosition) {
	if (! ChessPiece::canReach(DestPosition))
			return false;
	int SrcRow = getLocation() / 8;
	int SrcCol = getLocation() % 8;
	int DestRow = DestPosition / 8;
	int DestCol = DestPosition % 8;
    int coldiff = abs(SrcCol - DestCol);
    int rowdiff = abs(SrcRow - DestRow);
	if (coldiff == rowdiff) {
		int RowOffset = (DestRow - SrcRow > 0) ? 1 : -1;
		int ColOffset = (DestCol - SrcCol > 0) ? 1 : -1;
		int CheckRow;
		int CheckCol;
		for (CheckRow = SrcRow + RowOffset, CheckCol = SrcCol + ColOffset;
				CheckRow !=  DestRow; CheckRow += RowOffset, CheckCol += ColOffset){
			if (myboard->at(CheckRow*8 + CheckCol) != 0) {
				return false;
			}
		}
		return true;
	}
	return false;
}


