#ifndef STRING_UTILTIY_H
#define STRING_UTILTIY_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> split_string(std::string s, const char delim)
{
	std::stringstream ss(s);
	std::vector<std::string> svec;
	std::string frac;

	while(std::getline(ss, frac, delim))
	{
		svec.push_back(frac);
	}
	return svec;
}

#endif