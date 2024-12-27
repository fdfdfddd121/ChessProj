#include "Knight.h"
#include "Board.h"

Knight::Knight(const std::string& place, const char type, Piece* board[][BOARD_SIZE]):
	Piece(place, type, board)
{
}

Knight::~Knight()
{
}

void Knight::move(const std::string& dest, Piece* board[][BOARD_SIZE])
{
	int destIdx = placeToIndex(dest);
	if (isValidMove(dest, board))
	{
		eat(board[destIdx / 10][destIdx % 10], board);
	}
	else
	{
		Board::exceptionHandler(getPlace(), dest, board);
	}
	setPlace(dest, board);
}

bool Knight::isValidMove(const std::string& dest, Piece* board[][BOARD_SIZE])
{
	if (dest.compare(getPlace()) == 0)
	{
		throw 7;
	}
	int srcIdx = placeToIndex(getPlace()), destIdx = placeToIndex(dest);
	bool valid = ((((destIdx/10 == srcIdx/10+2 && (destIdx%10==srcIdx%10+1 || destIdx % 10 == srcIdx % 10-1))
		|| (destIdx / 10 == srcIdx / 10 - 2 && (destIdx % 10 == srcIdx % 10 + 1 || destIdx % 10 == srcIdx % 10 - 1)))
		|| ((destIdx % 10 == srcIdx % 10 + 2 && (destIdx / 10 == srcIdx / 10 + 1 || destIdx / 10 == srcIdx / 10 - 1))
		|| (destIdx % 10 == srcIdx % 10 - 2 && (destIdx / 10 == srcIdx / 10 + 1 || destIdx / 10 == srcIdx / 10 - 1)))));
	if (valid && board[destIdx/10][destIdx%10] != NULL) {
		return board[destIdx/10][destIdx%10]->getIsWhite() != getIsWhite();
	}
	return valid;
}

bool Knight::isValidMove(const Piece& other, Piece* board[][BOARD_SIZE])
{
	return isValidMove(other.getPlace(),board);
}
