#ifndef CSV_H
#define CSV_H

#include <string>
#include <vector>
//#include <iostream>
#include <fstream>
#include "utility\string_utility.h"

class csv_reader
{
	typedef std::vector<std::vector<std::string> > stringvector;
public:
	csv_reader(const std::string& nm);

	void read_all();
	void read_line();

	stringvector data() const;

private:
	std::string fname;
	stringvector svec;
	std::fstream file;
};

csv_reader::csv_reader(const std::string& nm):
	fname(nm)
{
	file.open(fname, std::ios_base::in);
}

void csv_reader::read_all()
{
	if(file.is_open())
	{
		while(!(file.eof()))
		{
			read_line();
		}
	}
}

void csv_reader::read_line()
{
	if(file.is_open())
	{
		if(!(file.eof())){
			std::string line;
			std::getline(file, line, '\n');
			std::vector<std::string> t(split_string(line, ','));
			svec.push_back(t);
		}
	}
}

inline typename csv_reader::stringvector csv_reader::data() const { return svec; }

#endif