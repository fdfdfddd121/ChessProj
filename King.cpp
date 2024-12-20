#include "King.h"

King::King(const std::string& place, const char type):
	Piece(place,type), _isChecked(false)
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
	if (!isValidMove(dest, board)) //check for valid move and exceptions that get thrown come before this exception
	{
		throw 6;
	}
	setPlace(dest);
}

bool King::isValidMove(const std::string& dest, Piece* board[][BOARD_SIZE])
{
	bool valid = true;
	bool blocked = false;
	int i = 0, j = 0;
	int x = 0, y = 0;
	x = dest[0] - 'a';
	y = dest[1] - '1';
	while (valid && i < BOARD_SIZE && !blocked)
	{
		if (board[i][y] != NULL && ((board[i][y]->getType()=='r' && getIsWhite() == true) || (board[i][y]->getType() == 'R' && getIsWhite() == false)))
		{

		}
	}
	return valid;
}

void King::eat(Piece& other)
{
}
