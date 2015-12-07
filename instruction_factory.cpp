#include "instruction_factory.h"
#include "cpu.h"
#include <iostream>
#include "hex_printing.h"

// INSTRUCTION onCall FUNCTIONS:

/*******************************
******** Loads & Moves *********
********************************/
// LD reg8, imm8
void LdReg8Imm8(ParamInstruction<Reg8Param> &instruction)
{
	instruction.params.reg = instruction.processor->ReadImm8Arg();
	instruction.SetImmArg(instruction.processor->ReadImm8Arg());
}

// LD reg8, reg8
void LdReg8Reg8(ParamInstruction<Reg8Reg8Param> &instruction)
{
	instruction.params.lhs = instruction.params.rhs;
}

// LD reg8, (reg8)
void LdReg8AddrReg8(ParamInstruction<Reg8Reg8Param> &instruction)
{	
	instruction.params.lhs = instruction.processor->ReadByte(0xff00U + instruction.params.rhs);
}

// LD reg8, (imm16)
void LdReg8AddrImm16(ParamInstruction<Reg8Param> &instruction)
{
	instruction.params.reg = instruction.processor->ReadByte(instruction.processor->ReadImm16Arg());
	instruction.SetImmArg(instruction.processor->ReadImm16Arg());
}

// LD reg8, (reg16)
void LdReg8AddrReg16(ParamInstruction<Reg16Reg8Param> &instruction)
{
	instruction.params.reg8 = instruction.processor->ReadByte(instruction.params.reg16->GetMemory());
}

// LD reg8, (reg16+)
void LdReg8AddrIncReg16(ParamInstruction<Reg16Reg8Param> &instruction)
{
	instruction.params.reg8 = instruction.processor->ReadByte(instruction.params.reg16->GetMemory());

	instruction.params.reg16->GetMemory()++;
	instruction.params.reg16->Finalize();
}

// LD reg8, (reg16-)
void LdReg8AddrDecReg16(ParamInstruction<Reg16Reg8Param> &instruction)
{
	instruction.params.reg8 = instruction.processor->ReadByte(instruction.params.reg16->GetMemory());

	instruction.params.reg16->GetMemory()--;
	instruction.params.reg16->Finalize();
}

// LD (reg8), reg8
void LdAddrReg8Reg8(ParamInstruction<Reg8Reg8Param> &instruction)
{
	instruction.processor->WriteByte(0xff00U + instruction.params.lhs, instruction.params.rhs);		// may not need 0xff00 + ...
}

// LD (reg16), imm8
void LdAddrReg16Imm8(ParamInstruction<Reg16Param> &instruction)
{
	instruction.processor->WriteByte(instruction.params.reg->GetMemory(),
		instruction.processor->ReadImm8Arg());
	instruction.SetImmArg(instruction.processor->ReadImm8Arg());
}

// LD (reg16), reg8
void LdAddrReg16Reg8(ParamInstruction<Reg16Reg8Param> &instruction)
{
	instruction.processor->WriteByte(instruction.params.reg16->GetMemory(),
		instruction.params.reg8);
}

// LD (reg16+), reg8
void LdAddrIncReg16Reg8(ParamInstruction<Reg16Reg8Param> &instruction)
{
	instruction.processor->WriteByte(instruction.params.reg16->GetMemory(),
		instruction.params.reg8);

	instruction.params.reg16->GetMemory()++;
	instruction.params.reg16->Finalize();
}

// LD (reg16-), reg8
void LdAddrDecReg16Reg8(ParamInstruction<Reg16Reg8Param> &instruction)
{
	instruction.processor->WriteByte(instruction.params.reg16->GetMemory(),
		instruction.params.reg8);

	instruction.params.reg16->GetMemory()--;
	instruction.params.reg16->Finalize();
}

// LD (imm16), reg8
void LdAddrImm16Reg8(ParamInstruction<Reg8Param> &instruction)
{
	instruction.processor->WriteByte(instruction.processor->ReadImm16Arg(), instruction.params.reg);
	instruction.SetImmArg(instruction.processor->ReadImm16Arg());
}

// LD reg16, imm16
void LdReg16Imm16(ParamInstruction<Reg16Param> &instruction)
{
	instruction.params.reg->GetMemory() = instruction.processor->ReadImm16Arg();

	instruction.params.reg->Finalize();

	instruction.SetImmArg(instruction.processor->ReadImm16Arg());
}

// LD reg16, reg16
void LdReg16Reg16(ParamInstruction<Reg16Reg16Param> &instruction)
{
	instruction.params.lhs->GetMemory() = instruction.params.rhs->GetMemory();
	instruction.params.lhs->Finalize();
}

// LD reg16, reg16 + S-imm8
void LdReg16Reg16AddImm8S(ParamInstruction<Reg16Reg16Param> &instruction)
{
	int rhsReg = instruction.params.rhs->GetMemory();
	int imm8S = (signed char) instruction.processor->ReadImm8Arg();

	instruction.processor->SetZeroFlag(0);
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetHalfCarryFlag((rhsReg & 0x0f) + (imm8S & 0x0f) > 0x0f);
	instruction.processor->SetCarryFlag(rhsReg + imm8S > 0xffff);

	instruction.params.lhs->GetMemory() = ((rhsReg + imm8S) & 0xffff);
	instruction.params.lhs->Finalize();

	instruction.SetImmArg(imm8S);
}

// LD (imm16), reg16
void LdAddrImm16Reg16(ParamInstruction<Reg16Param> &instruction)
{
	instruction.processor->WriteShort(instruction.processor->ReadImm16Arg(),
		instruction.params.reg->GetMemory());

	instruction.SetImmArg(instruction.processor->ReadImm16Arg());
}


// LDH (imm8), reg8
void LdHAddrImm8Reg8(ParamInstruction<Reg8Param> &instruction)
{
	instruction.processor->WriteByte(0xff00 | instruction.processor->ReadImm8Arg(), instruction.params.reg);

	instruction.SetImmArg(0xff00 | instruction.processor->ReadImm8Arg());
}

// LDH reg8, (imm8)
void LdHReg8AddrImm8(ParamInstruction<Reg8Param> &instruction)
{
	instruction.params.reg = instruction.processor->ReadByte(0xff00 | instruction.processor->ReadImm8Arg());

	instruction.SetImmArg(0xff00 | instruction.processor->ReadImm8Arg());
}


// POP reg16
void PopReg16(ParamInstruction<Reg16Param> &instruction)
{
	instruction.params.reg->GetMemory() = instruction.processor->PopShort();
	instruction.params.reg->Finalize();
}

// PUSH reg16
void PushReg16(ParamInstruction<Reg16Param> &instruction)
{
	instruction.processor->PushShort(instruction.params.reg->GetMemory());
}

/*******************************
********* Math & Logic *********
********************************/
// INC reg8
void IncReg8(ParamInstruction<Reg8Param> &instruction)
{
	uchar &reg = instruction.params.reg;
	CPU *processor = instruction.processor;

	processor->SetZeroFlag(reg + 0x01U == 0x00U);
	processor->SetSubtractFlag(0);
	processor->SetHalfCarryFlag((reg & 0x0fU) == 0x0fU);

	reg++;
}

// INC (reg16) ; 8-bit
void IncAddrReg16(ParamInstruction<Reg16Param> &instruction)
{
	uchar memVal = instruction.processor->ReadByte(instruction.params.reg->GetMemory());
	CPU *processor = instruction.processor;

	processor->SetZeroFlag(memVal + 0x01U == 0x00U);
	processor->SetSubtractFlag(0);
	processor->SetHalfCarryFlag((memVal & 0x0fU) == 0x0fU);

	memVal++;
	instruction.processor->WriteByte(instruction.params.reg->GetMemory(), memVal);
}

// INC reg16
void IncReg16(ParamInstruction<Reg16Param> &instruction)
{
	instruction.params.reg->GetMemory()++;
	instruction.params.reg->Finalize();
}


// DEC reg8
void DecReg8(ParamInstruction<Reg8Param> &instruction)
{
	uchar &reg = instruction.params.reg;
	CPU *processor = instruction.processor;

	processor->SetZeroFlag(reg - 0x01U == 0x00U);
	processor->SetSubtractFlag(1);
	processor->SetHalfCarryFlag((reg & 0x0fU) > 0x00);

	reg--;
}

// DEC (reg16) ; 8-bit
void DecAddrReg16(ParamInstruction<Reg16Param> &instruction)
{
	uchar memVal = instruction.processor->ReadByte(instruction.params.reg->GetMemory());
	CPU *processor = instruction.processor;

	processor->SetZeroFlag(memVal - 0x01U == 0x00U);
	processor->SetSubtractFlag(1);
	processor->SetHalfCarryFlag((memVal & 0x0fU) > 0x00);

	memVal--;
	instruction.processor->WriteByte(instruction.params.reg->GetMemory(), memVal);
}

