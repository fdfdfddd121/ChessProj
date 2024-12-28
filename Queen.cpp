#include "Queen.h"
#include "Board.h"
/// <summary>
/// constructor for Queen
/// </summary>
/// <param name="place: "> where the piece will be</param>
/// <param name="type:"> what is the type of the piece. will always be Q or q for this piece</param>
/// <param name="board:"> the board on which to create the queen</param>
Queen::Queen(const std::string& place, const char type, Piece* board[][BOARD_SIZE]) :
    Rook(place, type, board), Bishop(place, type, board), Piece(place, type, board)
{
    this->_hasMoved = false;
    this->_type = type;
    this->_place = place;
}
/// <summary>
/// destructor for Queen
/// </summary>
Queen::~Queen()
{
}
/// <summary>
/// attempt to move the queen
/// </summary>
/// <param name="dest:"> location to move the queen to</param>
/// <param name="board:"> the board on which to move the queen</param>
void Queen::move(const std::string& dest, Piece* board[][BOARD_SIZE])
{
    std::string pastPlace = this->Piece::getPlace();
    int destIndex = this->placeToIndex(dest);

    if (isValidMove(dest, board))
    {
        //in eat function if null we do nothing, implement in piece.cpp
        Piece::eat(board[int(destIndex / 10)][destIndex % 10], board);
    }
    else
    {
        throw 6;
    }
    Piece::setPlace(dest, board);

}
/// <summary>
/// checks if the attempted movement is valid for the queen
/// </summary>
/// <param name="dest:"> the place we want to move the queen to</param>
/// <param name="board:"> the board on which we check the validity of the movement</param>
/// <returns> is the move valid or not</returns>
bool Queen::isValidMove(const std::string& dest, Piece* board[][BOARD_SIZE])
{
    bool valid;
    valid = Rook::isValidMove( dest,board) || Bishop::isValidMove(dest, board);
    return valid;
}
/// <summary>
/// checks if the attempted movement is valid for the queen
/// </summary>
/// <param name="other:"> the piece to which we want to move the queen</param>
/// <param name="board:"> the board on which we want to validate the queen's movement</param>
/// <returns>is the move valid</returns>
bool Queen::isValidMove(const Piece& other, Piece* board[][BOARD_SIZE])
{
    return isValidMove(other.getPlace(), board);
}