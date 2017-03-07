#include <iostream>
#include <string>
#include "btree.h"

int main()
{
	btree<int> source;

	source.add(10);
	source.add(20);

	source.add(30);
	source.add(40);
	source.add(50);

	std::cout << source.size();
	std::cout << source.to_string();

	return 0;
}