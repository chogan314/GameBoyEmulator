#include "composite_register.h"

ushort &CompositeRegister::GetMemory()
{
	return memory;
}

void CReg16Bit::Finalize()
{
	reg = memory;
}

void CReg8Bit8Bit::Finalize()
{
	lsb = memory & 0xff;
	msb = (memory >> 8) & 0xff;
}