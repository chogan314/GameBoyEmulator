#include "instruction_factory.h"
#include "cpu.h"

// INSTRUCTION onCall FUNCTIONS:

/*******************************
******** Loads & Moves *********
********************************/
// LD reg8, imm8
void LdReg8Imm8(ParamInstruction<Reg8Param> &instruction)
{
	instruction.params.reg = instruction.processor->ReadImm8Arg();
}

// LD reg8, reg8
void LdReg8Reg8(ParamInstruction<Reg8Reg8Param> &instruction)
{
	instruction.params.lhs = instruction.params.rhs;
}

// LD reg8, (reg8)
void LdReg8AddrReg8(ParamInstruction<Reg8Reg8Param> &instruction)
{
	MemBlock *memory = instruction.processor->memory;
	
	instruction.params.lhs = memory->ReadByte(0xff00 + instruction.params.rhs);
}

// LD reg8, (imm16)
void LdReg8AddrImm16(ParamInstruction<Reg8Param> &instruction)
{
	MemBlock *memory = instruction.processor->memory;

	instruction.params.reg = memory->ReadByte(instruction.processor->ReadImm16Arg());
}

// LD reg8, (reg16)
void LdReg8AddrReg16(ParamInstruction<Reg16Reg8Param> &instruction)
{
	MemBlock *memory = instruction.processor->memory;

	instruction.params.reg8 = memory->ReadByte(instruction.params.reg16->GetMemory());
}

// LD reg8, (reg16+)
void LdReg8AddrIncReg16(ParamInstruction<Reg16Reg8Param> &instruction)
{
	MemBlock *memory = instruction.processor->memory;

	instruction.params.reg8 = memory->ReadByte(instruction.params.reg16->GetMemory());

	instruction.params.reg16->GetMemory()++;
	instruction.params.reg16->Finalize();
}

// LD reg8, (reg16-)
void LdReg8AddrDecReg16(ParamInstruction<Reg16Reg8Param> &instruction)
{
	MemBlock *memory = instruction.processor->memory;

	instruction.params.reg8 = memory->ReadByte(instruction.params.reg16->GetMemory());

	instruction.params.reg16->GetMemory()--;
	instruction.params.reg16->Finalize();
}

// LD (reg8), reg8
void LdAddrReg8Reg8(ParamInstruction<Reg8Reg8Param> &instruction)
{
	MemBlock *memory = instruction.processor->memory;

	memory->WriteByte(0xff00 + instruction.params.lhs, instruction.params.rhs);		// may not need 0xff00 + ...
}

// LD (reg16), imm8
void LdAddrReg16Imm8(ParamInstruction<Reg16Param> &instruction)
{
	MemBlock *memory = instruction.processor->memory;

	memory->WriteByte(instruction.params.reg->GetMemory(),
		instruction.processor->ReadImm8Arg());
}

// LD (reg16), reg8
void LdAddrReg16Reg8(ParamInstruction<Reg16Reg8Param> &instruction)
{
	MemBlock *memory = instruction.processor->memory;

	memory->WriteByte(instruction.params.reg16->GetMemory(),
		instruction.params.reg8);
}

// LD (reg16+), reg8
void LdAddrIncReg16Reg8(ParamInstruction<Reg16Reg8Param> &instruction)
{
	MemBlock *memory = instruction.processor->memory;

	memory->WriteByte(instruction.params.reg16->GetMemory(),
		instruction.params.reg8);

	instruction.params.reg16->GetMemory()++;
	instruction.params.reg16->Finalize();
}

// LD (reg16-), reg8
void LdAddrDecReg16Reg8(ParamInstruction<Reg16Reg8Param> &instruction)
{
	MemBlock *memory = instruction.processor->memory;

	memory->WriteByte(instruction.params.reg16->GetMemory(),
		instruction.params.reg8);

	instruction.params.reg16->GetMemory()--;
	instruction.params.reg16->Finalize();
}

// LD (imm16), reg8
void LdAddrImm16Reg8(ParamInstruction<Reg8Param> &instruction)
{
	MemBlock *memory = instruction.processor->memory;

	memory->WriteByte(instruction.processor->ReadImm16Arg(), instruction.params.reg);
}

// LD reg16, imm16
void LdReg16Imm16(ParamInstruction<Reg16Param> &instruction)
{
	instruction.params.reg->GetMemory() = instruction.processor->ReadImm16Arg();

	instruction.params.reg->Finalize();
}

// LD reg16, reg16 + S-imm8
void LdReg16Reg16AddImm8S(ParamInstruction<Reg16Reg16Param> &instruction)
{
	ushort rhsReg = instruction.params.rhs->GetMemory();
	char imm8S = instruction.processor->ReadImm8Arg();

	instruction.processor->SetZeroFlag(0);
	instruction.processor->SetSubtractFlag(0);


	// TODO: Handle signed 8-bit value

}

