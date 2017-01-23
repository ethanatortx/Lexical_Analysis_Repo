
#include "..\linked_list.h"

int main() {

	linked_list<int>* list = new linked_list<int>();
	list->push_back(10);
	list->push_back(20);
	list->push_back(15);

	list->print();
	
	std::cout<< std::endl;

	list->emplace_after(5, list->end());
	list->emplace_after(95, 2);

	list->print(); 

	std::cout<< std::endl;

	list->erase_after(list->end());

	list->print();

	return 0;
}