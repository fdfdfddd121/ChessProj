#pragma once
#include "Piece.h"
class Rook : public Piece {
public:
	//basic class functions
	Rook(const std::string& place, const char type);
	virtual ~Rook();

	//implement Piece functions
	virtual void move(const std::string& dest, Piece* board[][BOARD_SIZE]) override;
	virtual bool isValidMove(const std::string& dest, Piece* board[][BOARD_SIZE]) override;
	virtual bool isValidMove(const Piece& other, Piece* board[][BOARD_SIZE]) override;
};