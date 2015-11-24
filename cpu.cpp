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
	PopulateInstructionList();
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

void CPU::PopulateInstructionList()
{
	InstructionFactory factory(this);

	instructions[0x00] = factory.MakeNOP("NOP");
	instructions[0x01] = factory.MakeLdReg16Imm16(new CReg8Bit8Bit(B, C), "LD (BC), imm16");
	instructions[0x02] = factory.MakeLdAddrReg16Reg8(new CReg8Bit8Bit(B, C), A, "LD (BC), A");
	instructions[0x03] = factory.MakeIncReg16(new CReg8Bit8Bit(B, C), "INC BC");
	instructions[0x04] = factory.MakeIncReg8(B, "INC B");
	instructions[0x05] = factory.MakeDecReg8(B, "DEC B");
	instructions[0x06] = factory.MakeLdReg8Imm8(B, "LD B, imm8");
	instructions[0x07] = factory.MakeRLCA("RLCA");
	instructions[0x08] = factory.MakeLdAddrImm16Reg16(new CReg16Bit(SP), "LD (imm16), SP");
	instructions[0x09] = factory.MakeAddReg16Reg16(new CReg8Bit8Bit(H, L), new CReg8Bit8Bit(B, C), "ADD HL, BC");
	instructions[0x0f] = factory.MakeLdReg8AddrReg16(new CReg8Bit8Bit(B, C), A, "LD A, (BC)");
	instructions[0x0b] = factory.MakeDecReg16(new CReg8Bit8Bit(B, C), "DEC BC");
	instructions[0x0c] = factory.MakeIncReg8(C, "INC C");
	instructions[0x0d] = factory.MakeDecReg8(C, "DEC C");
	instructions[0x0e] = factory.MakeLdReg8Imm8(C, "LD C, imm8");
	instructions[0x0f] = factory.MakeRRCA("RRCA");
	instructions[0x10] = factory
	instructions[0x11] = factory
	instructions[0x12] = factory
	instructions[0x13] = factory
	instructions[0x14] = factory
	instructions[0x15] = factory
	instructions[0x16] = factory
	instructions[0x17] = factory
	instructions[0x18] = factory
	instructions[0x19] = factory
	instructions[0x1a] = factory
	instructions[0x1b] = factory
	instructions[0x1c] = factory
	instructions[0x1d] = factory
	instructions[0x1e] = factory
	instructions[0x1f] = factory
	instructions[0x20] = factory
	instructions[0x21] = factory
	instructions[0x22] = factory
	instructions[0x23] = factory
	instructions[0x24] = factory
	instructions[0x25] = factory
	instructions[0x26] = factory
	instructions[0x27] = factory
	instructions[0x28] = factory
	instructions[0x29] = factory
	instructions[0x2a] = factory
	instructions[0x2b] = factory
	instructions[0x2c] = factory
	instructions[0x2d] = factory
	instructions[0x2e] = factory
	instructions[0x2f] = factory
	instructions[0x30] = factory
	instructions[0x31] = factory
	instructions[0x32] = factory
	instructions[0x33] = factory
	instructions[0x34] = factory
	instructions[0x35] = factory
	instructions[0x36] = factory
	instructions[0x37] = factory
	instructions[0x38] = factory
	instructions[0x39] = factory
	instructions[0x3a] = factory
	instructions[0x3b] = factory
	instructions[0x3c] = factory
	instructions[0x3d] = factory
	instructions[0x3e] = factory
	instructions[0x3f] = factory
	instructions[0x40] = factory
	instructions[0x41] = factory
	instructions[0x42] = factory
	instructions[0x43] = factory
	instructions[0x44] = factory
	instructions[0x45] = factory
	instructions[0x46] = factory
	instructions[0x47] = factory
	instructions[0x48] = factory
	instructions[0x49] = factory
	instructions[0x4a] = factory
	instructions[0x4b] = factory
	instructions[0x4c] = factory
	instructions[0x4d] = factory
	instructions[0x4e] = factory
	instructions[0x4f] = factory
	instructions[0x50] = factory
	instructions[0x51] = factory
	instructions[0x52] = factory
	instructions[0x53] = factory
	instructions[0x54] = factory
	instructions[0x55] = factory
	instructions[0x56] = factory
	instructions[0x57] = factory
	instructions[0x58] = factory
	instructions[0x59] = factory
	instructions[0x5a] = factory
	instructions[0x5b] = factory
	instructions[0x5c] = factory
	instructions[0x5d] = factory
	instructions[0x5e] = factory
	instructions[0x5f] = factory
	instructions[0x60] = factory
	instructions[0x61] = factory
	instructions[0x62] = factory
	instructions[0x63] = factory
	instructions[0x64] = factory
	instructions[0x65] = factory
	instructions[0x66] = factory
	instructions[0x67] = factory
	instructions[0x68] = factory
	instructions[0x69] = factory
	instructions[0x6a] = factory
	instructions[0x6b] = factory
	instructions[0x6c] = factory
	instructions[0x6d] = factory
	instructions[0x6e] = factory
	instructions[0x6f] = factory
	instructions[0x70] = factory
	instructions[0x71] = factory
	instructions[0x72] = factory
	instructions[0x73] = factory
	instructions[0x74] = factory
	instructions[0x75] = factory
	instructions[0x76] = factory
	instructions[0x77] = factory
	instructions[0x78] = factory
	instructions[0x79] = factory
	instructions[0x7a] = factory
	instructions[0x7b] = factory
	instructions[0x7c] = factory
	instructions[0x7d] = factory
	instructions[0x7e] = factory
	instructions[0x7f] = factory
	instructions[0x80] = factory
	instructions[0x81] = factory
	instructions[0x82] = factory
	instructions[0x83] = factory
	instructions[0x84] = factory
	instructions[0x85] = factory
	instructions[0x86] = factory
	instructions[0x87] = factory
	instructions[0x88] = factory
	instructions[0x89] = factory
	instructions[0x8a] = factory
	instructions[0x8b] = factory
	instructions[0x8c] = factory
	instructions[0x8d] = factory
	instructions[0x8e] = factory
	instructions[0x8f] = factory
	instructions[0x90] = factory
	instructions[0x91] = factory
	instructions[0x92] = factory
	instructions[0x93] = factory
	instructions[0x94] = factory
	instructions[0x95] = factory
	instructions[0x96] = factory
	instructions[0x97] = factory
	instructions[0x98] = factory
	instructions[0x99] = factory
	instructions[0x9a] = factory
	instructions[0x9b] = factory
	instructions[0x9c] = factory
	instructions[0x9d] = factory
	instructions[0x9e] = factory
	instructions[0x9f] = factory
	instructions[0xa0] = factory
	instructions[0xa1] = factory
	instructions[0xa2] = factory
	instructions[0xa3] = factory
	instructions[0xa4] = factory
	instructions[0xa5] = factory
	instructions[0xa6] = factory
	instructions[0xa7] = factory
	instructions[0xa8] = factory
	instructions[0xa9] = factory
	instructions[0xaa] = factory
	instructions[0xab] = factory
	instructions[0xac] = factory
	instructions[0xad] = factory
	instructions[0xae] = factory
	instructions[0xaf] = factory
	instructions[0xb0] = factory
	instructions[0xb1] = factory
	instructions[0xb2] = factory
	instructions[0xb3] = factory
	instructions[0xb4] = factory
	instructions[0xb5] = factory
	instructions[0xb6] = factory
	instructions[0xb7] = factory
	instructions[0xb8] = factory
	instructions[0xb9] = factory
	instructions[0xba] = factory
	instructions[0xbb] = factory
	instructions[0xbc] = factory
	instructions[0xbd] = factory
	instructions[0xbe] = factory
	instructions[0xbf] = factory
	instructions[0xc0] = factory
	instructions[0xc1] = factory
	instructions[0xc2] = factory
	instructions[0xc3] = factory
	instructions[0xc4] = factory
	instructions[0xc5] = factory
	instructions[0xc6] = factory
	instructions[0xc7] = factory
	instructions[0xc8] = factory
	instructions[0xc9] = factory
	instructions[0xca] = factory
	instructions[0xcb] = factory
	instructions[0xcc] = factory
	instructions[0xcd] = factory
	instructions[0xce] = factory
	instructions[0xcf] = factory
	instructions[0xd0] = factory
	instructions[0xd1] = factory
	instructions[0xd2] = factory
	instructions[0xd3] = factory
	instructions[0xd4] = factory
	instructions[0xd5] = factory
	instructions[0xd6] = factory
	instructions[0xd7] = factory
	instructions[0xd8] = factory
	instructions[0xd9] = factory
	instructions[0xda] = factory
	instructions[0xdb] = factory
	instructions[0xdc] = factory
	instructions[0xdd] = factory
	instructions[0xde] = factory
	instructions[0xdf] = factory
	instructions[0xe0] = factory
	instructions[0xe1] = factory
	instructions[0xe2] = factory
	instructions[0xe3] = factory
	instructions[0xe4] = factory
	instructions[0xe5] = factory
	instructions[0xe6] = factory
	instructions[0xe7] = factory
	instructions[0xe8] = factory
	instructions[0xe9] = factory
	instructions[0xea] = factory
	instructions[0xeb] = factory
	instructions[0xec] = factory
	instructions[0xed] = factory
	instructions[0xee] = factory
	instructions[0xef] = factory
	instructions[0xf0] = factory
	instructions[0xf1] = factory
	instructions[0xf2] = factory
	instructions[0xf3] = factory
	instructions[0xf4] = factory
	instructions[0xf5] = factory
	instructions[0xf6] = factory
	instructions[0xf7] = factory
	instructions[0xf8] = factory
	instructions[0xf9] = factory
	instructions[0xfa] = factory
	instructions[0xfb] = factory
	instructions[0xfc] = factory
	instructions[0xfd] = factory
	instructions[0xfe] = factory
	instructions[0xff] = factory
}

void CPU::DoInterruptJump(ushort address)
{
	interruptMasterEnable = false;
	memory->WriteShort(SP, PC);
	SP -= 2;

	PC = address;

	// TODO: cycles and timings
}