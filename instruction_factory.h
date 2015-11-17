#ifndef INSTRUCTION_FACTORY_H
#define INSTRUCTION_FACTORY_H

#include "instruction.h"
class CPU;

class InstructionFactory
{
public:
	InstructionFactory(CPU *processor);

	// MAKE: LD reg16, imm16
	void MakeLoadReg16Imm16(uchar &msb, uchar &lsb);

	// MAKE: LD (reg16), reg8
	void MakeLoadAddrReg16Reg8(uchar &msb, uchar &lsb, uchar &reg8);

	// MAKE: INC reg16
	void MakeIncReg16(uchar &msb, uchar &lsb);

	// MAKE: INC reg8
	void MakeIncReg8(uchar &reg);

	// MAKE: DEC reg8
	void MakeDecReg8(uchar &reg);

	// MAKE: LD reg8, imm8
	void MakeLoadReg8Imm8(uchar &reg);

	// MAKE: LD (imm16), reg16
	void MakeLoadAddrImm16Reg16(ushort &reg);

	// MAKE: ADD reg16, reg16
	void MakeAddReg16Reg16(uchar &lhsMsb, uchar &lhsLsb, uchar &rhsMsb, uchar &rhsLsb);

	// MAKE: LD reg8, (reg16)
	void MakeLoadReg8AddrReg16(uchar &reg8, uchar &msb, uchar &lsb);

	// MAKE: DEC reg16
	void MakeDecReg16(uchar &msb, uchar &lsb);

	// MAKE: LD (reg16+), reg8
	void MakeLDAddrIncCReg16Reg8(uchar &msb, uchar &lsb, uchar &reg8);

	// MAKE: LD reg8, (reg16+)
	void MakeLDReg8AddrIncCReg16(uchar &reg8, uchar &msb, uchar &lsb);

	// MAKE: LD reg16, imm16
	void MakeLDReg16Imm16(ushort &reg);
private:
	CPU *processor;
};

// LD reg16, imm16
void LoadReg16Imm16(ParamInstruction<Reg16Param> &instruction);

// LD reg16, reg8
void LoadAddrReg16Reg8(ParamInstruction<Reg16Reg8Param> &instruction);

// INC reg16
void IncReg16(ParamInstruction<Reg16Param> &instruction);

// INC reg8
void IncReg8(ParamInstruction<Reg8Param> &instruction);

// DEC reg8
void DecReg8(ParamInstruction<Reg8Param> &instruction);

// LD reg8, imm8
void LoadReg8Imm8(ParamInstruction<Reg8Param> &instruction);

// LD (imm16), reg16
void LoadAddrImm16Reg16(ParamInstruction<Reg16Param> &instruction);

// ADD reg16, reg16
void AddReg16Reg16(ParamInstruction<Reg16Reg16Param> &instruction);

// LD reg8, (reg16)
void LoadReg8AddrReg16(ParamInstruction<Reg16Reg8Param> &instruction);

// DEC reg16
void DecReg16(ParamInstruction<Reg16Param> &instruction);

// LD (reg16+), reg8
void LDAddrIncReg16Reg8(ParamInstruction<Reg16Reg8Param> &instruction);

// LD reg8, (reg16+)
void LDReg8AddrIncReg16(ParamInstruction<Reg16Reg8Param> &instruction);

// LD reg16, imm16
void LDReg16Imm16(ParamInstruction<Reg16Param> &instruction);

// LD (reg16-), reg8
void LDAddrDecReg16Reg8(ParamInstruction<Reg16Reg8Param> &instruction);

// INC (reg16)
void IncAddrReg16(ParamInstruction<Reg16Param> &instruction);

// DEC (reg16)
void DecAddrReg16(ParamInstruction<Reg16Param> &instruction);

// LD (reg16), imm8
void LDAddrReg16Imm8(ParamInstruction<Reg16Param> &instruction);

// ADD reg16, reg16
void AddReg16Reg16(ParamInstruction<Reg16Reg16Param> &instruction);

#endif