// DEC reg16
void DecReg16(ParamInstruction<Reg16Param> &instruction)
{
	instruction.params.reg->GetMemory()--;
	instruction.params.reg->Finalize();
}


// ADD reg8, imm8
void AddReg8Imm8(ParamInstruction<Reg8Param> &instruction)
{
	uchar &reg = instruction.params.reg;
	uchar imm = instruction.processor->ReadImm8Arg();

	instruction.processor->SetZeroFlag(reg + imm == 0);
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetHalfCarryFlag((reg & 0x0fU) + (imm & 0x0fU) > 0x0fU);
	instruction.processor->SetCarryFlag(reg > 0xffU - imm);

	reg += imm;

	instruction.SetImmArg(instruction.processor->ReadImm8Arg());
}

// ADD reg8, reg8
void AddReg8Reg8(ParamInstruction<Reg8Reg8Param> &instruction)
{
	uchar &lhs = instruction.params.lhs;
	uchar &rhs = instruction.params.rhs;

	instruction.processor->SetZeroFlag(lhs + rhs == 0);
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetHalfCarryFlag((lhs & 0x0fU) + (rhs & 0x0fU) > 0x0fU);
	instruction.processor->SetCarryFlag(lhs > 0xffU - rhs);

	lhs += rhs;
}

// ADD reg8, (reg16)
void AddReg8AddrReg16(ParamInstruction<Reg16Reg8Param> &instruction)
{
	uchar &reg = instruction.params.reg8;
	uchar memVal = instruction.processor->ReadByte(instruction.params.reg16->GetMemory());

	instruction.processor->SetZeroFlag(reg + memVal == 0x00U);
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetHalfCarryFlag((reg & 0x0fU) + (memVal & 0x0fU) > 0x0fU);
	instruction.processor->SetCarryFlag(reg > 0xffU - memVal);

	reg += memVal;
}

// ADD reg16, reg16
void AddReg16Reg16(ParamInstruction<Reg16Reg16Param> &instruction)
{
	ushort &lhs = instruction.params.lhs->GetMemory();
	ushort &rhs = instruction.params.rhs->GetMemory();

	instruction.processor->SetSubtractFlag(0);
	// TODO: Handle carry flags

	lhs += rhs;
	instruction.params.lhs->Finalize();
}

// ADD reg16, S-imm8
void AddReg16Imm8S(ParamInstruction<Reg16Param> &instruction)
{
	int regVal = instruction.params.reg->GetMemory();
	int imm8S = (signed char) instruction.processor->ReadImm8Arg();

	instruction.processor->SetZeroFlag(0);
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetHalfCarryFlag((regVal & 0x0f) + (imm8S & 0x0f) > 0x0f);
	instruction.processor->SetCarryFlag(regVal + imm8S > 0xffff);

	instruction.params.reg->GetMemory() = ((regVal + imm8S) & 0xffff);
	instruction.params.reg->Finalize();

	instruction.SetImmArg(imm8S);
}


// ADC reg8, imm8
void AdcReg8Imm8(ParamInstruction<Reg8Param> &instruction)
{
	uchar &reg = instruction.params.reg;
	uchar imm = instruction.processor->ReadImm8Arg();
	bool carryFlag = instruction.processor->GetCarryFlag();

	instruction.processor->SetZeroFlag(reg + imm + carryFlag == 0x00U);
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetHalfCarryFlag((reg & 0x0fU) + (imm & 0x0fU) + carryFlag > 0x0fU);

	unsigned int result = reg;
	result += imm;
	result += carryFlag;
	instruction.processor->SetCarryFlag(result > 0xffU);

	reg += imm;
	reg += carryFlag;

	instruction.SetImmArg(instruction.processor->ReadImm8Arg());
}

// ADC reg8, reg8
void AdcReg8Reg8(ParamInstruction<Reg8Reg8Param> &instruction)
{
	uchar &lhs = instruction.params.lhs;
	uchar &rhs = instruction.params.rhs;
	bool carryFlag = instruction.processor->GetCarryFlag();

	instruction.processor->SetZeroFlag(lhs + rhs + carryFlag == 0x00U);
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetHalfCarryFlag((lhs & 0x0fU) + (rhs & 0x0fU) + carryFlag > 0x0fU);

	unsigned int result = lhs;
	result += rhs;
	result += carryFlag;
	instruction.processor->SetCarryFlag(result > 0xffU);

	lhs += rhs;
	lhs += carryFlag;
}

// ADC reg8, (reg16)
void AdcReg8AddrReg16(ParamInstruction<Reg16Reg8Param> &instruction)
{
	uchar &reg = instruction.params.reg8;
	uchar memVal = instruction.processor->ReadByte(instruction.params.reg16->GetMemory());
	bool carryFlag = instruction.processor->GetCarryFlag();

	instruction.processor->SetZeroFlag(reg + memVal + carryFlag == 0x00U);
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetHalfCarryFlag((reg & 0x0fU) + (memVal & 0x0fU) + carryFlag > 0x0fU);

	unsigned int result = reg;
	result += memVal;
	result += carryFlag;
	instruction.processor->SetCarryFlag(result > 0xffU);

	reg += memVal;
	reg += carryFlag;
}


// SUB imm8
void SubImm8(NoParamInstruction &instruction)
{
	uchar &acc = instruction.processor->A;
	uchar imm = instruction.processor->ReadImm8Arg();

	instruction.processor->SetZeroFlag(acc - imm == 0);
	instruction.processor->SetSubtractFlag(1);
	instruction.processor->SetHalfCarryFlag((acc & 0x0fU) < (imm &0x0fU));
	instruction.processor->SetCarryFlag(acc < imm);

	acc -= imm;

	instruction.SetImmArg(instruction.processor->ReadImm8Arg());
}

// SUB reg8
void SubReg8(ParamInstruction<Reg8Param> &instruction)
{
	uchar &acc = instruction.processor->A;
	uchar &reg = instruction.params.reg;

	instruction.processor->SetZeroFlag(acc - reg == 0);
	instruction.processor->SetSubtractFlag(1);
	instruction.processor->SetHalfCarryFlag((acc & 0x0fU) < (reg & 0x0fU));
	instruction.processor->SetCarryFlag(acc < reg);

	acc -= reg;
}

// SUB (reg16)
void SubAddrReg16(ParamInstruction<Reg16Param> &instruction)
{
	uchar &acc = instruction.processor->A;
	uchar memVal = instruction.processor->ReadByte(instruction.params.reg->GetMemory());

	instruction.processor->SetZeroFlag(acc - memVal == 0);
	instruction.processor->SetSubtractFlag(1);
	instruction.processor->SetHalfCarryFlag((acc & 0x0fU) < (memVal & 0x0fU));
	instruction.processor->SetCarryFlag(acc < memVal);

	acc -= memVal;
}


// SBC reg8, imm8
void SbcReg8Imm8(ParamInstruction<Reg8Param> &instruction)
{
	uchar &reg = instruction.params.reg;
	uchar imm = instruction.processor->ReadImm8Arg();
	bool carryFlag = instruction.processor->GetCarryFlag();

	instruction.processor->SetZeroFlag(reg - imm - carryFlag == 0);
	instruction.processor->SetSubtractFlag(1);
	instruction.processor->SetHalfCarryFlag((reg & 0x0fU) < (imm & 0x0fU) + carryFlag);

	unsigned int result = reg;
	result -= imm;
	result -= carryFlag;
	instruction.processor->SetCarryFlag(result > 0xffU);

	reg -= imm;
	reg -= carryFlag;

	instruction.SetImmArg(instruction.processor->ReadImm8Arg());
}

// SBC reg8, reg8
void SbcReg8Reg8(ParamInstruction<Reg8Reg8Param> &instruction)
{
	uchar &lhs = instruction.params.lhs;
	uchar &rhs = instruction.params.rhs;
	bool carryFlag = instruction.processor->GetCarryFlag();

	instruction.processor->SetZeroFlag(lhs - rhs - carryFlag == 0);
	instruction.processor->SetSubtractFlag(1);
	instruction.processor->SetHalfCarryFlag((lhs & 0x0fU) < (rhs & 0x0fU) + carryFlag);

	unsigned int result = lhs;
	result -= rhs;
	result -= carryFlag;
	instruction.processor->SetCarryFlag(result > 0xffU);

	lhs -= rhs;
	lhs -= carryFlag;
}

// SBC reg8, (reg16)
void SbcReg8AddrReg16(ParamInstruction<Reg16Reg8Param> &instruction)
{
	uchar &reg = instruction.params.reg8;
	uchar memVal = instruction.processor->ReadByte(instruction.params.reg16->GetMemory());
	bool carryFlag = instruction.processor->GetCarryFlag();

	instruction.processor->SetZeroFlag(reg - memVal - carryFlag == 0);
	instruction.processor->SetSubtractFlag(1);
	instruction.processor->SetHalfCarryFlag((reg & 0x0fU) < (memVal & 0x0fU) + carryFlag);

	unsigned int result = reg;
	result -= memVal;
	result -= carryFlag;
	instruction.processor->SetCarryFlag(result > 0xffU);

	reg -= memVal;
	reg -= carryFlag;
}


