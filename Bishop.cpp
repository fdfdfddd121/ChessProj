#include "Bishop.h"
#include "Board.h"
/// <summary>
/// constructor for Bishop
/// </summary>
/// <param name="place: "> where the piece will be</param>
/// <param name="type:"> what is the type of the piece. will always be B or b for this piece</param>
/// <param name="board:"> the board on which to create the bishop</param>
Bishop::Bishop(const std::string& place, const char type, Piece* board[][BOARD_SIZE]) :
    Piece(place, type, board)
{
    this->_hasMoved = false;
    this->_type = type;
    this->_place = place;
}
/// <summary>
/// destructor for Bishop
/// </summary>
Bishop::~Bishop()
{
}
/// <summary>
/// attempt to move the bishop
/// </summary>
/// <param name="dest:"> location to move the bishop to</param>
/// <param name="board:"> the board on which to move the bishop</param>
void Bishop::move(const std::string& dest, Piece* board[][BOARD_SIZE])
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
bool Bishop::isValidMove(const std::string& dest, Piece* board[][BOARD_SIZE])
{
    int destI = placeToIndex(dest) / 10, destJ = placeToIndex(dest) % 10;
    int srcI = placeToIndex(_place) / 10, srcJ = placeToIndex(_place) % 10;

    // Check if move is to same position
    if (dest.compare(this->getPlace()) == 0)
    {
        throw 7;
    }

    // Check if move is along rank or file
    if (abs(srcJ - destJ)!= abs(srcI - destI))
    {
        return false;
    }

    // Moving horizontally
    for (int i = 1; srcI-i > destI && srcJ-i > destJ; i++) {
        if (board[srcI - i][srcJ - i] != NULL) {
            return false;
        }
    }
    for (int i = 1; srcI-i > destI && srcJ+i < destJ; i++) {
        if (board[srcI - i][srcJ + i] != NULL) {
            return false;
        }
    }
    for (int i = 1; srcI+i <  destI && srcJ-i > destJ; i++) {
        if (board[srcI + i][srcJ - i] != NULL) {
            return false;
        }
    }
    for (int i = 1; srcI+i < destI && srcJ+i < destJ; i++) {
        if (board[srcI + i][srcJ + i] != NULL) {
            return false;
        }
    }

    // Check destination square
    if (board[destI][destJ] != NULL) {
        return board[destI][destJ]->getIsWhite() != this->getIsWhite();
    }

    return true;
}
/// <summary>
/// checks if the attempted movement is valid for the bishop
/// </summary>
/// <param name="other:"> the piece to which we want to move the bishop</param>
/// <param name="board:"> the board on which we want to validate the bishop's movement</param>
/// <returns>is the move valid</returns>
bool Bishop::isValidMove(const Piece& other, Piece* board[][BOARD_SIZE])
{
    return isValidMove(other.getPlace(), board);
}