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
	bool valid = false;
	if ((dest[0] == _place[0] + 1 || dest[0] == _place[0] - 1) && (dest[1] == _place[1] + 1 || dest[1] == _place[1] - 1))
	{
		valid = true;
		bool blocked = false;
		int i = 0, j = 0;
		int x = 0, y = 0;
		x = dest[0] - 'a';
		y = dest[1] - '1';
		for (i = 0; valid && i < BOARD_SIZE && !blocked; i++)
		{
			//will be general color if, later
			if (board[i][y] != NULL && ((board[i][y]->getType() == 'r' && getIsWhite() == true) || (board[i][y]->getType() == 'R' && getIsWhite() == false)))
			{
				valid = !board[i][y]->isValidMove(dest, board);
			}
		}
	}
	return valid;
}

bool King::isValidMove(const Piece& other, Piece* board[][BOARD_SIZE])
{
	return isValidMove(other.getPlace(),board);
}


void King::isChecked(Piece* board[][BOARD_SIZE])
{
	bool answer = false;

	int intSource = this->placeToIndex(this->getPlace());
	int sourceI = intSource % 10, sourceJ = intSource / 10;

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (this->getIsWhite() != board[sourceI][sourceJ]->getIsWhite() && board[sourceI][sourceJ]->isValidMove(*this, board))
			{
				answer = true;
			}
		}
	}

	this->setIsChecked(answer);
}
