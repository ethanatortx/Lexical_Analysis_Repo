#include <iostream>
#include "math_utility.h"
// #include "hash\hash.h"

int main()
{
	math_utility::hex keyhash("grape");
	std::cout << keyhash;

	return 0;
}