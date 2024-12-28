#pragma once
#include "Piece.h"
class Pawn : virtual public Piece {
public:
	//basic class functions
	Pawn(const std::string& place, const char type, Piece* board[][BOARD_SIZE]);
	virtual ~Pawn();

	//implement Piece functions
	virtual void move(const std::string& dest, Piece* board[][BOARD_SIZE]) override;
	virtual bool isValidMove(const std::string& dest, Piece* board[][BOARD_SIZE]) override;
	virtual bool isValidMove(const Piece& other, Piece* board[][BOARD_SIZE]) override;
};