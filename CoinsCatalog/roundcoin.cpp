#include "roundcoin.h"

RoundCoin::RoundCoin(int id, std::string fv, std::string name, int year, float weight, float diameter, std::string edge, std::string comment)
: Coin(id, fv, name, year, weight, edge, comment), diameter(diameter)
{

}

RoundCoin::~RoundCoin() {

}

bool RoundCoin::isRound() {
	return true;
}

float RoundCoin::getDiameter() {
	return diameter;
}

std::string RoundCoin::getDimensionsAsString() {
	if (diameter > 0) {
		return to_string(diameter);
	}
	else {
		return "";
	}
}

std::string RoundCoin::getToSave() {
	std::string coinline;

	coinline = to_string(id) + '|' + to_string(isRound()) + '|' + facevalue + '|' + name + '|' + to_string(year) + '|' + to_string(weight) + '|' + to_string(diameter) + '|' + edge + '|' + comment;
	
	return coinline;
}