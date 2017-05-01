#include <iostream>
#include "graph.h"

int main()
{
	graph G;

	G.insert("George");
	G.insert("Ethan");
	G.insert("Phillis");

	G.add_edge("George", "Ethan", 3);
	G.add_edge("Ethan", "Phillis", 5);
	G.add_edge("Phillis", "George", 10);
	G.add_edge("George", "Phillis", 10);

	std::cout << (G.to_string());

	return 0;
}