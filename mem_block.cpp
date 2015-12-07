#include "mem_block.h"

MemBlock::MemBlock(ulong size) :
	size(size),
	memory(new uchar[size])
{
	memset(memory, 0, size);
}

MemBlock::~MemBlock()
{
	delete[] memory;
}

void MemBlock::CopyFromFile(const std::string &source)
{
	FILE *in;
	in = fopen(source.c_str(), "rb");
	fread(memory, 1, size, in);
	fclose(in);
}

void MemBlock::WriteByte(ulong address, uchar data)
{
	memory[address] = data;
}

uchar MemBlock::ReadByte(ulong address)
{
	return memory[address];
}

bool MemBlock::TestBit(ulong address, uchar offset)
{
	return (memory[address] & (1 << offset)) > 1;
}