/*
 * pawn.h
 *
 *  Created on: Apr 1, 2015
 *      Author: shamann
 */

#ifndef PAWN_H_
#define PAWN_H_

#include "chesspiece.h"

class Pawn : public ChessPiece
{
public:
	Pawn(char clr, int loc, vector<ChessPiece*> *chessboard);
	~Pawn() {};
private:
	bool canReach(int DestPosition);
};



#endif /* PAWN_H_ */
