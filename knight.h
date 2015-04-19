/*
 * knight.h
 *
 *  Created on: Apr 1, 2015
 *      Author: shamann
 */

#ifndef KNIGHT_H_
#define KNIGHT_H_
#include "chesspiece.h"

class Knight : public ChessPiece
{
public:
	Knight(char clr, int loc, vector<ChessPiece*> *chessboard);
	~Knight() {};
private:
	bool canReach(int DestPosition);
};



#endif /* KNIGHT_H_ */