// AND imm8
void AndImm8(NoParamInstruction &instruction)
{
	uchar &acc = instruction.processor->A;
	uchar imm = instruction.processor->ReadImm8Arg();

	instruction.processor->SetZeroFlag((acc & imm) == 0x00U);
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetHalfCarryFlag(1);
	instruction.processor->SetCarryFlag(0);

	acc &= imm;

	instruction.SetImmArg(instruction.processor->ReadImm8Arg());
}

// AND reg8
void AndReg8(ParamInstruction<Reg8Param> &instruction)
{
	uchar &acc = instruction.processor->A;
	uchar &reg = instruction.params.reg;

	instruction.processor->SetZeroFlag((acc & reg) == 0x00U);
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetHalfCarryFlag(1);
	instruction.processor->SetCarryFlag(0);

	acc &= reg;
}

// AND (reg16)
void AndAddrReg16(ParamInstruction<Reg16Param> &instruction)
{
	uchar &acc = instruction.processor->A;
	uchar memVal = instruction.processor->ReadByte(instruction.params.reg->GetMemory());

	instruction.processor->SetZeroFlag((acc & memVal) == 0x00U);
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetHalfCarryFlag(1);
	instruction.processor->SetCarryFlag(0);

	acc &= memVal;
}


// XOR imm8
void XorImm8(NoParamInstruction &instruction)
{
	uchar &acc = instruction.processor->A;
	uchar imm = instruction.processor->ReadImm8Arg();

	instruction.processor->SetZeroFlag((acc ^ imm) == 0x00U);
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetHalfCarryFlag(0);
	instruction.processor->SetCarryFlag(0);

	acc ^= imm;

	instruction.SetImmArg(instruction.processor->ReadImm8Arg());
}

// XOR reg8
void XorReg8(ParamInstruction<Reg8Param> &instruction)
{
	uchar &acc = instruction.processor->A;
	uchar &reg = instruction.params.reg;

	instruction.processor->SetZeroFlag((acc ^ reg) == 0x00U);
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetHalfCarryFlag(0);
	instruction.processor->SetCarryFlag(0);

	acc ^= reg;
}

// XOR (reg16)
void XorAddrReg16(ParamInstruction<Reg16Param> &instruction)
{
	uchar &acc = instruction.processor->A;
	uchar memVal = instruction.processor->ReadByte(instruction.params.reg->GetMemory());

	instruction.processor->SetZeroFlag((acc ^ memVal) == 0x00U);
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetHalfCarryFlag(0);
	instruction.processor->SetCarryFlag(0);

	acc ^= memVal;
}


// OR imm8
void OrImm8(NoParamInstruction &instruction)
{
	uchar &acc = instruction.processor->A;
	uchar imm = instruction.processor->ReadImm8Arg();

	instruction.processor->SetZeroFlag((acc | imm) == 0x00U);
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetHalfCarryFlag(0);
	instruction.processor->SetCarryFlag(0);

	acc |= imm;

	instruction.SetImmArg(instruction.processor->ReadImm8Arg());
}

// OR reg8
void OrReg8(ParamInstruction<Reg8Param> &instruction)
{
	uchar &acc = instruction.processor->A;
	uchar &reg = instruction.params.reg;

	instruction.processor->SetZeroFlag((acc | reg) == 0x00U);
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetHalfCarryFlag(0);
	instruction.processor->SetCarryFlag(0);

	acc |= reg;
}

// OR (reg16)
void OrAddrReg16(ParamInstruction<Reg16Param> &instruction)
{
	uchar &acc = instruction.processor->A;
	uchar memVal = instruction.processor->ReadByte(instruction.params.reg->GetMemory());

	instruction.processor->SetZeroFlag((acc | memVal) == 0x00U);
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetHalfCarryFlag(0);
	instruction.processor->SetCarryFlag(0);

	acc |= memVal;
}


// CP imm8
void CpImm8(NoParamInstruction &instruction)
{
	uchar &acc = instruction.processor->A;
	uchar imm = instruction.processor->ReadImm8Arg();

	/*std::cout << hex(imm) << std::endl;
	std::cout << hex(acc) << std::endl;*/

	if (instruction.processor->A == 0x80)
	{
		std::cout << "lksjdflakjsfd" << std::endl;
	}

	instruction.processor->SetZeroFlag(acc - imm == 0);
	instruction.processor->SetSubtractFlag(1);
	instruction.processor->SetHalfCarryFlag((acc & 0x0fU) < (imm & 0x0fU));
	instruction.processor->SetCarryFlag(acc < imm);

	instruction.SetImmArg(instruction.processor->ReadImm8Arg());
}

// CP reg8
void CpReg8(ParamInstruction<Reg8Param> &instruction)
{
	uchar &acc = instruction.processor->A;
	uchar &reg = instruction.params.reg;

	instruction.processor->SetZeroFlag(acc - reg == 0);
	instruction.processor->SetSubtractFlag(1);
	instruction.processor->SetHalfCarryFlag((acc & 0x0fU) < (reg & 0x0fU));
	instruction.processor->SetCarryFlag(acc < reg);
}

// CP (reg16)
void CpAddrReg16(ParamInstruction<Reg16Param> &instruction)
{
	uchar &acc = instruction.processor->A;
	uchar memVal = instruction.processor->ReadByte(instruction.params.reg->GetMemory());

	instruction.processor->SetZeroFlag(acc - memVal == 0);
	instruction.processor->SetSubtractFlag(1);
	instruction.processor->SetHalfCarryFlag((acc & 0x0fU) < (memVal & 0x0fU));
	instruction.processor->SetCarryFlag(acc < memVal);
}


// DAA
void DAA(NoParamInstruction &instruction)
{
	// TODO: Binary Coded Decimal?
}

// CPL
void CPL(NoParamInstruction &instruction)
{
	uchar &acc = instruction.processor->A;
	acc ^= 0xffU;

	instruction.processor->SetSubtractFlag(1);
	instruction.processor->SetHalfCarryFlag(1);
}

// SCF
void SCF(NoParamInstruction &instruction)
{
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetHalfCarryFlag(0);
	instruction.processor->SetCarryFlag(1);
}

// CCF
void CCF(NoParamInstruction &instruction)
{
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetHalfCarryFlag(0);
	instruction.processor->SetCarryFlag(!instruction.processor->GetCarryFlag());
}

/*******************************
****** Shifts & Rotations ******
********************************/
// RLCA
void RLCA(NoParamInstruction &instruction)
{
	uchar &A = instruction.processor->A;
	uchar leftmostBit = (A & (1 << 7)) >> 7;
	A = A << 1;
	A |= leftmostBit;

	instruction.processor->SetZeroFlag(A == 0x00U);
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetHalfCarryFlag(0);
	instruction.processor->SetCarryFlag(leftmostBit != 0);
}

// RRCA
void RRCA(NoParamInstruction &instruction)
{
	uchar &A = instruction.processor->A;
	uchar rightmostBit = (A & 1);
	A = A >> 1;
	A |= (rightmostBit << 7);

	instruction.processor->SetZeroFlag(A == 0x00U);
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetHalfCarryFlag(0);
	instruction.processor->SetCarryFlag(rightmostBit != 0);
}

// RLA
void RLA(NoParamInstruction &instruction)
{
	uchar &A = instruction.processor->A;
	uchar leftmostBit = (A & (1 << 7)) >> 7;
	A = A << 1;
	A |= (uchar) instruction.processor->GetCarryFlag();

	instruction.processor->SetZeroFlag(A == 0x00U);
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetHalfCarryFlag(0);
	instruction.processor->SetCarryFlag(leftmostBit != 0);
}

// RRA
void RRA(NoParamInstruction &instruction)
{
	uchar &A = instruction.processor->A;
	uchar rightmostBit = (A & 1);
	A = A >> 1;
	A |= ((uchar) instruction.processor->GetCarryFlag() << 7);

	instruction.processor->SetZeroFlag(A == 0x00U);
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetHalfCarryFlag(0);
	instruction.processor->SetCarryFlag(rightmostBit != 0);
}


// RLC reg8
void RlcReg8(ParamInstruction<Reg8Param> &instruction)
{
	uchar &reg = instruction.params.reg;
	uchar leftmostBit = (reg & (1 << 7)) >> 7;
	reg = reg << 1;
	reg |= leftmostBit;

	instruction.processor->SetZeroFlag(reg == 0x00U);
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetHalfCarryFlag(0);
	instruction.processor->SetCarryFlag(leftmostBit != 0);
}

// RLC (reg16)
void RlcAddrReg16(ParamInstruction<Reg16Param> &instruction)
{
	uchar memVal = instruction.processor->ReadByte(instruction.params.reg->GetMemory());
	uchar leftmostBit = (memVal & (1 << 7)) >> 7;
	memVal = memVal << 1;
	memVal |= leftmostBit;

	instruction.processor->SetZeroFlag(memVal == 0x00U);
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetHalfCarryFlag(0);
	instruction.processor->SetCarryFlag(leftmostBit != 0);

	instruction.processor->WriteByte(instruction.params.reg->GetMemory(), memVal);
}


