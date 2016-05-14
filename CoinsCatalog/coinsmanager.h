#pragma once

#include <string>
#include <iostream>
#include <stdexcept>
#include <regex>
#include <fstream>
#include <vector>
#include <map>
#include "functions.h"
#include "coin.h"
#include "roundcoin.h"
#include "squarecoin.h"

class CoinsManager
{

private:
	std::string filename;
	std::map<int, Coin*> coins;
	int nextIndex;

public:
	CoinsManager(std::string);
	~CoinsManager();
	int getNextIndex();
	void countNextIndex();
	void addCoin(Coin*);
	bool removeCoin(int);
	bool setFilename(std::string);
	Coin* get(int);
	std::map<int, Coin*> getCoinsList();
	bool save();
};

