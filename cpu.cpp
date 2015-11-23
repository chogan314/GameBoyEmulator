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
	interruptMasterEnable(true),
	instructionExtenderFlag(false)
{
	InstructionFactory factory(this);
}

CPU::~CPU()
{
	delete[] &instructions;
}

void CPU::Update()
{
	int opcode = memory->ReadByte(PC);
	InvokeInstruction(opcode);

	uchar enabledFlags = ReadInterruptEnable() & ReadInterruptFlag();
	if (interruptMasterEnable && enabledFlags)
	{
		if (enabledFlags & 1)
		{
			DoInterruptJump(0x0040U);
		}
		else if (enabledFlags & (1 << 1))
		{
			DoInterruptJump(0x0048U);
		}
		else if (enabledFlags & (1 << 2))
		{
			DoInterruptJump(0x0050U);
		}
		else if (enabledFlags & (1 << 3))
		{
			DoInterruptJump(0x0058U);
		}
		else if (enabledFlags & (1 << 4))
		{
			DoInterruptJump(0x0060U);
		}
	}
}

void CPU::InvokeInstruction(int opcode)
{
	if (instructionExtenderFlag)
	{
		opcode += 256;
		instructionExtenderFlag = false;
	}

	instructions[opcode]->Call();


}

void CPU::SetZeroFlag(bool set)
{

}

bool CPU::GetZeroFlag()
{
	return false;
}

void CPU::SetSubtractFlag(bool set)
{

}

bool CPU::GetSubtractFlag()
{
	return false;
}

void CPU::SetHalfCarryFlag(bool set)
{

}

bool CPU::GetHalfCarryFlag()
{
	return false;
}

void CPU::SetCarryFlag(bool set)
{

}

bool CPU::GetCarryFlag()
{
	return false;
}

uchar CPU::ReadImm8Arg()
{
	return memory->ReadByte(PC + 1);
}

ushort CPU::ReadImm16Arg()
{
	return memory->ReadShort(PC + 1);
}

uchar CPU::ReadJoypadInfo()
{
	return memory->ReadByte(0xFF00U);
}

void CPU::WriteJoypadInfo(uchar byte)
{
	memory->WriteByte(0xFF00U, byte);
}

uchar CPU::ReadSerialTransferData()
{
	return memory->ReadByte(0xFF01U);
}

void CPU::WriteSerialTransferData(uchar byte)
{
	memory->WriteByte(0xFF01U, byte);
}

uchar CPU::ReadSI0Control()
{
	return memory->ReadByte(0xFF02U);
}

void CPU::WriteSI0Control(uchar byte)
{
	memory->WriteByte(0xFF02U, byte);
}

uchar CPU::ReadDivider()
{
	return memory->ReadByte(0xFF04U);
}

void CPU::WriteDivider(uchar byte)
{
	memory->WriteByte(0xFF04U, byte);
}

uchar CPU::ReadTimerCounter()
{
	return memory->ReadByte(0xFF05U);
}

void CPU::WriteTimerCounter(uchar byte)
{
	memory->WriteByte(0xFF05U, byte);
}

uchar CPU::ReadTimerModulo()
{
	return memory->ReadByte(0xFF06U);
}

void CPU::WriteTimerModulo(uchar byte)
{
	memory->WriteByte(0xFF06U, byte);
}

uchar CPU::ReadInterruptFlag()
{
	return memory->ReadByte(0xFF0FU);
}

void CPU::WriteInterruptFlag(uchar byte)
{
	memory->WriteByte(0xFF0FU, byte);
}

uchar CPU::ReadInterruptEnable()
{
	return memory->ReadByte(0xFFFFU);
}

void CPU::WriteInterruptEnable(uchar byte)
{
	memory->WriteByte(0xFFFFU, byte);
}

void CPU::DoInterruptJump(ushort address)
{
	interruptMasterEnable = false;
	memory->WriteShort(SP, PC);
	SP -= 2;

	PC = address;

	// TODO: cycles and timings
}