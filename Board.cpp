#include "Board.h"
#include "King.h"
#include "Rook.h"
#include "Knight.h"
#include "Queen.h"
#include "Bishop.h"
#include "Pawn.h"
#include <iostream>

//top left is [0][0] as it is wayyy easier to look at while running over the array
//#define startingBoard "RNBKQBNRPPPPPPPP################################pppppppprnbkqbnr"
#define startingBoard "RNBQKBNRP##############################################prnbqkbnr"

Piece* Board::_WhiteKing = nullptr; //pointer to white king
Piece* Board::_BlackKing = nullptr; //pointer to black king

/// <summary>
/// a funcrtion to create a chess piece
/// </summary>
/// <param name="place:"> locaiton of the piece on the board</param>
/// <param name="type:"> the type of chess piece: king, rook, knight,...</param>
/// <param name="board:"> the board on which to create the chess piece</param>
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
		board[i][j] = new Queen(place, type, board);
	}
	else if (type == 'P' || type == 'p')
	{
		board[i][j] = new Pawn(place, type, board);
	}
	else if (type == '#')
	{
		board[i][j] = NULL;
	}
}
/// <summary>
/// constructor for Board
/// </summary>
/// <param name="turn:"> true for black starting, false for white starting</param>
Board::Board(const bool turn):
	_turn(turn)
{
	//initialize the variables
	this->_BlackKing = NULL;
	this->_WhiteKing = NULL;
	std::string place = "";
	char type = 0;
	int iter = 0;
	//initialize the chess board with null pointers
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			_pieces[i][j] = NULL;
		}
	}
	//create a piece on the board according to the starting board string
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
	//just for debugging
	printBoard();
}
/// <summary>
/// destructor for Board
/// </summary>
Board::~Board()
{
	//deletes all the pointers of the chess board
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			delete this->_pieces[i][j];
		}
	}
}
/// <summary>
/// a function that interprates the message from the graphical engine with the Board
/// </summary>
/// <param name="move:">string that has the source and destenation of a piece on the board according to the graphical engine protocol</param>
/// <returns>movement code string according to the graphical engine protocol</returns>
std::string Board::makeMove(std::string move)
{
	//[i][j]
	//mov - e2e4
	std::string msg = "";
	std::string src = move.substr(0, 2); //e2
	std::string dest = move.substr(2, 2); //e4
	bool checked = false;
	//an easy way to catch code for bad movment
	try
	{
		//convert the source and destination to indexes in the board
		int src_idx = Piece::placeToIndex(src), dest_idx = Piece::placeToIndex(dest);
		int sourceI = src_idx / 10, sourceJ = src_idx % 10,destI = dest_idx/10, destJ = dest_idx%10;
		//check they are in the board bounds
		if (sourceI > BOARD_SIZE - 1 || sourceI < 0 || sourceJ > BOARD_SIZE - 1 || sourceJ < 0 || destI > BOARD_SIZE - 1 || destI < 0 || destJ > BOARD_SIZE - 1 || destJ < 0)
		{
				throw 5;
		}
		//check that the piece is of the color that is playing right now
		else if (_pieces[sourceI][sourceJ]!=NULL && _pieces[sourceI][sourceJ]->getIsWhite() != !_turn)
		{
			throw 2; //not yo turn!
		}

		Board::exceptionHandler(src,dest,_pieces); //check for any other bad movements
		_pieces[sourceI][sourceJ]->move(dest, _pieces); //move the piece if there are no problems
		_pieces[sourceI][sourceJ]->setHasMoved(true);
		//for debugging
		printBoard();
	}
	//if there is a movement problem send it to the graphical engine
	catch (int code)
	{
		msg += code + '0';
		return msg;
	}
	//if the move was correct we check if the opposite king is in check
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
/// <summary>
/// function for debugging that prints the chess board in text form
/// </summary>
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
/// <summary>
/// flip the turn to be the oppounents
/// </summary>
void Board::flipTurn()
{
	_turn = !_turn;
}
/// <summary>
/// function that returns the initial state of the board
/// </summary>
/// <returns>string of the chess boards initial state according to graphical engine protocol</returns>
std::string Board::getBoard() const
{
	std::string bord = startingBoard;
	char turn = char(int(_turn) + '0');
	bord += turn;
	return bord;
}
/// <summary>
/// exception handler that checks that the given movement is allowed and throws if there is a problem
/// </summary>
/// <param name="source:"> the place of the piece we want to move</param>
/// <param name="dest:"> the place we want the piece to move to</param>
/// <param name="board:"> the board on which we want to check the movement</param>
void Board::exceptionHandler(const std::string& source, const std::string& dest, Piece* board[][BOARD_SIZE])
{
	//getting the indexes for the placements
	int intSource = Piece::placeToIndex(source), intDest = Piece::placeToIndex(dest);
	int sourceI = intSource / 10, sourceJ = intSource % 10;
	int destI = intDest / 10, destJ = intDest % 10;

	if (board[sourceI][sourceJ] == NULL) //if there is no piece in the source location
	{
		throw 2;
	}

	else if (board[destI][destJ] != NULL && board[sourceI][sourceJ]->getIsWhite() == board[destI][destJ]->getIsWhite()) //if the destination location is already taken by a piece of the same color
	{
		throw 3;
	}

	else if (((board[sourceI][sourceJ]->getIsWhite() && King::isChecked(_WhiteKing->getPlace(), *(King*)_WhiteKing, board))
		|| (!board[sourceI][sourceJ]->getIsWhite() && King::isChecked(_BlackKing->getPlace(), *(King*)_BlackKing, board)))
		|| nextTurnCheck(source, dest, board)) //if the king of same color is in check or will be in check
	{
		
		bool stillInCheck = nextTurnCheck(source, dest, board); //check if the move will stop the check
		if (!board[sourceI][sourceJ]->isValidMove(dest, board) || stillInCheck) { //if not
			throw 4;
		}
	}

	else if (sourceI > BOARD_SIZE - 1 || sourceI < 0 || sourceJ > BOARD_SIZE - 1 || sourceJ < 0 || destI > BOARD_SIZE - 1 || destI < 0 || destJ > BOARD_SIZE - 1 || destJ < 0) //if the indexes are in bounds
	{
		throw 5;
	}

	else if (!(*board[sourceI][sourceJ]).isValidMove(dest, board)) //if the move is valid for the piece at the source location
	{
		throw 6;
	}
}
/// <summary>
/// checks that the wanted move wont pull it's own king in check
/// </summary>
/// <param name="source:"> place of the piece we want to move</param>
/// <param name="dest:"> location we want to move it to</param>
/// <param name="board:"> the board on which the movement occurs</param>
/// <returns>true if the move will put own king in check, false if not</returns>
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

