#include "Board.h"
#include "King.h"
#include "Rook.h"
#include <iostream>

//top left is [0][0] as it is wayyy easier to look at while running over the array
//#define startingBoard "RNBKQBNRPPPPPPPP################################pppppppprnbkqbnr"
#define startingBoard "R##K###R################################################r##k###r"

Piece* Board::_WhiteKing = nullptr;
Piece* Board::_BlackKing = nullptr;

Board::Board(const bool turn)
{
	this->_BlackKing = NULL;
	this->_WhiteKing = NULL;
	std::string place = "";
	int iter = 0;
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
			if (startingBoard[iter] == 'R' || startingBoard[iter] == 'r')
			{
				place = Piece::indexToPlace(i, j);
				this->_pieces[i][j] = new Rook(place, startingBoard[iter], this->_pieces);
			}
			else if (startingBoard[iter] == 'N' || startingBoard[iter] == 'n')
			{

			}
			else if (startingBoard[iter] == 'B' || startingBoard[iter] == 'b')
			{

			}
			else if (startingBoard[iter] == 'K' || startingBoard[iter] == 'k')
			{
				place = Piece::indexToPlace(i, j);
				this->_pieces[i][j] = new King(place, startingBoard[iter], this->_pieces);
				if (startingBoard[iter] == 'K')
				{
					_WhiteKing =(King*) this->_pieces[i][j];
				}
				else if (startingBoard[iter] == 'k')
				{
					_BlackKing =(King*) this->_pieces[i][j];
				}
			}
			else if (startingBoard[iter] == 'Q' || startingBoard[iter] == 'q')
			{

			}
			else if (startingBoard[iter] == 'P' || startingBoard[iter] == 'p')
			{

			}
			else if (startingBoard[iter] == '#')
			{
				this->_pieces[i][j] = NULL;
			}
			iter++;
		}
	}
	printBoard();
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
	//[i][j]
	//mov - e2e4
	std::string msg = "";
	std::string src = move.substr(0, 2); //e2
	std::string dest = move.substr(2, 2); //e4
	bool checked;
	try
	{
		int src_idx = Piece::placeToIndex(src);
		int sourceI = src_idx / 10, sourceJ = src_idx % 10;
		Board::exceptionHandler(src,dest,_pieces);
		if (_pieces[sourceI][sourceJ]->getIsWhite() != !_turn)
		{
			throw 2; //not yo turn!
		}
		_pieces[sourceI][sourceJ]->move(dest, _pieces);
		printBoard();
	}
	catch (int code)
	{
		msg += code + '0';
		return msg;
	}
	if (_turn)
	{
		checked = (King::isChecked(_WhiteKing->getPlace(), *(King*)_WhiteKing, _pieces));
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
		checked = (King::isChecked(_BlackKing->getPlace(), *(King*)_BlackKing ,_pieces));
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
			if (_pieces[i][j] == NULL)
			{
				std::cout << "#" << " ";
			}
			else
			{
				std::cout << this->_pieces[i][j]->getType() << " ";
			}
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

	else if (((board[sourceI][sourceJ]->getIsWhite() && King::isChecked(_WhiteKing->getPlace(), *(King*)_WhiteKing, board) && board[sourceI][sourceJ]->getType() != 'K') || (!board[sourceI][sourceJ]->getIsWhite() && King::isChecked(_BlackKing->getPlace(), *(King*)_BlackKing, board) && board[sourceI][sourceJ]->getType() != 'k')))
	{
		board[sourceI][sourceJ]->move(dest, board);
		if (((board[destI][destJ]->getIsWhite() && King::isChecked(_WhiteKing->getPlace(), *(King*)_WhiteKing, board) && board[destI][destJ]->getType() != 'K') || (!board[destI][destJ]->getIsWhite() && King::isChecked(_BlackKing->getPlace(), *(King*)_BlackKing, board) && board[destI][destJ]->getType() != 'k')))
		{
			board[destI][destJ]->move(source, board);
			throw 4;
		}

		board[destI][destJ]->move(source, board);
		
	}

	else if (sourceI > BOARD_SIZE - 1 || sourceI < 0 || sourceJ > BOARD_SIZE - 1 || sourceJ < 0 || destI > BOARD_SIZE - 1 || destI < 0 || destJ > BOARD_SIZE - 1 || destJ < 0)
	{
		throw 5;
	}

	else if (!(*board[sourceI][sourceJ]).isValidMove(dest, board))
	{
		throw 6;
	}
}

