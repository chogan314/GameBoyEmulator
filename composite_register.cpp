#include "composite_register.h"

ushort &CompositeRegister::GetMemory()
{
	return memory;
}

CReg16Bit::CReg16Bit(ushort &reg) :
	reg(reg)
{ }

CReg8Bit8Bit::CReg8Bit8Bit(uchar &msb, uchar &lsb) :
	msb(msb),
	lsb(lsb)
{ }

void CReg16Bit::Finalize()
{
	reg = memory;
}

void CReg8Bit8Bit::Finalize()
{
	lsb = memory & 0xff;
	msb = (memory >> 8) & 0xff;
}