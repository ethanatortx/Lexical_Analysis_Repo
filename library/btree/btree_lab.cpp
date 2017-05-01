#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include "btree.h"
#include "csv\csv.h"

/*
	I'm not sure what I was supposed to sort the airports by, 
		so I just went with a lexicographical sort. I
		figured that would make more sense than sorting it
		by longitude and latitude coordinates since the
		outcomes of the long/lat sort vary so much.
*/

class airport
{
public:
	airport(): code(""), latitude(0.0), longitude(0.0) {}
	airport(std::string c, double la, double lo):
		code(c), latitude(la), longitude(lo)
	{}
	friend std::ostream& operator<<(std::ostream&, const airport&);
	friend bool operator==(const airport&, const airport&);
	friend bool operator!=(const airport&, const airport&);
	friend bool operator<=(const airport&, const airport&);
	friend bool operator<(const airport&, const airport&);
	friend bool operator>=(const airport&, const airport&);
	friend bool operator>(const airport&, const airport&);
	std::string code;
	double latitude;
	double longitude;
};

std::ostream& operator<<(std::ostream& os, const airport& ap)
{
	os << ap.code << ' ' << ap.latitude << ' ' << ap.longitude << ' ';
	return os;
}

bool operator==(const airport& lhs, const airport& rhs)
{
	if(lhs.code == rhs.code)
		if(lhs.latitude == rhs.latitude)
			if(lhs.longitude == rhs.longitude)
				return true;
}
bool operator!=(const airport& lhs, const airport& rhs)
{
	if(lhs.code != rhs.code){
		return true;
	}
	else
	{ 
		if(lhs.latitude != rhs.latitude)
			return true;
		else if(lhs.longitude != rhs.longitude)
			return true;
	}

	return false;
}

bool operator<=(const airport& lhs, const airport& rhs)
{
	if(lhs == rhs)
		return true;
	else if(lhs < rhs)
		return true;
	else
		return false;
}

bool operator<(const airport& lhs, const airport& rhs)
{
	if(lhs.code < rhs.code)
		return true;
	else
		return false;
}

bool operator>=(const airport& lhs, const airport& rhs)
{
	if(lhs == rhs)
		return true;
	else if(lhs > rhs)
		return true;
	else
		return false;
}

bool operator>(const airport& lhs, const airport& rhs)
{
	if(lhs.code > rhs.code)
		return true;
	else
		return false;
}

int main()
{
	btree<airport> bt(3);

	csv_reader cread("USAirportCodes.csv");
	cread.read_all();
	std::vector<std::vector<std::string> > svec = cread.data();

	for(typename std::vector<std::vector<std::string> >::iterator out = svec.begin()+1; out != svec.end(); ++out)
	{
		if((*out).size() > 0)
		{
			typename std::vector<std::string>::iterator it = (*out).begin();
			std::string s = *(it);
			double la = std::stod(*(++it));
			double lo = std::stod(*(++it));
			airport tmp(s, la, lo);

			bt.insert(tmp);
		}
	}

	bt.print();

	std::cout << "\n\n";

	bt.print_keys();

	std::cout << "\nSize: " << bt.size() << '\n';
	std::cout << "Depth: " << bt.depth() << '\n';
	std::cout << "Leaf count: " << bt.leaf_count() << '\n';
	return 0;
}
