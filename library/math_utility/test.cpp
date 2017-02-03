#include <iostream>
#include <string>
#include "math_utility.h"
#include "hash\hash.h"

int main()
{
	hex keyhash(hash::algorithm::hash<int>(123905));
	std::cout << keyhash << std::endl;
	std::cout << math_utility::is_prime(convert(keyhash)) << std::endl;

	return 0;
}