/*****Please include following header files*****/
// from: https://www.programmingalgorithms.com/algorithm/huffman-compress?lang=C%2B%2B
// cstdint
/***********************************************/

#ifndef _BIT_OPERATIONS_
#define _BIT_OPERATIONS_

#include <iostream>
#include <stdio.h>
#include <string.h>

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

typedef struct {
	uint8_t* BytePointer;
	uint32_t BitPosition;
} BitStream;


static void initBitStream(BitStream* stream, uint8_t* buffer)
{
	stream->BytePointer = buffer;
	stream->BitPosition = 0;
}

static void writeBits(BitStream* stream, uint32_t x, uint32_t bits)
{
	uint8_t* buffer = stream->BytePointer;
	uint32_t bit = stream->BitPosition;
	uint32_t mask = 1 << (bits - 1);

	for (uint32_t count = 0; count < bits; ++count)
	{
		*buffer = (*buffer & (0xff ^ (1 << (7 - bit)))) + ((x & mask ? 1 : 0) << (7 - bit));
		x <<= 1;
		bit = (bit + 1) & 7;

		if (!bit)
		{
			++buffer;
		}
	}

	stream->BytePointer = buffer;
	stream->BitPosition = bit;
}


static uint32_t readBit(BitStream* stream)
{
	uint8_t* buffer = stream->BytePointer;
	uint32_t bit = stream->BitPosition;
	uint32_t x = (*buffer & (1 << (7 - bit))) ? 1 : 0;
	bit = (bit + 1) & 7;

	if (!bit)
	{
		++buffer;
	}

	stream->BitPosition = bit;
	stream->BytePointer = buffer;

	return x;
}



static uint32_t read8Bits(BitStream* stream)
{
	uint8_t* buffer = stream->BytePointer;
	uint32_t bit = stream->BitPosition;
	uint32_t x = (*buffer << bit) | (buffer[1] >> (8 - bit));
	++buffer;
	stream->BytePointer = buffer;

	return x;
}




#endif //_BIT_OPERATIONS_


