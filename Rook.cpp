#include "Rook.h"
#include "Board.h"
/// <summary>
/// constructor for Rook
/// </summary>
/// <param name="place: "> where the piece will be</param>
/// <param name="type:"> what is the type of the piece. will always be R or r for this piece</param>
/// <param name="board:"> the board on which to create the rook</param>
Rook::Rook(const std::string& place, const char type, Piece* board[][BOARD_SIZE]):
	Piece(place, type, board)
{
	this->_hasMoved = false;
	this->_type = type;
	this->_place = place;
}
/// <summary>
/// destructor for Rook
/// </summary>
Rook::~Rook()
{
}
/// <summary>
/// attempt to move the rook
/// </summary>
/// <param name="dest:"> location to move the rook to</param>
/// <param name="board:"> the board on which to move the rook</param>
void Rook::move(const std::string& dest, Piece* board[][BOARD_SIZE])
{
	std::string pastPlace = this->getPlace();
	int destIndex = this->placeToIndex(dest);

	if (isValidMove(dest, board))
	{
		//in eat function if null we do nothing
		eat(board[int(destIndex/10)][destIndex%10], board);
	}
	else
	{
		//throw the fucking exception
        throw 6;
	}
	setPlace(dest, board);

}
/// <summary>
/// checks if the attempted movement is valid for the rook
/// </summary>
/// <param name="dest:"> the place we want to move the rook to</param>
/// <param name="board:"> the board on which we check the validity of the movement</param>
/// <returns> is the move valid or not</returns>
bool Rook::isValidMove(const std::string& dest, Piece* board[][BOARD_SIZE])
{
    int destI = placeToIndex(dest) / 10, destJ = placeToIndex(dest) % 10;
    int srcI = placeToIndex(_place) / 10, srcJ = placeToIndex(_place) % 10;

    // Check if move is to same position
    if (dest.compare(this->getPlace()) == 0)
    {
        throw 7;
    }

    // Check if move is along rank or file
    if (destI != srcI && destJ != srcJ)
    {
        return false;
    }

    // Moving horizontally
    if (srcI == destI) {
        int start = std::min(srcJ, destJ) + 1;
        int end = std::max(srcJ, destJ);

        // Check path is clear
        for (int j = start; j < end; j++) {
            if (board[srcI][j] != NULL) {
                return false;
            }
        }
    }
    // Moving vertically
    else {
        int start = std::min(srcI, destI) + 1;
        int end = std::max(srcI, destI);

        // Check path is clear
        for (int i = start; i < end; i++) {
            if (board[i][srcJ] != NULL) {
                return false;
            }
        }
    }

    // Check destination square
    if (board[destI][destJ] != NULL) {
        return board[destI][destJ]->getIsWhite() != this->getIsWhite();
    }

    return true;
}
/// <summary>
/// checks if the attempted movement is valid for the rook
/// </summary>
/// <param name="other:"> the piece to which we want to move the rook</param>
/// <param name="board:"> the board on which we want to validate the rook's movement</param>
/// <returns>is the move valid</returns>
bool Rook::isValidMove(const Piece& other, Piece* board[][BOARD_SIZE])
{
	return isValidMove(other.getPlace(), board);
}