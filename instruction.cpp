#include "instruction.h"
#include "cpu.h"
#include "hex_printing.h"

/*******************************
********* Instruction **********
********************************/
Instruction::Instruction(CPU *processor, std::string mnemonic,
		int size, int duration) :
	processor(processor),
	mnemonic(mnemonic),
	size(size),
	duration(duration),
	jumped(false),
	immArg(0),
	hasImmArg(false)
{

}

uchar Instruction::GetDuration()
{
	return duration;
}

void Instruction::Call()
{
	processor->PC += size * (int) !jumped;
}

void Instruction::SetImmArg(int immArg)
{
	hasImmArg = true;
	this->immArg = immArg;
}

std::string Instruction::ToString()
{
	if (!hasImmArg)
	{
		return mnemonic;
	}

	else
	{
		std::string s = mnemonic;
		std::string argString = int_to_hex(immArg);

		if (s.find("imm16") != std::string::npos) {
			size_t f = s.find("imm16");
			s.replace(f, std::string("imm16").length(), argString);
		}
		else if (s.find("S-imm8") != std::string::npos)
		{
			size_t f = s.find("S-imm8");
			s.replace(f, std::string("S-imm8").length(), std::to_string(immArg));
		}
		else if (s.find("imm8") != std::string::npos)
		{
			size_t f = s.find("imm8");
			s.replace(f, std::string("imm8").length(), argString);
		}


		return s;
	}
}

/*******************************
****** NoParamInstruction ******
********************************/
NoParamInstruction::NoParamInstruction(CPU *processor, std::string mnemonic,
		int size, int duration, bool isJump, NoParamOnCall onCall) :
	Instruction(processor, mnemonic, size, duration),
	onCall(onCall)
{

}

void NoParamInstruction::Call()
{
	onCall(*this);
	Instruction::Call();
}