// LD (imm16), reg16
void LdAddrImm16Reg16(ParamInstruction<Reg16Param> &instruction)
{
	MemBlock *memory = instruction.processor->memory;

	memory->WriteShort(instruction.processor->ReadImm16Arg(),
		instruction.params.reg->GetMemory());
}


// LDH (imm8), reg8
void LdHAddrImm8Reg8(ParamInstruction<Reg8Param> &instruction)
{
	MemBlock *memory = instruction.processor->memory;

	memory->WriteByte(0xff00 + instruction.processor->ReadImm8Arg(), instruction.params.reg);
}

// LDH reg8, (imm8)
void LdHReg8AddrImm8(ParamInstruction<Reg8Param> &instruction)
{
	MemBlock *memory = instruction.processor->memory;

	memory->WriteByte(0xff00 + instruction.params.reg, instruction.processor->ReadImm8Arg());
}


// POP reg16
void PopReg16(ParamInstruction<Reg16Param> &instruction)
{
	MemBlock *memory = instruction.processor->memory;

	instruction.params.reg->GetMemory() = memory->ReadShort(instruction.processor->SP);
	instruction.params.reg->Finalize();

	instruction.processor->SP += 2;
}

// PUSH reg16
void PushReg16(ParamInstruction<Reg16Param> &instruction)
{
	MemBlock *memory = instruction.processor->memory;

	memory->WriteShort(instruction.processor->SP, instruction.params.reg->GetMemory());
	
	instruction.processor->SP -= 2;
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
	MemBlock *memory = instruction.processor->memory;
	uchar memVal = memory->ReadByte(instruction.params.reg->GetMemory());
	CPU *processor = instruction.processor;

	processor->SetZeroFlag(memVal + 0x01U == 0x00U);
	processor->SetSubtractFlag(0);
	processor->SetHalfCarryFlag((memVal & 0x0fU) == 0x0fU);

	memVal++;
	memory->WriteByte(instruction.params.reg->GetMemory(), memVal);
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
	MemBlock *memory = instruction.processor->memory;
	uchar memVal = memory->ReadByte(instruction.params.reg->GetMemory());
	CPU *processor = instruction.processor;

	processor->SetZeroFlag(memVal - 0x01U == 0x00U);
	processor->SetSubtractFlag(1);
	processor->SetHalfCarryFlag((memVal & 0x0fU) > 0x00);

	memVal--;
	memory->WriteByte(instruction.params.reg->GetMemory(), memVal);
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
}

// ADD reg8, reg8
void AddReg8Reg(ParamInstruction<Reg8Reg8Param> &instruction)
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
	MemBlock *memory = instruction.processor->memory;
	uchar memVal = memory->ReadByte(instruction.params.reg16->GetMemory());

	instruction.processor->SetZeroFlag(reg + memVal == 0x00U);
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetHalfCarryFlag((reg & 0x0fU) + (memVal & 0x0fU) > 0x0fU);
	instruction.processor->SetCarryFlag(reg > 0xffU - memVal);

	reg += memVal;
}

// ADD reg16, reg16
void AddReg16Reg16(ParamInstruction<Reg16Reg16Param> &instruction)
{

}

// ADD reg16, S-imm8
void AddReg16Imm8S(ParamInstruction<Reg16Param> &instruction)
{
	// TODO: signed values
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
	MemBlock *memory = instruction.processor->memory;
	uchar memVal = memory->ReadByte(instruction.params.reg16->GetMemory());
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
	MemBlock *memory = instruction.processor->memory;
	uchar memVal = memory->ReadByte(instruction.params.reg->GetMemory());

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
	MemBlock *memory = instruction.processor->memory;
	uchar memVal = memory->ReadByte(instruction.params.reg16->GetMemory());
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
	MemBlock *memory = instruction.processor->memory;
	uchar memVal = memory->ReadByte(instruction.params.reg->GetMemory());

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
	MemBlock *memory = instruction.processor->memory;
	uchar memVal = memory->ReadByte(instruction.params.reg->GetMemory());

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
	MemBlock *memory = instruction.processor->memory;
	uchar memVal = memory->ReadByte(instruction.params.reg->GetMemory());

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

	instruction.processor->SetZeroFlag(acc - imm == 0);
	instruction.processor->SetSubtractFlag(1);
	instruction.processor->SetHalfCarryFlag((acc & 0x0fU) < (imm & 0x0fU));
	instruction.processor->SetCarryFlag(acc < imm);
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
	MemBlock *memory = instruction.processor->memory;
	uchar memVal = memory->ReadByte(instruction.params.reg->GetMemory());

	instruction.processor->SetZeroFlag(acc - memVal == 0);
	instruction.processor->SetSubtractFlag(1);
	instruction.processor->SetHalfCarryFlag((acc & 0x0fU) < (memVal & 0x0fU));
	instruction.processor->SetCarryFlag(acc < memVal);
}


