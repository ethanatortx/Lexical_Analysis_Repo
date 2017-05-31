#include "HuffmanEncode.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <queue>
#include <vector>
#include <iomanip>
using namespace std;

HuffmanEncode::HuffmanEncode()
{
}

HuffmanEncode::~HuffmanEncode()
{
}

/*****Please include following header files*****/
// from: https://www.programmingalgorithms.com/algorithm/huffman-compress?lang=C%2B%2B
// cstdint
/***********************************************/


// Create a histogram of the symbols occuring in the file

void HuffmanEncode::histogram(std::string* input, 
	int* freq, 
	Symbol* sym)
{
	int i;

	for (i = 0; i < sizeof(input)/sizeof(input[0]); ++i)
	{
		sym[i].Symbol = input[i];
		sym[i].Number = i;
		sym[i].Count = freq[i];
		sym[i].Code = "";
		sym[i].Bits = 0;
	}

	printIt(sym);
}

void HuffmanEncode::printIt(Symbol* sym){
	for(int i = 0; i < 256; ++i){
		if(sym[i].Count > 0){
			std::cout << "Index: " << i << "\n";
			std::cout << "Symbol: " << sym[i].Symbol << "\n";
			std::cout << "Count: " << sym[i].Count << "\n\n";
		}
	}
}

// MakeTree: Create the Huffman code tree
// Input:
//		Symbol* sym: pointer to the histogram of characters
//		BitStream* stream: pointer for the resulting compressed stream.
// Output:
//		BitStream* stream: (Unused in lab) pointer to the resulting compressed stream.
//		stdout: Table dump of huffman codes for this text.
//		
void HuffmanEncode::makeTree(Symbol* sym, BitStream* stream)
{
	int arr[255];
	int c = 0;
	std::priority_queue<huffNode*, std::vector<huffNode*>, LessThanByHuffNode> pqueue;

	for (int i = 0; i < 256; ++i)
	{
		huffNode* node = new huffNode;
		node->Count = sym[i].Count;
		node->Symbol = sym[i].Symbol;
		node->Number = sym[i].Number;
		node->IsBottom = true;
		if(sym[i].Count > 0){
			pqueue.push(node);
		}
		//End of if statement
	}
	std::cout<<"\n";
	//Our Priority queue is ready to work on.

	while(pqueue.size() > 1){
		huffNode* n;
		huffNode* m;
		huffNode* l = new huffNode;
		n = pqueue.top();
		pqueue.pop();
		m = pqueue.top();
		pqueue.pop();
		l->ChildA = n;
		l->ChildB = m;
		l->Count = n->Count + m->Count;
		l->IsBottom = false;
		pqueue.push(l);
	}
	huffNode* root = pqueue.top();
	//Assign codes to each node
	std::vector<Symbol*>* v = new std::vector<Symbol*>();
	handle_tree(root, 0, "", sym);
	
//	traverse_root(sym, root);

}
void HuffmanEncode::handle_tree(huffNode* p, 
	int indent, 
	std::string s, 
	Symbol* sym)
{
    if(p != NULL) {
        if (indent) {
            std::cout << std::setw(indent) << ' ';
        }
        if(p->IsBottom){
	        std::cout << " | " 
	        << p->Count << " | " 
	        << "\n";
	        Symbol new_symbol;
	        new_symbol.Symbol = p->Symbol;
			new_symbol.Count = p->Count;
			new_symbol.Code = s;
			new_symbol.Bits = indent;
			sym[new_symbol.Number] = new_symbol;
	        return;
        }
        cout<< p->Count << "\n";
        if(p->ChildA && !p->IsBottom){
        	handle_tree(p->ChildA, indent+1, s+"0", sym);
        }
        if(p->ChildB && !p->IsBottom) 
        {
        	handle_tree(p->ChildB, indent+1, s+"1", sym);
        }
    }
}

void HuffmanEncode::traverse_root(Symbol* sym, huffNode* r){
	std::vector<bool> b;
	traverse_main(sym, r->ChildA, b, false);
	traverse_main(sym, r->ChildB, b, true);
}

void HuffmanEncode::traverse_main(Symbol* sym, 
	huffNode* n, 
	std::vector<bool> b, 
	bool a)
{

	b.push_back(a);
    if(n != NULL) {
        if(n->IsBottom){
			sym[n->Number].Bits = b.size();
			std::cout << "\n";
			for(int i = 0; i < b.size(); i++){
				if(b.at(i)){
					sym[n->Number].Code += "1";
				} else {
					sym[n->Number].Code += "0";
				}
//				std::cout << sym[n->Symbol].Code.size() << " " << n->Symbol << "\n";
			}
			std::cout << sym[n->Number].Code << "\n\n";
	        return;
        }
        cout<< n->Count << "\n ";
        if(n->ChildA && !n->IsBottom){
        	traverse_main(sym, n->ChildA, b, 0);
        }
        if(n->ChildB && !n->IsBottom) 
        {
        	traverse_main(sym, n->ChildA, b, 1);
        }
    }
}

// Compress: Function to convert plain text stream to a compressed huffman coded message
//	Input:
//		uint8_t* input: Pointer to the input string of characters
//		uint8_t* output: Pointer for an output buffer with compressed stream
//		uint32_t inputSize: length of input string to encode
//	Output:
//		uint8_t* output: Pointer to an output buffer for compressed stream
//		return int: Byte count of compressed message.



int HuffmanEncode::Compress(std::string* input, 
	int* freq)
{
	Symbol sym[256], temp;
	BitStream stream;
	uint32_t i, totalBytes, symbol;

	histogram(input, freq, sym);
	makeTree(sym, &stream);
	
	// Diagnostic print
	for (i = 0; i < 255; ++i)
	{
		if (sym[i].Bits > 0)
		{
			std::cout << 
			"Symbol: " << sym[i].Symbol << 
			", Code: " << sym[i].Code << 
			", Bits: " << sym[i].Bits << 
			", Num: " << i << std::endl;
		}
	}
	std::cout << "\n\n";
	// End: Diagnostic print
}
