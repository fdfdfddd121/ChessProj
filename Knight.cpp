#include "Knight.h"
#include "Board.h"
/// <summary>
/// constructor for Knight
/// </summary>
/// <param name="place: "> where the piece will be</param>
/// <param name="type:"> what is the type of the piece. will always be N or n for this piece</param>
/// <param name="board:"> the board on which to create the knight</param>
Knight::Knight(const std::string& place, const char type, Piece* board[][BOARD_SIZE]):
	Piece(place, type, board)
{
}
/// <summary>
/// destructor for Knight
/// </summary>
Knight::~Knight()
{
}
/// <summary>
/// attempt to move the knight
/// </summary>
/// <param name="dest:"> location to move the knight to</param>
/// <param name="board:"> the board on which to move the knight</param>
void Knight::move(const std::string& dest, Piece* board[][BOARD_SIZE])
{
	int destIdx = placeToIndex(dest);
	if (isValidMove(dest, board))
	{
		eat(board[destIdx / 10][destIdx % 10], board);
	}
	else
	{
		throw 6;
	}
	setPlace(dest, board);
}
/// <summary>
/// checks if the attempted movement is valid for the knight
/// </summary>
/// <param name="dest:"> the place we want to move the knight to</param>
/// <param name="board:"> the board on which we check the validity of the movement</param>
/// <returns> is the move valid or not</returns>
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
/// <summary>
/// checks if the attempted movement is valid for the knight
/// </summary>
/// <param name="other:"> the piece to which we want to move the knight</param>
/// <param name="board:"> the board on which we want to validate the knight's movement</param>
/// <returns>is the move valid</returns>
bool Knight::isValidMove(const Piece& other, Piece* board[][BOARD_SIZE])
{
	return isValidMove(other.getPlace(),board);
}
