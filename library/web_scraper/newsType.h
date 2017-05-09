#ifndef _NEWS_TYPE_H_
#define _NEWS_TYPE_H_

#include <string>
#include <vector>
#include <fstream>
#include "linked_list\list.h"

class article
{
public:
	article(std::string artName);

	std::string link() const;
	std::string sentence(unsigned&& loc) const;

	friend std::ostream& operator<<(std::ostream& os, const article& a);

	~article();
private:
	std::string _link;
	std::vector<list<std::string> > words;
};

#endif