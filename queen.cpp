/*
 * queen.cpp
 *
 *  Created on: Feb 27, 2015
 *      Author: shamann
 */
#include <cmath>
#include "chesspiece.h"
#include "queen.h"
using namespace std;


Queen::Queen(char clr, int loc, vector<ChessPiece*> chessboard[64]) : ChessPiece(clr, 'Q', loc, chessboard) {}


bool Queen::canReach(int DestPosition) {
	if (! ChessPiece::canReach(DestPosition))
			return false;
	int SrcRow = getLocation() / 8;
	int SrcCol = getLocation() % 8;
	int DestRow = DestPosition / 8;
	int DestCol = DestPosition % 8;
	int coldiff = abs(SrcCol - DestCol);
	int rowdiff = abs(SrcRow - DestRow);
	if (rowdiff == 0) {
		int ColOffset = (DestCol - SrcCol > 0) ? 1 : -1;
		for (int CheckCol = SrcCol + ColOffset; CheckCol !=  DestCol; CheckCol += ColOffset) {
			if (myboard->at(SrcRow*8 + CheckCol) != 0) {
				return false;
			}
		}
		return true;
	} else if (coldiff == 0) {
		int RowOffset = (DestRow - SrcRow > 0) ? 1 : -1;
		for (int CheckRow = SrcRow + RowOffset; CheckRow !=  DestRow; CheckRow += RowOffset) {
			if (myboard->at(CheckRow*8 + SrcCol) != 0) {
				return false;
			}
		}
		return true;
	} else if (coldiff == rowdiff) {
		int RowOffset = (DestRow - SrcRow > 0) ? 1 : -1;
		int ColOffset = (DestCol - SrcCol > 0) ? 1 : -1;
		int CheckRow;
		int CheckCol;
		for (CheckRow = SrcRow + RowOffset, CheckCol = SrcCol + ColOffset;
			CheckRow != DestRow;
			CheckRow += RowOffset, CheckCol += ColOffset)
		{
			if (myboard->at(CheckRow*8 + CheckCol) != 0) {
				return false;
			}
		}
		return true;
	}
	return false;
}




