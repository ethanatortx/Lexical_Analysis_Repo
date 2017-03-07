#include <iostream>
#include <string>
#include "btree.h"

int main()
{
	btree<std::string> source;

	source.add(" 10 ");
	source.add(" 20 ");

	std::cout << source;

	return 0;
}