// RRC reg8
void RrcReg8(ParamInstruction<Reg8Param> &instruction)
{
	uchar &reg = instruction.params.reg;
	uchar rightmostBit = (reg & 1);
	reg = reg >> 1;
	reg |= (rightmostBit << 7);

	instruction.processor->SetZeroFlag(reg == 0x00U);
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetHalfCarryFlag(0);
	instruction.processor->SetCarryFlag(rightmostBit != 0);
}

// RRC (reg16)
void RrcAddrReg16(ParamInstruction<Reg16Param> &instruction)
{
	uchar memVal = instruction.processor->ReadByte(instruction.params.reg->GetMemory());
	uchar rightmostBit = (memVal & 1);
	memVal = memVal >> 1;
	memVal |= (rightmostBit << 7);

	instruction.processor->SetZeroFlag(memVal == 0x00U);
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetHalfCarryFlag(0);
	instruction.processor->SetCarryFlag(rightmostBit != 0);

	instruction.processor->WriteByte(instruction.params.reg->GetMemory(), memVal);
}


// RL reg8
void RlReg8(ParamInstruction<Reg8Param> &instruction)
{
	uchar &reg = instruction.params.reg;
	uchar leftmostBit = (reg & (1 << 7)) >> 7;
	reg = reg << 1;
	reg |= (uchar) instruction.processor->GetCarryFlag();

	instruction.processor->SetZeroFlag(reg == 0x00U);
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetHalfCarryFlag(0);
	instruction.processor->SetCarryFlag(leftmostBit != 0);
}

// RL (reg16)
void RlAddrReg16(ParamInstruction<Reg16Param> &instruction)
{
	uchar memVal = instruction.processor->ReadByte(instruction.params.reg->GetMemory());
	uchar leftmostBit = (memVal & (1 << 7)) >> 7;
	memVal = memVal << 1;
	memVal |= (uchar) instruction.processor->GetCarryFlag();

	instruction.processor->SetZeroFlag(memVal == 0x00U);
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetHalfCarryFlag(0);
	instruction.processor->SetCarryFlag(leftmostBit != 0);

	instruction.processor->WriteByte(instruction.params.reg->GetMemory(), memVal);
}


// RR reg8
void RrReg8(ParamInstruction<Reg8Param> &instruction)
{
	uchar &reg = instruction.params.reg;
	uchar rightmostBit = (reg & 1);
	reg = reg >> 1;
	reg |= ((uchar) instruction.processor->GetCarryFlag() << 7);

	instruction.processor->SetZeroFlag(reg == 0x00U);
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetHalfCarryFlag(0);
	instruction.processor->SetCarryFlag(rightmostBit != 0);
}

// RR (reg16)
void RrAddrReg16(ParamInstruction<Reg16Param> &instruction)
{
	uchar memVal = instruction.processor->ReadByte(instruction.params.reg->GetMemory());
	uchar rightmostBit = (memVal & 1);
	memVal = memVal >> 1;
	memVal |= ((uchar) instruction.processor->GetCarryFlag() << 7);

	instruction.processor->SetZeroFlag(memVal == 0x00U);
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetHalfCarryFlag(0);
	instruction.processor->SetCarryFlag(rightmostBit != 0);

	instruction.processor->WriteByte(instruction.params.reg->GetMemory(), memVal);
}


// SLA reg8
void SlaReg8(ParamInstruction<Reg8Param> &instruction)
{
	uchar &reg = instruction.params.reg;
	uchar leftmostBit = (reg & (1 << 7)) >> 7;
	reg = reg << 1;

	instruction.processor->SetZeroFlag(reg == 0x00U);
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetHalfCarryFlag(0);
	instruction.processor->SetCarryFlag(leftmostBit != 0);
}

// SLA (reg16)
void SlaAddrReg16(ParamInstruction<Reg16Param> &instruction)
{
	uchar memVal = instruction.processor->ReadByte(instruction.params.reg->GetMemory());
	uchar leftmostBit = (memVal & (1 << 7)) >> 7;
	memVal = memVal << 1;

	instruction.processor->SetZeroFlag(memVal == 0x00U);
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetHalfCarryFlag(0);
	instruction.processor->SetCarryFlag(leftmostBit != 0);

	instruction.processor->WriteByte(instruction.params.reg->GetMemory(), memVal);
}


// SRA reg8
void SraReg8(ParamInstruction<Reg8Param> &instruction)
{
	uchar &reg = instruction.params.reg;
	uchar rightmostBit = (reg & 1);
	uchar leftmostBit = (reg & (1 << 7)) >> 7;
	reg = reg >> 1;
	reg |= leftmostBit << 7;

	instruction.processor->SetZeroFlag(reg == 0x00U);
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetHalfCarryFlag(0);
	instruction.processor->SetCarryFlag(rightmostBit != 0);
}

// SRA (reg16)
void SraAddrReg16(ParamInstruction<Reg16Param> &instruction)
{
	uchar memVal = instruction.processor->ReadByte(instruction.params.reg->GetMemory());
	uchar rightmostBit = (memVal & 1);
	uchar leftmostBit = (memVal & (1 << 7)) >> 7;
	memVal = memVal >> 1;
	memVal |= leftmostBit << 7;

	instruction.processor->SetZeroFlag(memVal == 0x00U);
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetHalfCarryFlag(0);
	instruction.processor->SetCarryFlag(rightmostBit != 0);

	instruction.processor->WriteByte(instruction.params.reg->GetMemory(), memVal);
}


// SRL reg8
void SrlReg8(ParamInstruction<Reg8Param> &instruction)
{
	uchar &reg = instruction.params.reg;
	uchar rightmostBit = (reg & 1);
	reg = reg >> 1;

	instruction.processor->SetZeroFlag(reg == 0x00U);
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetHalfCarryFlag(0);
	instruction.processor->SetCarryFlag(rightmostBit != 0);
}

// SRL (reg16)
void SrlAddrReg16(ParamInstruction<Reg16Param> &instruction)
{
	uchar memVal = instruction.processor->ReadByte(instruction.params.reg->GetMemory());
	uchar rightmostBit = (memVal & 1);
	memVal = memVal >> 1;

	instruction.processor->SetZeroFlag(memVal == 0x00U);
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetHalfCarryFlag(0);
	instruction.processor->SetCarryFlag(rightmostBit != 0);

	instruction.processor->WriteByte(instruction.params.reg->GetMemory(), memVal);
}


// SWAP reg8
void SwapReg8(ParamInstruction<Reg8Param> &instruction)
{
	uchar &reg = instruction.params.reg;

	uchar left = (reg & 0xf0U) >> 4;
	uchar right = reg & 0x0fU;

	reg = left;
	reg |= right << 4;
}

// SWAP (reg16)
void SwapAddrReg16(ParamInstruction<Reg16Param> &instruction)
{
	uchar memVal = instruction.processor->ReadByte(instruction.params.reg->GetMemory());

	uchar left = (memVal & 0xf0U) >> 4;
	uchar right = memVal & 0x0fU;

	memVal = left;
	memVal |= right << 4;

	instruction.processor->WriteByte(instruction.params.reg->GetMemory(), memVal);
}


// BIT imm8, reg8
void BitImm8Reg8(ParamInstruction<Imm8Reg8Param> &instruction)
{
	uchar &reg = instruction.params.reg8;
	uchar index = instruction.params.imm8;
	uchar mask = 1 << index;

	instruction.processor->SetZeroFlag((reg & mask) == 0);
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetHalfCarryFlag(1);
}

// BIT imm8, (reg16)
void BitImm8AddrReg16(ParamInstruction<Imm8Reg16Param> &instruction)
{
	uchar memVal = instruction.processor->ReadByte(instruction.params.reg16->GetMemory());
	uchar index = instruction.params.imm8;
	uchar mask = 1 << index;

	instruction.processor->SetZeroFlag((memVal & mask) == 0);
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetHalfCarryFlag(1);
}


// RES imm8, reg8
void ResImm8Reg8(ParamInstruction<Imm8Reg8Param> &instruction)
{
	uchar &reg = instruction.params.reg8;
	uchar index = instruction.params.imm8;
	uchar mask = 1 << index;

	reg ^= mask;
}

// RES imm8, (reg16)
void ResImm8AddrReg16(ParamInstruction<Imm8Reg16Param> &instruction)
{
	uchar memVal = instruction.processor->ReadByte(instruction.params.reg16->GetMemory());
	uchar index = instruction.params.imm8;
	uchar mask = 1 << index;

	memVal ^= mask;
	instruction.processor->WriteByte(instruction.params.reg16->GetMemory(), memVal);
}


