/*
 * rook.cpp
 *
 *  Created on: Feb 27, 2015
 *      Author: shamann
 */
#include "chesspiece.h"
#include "rook.h"

Rook::Rook(char clr, int loc, vector<ChessPiece*> *chessboard) : ChessPiece(clr, 'R', loc, chessboard) {}


bool Rook::canReach(int DestPosition) {
	if (! ChessPiece::canReach(DestPosition))
			return false;
	int SrcRow = getLocation() / 8;
	int SrcCol = getLocation() % 8;
	int DestRow = DestPosition / 8;
	int DestCol = DestPosition % 8;

	if (SrcRow == DestRow) {
		int ColOffset = (DestCol - SrcCol > 0) ? 1 : -1;
		for (int CheckCol = SrcCol + ColOffset; CheckCol !=  DestCol; CheckCol += ColOffset) {
			if (myboard->at(SrcRow*8 + CheckCol) != 0) {
				return false;
			}
		}
		return true;
	} else if (DestCol == SrcCol) {
		int RowOffset = (DestRow - SrcRow > 0) ? 1 : -1;
		for (int CheckRow = SrcRow + RowOffset; CheckRow !=  DestRow; CheckRow += RowOffset) {
			if (myboard->at(CheckRow*8 + SrcCol) != 0) {
				return false;
			}
		}
		return true;
	}
	return false;
}




