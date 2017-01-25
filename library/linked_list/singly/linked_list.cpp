
#include "..\linked_list.h"

int main() {

	linked_list<int> list;

	std::cout<< "\nPushing numbers to list 1";
	list.push_back(20);
	list.push_back(5);

	std::cout<< "\nList 1: " << std::endl;
	list.print();

	std::cout<< "\nReverse list 1";
	list.reverse();
	std::cout<< "\nAppend number to list 1";
	list.append(50);

	std::cout<< "\nList 1: " << std::endl;
	list.print();

	linked_list<int> list_2;

	std::cout<< "\nPushing numbers to list 2";
	list_2.push_back(500);
	list_2.push_back(34);
	std::cout<< "\nEmplacing number at fourth term in list 2";
	list_2.emplace(20, 1);

	list_2.print();

	std::cout<< "\nAppend list two to list one using operator+=";
	list += list_2;

	std::cout<< "\nList 1: " << std::endl;
	list.print();

	std::cout<< "\nRotate to fourth term";
	list.rotate(3);

	std::cout<< "\nList 1: " << std::endl;
	list.print();

	std::cout<< "\nPush numbers to beginning and end of list 1";
	list.append(20);
	list.push_back(30);

	std::cout<< "\nList 1: " << std::endl;
	list.print();

	std::cout<< "\nList 2: " << std::endl;
	list_2.print();

	std::cout << "\nSwap list contents" << std::endl;

	list.swap(list_2);

	std::cout<< "\nList 1: " << std::endl;
	list.print();

	std::cout<< "\nList 2: " << std::endl;
	list_2.print();
}