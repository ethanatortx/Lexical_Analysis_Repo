#include <iostream>
#include "hash.h"

using std::string;
using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
	string input256 = "grape";
	string output256 = hash::algorithm::hash<hash::algorithm::SHA256>(input256);

	cout << "sha256('"<< input256 << "'):" << output256 << endl;

	string input512 = "grape";
	string output512 = hash::algorithm::hash<hash::algorithm::SHA512>(input512);
 
	cout << "sha512('"<< input512 << "'):" << output512 << endl;

	hash::hash_table<int, hash::algorithm::SHA256>* tbl = new hash::hash_table<int, hash::algorithm::SHA256>();
	

	return 0;
}