#include "Board.h"
#include "King.h"
#include "Rook.h"
#include <iostream>

//top left is [0][0] as it is wayyy easier to look at while running over the array
#define startingBoard "RNBKQBNRPPPPPPPP################################pppppppprnbkqbnr"

Board::Board(Piece* pieces[BOARD_SIZE][BOARD_SIZE], const bool turn)
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
				this->_pieces[i][j] = new Rook(indexToPlace(i, j), startingBoard[i + j]);
			}
			else if (startingBoard[i + j] == 'N' || startingBoard[i + j] == 'n')
			{

			}
			else if (startingBoard[i + j] == 'B' || startingBoard[i + j] == 'b')
			{

			}
			else if (startingBoard[i + j] == 'K' || startingBoard[i + j] == 'k')
			{
				this->_pieces[i][j] = new King(indexToPlace(i, j), startingBoard[i + j]);
			}
			else if (startingBoard[i + j] == 'Q' || startingBoard[i + j] == 'q')
			{

			}
			else if (startingBoard[i + j] == 'P' || startingBoard[i + j] == 'p')
			{

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

//turns an index [i, j] to a placement, ie. e4
std::string Board::indexToPlace(int i, int j)
{
	std::string place = "";

	place += (int('a') + j);
	place += (8 - i);

	return place;
}

//turns aplacement to an index ij (i is ans/10 and j is ans%10)
int Board::placeToIndex(std::string place)
{
	int ans = 0;

	ans += (8 + int(place[1]));
	ans += (int(place[0]) - int('a'));

	return ans;
}