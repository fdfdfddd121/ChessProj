#pragma once
#include "Piece.h"
#define BOARD_SIZE 8

class Board {
protected:
	Piece* _pieces[BOARD_SIZE][BOARD_SIZE];
	bool _turn;
	int exceptionHandler(const std::string& source, const std::string& dest, Piece* board[][BOARD_SIZE], Piece& piece);
	Piece* _WhiteKing;
	Piece* _BlackKing;
public:
	//basic class functions
	Board(const bool turn = 0);
	virtual ~Board();
	
	void printBoard() const;
	void flipTurn();
	std::string getBoard() const;
};