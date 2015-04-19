/*
 * chesspieces.h
 *
 *  Created on: Feb 25, 2015
 *      Author: shamann
 */

#ifndef CHESSPIECES_H_
#define CHESSPIECES_H_
#include <vector>
using namespace std;


class ChessPiece
{
public:
	ChessPiece(char clr, char ptype, int loc, vector<ChessPiece*> *chessboard);
	virtual ~ChessPiece() {};
	char GetType();
	char GetColor();
	virtual bool canReach(int DestPosition);
	bool move(int DestPosition);
	bool hasMoved();
	void markAsMoved();
	bool hasLegalMove();
	int getLocation();
	bool myKingInCheck();
	void setLocation(int loc);
	bool opponentCanAttack(int sq);
private:
	int findOwnKing();
	char color;
	char piecetype;
	bool moved;
protected:
	vector<ChessPiece*> *myboard;
	int location;
};



#endif /* CHESSPIECES_H_ */




