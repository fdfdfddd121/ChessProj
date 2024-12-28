#include "Piece.h"
std::string pieceNota = "kKqQrRnNbBpP";
/// <summary>
/// constructor for Piece
/// </summary>
/// <param name="place:"> location of the piece on the board</param>
/// <param name="type:"> the type of chess piece</param>
/// <param name="board:"> the board on which to create the piece</param>
Piece::Piece(const std::string& place, const char type, Piece* board[][BOARD_SIZE]):
	_hasMoved(false)
{
	setPlace(place, board);
	setType(type);
}
/// <summary>
/// destructor for Piece
/// </summary>
Piece::~Piece()
{
}
/// <summary>
/// set the place of the piece on the board
/// </summary>
/// <param name="place:"> the location of the piece to be on the board</param>
/// <param name="board:"> the board on which we set the piece's place</param>
void Piece::setPlace(const std::string& place, Piece* board[][BOARD_SIZE])
{
    int intSource = placeToIndex(place);
    int sourceI = intSource / 10, sourceJ = intSource % 10;  // FIXED

    if (place.length() != 2 || (sourceI < 0 || sourceI > 7) || (sourceJ < 0 || sourceJ > 7)) // also fixed bounds
    {
        throw 5;
    }
    else if (_place == place)
    {
        throw 7;
    }

    if (!_place.empty()) //if the piece is already placed on the board
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
/// <summary>
/// sets the pieces type
/// </summary>
/// <param name="type:"> the type of the piece</param>
void Piece::setType(const char type)
{
//	if (pieceNota.find(type) == std::string::npos)
//	{
//		//special throw for none move stuff
//		//probably just do throw and the catch would be for (..)
//		//which means anything and then say that you did smth wrong in piece
//	}
	_type = type;
}
/// <summary>
/// sets if the piece has moved
/// </summary>
/// <param name="hasMoved:"> has the piece moved</param>
void Piece::setHasMoved(const bool hasMoved)
{
	_hasMoved = hasMoved;
}
/// <summary>
/// returns the place of the piece
/// </summary>
/// <returns>string of the piece's location</returns>
std::string Piece::getPlace() const
{
	return _place;
}
/// <summary>
/// returns if the piece is white
/// </summary>
/// <returns> if the piece white</returns>
bool Piece::getIsWhite() const
{
	return ('A' <=_type&&_type<='Z');
}
/// <summary>
/// returns the type of the piece
/// </summary>
/// <returns>the piece type character</returns>
char Piece::getType() const
{
	return _type;
}
/// <summary>
/// returns if the piece moved
/// </summary>
/// <returns>has the piece moved</returns>
bool Piece::gethasMoved() const
{
	return _hasMoved;
}
/// <summary>
/// if there is a piece to eat, eat it
/// </summary>
/// <param name="other:"> pointer to the piece we want to eat</param>
/// <param name="board:"> the board on which the piece is</param>
void Piece::eat(Piece* other, Piece* board[][BOARD_SIZE])
{
	if(other != NULL)
	{
	int pos = placeToIndex((*other).getPlace());
	int i = pos / 10, j = pos % 10;
	delete other;
	board[i][j] = nullptr;
	}
}
/// <summary>
/// turns an index [i, j] to a placement
/// </summary>
/// <param name="i:">board row index</param>
/// <param name="j:"> board column index</param>
/// <returns>string of the row and column</returns>
std::string Piece::indexToPlace(int i, int j)
{
	std::string place = "";

	place += ('a' + j); // j
	place += ((8 - i) + '0'); // i

	return place; // ji
}
/// <summary>
/// turns avplacement to an index ij (i is ans/10 and j is ans%10)
/// </summary>
/// <param name="place:"> string of the place of the piece</param>
/// <returns> int of the row in the ten's place and the column in the one's place indexes</returns>
int Piece::placeToIndex(std::string place)
{
	int ans = 0;

	ans += (8 - (int(place[1]) - int('0'))); // i - 7
	ans *= 10;
	ans += (int(place[0]) - int('a') ); //j - 7
	
	return ans; // ij
}