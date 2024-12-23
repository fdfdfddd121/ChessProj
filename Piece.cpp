#include "Piece.h"
std::string pieceNota = "kKqQrRnNbBpP";
Piece::Piece(const std::string& place, const char type):
	_hasMoved(false)
{
	setPlace(place);
	setType(type);
}

Piece::~Piece()
{
}

void Piece::setPlace(const std::string& place)
{
	if (place.length()!=2 || (place[0]<'a' || place[0]>'h') || (place[1] < '1' || place[1]>'8')) //invalid indeces(so basicaly the writing)
	{
		throw 5;
	}
	else if (_place == place) //dest is same location as src
	{
		throw 7;
	}
	_place = place;
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
}

//turns an index [i, j] to a placement, ie. e4
std::string Piece::indexToPlace(int i, int j)
{
	std::string place = "";

	place += (int('a') + j);
	place += (BOARD_SIZE - i);

	return place;
}

//turns aplacement to an index ij (i is ans/10 and j is ans%10)
int Piece::placeToIndex(std::string place)
{
	int ans = 0;

	ans += (BOARD_SIZE - int(place[1]));
	ans += (int(place[0]) - int('a'));

	return ans;
}