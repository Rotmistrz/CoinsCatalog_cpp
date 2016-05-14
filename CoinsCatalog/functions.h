#pragma once

#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <regex>

void split(const std::string&, char, std::vector<std::string>&);

template <typename T>
std::string to_string(T z) {
	std::ostringstream ss;
	ss << z;

	return ss.str();
}

int str2int(std::string);
float str2float(std::string);
std::string trim(std::string);
bool isInt(std::string);
bool isFloat(std::string);