// DAA
void DAA(NoParamInstruction &instruction)
{

}

// CPL
void CPL(NoParamInstruction &instruction)
{

}

// SCF
void SCF(NoParamInstruction &instruction)
{

}

// CCF
void CCF(NoParamInstruction &instruction)
{

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
	MemBlock *memory = instruction.processor->memory;
	uchar memVal = memory->ReadByte(instruction.params.reg->GetMemory());
	uchar leftmostBit = (memVal & (1 << 7)) >> 7;
	memVal = memVal << 1;
	memVal |= leftmostBit;

	instruction.processor->SetZeroFlag(memVal == 0x00U);
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetHalfCarryFlag(0);
	instruction.processor->SetCarryFlag(leftmostBit != 0);

	memory->WriteByte(instruction.params.reg->GetMemory(), memVal);
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
	MemBlock *memory = instruction.processor->memory;
	uchar memVal = memory->ReadByte(instruction.params.reg->GetMemory());
	uchar rightmostBit = (memVal & 1);
	memVal = memVal >> 1;
	memVal |= (rightmostBit << 7);

	instruction.processor->SetZeroFlag(memVal == 0x00U);
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetHalfCarryFlag(0);
	instruction.processor->SetCarryFlag(rightmostBit != 0);

	memory->WriteByte(instruction.params.reg->GetMemory(), memVal);
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
	MemBlock *memory = instruction.processor->memory;
	uchar memVal = memory->ReadByte(instruction.params.reg->GetMemory());
	uchar leftmostBit = (memVal & (1 << 7)) >> 7;
	memVal = memVal << 1;
	memVal |= (uchar) instruction.processor->GetCarryFlag();

	instruction.processor->SetZeroFlag(memVal == 0x00U);
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetHalfCarryFlag(0);
	instruction.processor->SetCarryFlag(leftmostBit != 0);

	memory->WriteByte(instruction.params.reg->GetMemory(), memVal);
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
	MemBlock *memory = instruction.processor->memory;
	uchar memVal = memory->ReadByte(instruction.params.reg->GetMemory());
	uchar rightmostBit = (memVal & 1);
	memVal = memVal >> 1;
	memVal |= ((uchar) instruction.processor->GetCarryFlag() << 7);

	instruction.processor->SetZeroFlag(memVal == 0x00U);
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetHalfCarryFlag(0);
	instruction.processor->SetCarryFlag(rightmostBit != 0);

	memory->WriteByte(instruction.params.reg->GetMemory(), memVal);
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
	MemBlock *memory = instruction.processor->memory;
	uchar memVal = memory->ReadByte(instruction.params.reg->GetMemory());
	uchar leftmostBit = (memVal & (1 << 7)) >> 7;
	memVal = memVal << 1;

	instruction.processor->SetZeroFlag(memVal == 0x00U);
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetHalfCarryFlag(0);
	instruction.processor->SetCarryFlag(leftmostBit != 0);

	memory->WriteByte(instruction.params.reg->GetMemory(), memVal);
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
	MemBlock *memory = instruction.processor->memory;
	uchar memVal = memory->ReadByte(instruction.params.reg->GetMemory());
	uchar rightmostBit = (memVal & 1);
	uchar leftmostBit = (memVal & (1 << 7)) >> 7;
	memVal = memVal >> 1;
	memVal |= leftmostBit << 7;

	instruction.processor->SetZeroFlag(memVal == 0x00U);
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetHalfCarryFlag(0);
	instruction.processor->SetCarryFlag(rightmostBit != 0);

	memory->WriteByte(instruction.params.reg->GetMemory(), memVal);
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
	MemBlock *memory = instruction.processor->memory;
	uchar memVal = memory->ReadByte(instruction.params.reg->GetMemory());
	uchar rightmostBit = (memVal & 1);
	memVal = memVal >> 1;

	instruction.processor->SetZeroFlag(memVal == 0x00U);
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetHalfCarryFlag(0);
	instruction.processor->SetCarryFlag(rightmostBit != 0);

	memory->WriteByte(instruction.params.reg->GetMemory(), memVal);
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
	MemBlock *memory = instruction.processor->memory;
	uchar memVal = memory->ReadByte(instruction.params.reg->GetMemory());

	uchar left = (memVal & 0xf0U) >> 4;
	uchar right = memVal & 0x0fU;

	memVal = left;
	memVal |= right << 4;

	memory->WriteByte(instruction.params.reg->GetMemory(), memVal);
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
	MemBlock *memory = instruction.processor->memory;
	uchar memVal = memory->ReadByte(instruction.params.reg16->GetMemory());
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
	MemBlock *memory = instruction.processor->memory;
	uchar memVal = memory->ReadByte(instruction.params.reg16->GetMemory());
	uchar index = instruction.params.imm8;
	uchar mask = 1 << index;

	memVal ^= mask;
	memory->WriteByte(instruction.params.reg16->GetMemory(), memVal);
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
	MemBlock *memory = instruction.processor->memory;
	uchar memVal = memory->ReadByte(instruction.params.reg16->GetMemory());
	uchar index = instruction.params.imm8;
	uchar mask = 1 << index;

	memVal |= mask;
	memory->WriteByte(instruction.params.reg16->GetMemory(), memVal);
}

