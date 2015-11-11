#include "mem_block.h"

MemBlock::MemBlock(ulong size) :
	size(size),
	memory(new uchar[size])
{

}

MemBlock::~MemBlock()
{
	delete[] memory;
}

void MemBlock::WriteByte(ulong address, uchar data)
{
	memory[address] = data;
}


void MemBlock::WriteShort(ulong address, ushort data)
{
	memory[address] = data & 0xff;
	memory[address + 1] = (data >> 8) & 0xff;
}

uchar MemBlock::ReadByte(ulong address)
{
	return memory[address];
}

ushort MemBlock::ReadShort(ulong address)
{
	ushort data = 0x0000;
	data = memory[address + 1];
	data = data << 8;
	data = data | memory[address];
	return data;
}