/*****Please include following header files*****/
// from: https://www.programmingalgorithms.com/algorithm/huffman-compress?lang=C%2B%2B
// cstdint
/***********************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <stdio.h>
#include <string.h>
#include "BitOperations.h"
#include "HuffmanEncode.h"

#define MAX_TREE_NODES 511

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

int main()
{
	
	std::ifstream infile;
	std::string settings = "WordFrequency.txt";
	std::string open;
	infile.open(settings);
	if(infile.is_open())
	{
		std::getline(infile, open, '\n');
		int len = std::stoi( open );
		std::string* arr = new std::string[len];
		int* frequencies = new int[len];
		for(int i=0; i<len; i++){
			std::getline(infile, open, ' ');
			arr[i] = open;
			std::getline(infile, open, ' ');
			frequencies[i] = std::stoi(open);
		}
		HuffmanEncode* he = new HuffmanEncode();
		int compressedDataSize = he->Compress(arr, frequencies);
	}
	else
		std::cout << "Error Opening Settings File";

}

