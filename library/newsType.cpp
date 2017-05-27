
#include "newsType.h"
#include "utility\string_utility.h"

article::article(std::string artName)
{
	std::string line, sent = "";
	std::ifstream file("articles\\" + artName);
	if(file.is_open()){}
}

std::string article::link() const
{ return _link; }
std::string article::text() const
{
	std::string all;
	for (std::vector<list<std::string> >::const_iterator i = words.begin(); i != words.end(); ++i)
	{
		for(list<std::string>::const_iterator k = i->begin(); k != i->end(); ++k)
		{
			all.append(*k);
		}
	}

	return all;
}

std::string article::operator[](int&& loc) const
{
	std::string sent;
	for(list<std::string>::const_iterator i = words[loc].begin(); i != words[loc].end(); ++i)
		sent.append(*i);
	return sent;
}

std::string article::sentence(int&& loc) const
{
	std::string sent;
	for(list<std::string>::const_iterator i = words[loc].begin(); i != words[loc].end(); ++i)
		sent.append(*i);
	return sent;
}

std::ostream& operator<<(std::ostream& os, const article& a)
{
	
}