// SET imm8, reg8
void SetImm8Reg8(ParamInstruction<Imm8Reg8Param> &instruction)
{
	uchar &reg = instruction.params.reg8;
	uchar index = instruction.params.imm8;
	uchar mask = 1 << index;
	
	reg |= mask;
}

// SET imm8, (reg16)
void SetImm8AddrReg16(ParamInstruction<Imm8Reg16Param> &instruction)
{
	uchar memVal = instruction.processor->ReadByte(instruction.params.reg16->GetMemory());
	uchar index = instruction.params.imm8;
	uchar mask = 1 << index;

	memVal |= mask;
	instruction.processor->WriteByte(instruction.params.reg16->GetMemory(), memVal);
}

/*******************************
******** Jumps & Calls *********
********************************/
// JR S-imm8
void JrImm8S(NoParamInstruction &instruction)
{
	int imm8S = (signed char) instruction.processor->ReadImm8Arg();
	instruction.processor->PC += imm8S + instruction.size;
	instruction.jumped = true;

	instruction.SetImmArg(imm8S);
}

// JR CONDITION, S-imm8
void JrCondImm8S(ParamInstruction<ConditionalParam> &instruction)
{
	uchar mask = 1 << instruction.params.flagOffset;
	bool set = (instruction.processor->F & mask) != 0;

	int imm8S = (signed char) instruction.processor->ReadImm8Arg();

	if (set == instruction.params.expectedValue)
	{
		instruction.processor->PC += imm8S + instruction.size;
		instruction.duration = 12;
		instruction.jumped = true;
	}
	else
	{
		instruction.duration = 8;
		instruction.jumped = false;
	}

	instruction.SetImmArg(imm8S);
}


// JP imm16
void JpImm16(NoParamInstruction &instruction)
{
	std::cout << int_to_hex(instruction.processor->PC) << std::endl;
	std::cout << int_to_hex(instruction.processor->ReadImm16Arg()) << std::endl;

	ushort data = instruction.processor->ReadImm16Arg();
	int data2 = data;

	instruction.processor->PC = instruction.processor->ReadImm16Arg();
	instruction.jumped = true;
	instruction.SetImmArg(data2);
}

// JP CONDITION, imm16
void JpCondImm16(ParamInstruction<ConditionalParam> &instruction)
{
	uchar mask = 1 << instruction.params.flagOffset;
	bool set = (instruction.processor->F & mask) != 0;

	if (set == instruction.params.expectedValue)
	{
		instruction.processor->PC = instruction.processor->ReadImm16Arg();
		instruction.duration = 16;
		instruction.jumped = true;
	}
	else
	{
		instruction.duration = 12;
		instruction.jumped = false;
	}

	instruction.SetImmArg(instruction.processor->ReadImm16Arg());
}

// JP (reg16)
void JpAddrReg16(ParamInstruction<Reg16Param> &instruction)
{
	instruction.processor->PC = instruction.processor->ReadByte(instruction.params.reg->GetMemory());
	instruction.jumped = true;
}


// CALL imm16
void CallImm16(NoParamInstruction &instruction)
{
	instruction.processor->PushShort(instruction.processor->PC);

	instruction.processor->PC = instruction.processor->ReadImm16Arg();
	instruction.jumped = true;
	instruction.SetImmArg(instruction.processor->ReadImm8Arg());
}

// CALL CONDITION, imm16
void CallCondImm16(ParamInstruction<ConditionalParam> &instruction)
{
	uchar mask = 1 << instruction.params.flagOffset;
	bool set = (instruction.processor->F & mask) != 0;

	if (set == instruction.params.expectedValue)
	{
		instruction.processor->PushShort(instruction.processor->PC);

		instruction.processor->PC = instruction.processor->ReadImm16Arg();

		instruction.duration = 24;
		instruction.jumped = true;
	}
	else
	{
		instruction.duration = 12;
		instruction.jumped = false;
	}

	instruction.SetImmArg(instruction.processor->ReadImm8Arg());
}


// RET
void RET(NoParamInstruction &instruction)
{
	instruction.processor->PC = instruction.processor->PopShort();
	instruction.jumped = true;
}

// RET CONDITION
void RetCond(ParamInstruction<ConditionalParam> &instruction)
{
	uchar mask = 1 << instruction.params.flagOffset;
	bool set = (instruction.processor->F & mask) != 0;

	if (set == instruction.params.expectedValue)
	{
		instruction.processor->PC = instruction.processor->PopShort();

		instruction.duration = 20;
		instruction.jumped = true;
	}
	else
	{
		instruction.duration = 8;
		instruction.jumped = false;
	}
}


// RETI
void RETI(NoParamInstruction &instruction)
{
	instruction.processor->interruptMasterEnable = true;

	instruction.processor->PC = instruction.processor->PopShort();
	instruction.jumped = true;
}


// RST imm8
void RstImm8(ParamInstruction<Imm8Param> &instruction)
{
	instruction.processor->PushShort(instruction.processor->PC);

	instruction.processor->PC = instruction.params.imm8;

	instruction.jumped = true;
}

/*******************************
******** Misc & Control ********
********************************/
// NOP
void NOP(NoParamInstruction &instruction)
{
	// Do nothing
}

// STOP 0
void Stop0(NoParamInstruction &instruction)
{
	// TODO
}

// HALT
void HALT(NoParamInstruction &instruction)
{
	// TODO
}

// PREFIX CB
void PrefixCB(NoParamInstruction &instruction)
{
	// do nothing
}

// DI
void DI(NoParamInstruction &instruction)
{
	// TODO
}

// EI
void EI(NoParamInstruction &instruction)
{
	// TODO
}




InstructionFactory::InstructionFactory(CPU *processor) : 
	processor(processor)
{

}

/*******************************
******** Loads & Moves *********
********************************/
// LD reg8, imm8
Instruction *InstructionFactory::MakeLdReg8Imm8(uchar &reg8, const std::string &mnemonic)
{
	Reg8Param param(reg8);
	return new ParamInstruction<Reg8Param>(processor, mnemonic, 2, 8, false, param, LdReg8Imm8);
}

// LD reg8, reg8
Instruction *InstructionFactory::MakeLdReg8Reg8(uchar &lhs, uchar &rhs, const std::string &mnemonic)
{
	Reg8Reg8Param param(lhs, rhs);
	return new ParamInstruction<Reg8Reg8Param>(processor, mnemonic, 1, 4, false, param, LdReg8Reg8);
}

// LD reg8, (reg8)
Instruction *InstructionFactory::MakeLdReg8AddrReg8(uchar &lhs, uchar &rhs, const std::string &mnemonic)
{
	Reg8Reg8Param param(lhs, rhs);
	return new ParamInstruction<Reg8Reg8Param>(processor, mnemonic, 2, 8, false, param, LdReg8AddrReg8);
}

// LD reg8, (imm16)
Instruction *InstructionFactory::MakeLdReg8AddrImm16(uchar &reg8, const std::string &mnemonic)
{
	Reg8Param param(reg8);
	return new ParamInstruction<Reg8Param>(processor, mnemonic, 3, 16, false, param, LdReg8AddrImm16);
}

// LD reg8, (reg16)
Instruction *InstructionFactory::MakeLdReg8AddrReg16(CompositeRegister *reg16, uchar &reg8, const std::string &mnemonic)
{
	Reg16Reg8Param param(reg16, reg8);
	return new ParamInstruction<Reg16Reg8Param>(processor, mnemonic, 1, 8, false, param, LdReg8AddrReg16);
}

// LD reg8, (reg16+)
Instruction *InstructionFactory::MakeLdReg8AddrIncReg16(CompositeRegister *reg16, uchar &reg8, const std::string &mnemonic)
{
	Reg16Reg8Param param(reg16, reg8);
	return new ParamInstruction<Reg16Reg8Param>(processor, mnemonic, 1, 8, false, param, LdReg8AddrIncReg16);
}

// LD reg8, (reg16-)
Instruction *InstructionFactory::MakeLdReg8AddrDecReg16(CompositeRegister *reg16, uchar &reg8, const std::string &mnemonic)
{
	Reg16Reg8Param param(reg16, reg8);
	return new ParamInstruction<Reg16Reg8Param>(processor, mnemonic, 1, 8, false, param, LdReg8AddrDecReg16);
}

// LD (reg8), reg8
Instruction *InstructionFactory::MakeLdAddrReg8Reg8(uchar &lhs, uchar &rhs, const std::string &mnemonic)
{
	Reg8Reg8Param param(lhs, rhs);
	return new ParamInstruction<Reg8Reg8Param>(processor, mnemonic, 2, 8, false, param, LdAddrReg8Reg8);
}

// LD (reg16), imm8
Instruction *InstructionFactory::MakeLdAddrReg16Imm8(CompositeRegister *reg16, const std::string &mnemonic)
{
	Reg16Param param(reg16);
	return new ParamInstruction<Reg16Param>(processor, mnemonic, 2, 12, false, param, LdAddrReg16Imm8);
}

