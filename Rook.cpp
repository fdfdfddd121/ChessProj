#include "Rook.h"

Rook::Rook(const std::string& place, const char type):
	Piece(place, type)
{
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
