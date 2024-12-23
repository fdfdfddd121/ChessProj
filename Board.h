#pragma once
#include "Piece.h"
#define BOARD_SIZE 8

class Board {
private:
	std::string indexToPlace(int i, int j);
protected:
	Piece* _pieces[BOARD_SIZE][BOARD_SIZE];
	bool _turn;
public:
	//basic class functions
	Board(Piece* pieces[BOARD_SIZE][BOARD_SIZE], const bool turn = 0);
	virtual ~Board();
	void startGame();
	void printBoard() const;

};