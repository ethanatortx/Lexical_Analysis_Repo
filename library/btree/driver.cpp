#include <iostream>
#include <cstdlib>
#include "btree.h"

template<class T>
void print_vec(std::vector<T> v)
{
	for(typename std::vector<T>::iterator i = v.begin(); i != v.end(); ++i)
	{
		std::cout << *i << ' ';
	}
}

int main()
{
	btree<int> b(50);
	int k;
	for(int i = 0; i < 10000; ++i)
	{
		std::cout << "\nTest " << i << '\n';
		k = std::rand();
		std::cout << "Inserting " << k << " into tree";
		b.insert(k);
	}
	std::cout << "\n\nData in tree: \n";
	b.print();
	std::cout << "\n\n";

	int size, q;
	std::vector<int> data_erased;
	char cont = 'y';
	while(cont == 'y')
	{
		std::cout << "How many times to prompt for erase? ";
		std::cin >> size;
		for(int i = 0; i < size; ++i)
		{
			std::cout << "Enter number to erase: ";
			std::cin >> q;
			if(b.search(q) == nullptr)
				std::cout << "Number not in btree.\n";
			else
			{
				data_erased.push_back(q);
				std::cout << "Number erased.\n";
			}
			b.erase(q);
		}

		std::cout << "Do erase again? y/n: ";
		std::cin >> cont;
	}
	if(data_erased.size() > 0)
	{
		std::cout << "\nDate erased:\n";
		print_vec(data_erased);
		std::cout << "\n\nTree after erasure:\n";
	}
	else
		std::cout << "\nData in tree:\n";
	b.print();
	std::cout << '\n';

	return 0;
}