// LD (reg16), reg8
Instruction *InstructionFactory::MakeLdAddrReg16Reg8(CompositeRegister *reg16, uchar &reg8, const std::string &mnemonic)
{
	Reg16Reg8Param param(reg16, reg8);
	return new ParamInstruction<Reg16Reg8Param>(processor, mnemonic, 1, 8, false, param, LdAddrReg16Reg8);
}

// LD (reg16+), reg8
Instruction *InstructionFactory::MakeLdAddrIncReg16Reg8(CompositeRegister *reg16, uchar &reg8, const std::string &mnemonic)
{
	Reg16Reg8Param param(reg16, reg8);
	return new ParamInstruction<Reg16Reg8Param>(processor, mnemonic, 1, 8, false, param, LdAddrIncReg16Reg8);
}

// LD (reg16-), reg8
Instruction *InstructionFactory::MakeLdAddrDecReg16Reg8(CompositeRegister *reg16, uchar &reg8, const std::string &mnemonic)
{
	Reg16Reg8Param param(reg16, reg8);
	return new ParamInstruction<Reg16Reg8Param>(processor, mnemonic, 1, 8, false, param, LdAddrDecReg16Reg8);
}

// LD (imm16), reg8
Instruction *InstructionFactory::MakeLdAddrImm16Reg8(uchar &reg8, const std::string &mnemonic)
{
	Reg8Param param(reg8);
	return new ParamInstruction<Reg8Param>(processor, mnemonic, 3, 16, false, param, LdAddrImm16Reg8);
}

// LD reg16, imm16
Instruction *InstructionFactory::MakeLdReg16Imm16(CompositeRegister *reg16, const std::string &mnemonic)
{
	Reg16Param param(reg16);
	return new ParamInstruction<Reg16Param>(processor, mnemonic, 3, 12, false, param, LdReg16Imm16);
}

Instruction *InstructionFactory::MakeLdReg16Reg16(CompositeRegister *lhs, CompositeRegister *rhs, const std::string &mnemonic)
{
	Reg16Reg16Param param(lhs, rhs);
	return new ParamInstruction<Reg16Reg16Param>(processor, mnemonic, 1, 8, false, param, LdReg16Reg16);
}

// LD reg16, reg16 + S-imm8
Instruction *InstructionFactory::MakeLdReg16Reg16AddImm8S(CompositeRegister *lhs, CompositeRegister *rhs, const std::string &mnemonic)
{
	Reg16Reg16Param param(lhs, rhs);
	return new ParamInstruction<Reg16Reg16Param>(processor, mnemonic, 2, 12, false, param, LdReg16Reg16AddImm8S);
}

// LD (imm16), reg16
Instruction *InstructionFactory::MakeLdAddrImm16Reg16(CompositeRegister *reg16, const std::string &mnemonic)
{
	Reg16Param param(reg16);
	return new ParamInstruction<Reg16Param>(processor, mnemonic, 3, 16, false, param, LdAddrImm16Reg16);
}


// LDH (imm8), reg8
Instruction *InstructionFactory::MakeLdHAddrImm8Reg8(uchar &reg8, const std::string &mnemonic)
{
	Reg8Param param(reg8);
	return new ParamInstruction<Reg8Param>(processor, mnemonic, 2, 12, false, param, LdHAddrImm8Reg8);
}

// LDH reg8, (imm8)
Instruction *InstructionFactory::MakeLdHReg8AddrImm8(uchar &reg8, const std::string &mnemonic)
{
	Reg8Param param(reg8);
	return new ParamInstruction<Reg8Param>(processor, mnemonic, 2, 12, false, param, LdHReg8AddrImm8);
}

// POP reg16
Instruction *InstructionFactory::MakePopReg16(CompositeRegister *reg16, const std::string &mnemonic)
{
	Reg16Param param(reg16);
	return new ParamInstruction<Reg16Param>(processor, mnemonic, 1, 12, false, param, PopReg16);
}

// PUSH reg16
Instruction *InstructionFactory::MakePushReg16(CompositeRegister *reg16, const std::string &mnemonic)
{
	Reg16Param param(reg16);
	return new ParamInstruction<Reg16Param>(processor, mnemonic, 1, 16, false, param, PushReg16);
}

/*******************************
********* Math & Logic *********
********************************/
// INC reg8
Instruction *InstructionFactory::MakeIncReg8(uchar &reg8, const std::string &mnemonic)
{
	Reg8Param param(reg8);
	return new ParamInstruction<Reg8Param>(processor, mnemonic, 1, 4, false, param, IncReg8);
}

// INC (reg16) ; 8-bit
Instruction *InstructionFactory::MakeIncAddrReg16(CompositeRegister *reg16, const std::string &mnemonic)
{
	Reg16Param param(reg16);
	return new ParamInstruction<Reg16Param>(processor, mnemonic, 1, 12, false, param, IncAddrReg16);
}

// INC reg16
Instruction *InstructionFactory::MakeIncReg16(CompositeRegister *reg16, const std::string &mnemonic)
{
	Reg16Param param(reg16);
	return new ParamInstruction<Reg16Param>(processor, mnemonic, 1, 8, false, param, IncReg16);
}


// DEC reg8
Instruction *InstructionFactory::MakeDecReg8(uchar &reg8, const std::string &mnemonic)
{
	Reg8Param param(reg8);
	return new ParamInstruction<Reg8Param>(processor, mnemonic, 1, 4, false, param, DecReg8);
}

// DEC (reg16) ; 8-bit
Instruction *InstructionFactory::MakeDecAddrReg16(CompositeRegister *reg16, const std::string &mnemonic)
{
	Reg16Param param(reg16);
	return new ParamInstruction<Reg16Param>(processor, mnemonic, 1, 12, false, param, DecAddrReg16);
}

// DEC reg16
Instruction *InstructionFactory::MakeDecReg16(CompositeRegister *reg16, const std::string &mnemonic)
{
	Reg16Param param(reg16);
	return new ParamInstruction<Reg16Param>(processor, mnemonic, 1, 8, false, param, DecReg16);
}


// ADD reg8, imm8
Instruction *InstructionFactory::MakeAddReg8Imm8(uchar &reg8, const std::string &mnemonic)
{
	Reg8Param param(reg8);
	return new ParamInstruction<Reg8Param>(processor, mnemonic, 2, 8, false, param, AddReg8Imm8);
}

// ADD reg8, reg8
Instruction *InstructionFactory::MakeAddReg8Reg8(uchar &lhs, uchar &rhs, const std::string &mnemonic)
{
	Reg8Reg8Param param(lhs, rhs);
	return new ParamInstruction<Reg8Reg8Param>(processor, mnemonic, 1, 4, false, param, AddReg8Reg8);
}

// ADD reg8, (reg16)
Instruction *InstructionFactory::MakeAddReg8AddrReg16(CompositeRegister *reg16, uchar &reg8, const std::string &mnemonic)
{
	Reg16Reg8Param param(reg16, reg8);
	return new ParamInstruction<Reg16Reg8Param>(processor, mnemonic, 1, 8, false, param, AddReg8AddrReg16);
}

// ADD reg16, reg16
Instruction *InstructionFactory::MakeAddReg16Reg16(CompositeRegister *lhs, CompositeRegister *rhs, const std::string &mnemonic)
{
	Reg16Reg16Param param(lhs, rhs);
	return new ParamInstruction<Reg16Reg16Param>(processor, mnemonic, 1, 8, false, param, AddReg16Reg16);
}

// ADD reg16, S-imm8
Instruction *InstructionFactory::MakeAddReg16Imm8S(CompositeRegister *reg16, const std::string &mnemonic)
{
	Reg16Param param(reg16);
	return new ParamInstruction<Reg16Param>(processor, mnemonic, 2, 16, false, param, AddReg16Imm8S);
}


// ADC reg8, imm8
Instruction *InstructionFactory::MakeAdcReg8Imm8(uchar &reg8, const std::string &mnemonic)
{
	Reg8Param param(reg8);
	return new ParamInstruction<Reg8Param>(processor, mnemonic, 2, 8, false, param, AdcReg8Imm8);
}

// ADC reg8, reg8
Instruction *InstructionFactory::MakeAdcReg8Reg8(uchar &lhs, uchar &rhs, const std::string &mnemonic)
{
	Reg8Reg8Param param(lhs, rhs);
	return new ParamInstruction<Reg8Reg8Param>(processor, mnemonic, 1, 4, false, param, AdcReg8Reg8);
}

// ADC reg8, (reg16)
Instruction *InstructionFactory::MakeAdcReg8AddrReg16(CompositeRegister *reg16, uchar &reg8, const std::string &mnemonic)
{
	Reg16Reg8Param param(reg16, reg8);
	return new ParamInstruction<Reg16Reg8Param>(processor, mnemonic, 1, 8, false, param, AdcReg8AddrReg16);
}


// SUB imm8
Instruction *InstructionFactory::MakeSubImm8(const std::string &mnemonic)
{
	return new NoParamInstruction(processor, mnemonic, 2, 8, false, SubImm8);
}

