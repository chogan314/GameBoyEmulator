#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>
#include "instruction_args.h"

class CPU;
template <typename T>
class ParamInstruction;
class NoParamInstruction;

typedef unsigned char uchar;
template <typename T>
using ParamOnCall = void(*)(ParamInstruction<T> &instruction);
using NoParamOnCall = void(*)(NoParamInstruction &instruction);

/*******************************
**********Instruction***********
********************************/
class Instruction
{
public:
	Instruction(CPU *processor, std::string mnemonic,
		int size, int duration, bool isJump);

	virtual ~Instruction() { }

	virtual void Call();
protected:
	std::string mnemonic;
	// affects memory?
	// flags affected?
	uchar size;			// in bytes
	uchar duration;		// in cpu cycles
	bool isJump;
	CPU *processor;
};

/*******************************
*******NoParamInstruction*******
********************************/
class NoParamInstruction : public Instruction
{
public:
	NoParamInstruction(CPU *processor, std::string mnemonic,
		int size, int duration, bool isJump, NoParamOnCall onCall);

	void Call();
private:
	NoParamOnCall onCall;
};

/*******************************
********ParamInstruction********
********************************/
template <typename T>
class ParamInstruction : public Instruction
{
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
	ParamInstruction(CPU *processor, std::string mnemonic,
		int size, int duration, bool isJump, T params, ParamOnCall<T> onCall);

	void Call();
private:
	T params;
	ParamOnCall<T> onCall;
};

// ParamInstruction implementation
template <typename T>
ParamInstruction<T>::ParamInstruction(CPU *processor, std::string mnemonic,
		int size, int duration, bool isJump, T params, ParamOnCall<T> onCall) :
	Instruction(processor, mnemonic, size, duration, isJump),
	params(params),
	onCall(onCall)
{

}

template <typename T>
void ParamInstruction<T>::Call()
{
	onCall(*this);
	Instruction::Call();
}

#endif