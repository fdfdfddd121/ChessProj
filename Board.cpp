#include "Board.h"
#include <iostream>

//top left is [0][0] as it is wayyy easier to look at while running over the array
#define startingBoard "RNBKQBNRPPPPPPPP################################pppppppprnbkqbnr"


Board::Board(Piece* _pieces[BOARD_SIZE][BOARD_SIZE], const bool turn = 0)
{
	this->_turn = turn;

	_pieces = new Piece*[BOARD_SIZE][BOARD_SIZE];

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			//piece needs to made as a pointer of the exact type, need to make piece creation system based on letter 
			this->_pieces[i][j] = new Piece(indexToPlace(i,j),startingBoard[i + j]);
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

//turns an index [i, j] to a placement, ie. e4
std::string indexToPlace(int i, int j)
{
	std::string place = "";

	place += (int('a') + j);
	place += (8 - i);
	
	return place;
}