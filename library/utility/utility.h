#ifndef UTILTIY_H
#define UTILTIY_H

#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> split_string(std::string s, const char delim)
{
	std::stringstream ss(s);
	std::string temp;
	std::vector<std::string> vec;
	
	while(std::getline(ss, temp, delim))
	{
		vec.push_back(temp);
	}

	return vec;
}

#endif