// SUB reg8
Instruction *InstructionFactory::MakeSubReg8(uchar &reg8, const std::string &mnemonic)
{
	Reg8Param param(reg8);
	return new ParamInstruction<Reg8Param>(processor, mnemonic, 1, 4, false, param, SubReg8);
}

// SUB (reg16)
Instruction *InstructionFactory::MakeSubAddrReg16(CompositeRegister *reg16, const std::string &mnemonic)
{
	Reg16Param param(reg16);
	return new ParamInstruction<Reg16Param>(processor, mnemonic, 1, 8, false, param, SubAddrReg16);
}


// SBC reg8, imm8
Instruction *InstructionFactory::MakeSbcReg8Imm8(uchar &reg8, const std::string &mnemonic)
{
	Reg8Param param(reg8);
	return new ParamInstruction<Reg8Param>(processor, mnemonic, 2, 8, false, param, SbcReg8Imm8);
}

// SBC reg8, reg8
Instruction *InstructionFactory::MakeSbcReg8Reg8(uchar &lhs, uchar &rhs, const std::string &mnemonic)
{
	Reg8Reg8Param param(lhs, rhs);
	return new ParamInstruction<Reg8Reg8Param>(processor, mnemonic, 1, 4, false, param, SbcReg8Reg8);
}

// SBC reg8, (reg16)
Instruction *InstructionFactory::MakeSbcReg8AddrReg16(CompositeRegister *reg16, uchar &reg8, const std::string &mnemonic)
{
	Reg16Reg8Param param(reg16, reg8);
	return new ParamInstruction<Reg16Reg8Param>(processor, mnemonic, 1, 8, false, param, SbcReg8AddrReg16);
}


// AND imm8
Instruction *InstructionFactory::MakeAndImm8(const std::string &mnemonic)
{
	return new NoParamInstruction(processor, mnemonic, 2, 8, false, AndImm8);
}

// AND reg8
Instruction *InstructionFactory::MakeAndReg8(uchar &reg8, const std::string &mnemonic)
{
	Reg8Param param(reg8);
	return new ParamInstruction<Reg8Param>(processor, mnemonic, 1, 4, false, param, AndReg8);
}

// AND (reg16)
Instruction *InstructionFactory::MakeAndAddrReg16(CompositeRegister *reg16, const std::string &mnemonic)
{
	Reg16Param param(reg16);
	return new ParamInstruction<Reg16Param>(processor, mnemonic, 1, 8, false, param, AndAddrReg16);
}


// XOR imm8
Instruction *InstructionFactory::MakeXorImm8(const std::string &mnemonic)
{
	return new NoParamInstruction(processor, mnemonic, 2, 8, false, XorImm8);
}

// XOR reg8
Instruction *InstructionFactory::MakeXorReg8(uchar &reg8, const std::string &mnemonic)
{
	Reg8Param param(reg8);
	return new ParamInstruction<Reg8Param>(processor, mnemonic, 1, 4, false, param, XorReg8);
}

// XOR (reg16)
Instruction *InstructionFactory::MakeXorAddrReg16(CompositeRegister *reg16, const std::string &mnemonic)
{
	Reg16Param param(reg16);
	return new ParamInstruction<Reg16Param>(processor, mnemonic, 1, 8, false, param, XorAddrReg16);
}


// OR imm8
Instruction *InstructionFactory::MakeOrImm8(const std::string &mnemonic)
{
	return new NoParamInstruction(processor, mnemonic, 2, 8, false, OrImm8);
}

// OR reg8
Instruction *InstructionFactory::MakeOrReg8(uchar &reg8, const std::string &mnemonic)
{
	Reg8Param param(reg8);
	return new ParamInstruction<Reg8Param>(processor, mnemonic, 1, 4, false, param, OrReg8);
}

// OR (reg16)
Instruction *InstructionFactory::MakeOrAddrReg16(CompositeRegister *reg16, const std::string &mnemonic)
{
	Reg16Param param(reg16);
	return new ParamInstruction<Reg16Param>(processor, mnemonic, 1, 8, false, param, OrAddrReg16);
}


// CP imm8
Instruction *InstructionFactory::MakeCpImm8(const std::string &mnemonic)
{
	return new NoParamInstruction(processor, mnemonic, 2, 8, false, CpImm8);
}

// CP reg8
Instruction *InstructionFactory::MakeCpReg8(uchar &reg8, const std::string &mnemonic)
{
	Reg8Param param(reg8);
	return new ParamInstruction<Reg8Param>(processor, mnemonic, 1, 4, false, param, CpReg8);
}

// CP (reg16)
Instruction *InstructionFactory::MakeCpAddrReg16(CompositeRegister *reg16, const std::string &mnemonic)
{
	Reg16Param param(reg16);
	return new ParamInstruction<Reg16Param>(processor, mnemonic, 1, 8, false, param, CpAddrReg16);
}


// DAA
Instruction *InstructionFactory::MakeDAA(const std::string &mnemonic)
{
	return new NoParamInstruction(processor, mnemonic, 1, 4, false, DAA);
}

// CPL
Instruction *InstructionFactory::MakeCPL(const std::string &mnemonic)
{
	return new NoParamInstruction(processor, mnemonic, 1, 4, false, CPL);
}

// SCF
Instruction *InstructionFactory::MakeSCF(const std::string &mnemonic)
{
	return new NoParamInstruction(processor, mnemonic, 1, 4, false, SCF);
}

// CCF
Instruction *InstructionFactory::MakeCCF(const std::string &mnemonic)
{
	return new NoParamInstruction(processor, mnemonic, 1, 4, false, CCF);
}

/*******************************
****** Shifts & Rotations ******
********************************/
// RLCA
Instruction *InstructionFactory::MakeRLCA(const std::string &mnemonic)
{
	return new NoParamInstruction(processor, mnemonic, 1, 4, false, RLCA);
}

// RRCA
Instruction *InstructionFactory::MakeRRCA(const std::string &mnemonic)
{
	return new NoParamInstruction(processor, mnemonic, 1, 4, false, RRCA);
}

// RRA
Instruction *InstructionFactory::MakeRRA(const std::string &mnemonic)
{
	return new NoParamInstruction(processor, mnemonic, 1, 4, false, RRA);
}

// RLA
Instruction *InstructionFactory::MakeRLA(const std::string &mnemonic)
{
	return new NoParamInstruction(processor, mnemonic, 1, 4, false, RLA);
}


// RLC reg8
Instruction *InstructionFactory::MakeRlcReg8(uchar &reg8, const std::string &mnemonic)
{
	Reg8Param param(reg8);
	return new ParamInstruction<Reg8Param>(processor, mnemonic, 2, 8, false, param, RlcReg8);
}

// RLC (reg16)
Instruction *InstructionFactory::MakeRlcAddrReg16(CompositeRegister *reg16, const std::string &mnemonic)
{
	Reg16Param param(reg16);
	return new ParamInstruction<Reg16Param>(processor, mnemonic, 2, 16, false, param, RlcAddrReg16);
}


// RRC reg8
Instruction *InstructionFactory::MakeRrcReg8(uchar &reg8, const std::string &mnemonic)
{
	Reg8Param param(reg8);
	return new ParamInstruction<Reg8Param>(processor, mnemonic, 2, 8, false, param, RrcReg8);
}

// RRC (reg16)
Instruction *InstructionFactory::MakeRrcAddrReg16(CompositeRegister *reg16, const std::string &mnemonic)
{
	Reg16Param param(reg16);
	return new ParamInstruction<Reg16Param>(processor, mnemonic, 2, 16, false, param, RrcAddrReg16);
}


// RL reg8
Instruction *InstructionFactory::MakeRlReg8(uchar &reg8, const std::string &mnemonic)
{
	Reg8Param param(reg8);
	return new ParamInstruction<Reg8Param>(processor, mnemonic, 2, 16, false, param, RlReg8);
}

// RL (reg16)
Instruction *InstructionFactory::MakeRlAddrReg16(CompositeRegister *reg16, const std::string &mnemonic)
{
	Reg16Param param(reg16);
	return new ParamInstruction<Reg16Param>(processor, mnemonic, 2, 16, false, param, RlAddrReg16);
}


// RR reg8
Instruction *InstructionFactory::MakeRrReg8(uchar &reg8, const std::string &mnemonic)
{
	Reg8Param param(reg8);
	return new ParamInstruction<Reg8Param>(processor, mnemonic, 2, 8, false, param, RrReg8);
}

// RR (reg16)
Instruction *InstructionFactory::MakeRrAddrReg16(CompositeRegister *reg16, const std::string &mnemonic)
{
	Reg16Param param(reg16);
	return new ParamInstruction<Reg16Param>(processor, mnemonic, 2, 16, false, param, RrAddrReg16);
}


