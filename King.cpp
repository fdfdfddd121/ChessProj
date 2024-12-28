#include "King.h"
#include "Board.h"
/// <summary>
/// constructor for King
/// </summary>
/// <param name="place: "> where the piece will be</param>
/// <param name="type:"> what is the type of the piece. will always be K or k for this piece</param>
/// <param name="board:"> the board on which to create the king</param>
King::King(const std::string& place, const char type, Piece* board[][BOARD_SIZE]):
	Piece(place,type, board), _isChecked(false)
{
}
/// <summary>
/// destructor for King
/// </summary>
King::~King()
{
}
/// <summary>
/// sets if the king is in check
/// </summary>
/// <param name="isChecked:"> true if the king is in check, false if not</param>
void King::setIsChecked(const bool isChecked)
{
	_isChecked = isChecked;
}
/// <summary>
/// returns if the king is in check
/// </summary>
/// <returns> the value of _isChecked</returns>
bool King::getIsChecked() const
{
	return _isChecked;
}
/// <summary>
/// attempt to move the king
/// </summary>
/// <param name="dest:"> location to move the king to</param>
/// <param name="board:"> the board on which to move the king</param>
void King::move(const std::string& dest, Piece* board[][BOARD_SIZE])
{
	std::string pastPlace = this->getPlace();
	int destIndex = this->placeToIndex(dest);

	if (isValidMove(dest, board))
	{
		eat(board[int(destIndex / 10)][destIndex % 10], board); //if the move is valid try eating the piece that might be at the destination
	}
	else
	{
		//throw the fucking exception
		throw 6;
	}
	setPlace(dest, board); //move the king to hte destination
}
/// <summary>
/// checks if the attempted movement is valid for the king
/// </summary>
/// <param name="dest:"> the place we want to move the king to</param>
/// <param name="board:"> the board on which we check the validity of the movement</param>
/// <returns> is the move valid or not</returns>
bool King::isValidMove(const std::string& dest, Piece* board[][BOARD_SIZE])
{
    bool valid = false;
    int destI = placeToIndex(dest) / 10, destJ = placeToIndex(dest) % 10;
    int srcI = placeToIndex(_place) / 10, srcJ = placeToIndex(_place) % 10;

    if (dest.compare(this->getPlace()) == 0) //if the movement is to the same place
    {
        throw 7;
    }

	if (((destI == (srcI + 1) || destI == (srcI - 1) || (destI == srcI)) &&
		(destJ == (srcJ + 1) || destJ == (srcJ - 1)) || (destJ == srcJ) &&
		(destI == (srcI + 1) || destI == (srcI - 1)))) //is the movement of one square only
    {
		valid = true;
    }

    return valid;
}
/// <summary>
/// checks if the attempted movement is valid for the king
/// </summary>
/// <param name="other:"> the piece to which we want to move the king</param>
/// <param name="board:"> the board on which we want to validate the king's movement</param>
/// <returns>is the move valid</returns>
bool King::isValidMove(const Piece& other, Piece* board[][BOARD_SIZE])
{
	return isValidMove(other.getPlace(),board);
}
/// <summary>
/// checks if the king is in check
/// </summary>
/// <param name="source:"> location of the king</param>
/// <param name="king:"> pointer to the king</param>
/// <param name="board:"> board on which the king exists</param>
/// <returns> is the king in check</returns>
bool King::isChecked(const std::string& source, King& king, Piece* board[][BOARD_SIZE])
{
	bool answer = false;

	int intSource = placeToIndex(source);
	int sourceI = intSource / 10, sourceJ = intSource % 10;

	for (int i = 0; i < BOARD_SIZE && !answer; i++)
	{
		for (int j = 0; j < BOARD_SIZE && !answer; j++)
		{
			if (board[i][j] != &king && board[i][j] != NULL && (board[i][j]->getIsWhite() != king.getIsWhite()) && (*board[i][j]).isValidMove(source, board)) //can an enemy piece get to the king
			{
				answer = true;
			}
		}
	}

	return answer;
}
