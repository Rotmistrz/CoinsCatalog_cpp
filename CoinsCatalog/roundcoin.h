#pragma once

#include "coin.h"
#include <string>

class RoundCoin : public Coin
{

protected:
	float diameter;

public:
	RoundCoin(int, std::string, std::string, int, float, float, std::string, std::string);
	~RoundCoin();
	bool isRound();
	float getDiameter();
	void setDiameter(float);
	std::string getToSave();
	std::string getDimensionsAsString();
	
	bool operator ==(const RoundCoin& coin) {
		return (this->year == coin.year) ? true : false;
	}

	bool operator >(const RoundCoin& coin) {
		return (this->year > coin.year) ? true : false;
	}

	bool operator <(const RoundCoin& coin) {
		return (this->year < coin.year) ? true : false;
	}
};