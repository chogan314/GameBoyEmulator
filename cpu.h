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

	friend void LoadCReg16Imm16(ParamInstruction<CReg16Param> &instruction);
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
};

#endif