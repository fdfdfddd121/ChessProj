#include "Board.h"
#include "King.h"
#include "Rook.h"
#include <iostream>

//top left is [0][0] as it is wayyy easier to look at while running over the array
#define startingBoard "RNBKQBNRPPPPPPPP################################pppppppprnbkqbnr"

Board::Board(const bool turn)
{
	this->_turn = turn;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			_pieces[i][j] = NULL;
		}
	}
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (startingBoard[i + j] == 'R' || startingBoard[i + j] == 'r')
			{
				this->_pieces[i][j] = new Rook(this->_pieces[i][j]->indexToPlace(i, j), startingBoard[i + j]);
			}
			else if (startingBoard[i + j] == 'N' || startingBoard[i + j] == 'n')
			{

			}
			else if (startingBoard[i + j] == 'B' || startingBoard[i + j] == 'b')
			{

			}
			else if (startingBoard[i + j] == 'K' || startingBoard[i + j] == 'k')
			{
				this->_pieces[i][j] = new King(this->_pieces[i][j]->indexToPlace(i, j), startingBoard[i + j]);
				if (startingBoard[i + j] == 'K')
				{
					_WhiteKing = this->_pieces[i][j];
				}
				if (startingBoard[i + j] == 'k')
				{
					_BlackKing = this->_pieces[i][j];
				}
			}
			else if (startingBoard[i + j] == 'Q' || startingBoard[i + j] == 'q')
			{

			}
			else if (startingBoard[i + j] == 'P' || startingBoard[i + j] == 'p')
			{

			}
			else if (startingBoard[i + j] == '#')
			{
				this->_pieces[i][j] = NULL;
			}
		}
	}
}

Board::~Board()
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			delete this->_pieces[i][j];
		}
	}
}

void Board::printBoard() const
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			std::cout << this->_pieces[i][j] << " ";
		}
		std::cout << '\n';
	}
}

void Board::flipTurn()
{
	_turn = !_turn;
}

std::string Board::getBoard() const
{
	return startingBoard+(_turn+'0');
}
//exceptionHandler
int Board::exceptionHandler(const std::string& source, const std::string& dest, Piece* board[][BOARD_SIZE], Piece& piece)
{
	//getting the indexes for the placements
	int intSource = piece.placeToIndex(source), intDest = piece.placeToIndex(dest);
	int sourceI = intSource % 10, sourceJ = intSource / 10;
	int destI = intDest % 10, destJ = intDest / 10;

	if (board[sourceI][sourceJ] == NULL)
	{
		throw 2;
	}

	else if (board[sourceI][sourceJ]->getIsWhite() == board[destI][destJ]->getIsWhite())
	{
		throw 3;
	}

	else if (false) //if after the move the king is in check
	{
		throw 4;
	}

	else if (sourceI > BOARD_SIZE - 1 || sourceI < 0 || sourceJ > BOARD_SIZE - 1 || sourceJ < 0 || destI > BOARD_SIZE - 1 || destI < 0 || destJ > BOARD_SIZE - 1 || destJ < 0)
	{
		throw 5;
	}

	else if (intSource == intDest)
	{
		throw 7;
	}

	else
	{
		throw 6; //if the move is from the start not valid and none of the other problems it must be this (invalid move from the piece type)
	}

}