/*******************************
******** Jumps & Calls *********
********************************/
// JR S-imm8
void JrImm8S(NoParamInstruction &instruction)
{
	// TODO: signed values
}

// JR CONDITION, S-imm8
void JrCondImm8S(ParamInstruction<ConditionalParam> &instruction)
{
	// TODO: signed values
}


// JP imm16
void JpImm16(NoParamInstruction &instruction)
{
	instruction.processor->PC = instruction.processor->ReadImm16Arg();
}

// JP CONDITION, imm16
void JpCondImm16(ParamInstruction<ConditionalParam> &instruction)
{
	uchar mask = 1 << instruction.params.flagOffset;
	bool set = (instruction.processor->F & mask) != 0;

	if (set == instruction.params.expectedValue)
	{
		instruction.processor->PC = instruction.processor->ReadImm16Arg();
	}
}

// JP (reg16)
void JpAddrReg16(ParamInstruction<Reg16Param> &instruction)
{
	MemBlock *memory = instruction.processor->memory;
	instruction.processor->PC = memory->ReadByte(instruction.params.reg->GetMemory());
}


// CALL imm16
void CallImm16(NoParamInstruction &instruction)
{
	MemBlock *memory = instruction.processor->memory;
	memory->WriteShort(instruction.processor->SP, instruction.processor->PC + 3);

	instruction.processor->SP -= 2;

	instruction.processor->PC = instruction.processor->ReadImm16Arg();
}

// CALL CONDITION, imm16
void CallCondImm16(ParamInstruction<ConditionalParam> &instruction)
{
	uchar mask = 1 << instruction.params.flagOffset;
	bool set = (instruction.processor->F & mask) != 0;

	if (set == instruction.params.expectedValue)
	{
		MemBlock *memory = instruction.processor->memory;
		memory->WriteShort(instruction.processor->SP, instruction.processor->PC + 3);

		instruction.processor->SP -= 2;

		instruction.processor->PC = instruction.processor->ReadImm16Arg();
	}
}


// RET
void RET(NoParamInstruction &instruction)
{
	MemBlock *memory = instruction.processor->memory;
	instruction.processor->PC = memory->ReadShort(instruction.processor->SP);

	instruction.processor->SP += 2;
}

// RET CONDITION
void RetCond(ParamInstruction<ConditionalParam> &instruction)
{
	uchar mask = 1 << instruction.params.flagOffset;
	bool set = (instruction.processor->F & mask) != 0;

	if (set == instruction.params.expectedValue)
	{
		MemBlock *memory = instruction.processor->memory;
		instruction.processor->PC = memory->ReadShort(instruction.processor->SP);

		instruction.processor->SP += 2;
	}
}


// RETI
void RETI(NoParamInstruction &instruction)
{
	// TODO: Interrupts
}


// RST imm8
void RstImm8(ParamInstruction<Imm8Param> &instruction)
{
	MemBlock *memory = instruction.processor->memory;
	memory->WriteShort(instruction.processor->SP, instruction.processor->PC + 3);

	instruction.processor->SP -= 2;

	instruction.processor->PC = instruction.params.imm8;
}

/*******************************
******** Misc & Control ********
********************************/
// NOP
void NOP(NoParamInstruction &instruction)
{

}

// STOP 0
void Stop0(NoParamInstruction &instruction)
{

}

// HALT
void HALT(NoParamInstruction &instruction)
{

}

// PREFIX CB
void PrefixCB(NoParamInstruction &instruction)
{

}

// DI
void DI(NoParamInstruction &instruction)
{

}

// EI
void EI(NoParamInstruction &instruction)
{

}













InstructionFactory::InstructionFactory(CPU *processor) : 
	processor(processor)
{

}