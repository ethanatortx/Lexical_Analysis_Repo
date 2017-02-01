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

	hash::hash_table<std::string, int, hash::algorithm::SHA256> tbl;
	hash::hash_table<std::string, int, hash::algorithm::SHA256> tbl_2;
	
	tbl.add("ten", 10);


	return 0;
}