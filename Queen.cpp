#include "Queen.h"
#include "Board.h"

Queen::Queen(const std::string& place, const char type, Piece* board[][BOARD_SIZE]) :
    Rook(place, type, board), Bishop(place, type, board), Piece(place, type, board)
{
    this->_hasMoved = false;
    this->_type = type;
    this->_place = place;
}

Queen::~Queen()
{
}

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

bool Queen::isValidMove(const std::string& dest, Piece* board[][BOARD_SIZE])
{
    bool valid;
    valid = Rook::isValidMove( dest,board) || Bishop::isValidMove(dest, board);
    return valid;
}
bool Queen::isValidMove(const Piece& other, Piece* board[][BOARD_SIZE])
{
    return isValidMove(other.getPlace(), board);
}