#ifndef INSTRUCTION_ARGS_H
#define INSTRUCTION_ARGS_H

#include "composite_register.h"

typedef unsigned short ushort;
typedef unsigned char uchar;

// reg8
struct Reg8Param
{
	uchar &reg;

	Reg8Param(uchar &reg) :
		reg(reg)
	{ }
};

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

// reg16
struct Reg16Param
{
	CompositeRegister *reg;

	Reg16Param(CompositeRegister *reg) :
		reg(reg)
	{ }

	/*~Reg16Param()
	{
		delete reg;
	}*/
};

// reg16, reg16
struct Reg16Reg16Param
{
	CompositeRegister *lhs;
	CompositeRegister *rhs;

	Reg16Reg16Param(CompositeRegister *lhs, CompositeRegister *rhs) :
		lhs(lhs),
		rhs(rhs)
	{ }

	/*~Reg16Reg16Param()
	{
		delete lhs;
		delete rhs;
	}*/
};

// reg16, reg8
struct Reg16Reg8Param
{
	CompositeRegister *reg16;
	uchar &reg8;

	Reg16Reg8Param(CompositeRegister *reg16, uchar &reg8) :
		reg16(reg16),
		reg8(reg8)
	{ }

	/*~Reg16Reg8Param()
	{
		delete reg16;
	}*/
};

// imm8
struct Imm8Param
{
	uchar imm8;

	Imm8Param(uchar imm8) :
		imm8(imm8)
	{ }
};

// imm8, reg8
struct Imm8Reg8Param
{
	uchar imm8;
	uchar &reg8;

	Imm8Reg8Param(uchar imm8, uchar &reg8) :
		imm8(imm8),
		reg8(reg8)
	{ }
};

// imm8, reg16
struct Imm8Reg16Param
{
	uchar imm8;
	CompositeRegister *reg16;

	Imm8Reg16Param(uchar imm8, CompositeRegister *reg16) :
		imm8(imm8),
		reg16(reg16)
	{ }

	/*~Imm8Reg16Param()
	{
		delete reg16;
	}*/
};

// flagOffset, expectedValue
struct ConditionalParam
{
	uchar flagOffset;
	bool expectedValue;

	ConditionalParam(uchar flagOffset, bool expectedValue) :
		flagOffset(flagOffset),
		expectedValue(expectedValue)
	{ }
};

#endif