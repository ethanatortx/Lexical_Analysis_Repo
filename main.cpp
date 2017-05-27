/*****Please include following header files*****/
// from: https://www.programmingalgorithms.com/algorithm/huffman-compress?lang=C%2B%2B
// cstdint
/***********************************************/

#include <iostream>
#include <stdio.h>
#include <string.h>
#include "BitOperations.h"
#include "HuffmanEncode.h"

using namespace std;

#define MAX_TREE_NODES 511

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

int main()
{
	
	HuffmanEncode* he = new HuffmanEncode();
	
	const char* str = "The quick brown fox jumped over the lazy dog";
	uint8_t* originalData = (uint8_t*)str;
	int originalDataSize = strlen(str);
	uint8_t* compressedData = new uint8_t[originalDataSize * (101 / 100) + 320];

	int compressedDataSize = he->Compress(str, compressedData, originalDataSize);
	cout << "Compressed size: " << compressedDataSize << endl;
}

