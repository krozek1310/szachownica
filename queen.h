/*
 * queen.h
 *
 *  Created on: Apr 1, 2015
 *      Author: shamann
 */

#ifndef QUEEN_H_
#define QUEEN_H_

class Queen : public ChessPiece
{
public:
	Queen(char clr, int loc, vector<ChessPiece*> *chessboard);
	~Queen() {}
private:
	bool canReach(int DestPosition);
};



#endif /* QUEEN_H_ */
