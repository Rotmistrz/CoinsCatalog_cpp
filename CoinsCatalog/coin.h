#pragma once
#include "functions.h"
#include <string>

class Coin
{
protected:
	unsigned int id;
	std::string facevalue;
	std::string name;
	int year;
	float weight;
	std::string edge;
	std::string comment;

public:
	Coin(int, std::string, std::string, int, float, std::string, std::string);
	~Coin();
	virtual bool isRound() = 0;
	int getId();
	std::string getFaceValue();
	std::string getName();
	int getYear();
	float getWeight();
	std::string getEdge();
	std::string getComment();
	void setFaceValue(std::string);
	void setName(std::string);
	void setYear(int);
	void setWeight(float);
	void setEdge(std::string);
	void setComment(std::string);
	virtual std::string getToSave() = 0;
	virtual std::string getDimensionsAsString() = 0;
};

