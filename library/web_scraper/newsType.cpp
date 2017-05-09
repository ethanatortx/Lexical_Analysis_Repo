
#include "newsType.h"
#include "utility\string_utility.h"

article::article(std::string artName)
{
	std::string line, sent = "";
	std::ifstream file("articles\\" + artName);
	if(file.is_open())
	{
		while(std::getline(file, line))
		{
			sent.append(split_string(line, ".!?", 3));
			if(sent != line)
			{
				std::vector<std::string> vec = split_string(line, ' ');
				list<std::string> sList;
				for(std::vector<std::string>::iterator i = vec.begin(); i != vec.end(); ++i)
				{
					sList.push_back(*i);
				}
				words.push_back(sList);
			}
		}
	}
}

std::string article::link() const
{ return _link; }
std::string article::sentence() const
{
	std::string all;
	for (std::vector<list<std::string> >::const_iterator i = words.begin(); i != words.end(); ++i)
	{
		for(list<std::string>::const_iterator k = i->begin(); i != i->end(); ++k)
		{
			all.append(*k);
		}
	}

	return all;
}

std::string article