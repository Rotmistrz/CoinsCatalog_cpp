#include "squarecoin.h"

SquareCoin::SquareCoin(int id, std::string fv, std::string name, int year, float weight, Dimensions dimensions, std::string edge, std::string comment)
: Coin(id, fv, name, year, weight, edge, comment), dimensions(dimensions)
{

}

SquareCoin::~SquareCoin() {

}

bool SquareCoin::isRound() {
	return false;
}

Dimensions SquareCoin::getDimensions() {
	return dimensions;
}

std::string SquareCoin::getDimensionsAsString() {
	if (dimensions.getWidth() > 0 && dimensions.getHeight() > 0) {
		return to_string(dimensions.getWidth()) + " x " + to_string(dimensions.getHeight());
	}
	else {
		return "";
	}
}

std::string SquareCoin::getToSave() {
	std::string coinline;

	float width = dimensions.getWidth();
	float height = dimensions.getHeight();
	std::string current_dimensions;

	if (width > 0 && height > 0) {
		current_dimensions = to_string(width) + ',' + to_string(height);
	}
	else {
		current_dimensions = to_string(0);
	}

	coinline = to_string(id) + '|' + to_string(isRound()) + '|' + facevalue + '|' + name + '|' + to_string(year) + '|' + to_string(weight) + '|' + current_dimensions + '|' + edge + '|' + comment;

	return coinline;
}

