#pragma once
#include "Piece.h"
class Knight : public Piece
{
public:
	//basic class functions
	Knight(const std::string& place, const char type, Piece* board[][BOARD_SIZE]);
	virtual ~Knight();

	//implement Piece functions
	virtual void move(const std::string& dest, Piece* board[][BOARD_SIZE]) override;
	virtual bool isValidMove(const std::string& dest, Piece* board[][BOARD_SIZE]) override;
	virtual bool isValidMove(const Piece& other, Piece* board[][BOARD_SIZE]) override;
};