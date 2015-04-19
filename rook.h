/*
 * rook.h
 *
 *  Created on: Apr 1, 2015
 *      Author: shamann
 */

#ifndef ROOK_H_
#define ROOK_H_


class Rook : public ChessPiece
{
public:
	Rook(char clr, int loc, vector<ChessPiece*> *chessboard);
	~Rook() {}
private:
	bool canReach(int DestPosition);
};


#endif /* ROOK_H_ */
