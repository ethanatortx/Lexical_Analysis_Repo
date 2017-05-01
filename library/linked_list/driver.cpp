
#include <iostream>
#include "list.h"

int main()
{
	list<int> test;

	test.push_back(10);
	test.push_back(5);
	test.push_back(15);
	test.push_back(20);
	test.push_back(0);
	test.push_back(25);

	merge_sort(&test);

	std::cout << test;
}