#ifndef MEM_BLOCK_H
#define MEM_BLOCK_H

#include <string>

typedef unsigned long ulong;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;

class MemBlock
{
public:
	MemBlock(uint size);
	~MemBlock();

	void CopyFromFile(const std::string &source);

	void WriteByte(uint address, uchar data);

	uchar ReadByte(uint address);

	uchar *GetMemory();

	bool TestBit(uint address, uchar offset);
private:
	uint size;
	uchar *memory;
};

#endif