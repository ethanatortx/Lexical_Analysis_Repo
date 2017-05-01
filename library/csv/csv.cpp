#include <vector>
#include <iostream>
#include <string>
#include "csv.h"

int main()
{
	csv_reader cread("USAirportCodes.csv");
	cread.read_all();
	std::vector<std::vector<std::string> > svec = cread.data();

	for (typename std::vector<std::vector<std::string> >::iterator out = svec.begin(); out != svec.end(); ++out)
	{
		for (typename std::vector<std::string>::iterator in = (*out).begin(); in != (*out).end(); ++in)
		{
			std::cout << *in;
		}

		std::cout << '\n';
	}
	return 0;
}