// SLA reg8
Instruction *InstructionFactory::MakeSlaReg8(uchar &reg8, const std::string &mnemonic)
{
	Reg8Param param(reg8);
	return new ParamInstruction<Reg8Param>(processor, mnemonic, 2, 8, false, param, SlaReg8);
}

// SLA (reg16)
Instruction *InstructionFactory::MakeSlaAddrReg16(CompositeRegister *reg16, const std::string &mnemonic)
{
	Reg16Param param(reg16);
	return new ParamInstruction<Reg16Param>(processor, mnemonic, 2, 16, false, param, SlaAddrReg16);
}


// SRA reg8
Instruction *InstructionFactory::MakeSraReg8(uchar &reg8, const std::string &mnemonic)
{
	Reg8Param param(reg8);
	return new ParamInstruction<Reg8Param>(processor, mnemonic, 2, 8, false, param, SraReg8);
}

// SRA (reg16)
Instruction *InstructionFactory::MakeSraAddrReg16(CompositeRegister *reg16, const std::string &mnemonic)
{
	Reg16Param param(reg16);
	return new ParamInstruction<Reg16Param>(processor, mnemonic, 2, 16, false, param, SraAddrReg16);
}


// SWAP reg8
Instruction *InstructionFactory::MakeSwapReg8(uchar &reg8, const std::string &mnemonic)
{
	Reg8Param param(reg8);
	return new ParamInstruction<Reg8Param>(processor, mnemonic, 2, 8, false, param, SwapReg8);
}

// SWAP (reg16)
Instruction *InstructionFactory::MakeSwapAddrReg16(CompositeRegister *reg16, const std::string &mnemonic)
{
	Reg16Param param(reg16);
	return new ParamInstruction<Reg16Param>(processor, mnemonic, 2, 16, false, param, SwapAddrReg16);
}


// SRL reg8
Instruction *InstructionFactory::MakeSrlReg8(uchar &reg8, const std::string &mnemonic)
{
	Reg8Param param(reg8);
	return new ParamInstruction<Reg8Param>(processor, mnemonic, 2, 8, false, param, SrlReg8);
}

// SRL (reg16)
Instruction *InstructionFactory::MakeSrlAddrReg16(CompositeRegister *reg16, const std::string &mnemonic)
{
	Reg16Param param(reg16);
	return new ParamInstruction<Reg16Param>(processor, mnemonic, 2, 16, false, param, SrlAddrReg16);
}


// BIT imm8, reg8
Instruction *InstructionFactory::MakeBitImm8Reg8(uchar imm8, uchar &reg8, const std::string &mnemonic)
{
	Imm8Reg8Param param(imm8, reg8);
	return new ParamInstruction<Imm8Reg8Param>(processor, mnemonic, 2, 8, false, param, BitImm8Reg8);
}

// BIT imm8, (reg16)
Instruction *InstructionFactory::MakeBitImm8AddrReg16(uchar imm8, CompositeRegister *reg16, const std::string &mnemonic)
{
	Imm8Reg16Param param(imm8, reg16);
	return new ParamInstruction<Imm8Reg16Param>(processor, mnemonic, 2, 16, false, param, BitImm8AddrReg16);
}


// RES imm8, reg8
Instruction *InstructionFactory::MakeResImm8Reg8(uchar imm8, uchar &reg8, const std::string &mnemonic)
{
	Imm8Reg8Param param(imm8, reg8);
	return new ParamInstruction<Imm8Reg8Param>(processor, mnemonic, 2, 8, false, param, ResImm8Reg8);
}

// RES imm8, (reg16)
Instruction *InstructionFactory::MakeResImm8AddrReg16(uchar imm8, CompositeRegister *reg16, const std::string &mnemonic)
{
	Imm8Reg16Param param(imm8, reg16);
	return new ParamInstruction<Imm8Reg16Param>(processor, mnemonic, 2, 16, false, param, ResImm8AddrReg16);
}


// SET imm8, reg8
Instruction *InstructionFactory::MakeSetImm8Reg8(uchar imm8, uchar &reg8, const std::string &mnemonic)
{
	Imm8Reg8Param param(imm8, reg8);
	return new ParamInstruction<Imm8Reg8Param>(processor, mnemonic, 2, 8, false, param, SetImm8Reg8);
}

// SET imm8, (reg16)
Instruction *InstructionFactory::MakeSetImm8AddrReg16(uchar imm8, CompositeRegister *reg16, const std::string &mnemonic)
{
	Imm8Reg16Param param(imm8, reg16);
	return new ParamInstruction<Imm8Reg16Param>(processor, mnemonic, 2, 16, false, param, SetImm8AddrReg16);
}

/*******************************
******** Jumps & Calls *********
********************************/
// JR S-imm8
Instruction *InstructionFactory::MakeJrImm8S(const std::string &mnemonic)
{
	return new NoParamInstruction(processor, mnemonic, 2, 12, true, JrImm8S);
}

// JR CONDITION, S-imm8
Instruction *InstructionFactory::MakeJrCondImm8S(uchar flagOffset, bool expectedValue, const std::string &mnemonic)
{
	ConditionalParam param(flagOffset, expectedValue);
	return new ParamInstruction<ConditionalParam>(processor, mnemonic, 2, 12, true, param, JrCondImm8S);
}


// JP imm16
Instruction *InstructionFactory::MakeJpImm16(const std::string &mnemonic)
{
	return new NoParamInstruction(processor, mnemonic, 3, 16, true, JpImm16);
}

// JP CONDITION, imm16
Instruction *InstructionFactory::MakeJpCondImm16(uchar flagOffset, bool expectedValue, const std::string &mnemonic)
{
	ConditionalParam param(flagOffset, expectedValue);
	return new ParamInstruction<ConditionalParam>(processor, mnemonic, 3, 16, true, param, JpCondImm16);
}

// JP (reg16)
Instruction *InstructionFactory::MakeJpAddrReg16(CompositeRegister *reg16, const std::string &mnemonic)
{
	Reg16Param param(reg16);
	return new ParamInstruction<Reg16Param>(processor, mnemonic, 1, 4, true, param, JpAddrReg16);
}


// CALL imm16
Instruction *InstructionFactory::MakeCallImm16(const std::string &mnemonic)
{
	return new NoParamInstruction(processor, mnemonic, 3, 24, true, CallImm16);
}

// CALL CONDITION, imm16
Instruction *InstructionFactory::MakeCallCondImm16(uchar flagOffset, bool expectedValue, const std::string &mnemonic)
{
	ConditionalParam param(flagOffset, expectedValue);
	return new ParamInstruction<ConditionalParam>(processor, mnemonic, 3, 24, true, param, CallCondImm16);
}


// RET
Instruction *InstructionFactory::MakeRET(const std::string &mnemonic)
{
	return new NoParamInstruction(processor, mnemonic, 1, 16, true, RET);
}

// RET CONDITION
Instruction *InstructionFactory::MakeRetCond(uchar flagOffset, bool expectedValue, const std::string &mnemonic)
{
	ConditionalParam param(flagOffset, expectedValue);
	return new ParamInstruction<ConditionalParam>(processor, mnemonic, 1, 20, true, param, RetCond);
}


// RETI
Instruction *InstructionFactory::MakeRETI(const std::string &mnemonic)
{
	return new NoParamInstruction(processor, mnemonic, 1, 16, true, RETI);
}


// RST imm8
Instruction *InstructionFactory::MakeRstImm8(uchar imm8, const std::string &mnemonic)
{
	Imm8Param param(imm8);
	return new ParamInstruction<Imm8Param>(processor, mnemonic, 1, 16, true, param, RstImm8);
}

/*******************************
******** Misc & Control ********
********************************/
// NOP
Instruction *InstructionFactory::MakeNOP(const std::string &mnemonic)
{
	return new NoParamInstruction(processor, mnemonic, 1, 4, false, NOP);
}

// STOP 0
Instruction *InstructionFactory::MakeStop0(const std::string &mnemonic)
{
	return new NoParamInstruction(processor, mnemonic, 2, 4, false, Stop0);
}

// HALT
Instruction *InstructionFactory::MakeHALT(const std::string &mnemonic)
{
	return new NoParamInstruction(processor, mnemonic, 1, 4, false, HALT);
}

// PREFIX CB
Instruction *InstructionFactory::MakePrefixCB(const std::string &mnemonic)
{
	return new NoParamInstruction(processor, mnemonic, 1, 4, false, PrefixCB);
}

// DI
Instruction *InstructionFactory::MakeDI(const std::string &mnemonic)
{
	return new NoParamInstruction(processor, mnemonic, 1, 4, false, DI);
}

// EI
Instruction *InstructionFactory::MakeEI(const std::string &mnemonic)
{
	return new NoParamInstruction(processor, mnemonic, 1, 4, false, EI);
}

Instruction *InstructionFactory::MakeNoInstruction(const std::string &mnemonic)
{
	NoParamOnCall onCall = [](NoParamInstruction &instruction){};
	return new NoParamInstruction(processor, mnemonic, 0, 0, false, onCall);
}