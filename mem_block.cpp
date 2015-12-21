#include "mem_block.h"
#include <algorithm>

MemBlock::MemBlock(uint size) :
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

void MemBlock::WriteByte(uint address, uchar data)
{
	memory[address] = data;
}

uchar MemBlock::ReadByte(uint address)
{
	return memory[address];
}

uchar *MemBlock::GetMemory()
{
	return memory;
}

bool MemBlock::TestBit(uint address, uchar offset)
{
	return (memory[address] & (1 << offset)) > 1;
}