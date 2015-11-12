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
		int size, int duration);

	virtual ~Instruction() { }

	virtual void Call();
protected:
	std::string mnemonic;
	// affects memory?
	// flags affected?
	uchar size;			// in bytes
	uchar duration;		// in cpu cycles
	CPU *processor;
};

/*******************************
*******NoParamInstruction*******
********************************/
class NoParamInstruction : public Instruction
{
public:
	NoParamInstruction(CPU *processor, std::string mnemonic,
		int size, int duration, NoParamOnCall onCall);

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
	friend void LoadCReg16Imm16(ParamInstruction<CReg16Param> &instruction);
public:
	ParamInstruction(CPU *processor, std::string mnemonic,
		int size, int duration, T params, ParamOnCall<T> onCall);

	void Call();
private:
	T params;
	ParamOnCall<T> onCall;
};

// ParamInstruction implementation
template <typename T>
ParamInstruction<T>::ParamInstruction(CPU *processor, std::string mnemonic,
	int size, int duration, T params, ParamOnCall<T> onCall) :
	Instruction(processor, mnemonic, size, duration),
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