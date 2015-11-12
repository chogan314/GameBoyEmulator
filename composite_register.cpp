#include "composite_register.h"

CompositeRegister::CompositeRegister(uchar &msb, uchar &lsb) : 
	msb(msb),
	lsb(lsb)
{
	memory = msb;
	memory = memory << 8;
	memory = memory | lsb;
}

ushort &CompositeRegister::GetMemory()
{
	return memory;
}

void CompositeRegister::Finalize()
{
	lsb = memory & 0xff;
	msb = (memory >> 8) & 0xff;
}