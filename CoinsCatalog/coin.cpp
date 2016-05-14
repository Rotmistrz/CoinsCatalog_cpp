#include "coin.h"

Coin::Coin(int id, std::string fv, std::string name, int year, float weight, std::string edge, std::string comment)
: id(id), facevalue(fv), name(name), year(year), weight(weight), edge(edge), comment(comment)
{

}

Coin::~Coin() {

}

int Coin::getId() {
	return id;
}

std::string Coin::getFaceValue() {
	return facevalue;
}

void Coin::setFaceValue(std::string fv) {
	facevalue = fv;
}

std::string Coin::getName() {
	return name;
}

void Coin::setName(std::string n) {
	name = n;
}

int Coin::getYear() {
	return year;
}

float Coin::getWeight() {
	return weight;
}

std::string Coin::getEdge() {
	return edge;
}

std::string Coin::getComment() {
	return comment;
}