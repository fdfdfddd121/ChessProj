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
	virtual void move(const std::string& dest, Piece* board[][BOARD_SIZE]) override;
	virtual bool isValidMove(const std::string& dest, Piece* board[][BOARD_SIZE]) override;
	virtual bool isValidMove(const Piece& other, Piece* board[][BOARD_SIZE]) override;
	void isChecked(Piece* board[][BOARD_SIZE]);
};