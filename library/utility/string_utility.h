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

std::vector<std::string> split_string(std::string s, const char* delims, unsigned delimC)
{
	std::vector<std::string> svec;
	std::string frac;

	for(std::string::iterator i = s.begin(); i != s.end(); ++i)
	{
		for(unsigned q = 0; q < delimC; ++q)
		{
			if((*i) == delims[q])
			{
				svec.push_back(frac);
				frac.clear();
				++i;
				break;
			}
		}

		frac.append(1, *i);
	}

	return svec;
}

#endif