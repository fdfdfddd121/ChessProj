#pragma once
#include "Piece.h"
#define BOARD_SIZE 8

class Board {
protected:
	Piece* _pieces[BOARD_SIZE][BOARD_SIZE];
	bool _turn;
public:
	//basic class functions
	Board(const bool turn = 0);
	virtual ~Board();
	void startGame();
	void printBoard() const;
	std::string getBoard() const;
};