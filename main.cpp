#include <iostream>
#include "mem_block.h"

typedef unsigned long ulong;
typedef unsigned short ushort;

struct HexCharStruct
{
	unsigned char c;
	HexCharStruct(char _c) : c(_c) { }
};

struct HexUshortStruct
{
	ushort s;
	HexUshortStruct(ushort s) : s(s) { }
};

inline std::ostream& operator<<(std::ostream& o, const HexCharStruct& hs)
{
	return (o << std::hex << (int) hs.c);
}

inline std::ostream& operator<<(std::ostream& o, const HexUshortStruct& hs)
{
	return (o << std::hex << (int) hs.s);
}

inline HexCharStruct hex(char _c)
{
	return HexCharStruct(_c);
}

inline HexUshortStruct hex(ushort s)
{
	return HexUshortStruct(s);
}

int main()
{
	MemBlock memory(8);
	memory.WriteByte(0, 0xab);
	memory.WriteShort(1, 0x1234);

	char val = memory.ReadByte(0);

	std::cout << hex(val) << std::endl;
	//std::cout << hex(memory.ReadShort(1)) << std::endl;
}