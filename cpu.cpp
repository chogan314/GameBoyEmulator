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
	instructions[0x01] = factory.MakeLdReg16Imm16(new CReg8Bit8Bit(B, C), "LD BC, imm16");
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
	instructions[0x10] = factory.MakeStop0("STOP 0");
	instructions[0x11] = factory.MakeLdReg16Imm16(new CReg8Bit8Bit(D, E), "LD DE, imm16");
	instructions[0x12] = factory.MakeLdAddrReg16Reg8(new CReg8Bit8Bit(D, E), A, "LD (DE), A");
	instructions[0x13] = factory.MakeIncReg16(new CReg8Bit8Bit(D, E), "INC DE");
	instructions[0x14] = factory.MakeIncReg8(D, "INC D");
	instructions[0x15] = factory.MakeDecReg8(D, "DEC D");
	instructions[0x16] = factory.MakeLdReg8Imm8(D, "LD D, imm8");
	instructions[0x17] = factory.MakeRLA("RLA");
	instructions[0x18] = factory.MakeJrImm8S("JR S-imm8");
	instructions[0x19] = factory.MakeAddReg16Reg16(new CReg8Bit8Bit(H, L), new CReg8Bit8Bit(D, E), "ADD HL, DE");
	instructions[0x1a] = factory.MakeLdReg8AddrReg16(new CReg8Bit8Bit(D, E), A, "LD A, (DE)");
	instructions[0x1b] = factory.MakeDecReg16(new CReg8Bit8Bit(D, E), "DEC DE");
	instructions[0x1c] = factory.MakeIncReg8(E, "INC E");
	instructions[0x1d] = factory.MakeDecReg8(E, "DEC E");
	instructions[0x1e] = factory.MakeLdReg8Imm8(E, "LD E, imm8");
	instructions[0x1f] = factory.MakeRRA("RRA");
	instructions[0x20] = factory.MakeJrCondImm8S(7, 0, "JR NZ, S-imm8");
	instructions[0x21] = factory.MakeLdReg16Imm16(new CReg8Bit8Bit(H, L), "LD HL, imm16");
	instructions[0x22] = factory.MakeLdAddrIncReg16Reg8(new CReg8Bit8Bit(H, L), A, "LD (HL+), A");
	instructions[0x23] = factory.MakeIncReg16(new CReg8Bit8Bit(H, L), "INC HL");
	instructions[0x24] = factory.MakeIncReg8(H, "INC H");
	instructions[0x25] = factory.MakeDecReg8(H, "DEC H");
	instructions[0x26] = factory.MakeLdReg8Imm8(H, "LD H, imm8");
	instructions[0x27] = factory.MakeDAA("DAA");
	instructions[0x28] = factory.MakeJrCondImm8S(7, 1, "JR Z, S-imm8");
	instructions[0x29] = factory.MakeAddReg16Reg16(new CReg8Bit8Bit(H, L), new CReg8Bit8Bit(H, L), "ADD HL, HL");
	instructions[0x2a] = factory.MakeLdReg8AddrIncReg16(new CReg8Bit8Bit(H, L), A, "LD A, (HL+)");
	instructions[0x2b] = factory.MakeDecReg16(new CReg8Bit8Bit(H, L), "DEC HL");
	instructions[0x2c] = factory.MakeIncReg8(L, "INC L");
	instructions[0x2d] = factory.MakeDecReg8(L, "DEC L");
	instructions[0x2e] = factory.MakeLdReg8Imm8(L, "LD L, imm8");
	instructions[0x2f] = factory.MakeCPL("CPL");
	instructions[0x30] = factory.MakeJrCondImm8S(4, 0, "JR NC, S-imm8");
	instructions[0x31] = factory.MakeLdReg16Imm16(new CReg16Bit(SP), "LD SP, imm16");
	instructions[0x32] = factory.MakeLdAddrDecReg16Reg8(new CReg8Bit8Bit(H, L), A, "LD (HL-), A");
	instructions[0x33] = factory.MakeIncReg16(new CReg16Bit(SP), "INC SP");
	instructions[0x34] = factory.MakeIncAddrReg16(new CReg8Bit8Bit(H, L), "INC (HL)");
	instructions[0x35] = factory.MakeDecAddrReg16(new CReg8Bit8Bit(H, L), "DEC (HL)");
	instructions[0x36] = factory.MakeLdAddrReg16Imm8(new CReg8Bit8Bit(H, L), "LD (HL), imm8");
	instructions[0x37] = factory.MakeSCF("SCF");
	instructions[0x38] = factory.MakeJrCondImm8S(4, 1, "JR C, S-imm8");
	instructions[0x39] = factory.MakeAddReg16Reg16(new CReg8Bit8Bit(H, L), new CReg16Bit(SP), "LD HL, SP");
	instructions[0x3a] = factory.MakeLdReg8AddrDecReg16(new CReg8Bit8Bit(H, L), A, "LD A, (HL-)");
	instructions[0x3b] = factory.MakeDecReg16(new CReg16Bit(SP), "DEC SP");
	instructions[0x3c] = factory.MakeIncReg8(A, "INC A");
	instructions[0x3d] = factory.MakeDecReg8(A, "DEC A");
	instructions[0x3e] = factory.MakeLdReg8Imm8(A, "LD A, imm8");
	instructions[0x3f] = factory.MakeCCF("CCF");
	instructions[0x40] = factory.MakeLdReg8Reg8(B, B, "LD B, B");
	instructions[0x41] = factory.MakeLdReg8Reg8(B, C, "LD B, C");
	instructions[0x42] = factory.MakeLdReg8Reg8(B, D, "LD B, D");
	instructions[0x43] = factory.MakeLdReg8Reg8(B, E, "LD B, E");
	instructions[0x44] = factory.MakeLdReg8Reg8(B, H, "LD B, H");
	instructions[0x45] = factory.MakeLdReg8Reg8(B, L, "LD B, L");
	instructions[0x46] = factory.MakeLdReg8AddrReg16(new CReg8Bit8Bit(H, L), B, "LD B, (HL)");
	instructions[0x47] = factory.MakeLdReg8Reg8(B, A, "LD B, A");
	instructions[0x48] = factory.MakeLdReg8Reg8(C, B, "LD C, B");
	instructions[0x49] = factory.MakeLdReg8Reg8(C, C, "LD C, C");
	instructions[0x4a] = factory.MakeLdReg8Reg8(C, D, "LD C, D");
	instructions[0x4b] = factory.MakeLdReg8Reg8(C, E, "LD C, E");
	instructions[0x4c] = factory.MakeLdReg8Reg8(C, H, "LD C, H");
	instructions[0x4d] = factory.MakeLdReg8Reg8(C, L, "LD C, L");
	instructions[0x4e] = factory.MakeLdReg8AddrReg16(new CReg8Bit8Bit(H, L), C, "LD C, (HL)");
	instructions[0x4f] = factory.MakeLdReg8Reg8(C, A, "LD C, A");
	instructions[0x50] = factory.MakeLdReg8Reg8(D, B, "LD D, B");
	instructions[0x51] = factory.MakeLdReg8Reg8(D, C, "LD D, C");
	instructions[0x52] = factory.MakeLdReg8Reg8(D, D, "LD D, D");
	instructions[0x53] = factory.MakeLdReg8Reg8(D, E, "LD D, E");
	instructions[0x54] = factory.MakeLdReg8Reg8(D, H, "LD D, H");
	instructions[0x55] = factory.MakeLdReg8Reg8(D, L, "LD D, L");
	instructions[0x56] = factory.MakeLdReg8AddrReg16(new CReg8Bit8Bit(H, L), D, "LD D, (HL)");
	instructions[0x57] = factory.MakeLdReg8Reg8(D, B, "LD D, A");
	instructions[0x58] = factory.MakeLdReg8Reg8(E, B, "LD E, B");
	instructions[0x59] = factory.MakeLdReg8Reg8(E, C, "LD E, C");
	instructions[0x5a] = factory.MakeLdReg8Reg8(E, D, "LD E, D");
	instructions[0x5b] = factory.MakeLdReg8Reg8(E, E, "LD E, E");
	instructions[0x5c] = factory.MakeLdReg8Reg8(E, H, "LD E, H");
	instructions[0x5d] = factory.MakeLdReg8Reg8(E, L, "LD E, L");
	instructions[0x5e] = factory.MakeLdReg8AddrReg16(new CReg8Bit8Bit(H, L), E, "LD E, (HL)");
	instructions[0x5f] = factory.MakeLdReg8Reg8(E, A, "LD E, A");
	instructions[0x60] = factory.MakeLdReg8Reg8(H, B, "LD H, B");
	instructions[0x61] = factory.MakeLdReg8Reg8(H, C, "LD H, C");
	instructions[0x62] = factory.MakeLdReg8Reg8(H, D, "LD H, D");
	instructions[0x63] = factory.MakeLdReg8Reg8(H, E, "LD H, E");
	instructions[0x64] = factory.MakeLdReg8Reg8(H, H, "LD H, H");
	instructions[0x65] = factory.MakeLdReg8Reg8(H, L, "LD H, L");
	instructions[0x66] = factory.MakeLdReg8AddrReg16(new CReg8Bit8Bit(H, L), H, "LD H, (HL)");
	instructions[0x67] = factory.MakeLdReg8Reg8(H, A, "LD H, A");
	instructions[0x68] = factory.MakeLdReg8Reg8(L, B, "LD L, B");
	instructions[0x69] = factory.MakeLdReg8Reg8(L, C, "LD L, C");
	instructions[0x6a] = factory.MakeLdReg8Reg8(L, D, "LD L, D");
	instructions[0x6b] = factory.MakeLdReg8Reg8(L, E, "LD L, E");
	instructions[0x6c] = factory.MakeLdReg8Reg8(L, H, "LD L, H");
	instructions[0x6d] = factory.MakeLdReg8Reg8(L, L, "LD L, L");
	instructions[0x6e] = factory.MakeLdReg8AddrReg16(new CReg8Bit8Bit(H, L), L, "LD L, (HL)");
	instructions[0x6f] = factory.MakeLdReg8Reg8(L, A, "LD L, A");
	instructions[0x70] = factory.MakeLdAddrReg16Reg8(new CReg8Bit8Bit(H, L), B, "LD (HL), B");
	instructions[0x71] = factory.MakeLdAddrReg16Reg8(new CReg8Bit8Bit(H, L), C, "LD (HL), C");
	instructions[0x72] = factory.MakeLdAddrReg16Reg8(new CReg8Bit8Bit(H, L), D, "LD (HL), D");
	instructions[0x73] = factory.MakeLdAddrReg16Reg8(new CReg8Bit8Bit(H, L), E, "LD (HL), E");
	instructions[0x74] = factory.MakeLdAddrReg16Reg8(new CReg8Bit8Bit(H, L), H, "LD (HL), H");
	instructions[0x75] = factory.MakeLdAddrReg16Reg8(new CReg8Bit8Bit(H, L), L, "LD (HL), L");
	instructions[0x76] = factory.MakeHALT("HALT");
	instructions[0x77] = factory.MakeLdAddrReg16Reg8(new CReg8Bit8Bit(H, L), L, "LD (HL), A");
	instructions[0x78] = factory.MakeLdReg8Reg8(A, B, "LD A, B");
	instructions[0x79] = factory.MakeLdReg8Reg8(A, C, "LD A, C");
	instructions[0x7a] = factory.MakeLdReg8Reg8(A, D, "LD A, D");
	instructions[0x7b] = factory.MakeLdReg8Reg8(A, E, "LD A, E");
	instructions[0x7c] = factory.MakeLdReg8Reg8(A, H, "LD A, H");
	instructions[0x7d] = factory.MakeLdReg8Reg8(A, L, "LD A, L");
	instructions[0x7e] = factory.MakeLdReg8AddrReg16(new CReg8Bit8Bit(H, L), A, "LD A, (HL)");
	instructions[0x7f] = factory.MakeLdReg8Reg8(A, A, "LD A, A");
	instructions[0x80] = factory.MakeAddReg8Reg8(A, B, "ADD A, B");
	instructions[0x81] = factory.MakeAddReg8Reg8(A, C, "ADD A, C");
	instructions[0x82] = factory.MakeAddReg8Reg8(A, D, "ADD A, D");
	instructions[0x83] = factory.MakeAddReg8Reg8(A, E, "ADD A, E");
	instructions[0x84] = factory.MakeAddReg8Reg8(A, H, "ADD A, H");
	instructions[0x85] = factory.MakeAddReg8Reg8(A, L, "ADD A, L");
	instructions[0x86] = factory.MakeAddReg8AddrReg16(new CReg8Bit8Bit(H, L), A, "ADD A, (HL)");
	instructions[0x87] = factory.MakeAddReg8Reg8(A, A, "ADD A, A");
	instructions[0x88] = factory.MakeAdcReg8Reg8(A, B, "ADC A, B");
	instructions[0x89] = factory.MakeAdcReg8Reg8(A, C, "ADC A, C");
	instructions[0x8a] = factory.MakeAdcReg8Reg8(A, D, "ADC A, D");
	instructions[0x8b] = factory.MakeAdcReg8Reg8(A, E, "ADC A, E");
	instructions[0x8c] = factory.MakeAdcReg8Reg8(A, H, "ADC A, H");
	instructions[0x8d] = factory.MakeAdcReg8Reg8(A, L, "ADC A, L");
	instructions[0x8e] = factory.MakeAdcReg8AddrReg16(new CReg8Bit8Bit(H, L), A, "ADC A, (HL)");
	instructions[0x8f] = factory.MakeAdcReg8Reg8(A, A, "ADC A, A");
	instructions[0x90] = factory.MakeSubReg8(B, "SUB B");
	instructions[0x91] = factory.MakeSubReg8(C, "SUB C");
	instructions[0x92] = factory.MakeSubReg8(D, "SUB D");
	instructions[0x93] = factory.MakeSubReg8(E, "SUB E");
	instructions[0x94] = factory.MakeSubReg8(H, "SUB H");
	instructions[0x95] = factory.MakeSubReg8(L, "SUB L");
	instructions[0x96] = factory.MakeSubAddrReg16(new CReg8Bit8Bit(H, L), "SUB (HL)");
	instructions[0x97] = factory.MakeSubReg8(A, "SUB A");
	instructions[0x98] = factory.MakeSbcReg8Reg8(A, B, "SBC A, B");
	instructions[0x99] = factory.MakeSbcReg8Reg8(A, C, "SBC A, C");
	instructions[0x9a] = factory.MakeSbcReg8Reg8(A, D, "SBC A, D");
	instructions[0x9b] = factory.MakeSbcReg8Reg8(A, E, "SBC A, E");
	instructions[0x9c] = factory.MakeSbcReg8Reg8(A, H, "SBC A, H");
	instructions[0x9d] = factory.MakeSbcReg8Reg8(A, L, "SBC A, L");
	instructions[0x9e] = factory.MakeSbcReg8AddrReg16(new CReg8Bit8Bit(H, L), A, "SUB A, (HL)");
	instructions[0x9f] = factory.MakeSbcReg8Reg8(A, A, "SBC A, A");
	instructions[0xa0] = factory.MakeAndReg8(B, "AND B");
	instructions[0xa1] = factory.MakeAndReg8(C, "AND C");
	instructions[0xa2] = factory.MakeAndReg8(D, "AND D");
	instructions[0xa3] = factory.MakeAndReg8(E, "AND E");
	instructions[0xa4] = factory.MakeAndReg8(H, "AND H");
	instructions[0xa5] = factory.MakeAndReg8(L, "AND L");
	instructions[0xa6] = factory.MakeAndAddrReg16(new CReg8Bit8Bit(H, L), "AND (HL)");
	instructions[0xa7] = factory.MakeAndReg8(A, "AND A");
	instructions[0xa8] = factory.MakeXorReg8(B, "XOR B");
	instructions[0xa9] = factory.MakeXorReg8(C, "XOR C");
	instructions[0xaa] = factory.MakeXorReg8(D, "XOR D");
	instructions[0xab] = factory.MakeXorReg8(E, "XOR E");
	instructions[0xac] = factory.MakeXorReg8(H, "XOR H");
	instructions[0xad] = factory.MakeXorReg8(L, "XOR L");
	instructions[0xae] = factory.MakeXorAddrReg16(new CReg8Bit8Bit(H, L), "XOR (HL)");
	instructions[0xaf] = factory.MakeXorReg8(A, "XOR A");
	instructions[0xb0] = factory.MakeOrReg8(B, "OR B");
	instructions[0xb1] = factory.MakeOrReg8(C, "OR C");
	instructions[0xb2] = factory.MakeOrReg8(D, "OR D");
	instructions[0xb3] = factory.MakeOrReg8(E, "OR E");
	instructions[0xb4] = factory.MakeOrReg8(H, "OR H");
	instructions[0xb5] = factory.MakeOrReg8(L, "OR L");
	instructions[0xb6] = factory.MakeOrAddrReg16(new CReg8Bit8Bit(H, L), "OR (HL)");
	instructions[0xb7] = factory.MakeOrReg8(A, "OR A");
	instructions[0xb8] = factory.MakeCpReg8(B, "CP B");
	instructions[0xb9] = factory.MakeCpReg8(C, "CP C");
	instructions[0xba] = factory.MakeCpReg8(D, "CP D");
	instructions[0xbb] = factory.MakeCpReg8(E, "CP E");
	instructions[0xbc] = factory.MakeCpReg8(H, "CP H");
	instructions[0xbd] = factory.MakeCpReg8(L, "CP L");
	instructions[0xbe] = factory.MakeCpAddrReg16(new CReg8Bit8Bit(H, L), "CP (HL)");
	instructions[0xbf] = factory.MakeCpReg8(A, "CP A");
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