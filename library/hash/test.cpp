#include <iostream>
#include <string>
#include <functional>
#include "hash.h"

int main(int argc, char *argv[])
{
	std::string input = "kdfl;ajvcnxzl;jdnafjdhiuowfn u9489fuicxv ";
	std::hash<std::string> h;
	std::size_t hash = h(input);
	std::cout << hash;

	return 0;
}