#ifndef CPU_H
#define CPU_H

#include "mem_block.h"
#include "instruction_args.h"

typedef unsigned short ushort;
typedef unsigned char uchar;

class Instruction;
template <typename T>
class ParamInstruction;
class NoParamInstruction;

class CPU
{
	friend class Instruction;
	friend class InstructionFactory;

	// INC reg8
	friend void IncReg8(ParamInstruction<Reg8Param> &instruction);

	// DEC reg8
	friend void DecReg8(ParamInstruction<Reg8Param> &instruction);

	// LD reg8, imm8
	friend void LdReg8Imm8(ParamInstruction<Reg8Param> &instruction);

	// LD reg8, reg8
	friend void LdReg8Reg8(ParamInstruction<Reg8Reg8Param> &instruction);

	// LD reg8, (reg16)
	friend void LdReg8AddrReg16(ParamInstruction<Reg16Reg8Param> &instruction);

	// LD reg8, (reg16+)
	friend void LdReg8AddrIncReg16(ParamInstruction<Reg16Reg8Param> &instruction);

	// INC reg16
	friend void IncReg16(ParamInstruction<Reg16Param> &instruction);

	// DEC reg16
	friend void DecReg16(ParamInstruction<Reg16Param> &instruction);

	// LD reg16, imm16
	friend void LdReg16Imm16(ParamInstruction<Reg16Param> &instruction);

	// ADD reg16, reg16
	friend void AddReg16Reg16(ParamInstruction<Reg16Reg16Param> &instruction);

	// INC (reg16)
	friend void IncAddrReg16(ParamInstruction<Reg16Param> &instruction);

	// DEC (reg16)
	friend void DecAddrReg16(ParamInstruction<Reg16Param> &instruction);

	// LD (reg16), imm8
	friend void LdAddrReg16Imm8(ParamInstruction<Reg16Param> &instruction);

	// LD (reg16), reg8
	friend void LdAddrReg16Reg8(ParamInstruction<Reg16Reg8Param> &instruction);

	// LD (reg16+), reg8
	friend void LdAddrIncReg16Reg8(ParamInstruction<Reg16Reg8Param> &instruction);

	// LD (reg16-), reg8
	friend void LdAddrDecReg16Reg8(ParamInstruction<Reg16Reg8Param> &instruction);

	// LD (imm16), reg16
	friend void LdAddrImm16Reg16(ParamInstruction<Reg16Param> &instruction);
public:
	CPU();

	~CPU();

	void InvokeInstruction(int index);
private:
	uchar A;		// accumulator
	uchar F;		// flags [Zero][Subtract][Half Carry][Carry][0][0][0][0]
					// combine for 16 bit register AF, only valid operations are push and pop

	uchar B;
	uchar C;		// combine for 16 bit register BC

	uchar D;
	uchar E;		// combine for 16 bit register DE

	uchar H;
	uchar L;		// combine for 16 bit register HL
					// for some reason has significantly more operations than other combination registers

	ushort SP;		// stack pointer
	ushort PC;		// program counter

	bool instructionExtenderFlag;

	Instruction *instructions[512];

	MemBlock *memory;

	void SetZeroFlag(bool set);

	void SetSubtractFlag(bool set);

	void SetHalfCarryFlag(bool set);

	void SetCarryFlag(bool set);

	uchar ReadImm8Arg();

	ushort ReadImm16Arg();
};

#endif