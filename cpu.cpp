#include "cpu.h"
#include "instruction.h"
#include "instruction_factory.h"

CPU::CPU() :
	A(0x00),
	F(0x00),
	B(0x00),
	C(0x00),
	D(0x00),
	E(0x00),
	H(0x00),
	L(0x00),
	SP(0x0000),
	PC(0x0000),
	instructionExtenderFlag(false)
{
	InstructionFactory factory(this);
}

CPU::~CPU()
{
	delete[] &instructions;
}

void CPU::InvokeInstruction(int index)
{
	if (instructionExtenderFlag)
	{
		index += 256;
		instructionExtenderFlag = false;
	}

	instructions[index]->Call();
}

void CPU::SetZeroFlag(bool set)
{

}

void CPU::SetSubtractFlag(bool set)
{

}

void CPU::SetHalfCarryFlag(bool set)
{

}

void CPU::SetCarryFlag(bool set)
{

}

uchar CPU::ReadImm8Arg()
{
	return memory->ReadByte(PC + 1);
}

ushort CPU::ReadImm16Arg()
{
	return memory->ReadShort(PC + 1);
}