#pragma once
#include <string>
#include "coin.h"
#include "dimensions.h"

class SquareCoin : public Coin
{

protected:
	Dimensions dimensions;

public:
	SquareCoin(int, std::string, std::string, int, float, Dimensions, std::string, std::string);
	~SquareCoin();
	bool isRound();
	Dimensions getDimensions();
	std::string getToSave();
	std::string getDimensionsAsString();

	bool operator ==(const SquareCoin& coin) {
		return (this->year == coin.year) ? true : false;
	}

	bool operator >(const SquareCoin& coin) {
		return (this->year > coin.year) ? true : false;
	}

	bool operator <(const SquareCoin& coin) {
		return (this->year < coin.year) ? true : false;
	}
};
