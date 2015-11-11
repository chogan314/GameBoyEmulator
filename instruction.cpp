#include "instruction.h"
#include "cpu.h"

/*******************************
**********Instruction***********
********************************/
Instruction::Instruction(CPU *processor, std::string mnemonic,
		int size, int duration) :
	processor(processor),
	mnemonic(mnemonic),
	size(size),
	duration(duration)
{

}

void Instruction::Call()
{
	processor->PC += size;
}

/*******************************
*******NoParamInstruction*******
********************************/
NoParamInstruction::NoParamInstruction(CPU *processor, std::string mnemonic,
		int size, int duration, NoParamOnCall onCall) :
	Instruction(processor, mnemonic, size, duration),
	onCall(onCall)
{

}

void NoParamInstruction::Call()
{
	Instruction::Call();
	onCall(*this);
}

/*******************************
********ParamInstruction********
********************************/
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
	Instruction::Call();
	onCall(*this);
}


Instruction *MakeInstruction(CPU *processor)
{
	/*Reg8Reg8Param param(processor->B, processor->D);

	ParamInstruction<Reg8Reg8Param> *instruction = new ParamInstruction<Reg8Reg8Param>(processor, "LD B, D", 1, 4, )*/
	return nullptr;
}