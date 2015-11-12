#ifndef INSTRUCTION_FACTORY_H
#define INSTRUCTION_FACTORY_H

#include "instruction.h"
class CPU;

class InstructionFactory
{
public:
	InstructionFactory(CPU *processor);

	// NOP
	Instruction *MakeOp0x00();

	// LD BC, d16
	Instruction *MakeOp0x01();

	// LD (BC), A
	Instruction *MakeOp0x02();

	// INC BC
	Instruction *MakeOp0x03();

	// INC B
	Instruction *MakeOp0x04();

	// DEC B
	Instruction *MakeOp0x05();

	// LD B, d8
	Instruction *MakeOp0x06();

	// RLCA
	Instruction *MakeOp0x07();

	// LD (a16), SP
	Instruction *MakeOp0x08();

	// ADD HL, BC
	Instruction *MakeOp0x09();

	// LD A, (BC)
	Instruction *MakeOp0x0A();

	// DEC BC
	Instruction *MakeOp0x0B();

	// INC C
	Instruction *MakeOp0x0C();

	// DEC C
	Instruction *MakeOp0x0D();

	// LD C, d8
	Instruction *MakeOp0x0E();

	// RRCA
	Instruction *MakeOp0x0F();

	// STOP 0
	Instruction *MakeOp0x10();

	// LD DE, d16
	Instruction *MakeOp0x11();

	// LD (DE), A
	Instruction *MakeOp0x12();

	// INC DE
	Instruction *MakeOp0x13();

	// INC D
	Instruction *MakeOp0x14();

	// DEC D
	Instruction *MakeOp0x15();

	// LD D, d8
	Instruction *MakeOp0x16();

	// RLA
	Instruction *MakeOp0x17();

	// JR r8
	Instruction *MakeOp0x18();

	// ADD HL, DE
	Instruction *MakeOp0x19();

	// LD A, (DE)
	Instruction *MakeOp0x1A();

	// DEC DE
	Instruction *MakeOp0x1B();

	// INC E
	Instruction *MakeOp0x1C();

	// DEC E
	Instruction *MakeOp0x1D();

	// LD E, d8
	Instruction *MakeOp0x1E();

	// RRA
	Instruction *MakeOp0x1F();

	// JR NZ, r8
	Instruction *MakeOp0x20();

	// LD HL, d16
	Instruction *MakeOp0x21();

	// LD (HL+), A
	Instruction *MakeOp0x22();

	// INC HL
	Instruction *MakeOp0x23();

	// INC H
	Instruction *MakeOp0x24();

	// DEC H
	Instruction *MakeOp0x25();

	// LD H, d8
	Instruction *MakeOp0x26();

	// DAA
	Instruction *MakeOp0x27();

	// JR Z, r8
	Instruction *MakeOp0x28();

	// ADD HL, HL
	Instruction *MakeOp0x29();

	// LD A, (HL+)
	Instruction *MakeOp0x2A();

	// DEC HL
	Instruction *MakeOp0x2B();

	// INC L
	Instruction *MakeOp0x2C();

	// DEC L
	Instruction *MakeOp0x2D();

	// LD L, d8
	Instruction *MakeOp0x2E();

	// CPL
	Instruction *MakeOp0x2F();
private:
	CPU *processor;
};

// LD cReg16, imm16
// Load a 16-bit immediate value to a composite 16-bit register
void LoadCReg16Imm16(ParamInstruction<CReg16Param> &instruction);

// LD (cReg16), reg8
// Load an 8-bit register to memory address pointed to by composite 16-bit register
void LoadAddrCReg16Reg8(ParamInstruction<CReg16Reg8Param> &instruction);

// INC cReg16
// Increment a composite 16-bit register
void IncCReg16(ParamInstruction<CReg16Param> &instruction);

// INC reg8
// Increment an 8-bit register
void IncReg8(ParamInstruction<Reg8Param> &instruction);

// DEC reg8
// Decrement 8-bit register
void DecReg8(ParamInstruction<Reg8Param> &instruction);

// LD reg8, imm8
// Load an 8-bit immediate value to an 8-bit register
void LoadReg8Imm8(ParamInstruction<Reg8Param> &instruction);

// LD (imm16), reg16
// Load a 16-bit register to memory address represented by 16-bit immediate value
void LoadAddrImm16Reg16(ParamInstruction<Reg16Param> &instruction);

// ADD cReg16, cReg16
// Add a composite 16-bit register to a composite 16-bit register
void AddCReg16CReg16(ParamInstruction<CReg16CReg16Param> &instruction);

// LD reg8, (cReg16)
// Load value at memory address pointed to by composite 16-bit register to 8-bit regsiter
void LoadReg8AddrCReg16(ParamInstruction<CReg16Reg8Param> &instruction);

// DEC cReg16
// Decrement composite 16-bit register
void DecCReg16(ParamInstruction<CReg16Param> &instruction);

// LD (cReg16+), reg8
// Load an 8-bit register to address pointed to by a composite 16-bit register, then increment composite 16-bit register
void LDAddrIncCReg16Reg8(ParamInstruction<CReg16Reg8Param> &instruction);

// LD reg8, (cReg16+)
void LDReg8AddrIncCReg16(ParamInstruction<CReg16Reg8Param> &instruction);

#endif