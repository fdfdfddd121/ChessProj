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
	if (isValidMove(dest, board))
	{

	}
	setPlace(dest);
}

bool Rook::isValidMove(const std::string& dest, Piece* board[][BOARD_SIZE])
{
	bool valid = (dest[0]==_place[0] && 0 <= dest[1] && dest[1] < BOARD_SIZE) || (dest[1]==_place[1] && 0 <= dest[0] && dest[0]<BOARD_SIZE);
	if (valid)
	{
		int j = 0;
		if (dest[0] == _place[0])
		{
			if (dest[1] < _place[1])
			{
				for (j = _place[1] - '1'; j < dest[1] && valid; j++)
				{
					if (board[_place[0]][j] != NULL)
					{
						valid = false;
					}
				}
				if (board[dest[0]][dest[1]] != NULL)
				{
					valid = getIsWhite() == board[dest[0]][dest[1]]->getIsWhite();
				}
			}
			else
			{
				for (j = _place[1] - '1'; dest[1] < j && valid; j--)
				{
					if (board[_place[0]][j] != NULL)
					{
						valid = false;
					}
				}
				if (board[dest[0]][dest[1]] != NULL)
				{
					valid = getIsWhite() == board[dest[0]][dest[1]]->getIsWhite();
				}
			}
		}
		else if (dest[1] == _place[1])
		{
			if (dest[1] < _place[1])
			{
				for (j = _place[0] - 'a'; j < dest[0] && valid; j++)
				{
					if (board[j][_place[1]] != NULL)
					{
						valid = false;
					}
				}
				if (board[dest[0]][dest[1]] != NULL)
				{
					valid = getIsWhite() == board[dest[0]][dest[1]]->getIsWhite();
				}
			}
			else
			{
				for (j = _place[1] - 'a'; dest[0] < j && valid; j--)
				{
					if (board[j][_place[1]] != NULL)
					{
						valid = false;
					}
				}
				if (board[dest[0]][dest[1]] != NULL)
				{
					valid = getIsWhite() == board[dest[0]][dest[1]]->getIsWhite();
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