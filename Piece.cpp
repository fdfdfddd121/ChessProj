#include "Piece.h"
std::string pieceNota = "kKqQrRnNbBpP";
Piece::Piece(const std::string& place, const char type, Piece* board[][BOARD_SIZE]):
	_hasMoved(false)
{
	setPlace(place, board);
	setType(type);
}

Piece::~Piece()
{
}

void Piece::setPlace(const std::string& place, Piece* board[][BOARD_SIZE])
{
	int intSource = placeToIndex(place);
	int sourceI = intSource % 10, sourceJ = intSource / 10;
	if (place.length()!=2 || (sourceI <0 || sourceI>8) || (sourceJ < 0 || sourceJ>8)) //invalid indeces(so basicaly the writing)
	{
		throw 5;
	}
	else if (_place == place) //dest is same location as src
	{
		throw 7;
	}
	if (!_place.empty())
	{
		int old_place = placeToIndex(_place);
		int oldI = old_place / 10, oldJ = old_place % 10;
		Piece* this_piece = board[oldI][oldJ];
		_place = place;
		int new_place = placeToIndex(_place);
		int newI = new_place / 10, newJ = new_place % 10;
		board[newI][newJ] = this_piece;
		board[oldI][oldJ] = NULL;
	}
	else
	{
		_place = place;
	}

}

void Piece::setType(const char type)
{
	if (pieceNota.find(type) == std::string::npos)
	{
		//special throw for none move stuff
		//probably just do throw and the catch would be for (..)
		//which means anything and then say that you did smth wrong in piece
	}
	_type = type;
}

void Piece::setHasMoved(const bool hasMoved)
{
	_hasMoved = hasMoved;
}

std::string Piece::getPlace() const
{
	return _place;
}

bool Piece::getIsWhite() const
{
	return ('A' <=_type&&_type<='Z');
}

char Piece::getType() const
{
	return _type;
}

bool Piece::gethasMoved() const
{
	return _hasMoved;
}

void Piece::eat(Piece& other)
{
	delete &other;
}

//turns an index [i, j] to a placement, ie. e4
std::string Piece::indexToPlace(int i, int j)
{
	std::string place = "";

	place += ('a' + j); // j
	place += ((8 - i) + '0'); // i

	return place; // ji
}

//turns aplacement to an index ij (i is ans/10 and j is ans%10)
//h8
int Piece::placeToIndex(std::string place)
{
	int ans = 0;

	ans += (8 - (int(place[1]) - int('0'))); // i - 7
	ans *= 10;
	ans += (int(place[0]) - int('a') ); //j - 7
	
	return ans; // ij
}