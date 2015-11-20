#ifndef INSTRUCTION_FACTORY_H
#define INSTRUCTION_FACTORY_H

#include "instruction.h"
class CPU;

class InstructionFactory
{
public:
	InstructionFactory(CPU *processor);

	// MAKE: INC reg8
	void MakeIncReg8(uchar &reg);

	// MAKE: DEC reg8
	void MakeDecReg8(uchar &reg);

	// MAKE: LD reg8, imm8
	void MakeLdReg8Imm8(uchar &reg);

	// MAKE: LD reg8, reg8
	void MakeLdReg8Reg8(uchar &lhs, uchar &rhs);

	// MAKE: LD reg8, (reg16)
	void MakeLdReg8AddrReg16(uchar &reg8, CompositeRegister *reg16);

	// MAKE: LD reg8, (reg16+)
	void MakeLdReg8AddrIncReg16(uchar &reg8, CompositeRegister *reg16);

	// MAKE: INC reg16
	void MakeIncReg16(CompositeRegister *reg16);

	// MAKE: DEC reg16
	void MakeDecReg16(CompositeRegister *reg16);

	// MAKE: LD reg16, imm16
	void MakeLdReg16Imm16(CompositeRegister *reg16);

	// MAKE: ADD reg16, reg16
	void MakeAddReg16Reg16(CompositeRegister *lhs, CompositeRegister *rhs);

	// MAKE: LD (reg16), reg8
	void MakeLdAddrReg16Reg8(CompositeRegister *reg16, uchar &reg8);

	// MAKE: LD (reg16+), reg8
	void MakeLdAddrIncReg16Reg8(CompositeRegister *reg16, uchar &reg8);

	// MAKE: LD (reg16-), reg8
	void MakeLdAddrDecReg16Reg8(CompositeRegister *reg16, uchar &reg8);

	// MAKE: LD (imm16), reg16
	void MakeLdAddrImm16Reg16(CompositeRegister *reg16);
private:
	CPU *processor;
};

// NOP

// RLCA

// RRCA

// STOP 0

// RRA

// RLA

// JR S-imm8

// JR NZ, S-imm8

// JR NC, S-imm8

// DAA

// JR Z, S-imm8

// CPL

// SCF

// JR C, S-imm8

// CCF

// HALT

// RET NZ

// JP NZ, imm16

// JP imm16

// CALL NZ, imm16

// RST 00H

// RET Z

// RET

// JP Z imm16

// PREFIX CB

// CALL Z imm16

// CALL imm16

// RST 08H

// RET NC

// JP NC, imm16

// CALL NC, imm16

// RST 10H

// RET C

// RETI

// JP C, imm16

// CALL C, imm16

// RST 18H

// RST 20H

// JP (reg16)

// RST 28H

// DI

// RST 30H

// EI

// RST 38H

// INC reg8
void IncReg8(ParamInstruction<Reg8Param> &instruction);

// DEC reg8
void DecReg8(ParamInstruction<Reg8Param> &instruction);

// LD reg8, imm8
void LdReg8Imm8(ParamInstruction<Reg8Param> &instruction);

// LD reg8, reg8
void LdReg8Reg8(ParamInstruction<Reg8Reg8Param> &instruction);

// LD (reg8), reg8

// LD reg8, (reg8)

// ADD reg8, reg8

// ADD reg8, (reg16)

// ADD reg16, S-imm8

// ADC reg8, reg8

// ADC reg8, (reg16)

// ADC reg8, imm8

// SUB reg8

// SUB (reg16)

// SUB imm8

// SBC reg8, reg8

// SBC reg8, (reg16)

// SBC reg8, imm8

// AND reg8

// AND (reg16)

// AND imm8

// XOR reg8

// XOR (reg16)

// XOR imm8

// OR reg8

// OR (reg16)

// OR imm8

// CP reg8

// CP (reg16)

// CP imm8

// POP reg16

// PUSH reg16

// ADD reg8, imm8

// LDH (imm8), A

// LDH reg8, (imm8)

// LD (imm16), reg8

// LD reg16, reg16 + S-imm8

// LD reg8, (imm16)

// LD reg8, (reg16)
void LdReg8AddrReg16(ParamInstruction<Reg16Reg8Param> &instruction);

// LD reg8, (reg16+)
void LdReg8AddrIncReg16(ParamInstruction<Reg16Reg8Param> &instruction);

// INC reg16
void IncReg16(ParamInstruction<Reg16Param> &instruction);

// DEC reg16
void DecReg16(ParamInstruction<Reg16Param> &instruction);

// LD reg16, imm16
void LdReg16Imm16(ParamInstruction<Reg16Param> &instruction);

// ADD reg16, reg16
void AddReg16Reg16(ParamInstruction<Reg16Reg16Param> &instruction);

// INC (reg16)
void IncAddrReg16(ParamInstruction<Reg16Param> &instruction);

// DEC (reg16)
void DecAddrReg16(ParamInstruction<Reg16Param> &instruction);

// LD (reg16), imm8
void LdAddrReg16Imm8(ParamInstruction<Reg16Param> &instruction);

// LD (reg16), reg8
void LdAddrReg16Reg8(ParamInstruction<Reg16Reg8Param> &instruction);

// LD (reg16+), reg8
void LdAddrIncReg16Reg8(ParamInstruction<Reg16Reg8Param> &instruction);

// LD (reg16-), reg8
void LdAddrDecReg16Reg8(ParamInstruction<Reg16Reg8Param> &instruction);

// LD (imm16), reg16
void LdAddrImm16Reg16(ParamInstruction<Reg16Param> &instruction);

#endif