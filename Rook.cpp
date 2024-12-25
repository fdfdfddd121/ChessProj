#include "Rook.h"
#include "Board.h"

Rook::Rook(const std::string& place, const char type, Piece* board[][BOARD_SIZE]):
	Piece(place, type, board)
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
	std::string pastPlace = this->getPlace();
	int destIndex = this->placeToIndex(dest);

	if (isValidMove(dest, board))
	{
		//in eat function if null we do nothing, implement in piece.cpp
		eat(*board[int(destIndex/10)][destIndex%10]);
	}
	else
	{
		//throw the fucking exception
		Board::exceptionHandler(this->getPlace(), dest, board);
	}
	setPlace(dest, board);

}

bool Rook::isValidMove(const std::string& dest, Piece* board[][BOARD_SIZE])
{
	bool valid = (dest[0]==_place[0]) || (dest[1]==_place[1]);
	int destI = placeToIndex(dest) / 10, destJ = placeToIndex(dest) % 10;
	int srcI = placeToIndex(_place) / 10, srcJ = placeToIndex(_place) % 10;
	if (dest.compare(this->getPlace()) == 0)
	{
		throw 7;
	}
	if (valid)
	{
		int j = 0;
		if (destI == srcI)
		{
			if (destJ > srcJ)
			{
				for (j = srcJ + 1; j < destJ && valid; j++)
				{
					if (board[srcI][j] != NULL)
					{
						valid = false;
					}
				}
				if (board[destI][destJ] != NULL)
				{
					valid = !(getIsWhite() == board[destI][destJ]->getIsWhite());
				}
			}
			else
			{
				for (j = srcJ - 1; destJ < j && valid; j--)
				{
					if (board[srcI][j] != NULL)
					{
						valid = false;
					}
				}
				if (board[destI][destJ] != NULL)
				{
					valid = !(getIsWhite() == board[destI][destJ]->getIsWhite());
				}
			}
		}
		else if (destJ == srcJ)
		{
			int i = srcI;
			if (destI > srcI)
			{
				for (i = srcI + 1; i < destI && valid; i++)
				{
					if (board[i][srcJ] != NULL)
					{
						valid = false;
					}
				}
				if (board[destI][destJ] != NULL)
				{
					valid = !(getIsWhite() == board[destI][destJ]->getIsWhite());
				}
			}
			else
			{
				for (i = srcI - 1; destI < i && valid; i--)
				{
					if (board[i][srcJ] != NULL)
					{
						valid = false;
					}
				}
				if (board[destI][destJ] != NULL)
				{
					valid = !(getIsWhite() == board[destI][destJ]->getIsWhite());
				}
			}
		}
	}
	return valid;
}
bool Rook::isValidMove(const Piece& other, Piece* board[][BOARD_SIZE])
{
	return isValidMove(other.getPlace(), board);
}