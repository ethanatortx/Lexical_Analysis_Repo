#include "BitOperations.h"
#include <vector>
#ifndef HUFFMANENCODE_H
#define HUFFMANENCODE_H
#define MAX_TREE_NODES 511


typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

class HuffmanEncode
{
	
public:
	typedef struct {
		int Symbol;
		uint32_t Count;
		std::string Code;
		uint32_t Bits;
	} Symbol;

	typedef struct huffNode {
	    struct huffNode* ChildA;
		struct huffNode* ChildB;
		int Count;
		int Symbol;
		bool IsBottom;
	} huffNode;

	HuffmanEncode();
	~HuffmanEncode();

	void printIt(Symbol* sym);
	void histogram(std::string input, Symbol* sym, uint32_t size);
	void makeTree(Symbol* sym, BitStream* stream);
	void storeTree(huffNode* node, Symbol* sym, BitStream* stream, uint32_t code, uint32_t bits);
	int Compress(std::string input, uint8_t* output, uint32_t inputSize);
	void traverse_root(Symbol* sym, huffNode* r);
	void handle_tree(huffNode* p, int indent, std::string s, Symbol* sym);
	void traverse_main(Symbol* sym, huffNode* n, std::vector<bool> b, bool a);
	
	struct LessThanByHuffNode
	{
	  bool operator()(huffNode* lhs, huffNode* rhs)
	  {
	    return lhs->Count > rhs->Count;
	  }

	};


};
/*
inline bool operator<(const HuffmanEncode::huffNode& lhs, const HuffmanEncode::huffNode& rhs)
{
	return lhs.Count > rhs.Count;
}
*/
#endif // HUFFMANENCODE_H
