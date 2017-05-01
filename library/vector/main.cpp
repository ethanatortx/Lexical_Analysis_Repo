#include <iostream>
#include <string>
#include "vector.h"

int main()
{
	vector<int> vec;

	int t, data;
	std::cout << "How many elements to insert? ";
	std::cin >> t;

	for(int i = 0; i < t; ++i)
	{
		std::cin >> data;
		vec.push_back(data);
	}

	std::cout << "Which element to get? ";
	std::cin >> t;

	std::cout << "Element " << t << ": " << vec[t] << std::endl;

	std::cout << "Full vector: " << vec << std::endl;

	return 0;
}