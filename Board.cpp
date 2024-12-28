#include "Board.h"
#include "King.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include <iostream>

//top left is [0][0] as it is wayyy easier to look at while running over the array
//#define startingBoard "RNBKQBNRPPPPPPPP################################pppppppprnbkqbnr"
#define startingBoard "RNBK#BNR################################################rnbk#bnr"

Piece* Board::_WhiteKing = nullptr;
Piece* Board::_BlackKing = nullptr;

void Board::makePiece(const std::string& place, const char type, Piece* board[][BOARD_SIZE])
{
	int i = Piece::placeToIndex(place) / 10, j = Piece::placeToIndex(place) % 10;
	if (type == 'R' || type == 'r')
	{
		board[i][j] = new Rook(place, type, board);
	}
	else if (type == 'N' || type == 'n')
	{
		board[i][j] = new Knight(place, type, board);
	}
	else if (type == 'B' || type == 'b')
	{
		board[i][j] = new Bishop(place, type, board);
	}
	else if (type == 'K' || type == 'k')
	{
		board[i][j] = new King(place, type, board);
		if (type == 'K')
		{
			_WhiteKing = (King*)board[i][j];
		}
		else if (type == 'k')
		{
			_BlackKing = (King*)board[i][j];
		}
	}
	else if (type == 'Q' || type == 'q')
	{

	}
	else if (type == 'P' || type == 'p')
	{

	}
	else if (type == '#')
	{
		board[i][j] = NULL;
	}
}

Board::Board(const bool turn)
{
	this->_BlackKing = NULL;
	this->_WhiteKing = NULL;
	std::string place = "";
	char type = 0;
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
			place = Piece::indexToPlace(i, j);
			type = startingBoard[iter];
			makePiece(place, type, _pieces);
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
		int src_idx = Piece::placeToIndex(src), dest_idx = Piece::placeToIndex(dest);
		int sourceI = src_idx / 10, sourceJ = src_idx % 10,destI = dest_idx/10, destJ = dest_idx%10;
		if (sourceI > BOARD_SIZE - 1 || sourceI < 0 || sourceJ > BOARD_SIZE - 1 || sourceJ < 0 || destI > BOARD_SIZE - 1 || destI < 0 || destJ > BOARD_SIZE - 1 || destJ < 0)
		{
				throw 5;
		}
		else if (_pieces[sourceI][sourceJ]!=NULL && _pieces[sourceI][sourceJ]->getIsWhite() != !_turn)
		{
			throw 2; //not yo turn!
		}
		Board::exceptionHandler(src,dest,_pieces);
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

	else if (((board[sourceI][sourceJ]->getIsWhite() && King::isChecked(_WhiteKing->getPlace(), *(King*)_WhiteKing, board))
		|| (!board[sourceI][sourceJ]->getIsWhite() && King::isChecked(_BlackKing->getPlace(), *(King*)_BlackKing, board)))
		|| nextTurnCheck(source, dest, board))
	{
		
		bool stillInCheck = nextTurnCheck(source, dest, board);
		if (!board[sourceI][sourceJ]->isValidMove(dest, board) || stillInCheck) {
			throw 4;
		}
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

bool Board::nextTurnCheck(const std::string& source, const std::string& dest, Piece* board[][BOARD_SIZE])
{
	int intSource = Piece::placeToIndex(source), intDest = Piece::placeToIndex(dest);
	int sourceI = intSource / 10, sourceJ = intSource % 10;
	int destI = intDest / 10, destJ = intDest % 10;
	char type = 0;
	if (board[destI][destJ] != NULL)
	{
		type = board[destI][destJ]->getType();
	}
	// First check if it's an invalid move before testing check block
	if (!board[sourceI][sourceJ]->isValidMove(dest, board))
	{
		throw 6;  // Invalid move
	}

	// Test if the move would block the check
	std::string origSource = board[sourceI][sourceJ]->getPlace();

	// Make the test move
	board[sourceI][sourceJ]->move(dest, board);
	printBoard();

	// Check if king is still in check
	bool stillInCheck;
	if (board[destI][destJ]->getIsWhite()) {
		stillInCheck = King::isChecked(_WhiteKing->getPlace(), *(King*)_WhiteKing, board);
	}
	else {
		stillInCheck = King::isChecked(_BlackKing->getPlace(), *(King*)_BlackKing, board);
	}

	// Restore board state
	board[destI][destJ]->move(origSource, board);
	printBoard();
	if (type != 0)
	{
		makePiece(dest, type, board);
	}
	return stillInCheck;
}

