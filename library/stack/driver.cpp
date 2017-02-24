#include <iostream>
#include "stack.h"
#include "queue.h"

int main()
{
	std::cout << "Initializing queue..." << std::endl;

	queue<int> q;

	std::cout << "Pushing to queue..." << std::endl;

	q.push(10);
	q.push(25);
	q.push(5);
	q.push(17);

	std::cout << "Queue: " << q << std::endl;

	std::cout << "Cloning queue..." << std::endl;

	queue<int> new_q(q);

	std::cout << "Pushing number to new queue: ";

	std::cin >> new_q;

	std::cout << "Queue one: " << q << std::endl;
	std::cout << "Queue two: " << new_q << std::endl;

	std::cout << "Swapping queues..." << std::endl;

	swap(q, new_q);

	std::cout << "Queue one (swapped): " << q << std::endl;
	std::cout << "Queue two (swapped): " << new_q << std::endl;

	std::cout << "Clearing queues..." << std::endl;
	q.clear();
	new_q.clear();

	std::cout << std::endl << "Initializing stack..." << std::endl;

	stack<double> s;

	std::cout << "Pushing to stack..." << std::endl;

	s.push(.909);
	s.push(.833);
	s.push(.374);
	s.push(.843);

	std::cout << "Stack: " << s << std::endl;

	std::cout << "Cloning stack..." << std::endl;

	stack<double> new_s(s);

	std::cout << "Pushing number to new stack: ";

	std::cin >> new_s;

	std::cout << "Stack one: " << s << std::endl;
	std::cout << "Stack two: " << new_s << std::endl;

	std::cout << "Swapping stacks..." << std::endl;

	swap(s, new_s);

	std::cout << "Stack one (swapped): " << s << std::endl;
	std::cout << "Stack two (swapped): " << new_s << std::endl;

	std::cout << "Clearing stacks..." << std::endl;
	s.clear();
	new_s.clear();
}