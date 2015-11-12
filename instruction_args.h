#ifndef INSTRUCTION_ARGS_H
#define INSTRUCTION_ARGS_H

#include "composite_register.h"

typedef unsigned short ushort;
typedef unsigned char uchar;

// reg8, reg8
struct Reg8Reg8Param
{
	uchar &lhs;
	uchar &rhs;

	Reg8Reg8Param(uchar &lhs, uchar &rhs) :
		lhs(lhs),
		rhs(rhs)
	{ }
};

// composite reg16
struct CReg16Param
{
	CompositeRegister reg;

	CReg16Param(uchar &msb, uchar &lsb) :
		reg(msb, lsb)
	{ }
};

// comp reg16, reg8
struct CReg16Reg8Param
{
	CompositeRegister cReg16;
	uchar &reg8;

	CReg16Reg8Param(uchar &msb, uchar &lsb, uchar &reg8) :
		cReg16(msb, lsb),
		reg8(reg8)
	{ }
};

// reg8
struct Reg8Param
{
	uchar &reg;

	Reg8Param(uchar &reg) :
		reg(reg)
	{ }
};

// reg8, imm8

// imm16, reg16

// comp reg16, comp reg16
struct CReg16CReg16Param
{
	CompositeRegister lhs;
	CompositeRegister rhs;

	CReg16CReg16Param(uchar &lhsMsb, uchar &lhsLsb, uchar &rhsMsb, uchar &rhsLsb) :
		lhs(lhsMsb, lhsLsb),
		rhs(rhsMsb, rhsLsb)
	{ }
};

// reg8, comp reg16

// reg16
struct Reg16Param
{
	ushort &reg;
	Reg16Param(ushort &reg) :
		reg(reg)
	{ }
};

// imm16

#endif