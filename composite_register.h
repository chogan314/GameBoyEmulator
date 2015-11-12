#ifndef COMPOSITE_REGISTER_H
#define COMPOSITE_REGISTER_H

typedef unsigned char uchar;
typedef unsigned short ushort;

class CompositeRegister
{
public:
	CompositeRegister(uchar &msb, uchar &lsb);

	ushort &GetMemory();

	void Finalize();
private:
	uchar &msb;		// most significant byte
	uchar &lsb;		// least significant byte
	ushort memory;
};

#endif