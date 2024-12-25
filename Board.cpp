#include "Board.h"
#include "King.h"
#include "Rook.h"
#include <iostream>

//top left is [0][0] as it is wayyy easier to look at while running over the array
//#define startingBoard "RNBKQBNRPPPPPPPP################################pppppppprnbkqbnr"
#define startingBoard "R##K###R################################################r##k###r"

Board::Board(const bool turn)
{
	this->_BlackKing = NULL;
	this->_WhiteKing = NULL;
	std::string place = "";
	std::string type = "";
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
				place = Piece::indexToPlace(i, j);
				type = startingBoard[i + j];
				this->_pieces[i][j] = new Rook(place, startingBoard[i + j], this->_pieces);
			}
			else if (startingBoard[i + j] == 'N' || startingBoard[i + j] == 'n')
			{

			}
			else if (startingBoard[i + j] == 'B' || startingBoard[i + j] == 'b')
			{

			}
			else if (startingBoard[i + j] == 'K' || startingBoard[i + j] == 'k')
			{
				place = Piece::indexToPlace(i, j);
				this->_pieces[i][j] = new King(place, startingBoard[i + j], this->_pieces);
				if (startingBoard[i + j] == 'K')
				{
					_WhiteKing =(King*) this->_pieces[i][j];
				}
				else if (startingBoard[i + j] == 'k')
				{
					_BlackKing =(King*) this->_pieces[i][j];
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

std::string Board::makeMove(std::string move)
{
	//mov - e2e4
	std::string msg = "";
	std::string src = move.substr(0, 2); //e2
	std::string dest = move.substr(2, 2); //e4
	bool checked;
	try
	{
		int src_idx = Piece::placeToIndex(src);
		int sourceI = src_idx % 10, sourceJ = src_idx / 10;
		Board::exceptionHandler(src,dest,_pieces);
		_pieces[sourceI][sourceJ]->move(dest, _pieces);
	}
	catch (int code)
	{
		msg += code + '0';
		return msg;
	}
	if (!_turn)
	{
		checked = ((King*)_WhiteKing)->isChecked(_WhiteKing->getPlace(), _pieces);
		((King*)_WhiteKing)->setIsChecked(checked);
		if (checked)
		{
			msg = '1';
		}
		else
		{
			msg = '0';
		}
	}
	else
	{
		checked = ((King*)_BlackKing)->isChecked(_BlackKing->getPlace(), _pieces);
		((King*)_BlackKing)->setIsChecked(checked);
		if (checked)
		{
			msg = '1';
		}
		else
		{
			msg = '0';
		}
	}
	flipTurn();
	return msg;
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
	std::string bord = startingBoard;
	char turn = char(int(_turn) + '0');
	bord += turn;
	return bord;
}
//exceptionHandler
void Board::exceptionHandler(const std::string& source, const std::string& dest, Piece* board[][BOARD_SIZE])
{
	//getting the indexes for the placements
	int intSource = Piece::placeToIndex(source), intDest = Piece::placeToIndex(dest);
	int sourceI = intSource / 10, sourceJ = intSource % 10;
	int destI = intDest / 10, destJ = intDest % 10;

	if (board[sourceI][sourceJ] == NULL)
	{
		throw 2;
	}

	else if (board[destI][destJ] != NULL && board[sourceI][sourceJ]->getIsWhite() == board[destI][destJ]->getIsWhite())
	{
		throw 3;
	}

	/*
	else if (false) //if after the move the king is in check
	{
		throw 4; is thrown already in king, not needed here
	}
	*/

	else if (sourceI > BOARD_SIZE - 1 || sourceI < 0 || sourceJ > BOARD_SIZE - 1 || sourceJ < 0 || destI > BOARD_SIZE - 1 || destI < 0 || destJ > BOARD_SIZE - 1 || destJ < 0)
	{
		throw 5;
	}

	else if (intSource == intDest)
	{
		throw 7;
	}
}

