#include "Rook.h"

Rook::Rook(const std::string& place, const char type):
	Piece(place, type)
{
	this->_hasMoved = false;
	this->_type = type;
	this->_place = place;
}

Rook::~Rook()
{
}

void Rook::move(const std::string& dest, Piece* board[][BOARD_SIZE])
{
}

bool Rook::isValidMove(const std::string& dest, Piece* board[][BOARD_SIZE])
{
	return false;
}
