#include "Pawn.h"
#include "Board.h"
/// <summary>
/// constructor for Bishop
/// </summary>
/// <param name="place: "> where the piece will be</param>
/// <param name="type:"> what is the type of the piece. will always be B or b for this piece</param>
/// <param name="board:"> the board on which to create the bishop</param>
Pawn::Pawn(const std::string& place, const char type, Piece* board[][BOARD_SIZE]) :
    Piece(place, type, board)
{
    this->_hasMoved = false;
    this->_type = type;
    this->_place = place;
}
/// <summary>
/// destructor for Bishop
/// </summary>
Pawn::~Pawn()
{
}
/// <summary>
/// attempt to move the bishop
/// </summary>
/// <param name="dest:"> location to move the bishop to</param>
/// <param name="board:"> the board on which to move the bishop</param>
void Pawn::move(const std::string& dest, Piece* board[][BOARD_SIZE])
{
    std::string pastPlace = this->getPlace();
    int destIndex = this->placeToIndex(dest);

    if (isValidMove(dest, board))
    {
        //in eat function if null we do nothing, implement in piece.cpp
        eat(board[int(destIndex / 10)][destIndex % 10], board);
    }
    else
    {
        throw 6;
    }
    setPlace(dest, board);

}
/// <summary>
/// checks if the attempted movement is valid for the bishop
/// </summary>
/// <param name="dest:"> the place we want to move the bishop to</param>
/// <param name="board:"> the board on which we check the validity of the movement</param>
/// <returns> is the move valid or not</returns>
bool Pawn::isValidMove(const std::string& dest, Piece* board[][BOARD_SIZE])
{
    int destI = placeToIndex(dest) / 10, destJ = placeToIndex(dest) % 10;
    int srcI = placeToIndex(_place) / 10, srcJ = placeToIndex(_place) % 10;

    // Check if move is to same position
    if (dest.compare(this->getPlace()) == 0)
    {
        throw 7;
    }

    bool valid = true;

    if (srcJ != destJ || (srcI + 1 != destI || srcI + 1 + int(this->gethasMoved()) != destI))
    {
        valid = false;
    }
    if ((srcI + 1 == destI) && abs(srcJ - destJ) == 1)
    {
        if (board[srcJ][destJ] != NULL && board[srcJ][destJ]->getIsWhite() != this->getIsWhite())
        {
            valid = true;
        }
    }

    return valid;
}
/// <summary>
/// checks if the attempted movement is valid for the bishop
/// </summary>
/// <param name="other:"> the piece to which we want to move the bishop</param>
/// <param name="board:"> the board on which we want to validate the bishop's movement</param>
/// <returns>is the move valid</returns>
bool Pawn::isValidMove(const Piece& other, Piece* board[][BOARD_SIZE])
{
    return isValidMove(other.getPlace(), board);
}