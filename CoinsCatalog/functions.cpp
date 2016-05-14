#include "functions.h"

void split(const std::string& s, char c,
	std::vector<std::string>& v) {
	std::string::size_type i = 0;
	std::string::size_type j = s.find(c);

	while (j != std::string::npos) {
		v.push_back(s.substr(i, j - i));
		i = ++j;
		j = s.find(c, j);

		if (j == std::string::npos)
			v.push_back(s.substr(i, s.length()));
	}
}

int str2int(std::string str)
{
	std::stringstream ss;
	int temp;
	ss << str;
	ss >> temp;
	
	return temp;
}

std::string trim(std::string s)
{
	std::string::size_type pos = s.find_last_not_of(' ');
	if (pos != std::string::npos)
	{
		if (s.length() != pos + 1)
			s.erase(pos + 1);
		pos = s.find_first_not_of(' ');
		if (pos != 0)
			s.erase(0, pos);
	}
	else s = "";

	return s;
}

float str2float(std::string str)
{
	str = trim(str);

	if (str.empty()) {
		return 0;
	}


	for (int i = 0; i < str.size(); i++) {
		if (str[i] == ',') str[i] = '.';
	}

	std::stringstream ss;
	float temp;
	ss << str;
	ss >> temp;
	return temp;
}

bool isInt(std::string str) {
	return (std::regex_match(str, std::regex("[0-9]*|(-[0-9]+)"))) ? true : false;
}
bool isFloat(std::string str) {
	return (std::regex_match(str, std::regex("^[0-9]*|([0-9]+[,\.]{1}[0-9]+)$"))) ? true : false;
}