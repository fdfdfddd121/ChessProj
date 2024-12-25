#include "King.h"
#include "Board.h"

King::King(const std::string& place, const char type, Piece* board[][BOARD_SIZE]):
	Piece(place,type, board), _isChecked(false)
{
}

King::~King()
{
}

void King::setIsChecked(const bool isChecked)
{
	_isChecked = isChecked;
}

bool King::getIsChecked() const
{
	return _isChecked;
}

void King::move(const std::string& dest, Piece* board[][BOARD_SIZE])
{
	std::string pastPlace = this->getPlace();
	int destIndex = this->placeToIndex(dest);

	if (isValidMove(dest, board))
	{
		//in eat function if null we do nothing, implement in piece.cpp
		eat(*board[int(destIndex / 10)][destIndex % 10]);
	}
	else
	{
		//throw the fucking exception
		Board::exceptionHandler(this->getPlace(), dest, board);
	}
	setPlace(dest, board);
}

bool King::isValidMove(const std::string& dest, Piece* board[][BOARD_SIZE])
{
	bool valid = false;
	int destI = placeToIndex(dest) / 10, destJ = placeToIndex(dest) % 10;
	int srcI = placeToIndex(_place) / 10, srcJ = placeToIndex(_place) % 10;
	if (dest.compare(this->getPlace())==0)
	{
		throw 7;
	}
	else if ((destI == (srcI + 1) || destI == (srcI - 1) || (destI == srcI)) && (destJ == (srcJ + 1) || destJ == (srcJ - 1)) || (destJ == srcJ) && (destI == (srcI + 1) || destI == (srcI - 1)))
	{
		valid = !isChecked(dest, board);
	}
	else
	{
		valid = false;
	}
	return valid;
}

bool King::isValidMove(const Piece& other, Piece* board[][BOARD_SIZE])
{
	return isValidMove(other.getPlace(),board);
}


bool King::isChecked(const std::string& source, Piece* board[][BOARD_SIZE])
{
	bool answer = false;

	int intSource = placeToIndex(source);
	int sourceI = intSource / 10, sourceJ = intSource % 10;

	for (int i = 0; i < BOARD_SIZE && !answer; i++)
	{
		for (int j = 0; j < BOARD_SIZE && !answer; j++)
		{
			if (board[i][j] != NULL && (board[i][j]->getIsWhite() != board[sourceI][sourceJ]->getIsWhite()) && (*board[i][j]).isValidMove(source, board))
			{
				answer = true;
			}
		}
	}

	return answer;
}
