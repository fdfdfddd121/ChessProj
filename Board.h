#pragma once
#include "Piece.h"
#define BOARD_SIZE 8

class Board {
protected:
	Piece* _pieces[BOARD_SIZE][BOARD_SIZE];
	bool _turn;
	static Piece* _WhiteKing;
	static Piece* _BlackKing;
	static void makePiece(const std::string& place, const char type, Piece* board[][BOARD_SIZE]);
public:
	//basic class functions
	Board(const bool turn = 0);
	virtual ~Board();
	std::string makeMove(std::string move);
	void printBoard() const;
	void flipTurn();
	std::string getBoard() const;
	static void exceptionHandler(const std::string& source, const std::string& dest, Piece* board[][BOARD_SIZE]);
	static bool nextTurnCheck(const std::string& source, const std::string& dest, Piece* board[][BOARD_SIZE]);
};