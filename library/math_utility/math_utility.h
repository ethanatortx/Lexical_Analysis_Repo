#ifndef MATH_UTILITY_H
#define MATH_UTILITY_H

#include <string>
#include <cstring>
#include <cstdlib>
#include <stdlib.h>
#include <vector>
#include <ios>
#include <sstream>
#include <typeinfo>
#include "hash\hash.h"

namespace math_utility
{
	bool is_prime(unsigned long long num)
	{
		if (num < 2) return 0;

		if (num > 2 && (num % 2) == 0) return 0;

		for(unsigned long long i = 2; i < num; i++ )
		{
			if ( (num % i) == 0)
			{
				return 0;
			}
		}

		return 1;
	}

	std::vector<unsigned long long> get_primes(unsigned long long max)
	{
		std::vector<unsigned long long> primes;
		char *sieve;
		sieve = new char[max/8+1];
		// Fill sieve with 1  
		std::memset(sieve, 0xFF, (max/8+1) * sizeof(char));
		for(unsigned long long x = 2; x <= max; x++)
			if(sieve[x/8] & (0x01 << (x % 8))){
				primes.push_back(x);
				// Is prime. Mark multiplicates.
				for(unsigned long long j = 2*x; j <= max; j += x)
					sieve[j/8] &= ~(0x01 << (j % 8));
			}
		delete[] sieve;
		return primes;
	}

	unsigned long long get_next_prime(unsigned long long start = 0)
	{
		unsigned long long prime = start+1;

		while(!is_prime(prime))
		{
			prime++;
		}

		return prime;
	}
}

#endif