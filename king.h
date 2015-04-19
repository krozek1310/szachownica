/*
 * king.h
 *
 *  Created on: Apr 1, 2015
 *      Author: shamann
 */

#ifndef KING_H_
#define KING_H_
#include "chesspiece.h"

class King : public ChessPiece
{
public:
	King(char clr, int loc, vector<ChessPiece*> *chessboard);
	~King() {}
private:
	bool canReach(int DestPosition);
};

#endif /* KING_H_ */
