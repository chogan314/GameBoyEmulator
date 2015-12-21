#include "composite_register.h"

CReg16Bit::CReg16Bit(ushort &reg) :
	reg(reg)
{ }

ushort &CReg16Bit::GetMemory()
{
	memory = reg;
	return memory;
}

void CReg16Bit::Finalize()
{
	reg = memory;
}

CReg8Bit8Bit::CReg8Bit8Bit(uchar &msb, uchar &lsb) :
	msb(msb),
	lsb(lsb)
{ }

ushort &CReg8Bit8Bit::GetMemory()
{
	memory = msb;
	memory <<= 8;
	memory |= lsb;
	return memory;
}

void CReg8Bit8Bit::Finalize()
{
	lsb = memory & 0xff;
	msb = (memory >> 8) & 0xff;
}