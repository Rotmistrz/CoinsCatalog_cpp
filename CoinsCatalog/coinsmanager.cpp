#include "coinsmanager.h"

CoinsManager::CoinsManager(std::string filename) : filename(filename)
{	
	std::fstream file;
	file.open(filename, std::ios::in);

	std::string line;
	std::vector<std::string> data, dimensions;

	int id, shape, year;
	float weight, diameter, width, height;

	if (!file.is_open()) {
		throw std::string("Wystapil problem podczas otwierania pliku. Aplikacja moze nie dzialac poprawnie. Sprawdz, czy plik z baza danych istnieje.");
	}
	else {
		if (!file.eof()) {
			getline(file, line);
			
			line = trim(line);

			if (line.empty()) {
				nextIndex = 1;
			}
			else if (!std::regex_match(line, std::regex("[0-9]+"))) {
				throw std::string("Wystapil problem podczas odczytywania pliku. Aplikacja moze nie dzialac poprawnie. Sprawdz, czy plik z baza danych jest w odpowiedniej formie.");
			}
			else {
				nextIndex = str2int(line);
			}

			while (!file.eof()) {
				getline(file, line);

				if (std::regex_match(line, std::regex("([^\\|]*\\|){8}(.)*"))) {
					split(line, '|', data);

					id = str2int(data[0]);
					shape = str2int(data[1]);
					year = str2int(data[4]);
					weight = str2float(data[5]);

					if (shape == 1) {
						diameter = str2float(data[6]);

						RoundCoin* roundcoin = new RoundCoin(id, data[2], data[3], year, weight, diameter, data[7], data[8]);

						addCoin(roundcoin);
					}
					else {
						split(data[6], ',', dimensions);
						width = str2float(dimensions[0]);
						height = str2float(dimensions[1]);

						Dimensions dim = Dimensions(width, height);

						SquareCoin* squarecoin = new SquareCoin(id, data[2], data[3], year, weight, dim, data[7], data[8]);

						addCoin(squarecoin);
					}

					data.clear();
				}
				else {

				}
			}
		}
		file.close();
	}
}

CoinsManager::~CoinsManager()
{
}

int CoinsManager::getNextIndex() {
	return nextIndex;
}

void CoinsManager::countNextIndex() {
	std::map<int, Coin*>::iterator i = coins.end();
	Coin* lastCoin;

	if (i == coins.begin()) {
		nextIndex = 0;
	}
	else {
		try {
			--i;
			lastCoin = coins.at(i->first);
			nextIndex = lastCoin->getId() + 1;
		}
		catch (std::out_of_range& e) {
			nextIndex = 0;
		}
	}
}

bool CoinsManager::setFilename(std::string fn) {
	this->filename = fn;

	return true;
}

void CoinsManager::addCoin(Coin* coin) {
	int id = coin->getId();

	coins[id] = coin;

	if (nextIndex == id) {
		nextIndex++;
	}
}

bool CoinsManager::removeCoin(int id) {
	if (coins.erase(id)) {
		return true;
	}
	else {
		return false;
	}
}

Coin* CoinsManager::get(int id) {
	Coin* coin;

	try {
		coin = coins.at(id);
	}
	catch (std::out_of_range& e) {
		throw std::string("Nie ma monety o takim id.");
	}
	
	return coin;
}

bool CoinsManager::save() {
	std::fstream file;
	file.open(filename, std::ios::out);

	if (!file.is_open()) {
		return false;
	}
	else {
		file << to_string(nextIndex) + "\n";

		for (std::map<int, Coin*>::iterator i = coins.begin(); i != coins.end(); i++) {
			file << coins[i->first]->getToSave() + "\n";
		}

		file.close();
	}

	return true;
}

std::map<int, Coin*> CoinsManager::getCoinsList() {
	return coins;
}