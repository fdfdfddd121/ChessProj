#pragma once
#include <string>

#define BOARD_SIZE 8
class Piece {
protected:
	std::string _place;
	char _type;
	bool _hasMoved;
public:
	//basic class functions
	Piece(const std::string& place, const char type);
	virtual ~Piece();
	//setters
	void setPlace(const std::string& place);
	void setType(const char type);
	void setHasMoved(const bool hasMoved);
	//getters
	std::string getPlace() const;
	bool getIsWhite() const;
	char getType() const;
	bool gethasMoved() const;
	//pure virtual per piece functions
	virtual void move(const std::string& dest, Piece* board[][BOARD_SIZE]) = 0;
	virtual bool isValidMove(const std::string& dest, Piece* board[][BOARD_SIZE]) = 0;
	void eat(Piece& other);  //not virtual, eat is the same in all, valid is different
};