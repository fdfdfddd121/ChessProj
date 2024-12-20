#pragma once
#include "Piece.h"
class King : public Piece {
private:
	bool _isChecked;
public:
	//basic class functions
	King(const std::string& place, const char type);
	virtual ~King();
	//setters
	void setIsChecked(const bool isChecked);
	//getters
	bool getIsChecked() const;
	//implement Piece functions
	virtual void move(const std::string& dest);
	virtual bool isValidMove(const std::string& dest);
	virtual void eat(Piece& other);
};