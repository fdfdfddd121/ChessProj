#include "Piece.h"

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
