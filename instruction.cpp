#include "instruction.h"
#include "cpu.h"

/*******************************
********* Instruction **********
********************************/
Instruction::Instruction(CPU *processor, std::string mnemonic,
		int size, int duration, bool isJump) :
	processor(processor),
	mnemonic(mnemonic),
	size(size),
	duration(duration),
	isJump(isJump)
{

}

void Instruction::Call()
{
	processor->PC += size * isJump;
}

/*******************************
****** NoParamInstruction ******
********************************/
NoParamInstruction::NoParamInstruction(CPU *processor, std::string mnemonic,
		int size, int duration, bool isJump, NoParamOnCall onCall) :
	Instruction(processor, mnemonic, size, duration, isJump),
	onCall(onCall)
{

}

void NoParamInstruction::Call()
{
	onCall(*this);
	Instruction::Call();
}