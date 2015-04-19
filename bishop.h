/*
 * bishop.h
 *
 *  Created on: Apr 1, 2015
 *      Author: shamann
 */

#ifndef BISHOP_H_
#define BISHOP_H_


class Bishop : public ChessPiece
{
public:
	Bishop(char clr, int loc, vector<ChessPiece*> *chessboard);
	~Bishop() {}
private:
	bool canReach(int DestPosition);
};


#endif /* BISHOP_H_ */
