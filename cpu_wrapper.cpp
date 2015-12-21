#include "cpu_wrapper.h"
#include "instruction.h"
#include <iostream>
#include "hex_printing.h"

CPUWrapper::CPUWrapper() : 
	memory(0x10000),
	cartridge("res/test_roms/06.gb")
{
	processor = new CPU(&memory);
	processor->InsertCartridge(&cartridge);

	Init();

	ResetState();
}

uchar &CPUWrapper::A()
{
	return processor->A;
}

uchar &CPUWrapper::F()
{
	return processor->F;
}

uchar &CPUWrapper::B()
{
	return processor->B;
}

uchar &CPUWrapper::C()
{
	return processor->C;
}

uchar &CPUWrapper::D()
{
	return processor->D;
}

uchar &CPUWrapper::E()
{
	return processor->E;
}

uchar &CPUWrapper::H()
{
	return processor->H;
}

uchar &CPUWrapper::L()
{
	return processor->L;
}

ushort CPUWrapper::AF()
{
	ushort reg = processor->A;
	reg <<= 8;
	reg |= processor->F;
	return reg;
}

ushort CPUWrapper::BC()
{
	ushort reg = processor->B;
	reg <<= 8;
	reg |= processor->C;
	return reg;
}

ushort CPUWrapper::DE()
{
	ushort reg = processor->D;
	reg <<= 8;
	reg |= processor->E;
	return reg;
}

ushort CPUWrapper::HL()
{
	ushort reg = processor->H;
	reg <<= 8;
	reg |= processor->L;
	return reg;
}

ushort &CPUWrapper::SP()
{
	return processor->SP;
}

ushort &CPUWrapper::PC()
{
	return processor->PC;
}

bool &CPUWrapper::IME()
{
	return processor->interruptMasterEnable;
}

uchar CPUWrapper::LastImm8Arg()
{
	return lastImm8Arg;
}

ushort CPUWrapper::LastImm16Arg()
{
	return lastImm16Arg;
}

uchar CPUWrapper::ReadByte(ushort address)
{
	return processor->ReadByte(address);
}

ushort CPUWrapper::ReadShort(ushort address)
{
	return processor->ReadShort(address);
}

void CPUWrapper::ExpectCyclesVarying(int cycles)
{
	expectedCyclesVarying = cycles;
}

void CPUWrapper::ExpectPCJump(int memAddress)
{
	expectedPC = memAddress;
}

void CPUWrapper::ExpectFlags(FlagState Z, FlagState N, FlagState H, FlagState C)
{
	expectedFlags[0] = Z;
	expectedFlags[1] = N;
	expectedFlags[2] = H;
	expectedFlags[3] = C;
}

void CPUWrapper::ExpectAllFlags(FlagState flags)
{
	expectedFlags[0] = flags;
	expectedFlags[1] = flags;
	expectedFlags[2] = flags;
	expectedFlags[3] = flags;
}

void CPUWrapper::SetFlags(bool zSet, bool nSet, bool hSet, bool cSet)
{
	processor->SetZeroFlag(zSet);
	processor->SetSubtractFlag(nSet);
	processor->SetHalfCarryFlag(hSet);
	processor->SetCarryFlag(cSet);
}

void CPUWrapper::SetAllFlags(bool set)
{
	processor->SetZeroFlag(set);
	processor->SetSubtractFlag(set);
	processor->SetHalfCarryFlag(set);
	processor->SetCarryFlag(set);
}

void CPUWrapper::PrepareTest(TestType testType)
{
	ResetState();
	switch (testType)
	{
	case IMM_8:
		PC() = IMM_8_TEST_ADDRESS;
		break;
	case IMM_16:
		PC() = IMM_16_TEST_ADDRESS;
		break;
	case NO_INPUT:
		PC() = NO_INPUT_ADDRESS;
		break;
	}

	this->testType = testType;
	this->testDescription = testDescription;
}

void CPUWrapper::TestJump(int opcode)
{
	if (testType == IMM_8)
	{
		lastImm8Arg = processor->ReadImm8Arg();
	}
	else if (testType == IMM_16)
	{
		lastImm16Arg = processor->ReadImm16Arg();
	}

	Instruction *instruction = processor->instructions[opcode];
	instruction->Call();

	assert(instruction->GetDuration() == expectedCyclesVarying);
	assert(PC() == expectedPC);

	CheckFlags();
}

void CPUWrapper::TestInstruction(int opcode)
{
	ushort oldPC = PC();

	if (testType == IMM_8)
	{
		lastImm8Arg = processor->ReadImm8Arg();
	}
	else if (testType == IMM_16)
	{
		lastImm16Arg = processor->ReadImm16Arg();
	}

	Instruction *instruction = processor->instructions[opcode];
	instruction->Call();

	assert(instruction->GetDuration() == expectedCycles[opcode]);
	assert(oldPC + expectedPCAdvance[opcode] == PC());

	CheckFlags();
}

void CPUWrapper::Write16BitReg(uchar &msb, uchar &lsb, ushort val)
{
	msb = ((val >> 8) & 0xff);
	lsb = val & 0xff;
}

void CPUWrapper::SetImm8TestVal(uchar val)
{
	processor->WriteByte(EIGHT_BIT_READ_ADDRESS, val);
}

void CPUWrapper::SetImm16TestVal(ushort val)
{
	processor->WriteShort(SIXTEEN_BIT_READ_ADDRESS, val);
}

void CPUWrapper::ResetState()
{
	testType = NO_INPUT;

	ExpectAllFlags(IGNORE);

	expectedCyclesVarying = 0;
	expectedPC = 0;

	lastImm8Arg = 0;
	lastImm16Arg = 0;

	F() = 0x00;		// also resets flags
	A() = 0x11;
	B() = 0x22;
	C() = 0x33;
	D() = 0x44;
	E() = 0x55;
	H() = 0x77;
	L() = 0x88;
	SP() = 0xD800;

	IME() = true;

	for (ushort i = 0xD000; i < 0xE000; i++)
	{
		processor->WriteByte(i, 0x00);
	}

	processor->WriteByte(IMM_8_TEST_ADDRESS + 1, 0xDD);
	processor->WriteShort(IMM_16_TEST_ADDRESS + 1, 0xFF80);
}

void CPUWrapper::CheckFlags()
{
	std::string flags[4] = { "Z", "N", "H", "C" };
	std::string flagStatus[2] = { "reset", "set" };

	for (int i = 0; i < 4; i++)
	{
		if (expectedFlags[i] == IGNORE)
		{
			continue;
		}

		int flagOffset = 7 - i;
		bool setExpected = expectedFlags[i] == SET;

		bool set = ((F() >> flagOffset) & 1) == 1;

		if (setExpected != set)
		{
			std::cerr << "Flag " + flags[i] + " is " + flagStatus[(int) set] + ". Expected " + flagStatus[(int) setExpected] + "." << std::endl;
			throw 0;
		}
	}
}