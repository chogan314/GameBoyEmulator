#ifndef MEM_BLOCK_H
#define MEM_BLOCK_H

#include <string>

typedef unsigned long ulong;
typedef unsigned short ushort;
typedef unsigned char uchar;

class MemBlock
{
public:
	MemBlock(ulong size);
	~MemBlock();

	void CopyFromFile(const std::string &source);

	void WriteByte(ulong address, uchar data);

	uchar ReadByte(ulong address);

	bool TestBit(ulong address, uchar offset);
private:
	ulong size;		// max size = 2^34 bytes
	uchar *memory;
};

#endif