#pragma once
#include "Piece.h"
#include "Bishop.h"
#include "Rook.h"
class Queen : public Rook, public Bishop {
public:
	//basic class functions
	Queen(const std::string& place, const char type, Piece* board[][BOARD_SIZE]);
	virtual ~Queen();

	//implement Piece functions
	virtual void move(const std::string& dest, Piece* board[][BOARD_SIZE]) override;
	virtual bool isValidMove(const std::string& dest, Piece* board[][BOARD_SIZE]) override;
	virtual bool isValidMove(const Piece& other, Piece* board[][BOARD_SIZE]) override;
};