#ifndef MATH_UTILITY_H
#define MATH_UTILITY_H

#include <string>
#include <cstring>
#include <vector>
#include <ios>
#include <sstream>

namespace math_utility
{
	namespace prime
	{

		int is_prime(unsigned long num)
		{
			if (num < 2) return 0;

			if (num > 2 && (num % 2) == 0) return 0;

			for(int i = 2; i < num; i++ )
			{
				if ( (num % i) == 0)
				{
					return 0;
				}
			}

			return 1;
		}

		std::vector<unsigned long> get_primes(unsigned long max)
		{
			std::vector<unsigned long> primes;
		    char *sieve;
		    sieve = new char[max/8+1];
		    // Fill sieve with 1  
		    std::memset(sieve, 0xFF, (max/8+1) * sizeof(char));
		    for(unsigned long x = 2; x <= max; x++)
		        if(sieve[x/8] & (0x01 << (x % 8))){
		            primes.push_back(x);
		            // Is prime. Mark multiplicates.
		            for(unsigned long j = 2*x; j <= max; j += x)
		                sieve[j/8] &= ~(0x01 << (j % 8));
		        }
		    delete[] sieve;
		    return primes;
		}

		unsigned long get_next_prime(unsigned long start = 0)
		{
			unsigned long prime = start+1;

			while(!is_prime(prime))
			{
				prime++;
			}

			return prime;
		}
	}

	class hex
	{

	public:
		inline std::string str() const { return hex_str; }

		hex(): hex_str("") {}
		hex(const std::string& s): hex_str(s) {}
		hex(const hex& other): hex_str(other.str()) {}

		std::ostream& operator<<(const hex& other) 
		{
		}

	private:
		std::string hex_str;
	};

	namespace hex_util
	{
		inline hex get_hex(unsigned long long input)
		{
			std::stringstream h;
			h.str("");
			h << std::hex << input;
			return math_utility::hex(h.str());
		}

		inline unsigned long long get_dec(const std::string& hex_num){
			std::stringstream h;
			unsigned long long val;
			h << std::dec << hex_num;
			h >> val;
			return val;
		}
	}


}

#endif