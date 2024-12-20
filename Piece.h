#pragma once
#include <string>
std::string pieceNota = "kKqQrRnNbBpP";
class Piece {
protected:
	std::string _place;
	char _type;
	bool _hasMoved;
public:
	//basic object actions
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
	virtual void move(const std::string& dest) = 0;
	virtual bool isValidMove(const std::string& dest) = 0;
	virtual void eat(Piece& other) = 0;
};