#pragma once
#include "Piece.h"
class Bishop : public Piece {
public:
	//basic class functions
	Bishop(const std::string& place, const char type, Piece* board[][BOARD_SIZE]);
	virtual ~Bishop();

	//implement Piece functions
	virtual void move(const std::string& dest, Piece* board[][BOARD_SIZE]) override;
	virtual bool isValidMove(const std::string& dest, Piece* board[][BOARD_SIZE]) override;
	virtual bool isValidMove(const Piece& other, Piece* board[][BOARD_SIZE]) override;
};