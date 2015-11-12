#ifndef MEM_BLOCK_H
#define MEM_BLOCK_H

typedef unsigned long ulong;
typedef unsigned short ushort;
typedef unsigned char uchar;

// Represents a block of memory
// Little-endian
class MemBlock
{
public:
	MemBlock(ulong size);
	~MemBlock();

	void WriteByte(ulong address, uchar data);

	// Takes a short (2 bytes, big-endian)
	void WriteShort(ulong address, ushort data);
	uchar ReadByte(ulong address);

	// Returns a short (2 bytes, big-endian)
	ushort ReadShort(ulong address);
private:
	ulong size;		// max size = 2^34 bytes
	uchar *memory;
};

#endif