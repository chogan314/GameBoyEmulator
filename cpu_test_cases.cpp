#include "cpu_test_cases.h"
#include "utils.h"

CPUTestCases::CPUTestCases()
{

}

// NOP
void CPUTestCases::TestOP0x00()
{
	w.PrepareTest(NO_INPUT);
	w.TestInstruction(0x00);
}

// LD BC, imm16
void CPUTestCases::TestOP0x01()
{
	w.PrepareTest(IMM_16);
	w.TestInstruction(0x01);
	assert(w.BC() == w.LastImm16Arg());
}

// LD (BC), A
void CPUTestCases::TestOP0x02()
{
	w.PrepareTest(NO_INPUT);
	w.Write16BitReg(w.B(), w.C(), CPUWrapper::EIGHT_BIT_WRITE_ADDRESS);
	w.TestInstruction(0x02);
	assert(w.ReadShort(w.BC()) == w.A());
}

// INC BC
void CPUTestCases::TestOP0x03()
{
	w.PrepareTest(NO_INPUT);
	w.Write16BitReg(w.B(), w.C(), 0x0010);
	w.TestInstruction(0x03);
	assert(w.BC() == 0x0011);

	w.PrepareTest(NO_INPUT);
	w.Write16BitReg(w.B(), w.C(), 0xffff);
	w.TestInstruction(0x03);
	assert(w.BC() == 0x0000);
}

// INC B
void CPUTestCases::TestOP0x04()
{
	w.PrepareTest(NO_INPUT);
	w.B() = 0x00;
	w.ExpectFlags(RESET, RESET, RESET, IGNORE);
	w.TestInstruction(0x04);
	assert(w.B() == 0x01);

	w.PrepareTest(NO_INPUT);
	w.B() = 0x0F;
	w.ExpectFlags(RESET, RESET, SET, IGNORE);
	w.TestInstruction(0x04);
	assert(w.B() == 0x10);

	w.PrepareTest(NO_INPUT);
	w.B() = 0x2F;
	w.ExpectFlags(RESET, RESET, SET, IGNORE);
	w.TestInstruction(0x04);
	assert(w.B() == 0x30);

	w.PrepareTest(NO_INPUT);
	w.B() = 0xFF;
	w.ExpectFlags(SET, RESET, SET, IGNORE);
	w.TestInstruction(0x04);
	assert(w.B() == 0x00);
}

// DEC B
void CPUTestCases::TestOP0x05()
{
	w.PrepareTest(NO_INPUT);
	w.B() = 0x02;
	w.ExpectFlags(RESET, SET, RESET, IGNORE);
	w.TestInstruction(0x05);
	assert(w.B() == 0x01);

	w.PrepareTest(NO_INPUT);
	w.B() = 0x30;
	w.ExpectFlags(RESET, SET, SET, IGNORE);
	w.TestInstruction(0x05);
	assert(w.B() == 0x2f);

	w.PrepareTest(NO_INPUT);
	w.B() = 0x01;
	w.ExpectFlags(SET, SET, RESET, IGNORE);
	w.TestInstruction(0x05);
	assert(w.B() == 0x00);
}

// LD B, imm8
void CPUTestCases::TestOP0x06()
{
	w.PrepareTest(IMM_8);
	w.TestInstruction(0x06);
	assert(w.B() == w.LastImm8Arg());
}

// RLCA
void CPUTestCases::TestOP0x07()
{

}

// LD (imm16), SP
void CPUTestCases::TestOP0x08()
{
	w.PrepareTest(IMM_16);
	w.TestInstruction(0x08);
	assert(w.ReadShort(w.LastImm16Arg()) == w.SP());
}

// ADD HL, BC
void CPUTestCases::TestOP0x09()
{
	w.PrepareTest(NO_INPUT);
	w.Write16BitReg(w.H(), w.L(), 0x1010);
	w.Write16BitReg(w.B(), w.C(), 0x0303);
	w.ExpectFlags(IGNORE, RESET, RESET, RESET);
	w.TestInstruction(0x09);
	assert(w.HL() == 0x1313);

	w.PrepareTest(NO_INPUT);
	w.Write16BitReg(w.H(), w.L(), 0xff00);
	w.Write16BitReg(w.B(), w.C(), 0x00ff);
	w.ExpectFlags(IGNORE, RESET, RESET, RESET);
	w.TestInstruction(0x09);
	assert(w.HL() == 0xffff);

	w.PrepareTest(NO_INPUT);
	w.Write16BitReg(w.H(), w.L(), 0xaaaa);
	w.Write16BitReg(w.B(), w.C(), 0x7777);
	w.ExpectFlags(IGNORE, RESET, SET, SET);
	w.TestInstruction(0x09);
	assert(w.HL() == 0x2221);

	w.PrepareTest(NO_INPUT);
	w.Write16BitReg(w.H(), w.L(), 0xffff);
	w.Write16BitReg(w.B(), w.C(), 0x0001);
	w.ExpectFlags(IGNORE, RESET, SET, SET);
	w.TestInstruction(0x09);
	assert(w.HL() == 0x0000);

	w.PrepareTest(NO_INPUT);
	w.Write16BitReg(w.H(), w.L(), 0x12ff);
	w.Write16BitReg(w.B(), w.C(), 0x0001);
	w.ExpectFlags(IGNORE, RESET, SET, RESET);
	w.TestInstruction(0x09);
	assert(w.HL() == 0x1300);
}

// LD A, (BC)
void CPUTestCases::TestOP0x0a()
{
	w.PrepareTest(IMM_8);
	w.Write16BitReg(w.B(), w.C(), CPUWrapper::EIGHT_BIT_READ_ADDRESS);
	w.TestInstruction(0x0a);
	assert(w.A() == w.ReadByte(w.BC()));
}

// DEC BC
void CPUTestCases::TestOP0x0b()
{
	w.PrepareTest(NO_INPUT);
	w.Write16BitReg(w.B(), w.C(), 0x0002);
	w.TestInstruction(0x0b);
	assert(w.BC() == 0x0001);

	w.PrepareTest(NO_INPUT);
	w.Write16BitReg(w.B(), w.C(), 0x0000);
	w.TestInstruction(0x0b);
	assert(w.BC() == 0xffff);

	w.PrepareTest(NO_INPUT);
	w.Write16BitReg(w.B(), w.C(), 0x0100);
	w.TestInstruction(0x0b);
	assert(w.BC() == 0x00ff);
}

// INC C
void CPUTestCases::TestOP0x0c()
{
	w.PrepareTest(NO_INPUT);
	w.C() = 0x00;
	w.ExpectFlags(RESET, RESET, RESET, IGNORE);
	w.TestInstruction(0x0c);
	assert(w.C() == 0x01);

	w.PrepareTest(NO_INPUT);
	w.C() = 0x0F;
	w.ExpectFlags(RESET, RESET, SET, IGNORE);
	w.TestInstruction(0x0c);
	assert(w.C() == 0x10);

	w.PrepareTest(NO_INPUT);
	w.C() = 0x2F;
	w.ExpectFlags(RESET, RESET, SET, IGNORE);
	w.TestInstruction(0x0c);
	assert(w.C() == 0x30);

	w.PrepareTest(NO_INPUT);
	w.C() = 0xFF;
	w.ExpectFlags(SET, RESET, SET, IGNORE);
	w.TestInstruction(0x0c);
	assert(w.C() == 0x00);
}

// DEC C
void CPUTestCases::TestOP0x0d()
{
	w.PrepareTest(NO_INPUT);
	w.C() = 0x02;
	w.ExpectFlags(RESET, SET, RESET, IGNORE);
	w.TestInstruction(0x0d);
	assert(w.C() == 0x01);

	w.PrepareTest(NO_INPUT);
	w.C() = 0x30;
	w.ExpectFlags(RESET, SET, SET, IGNORE);
	w.TestInstruction(0x0d);
	assert(w.C() == 0x2f);

	w.PrepareTest(NO_INPUT);
	w.C() = 0x01;
	w.ExpectFlags(SET, SET, RESET, IGNORE);
	w.TestInstruction(0x0d);
	assert(w.C() == 0x00);
}

// LD C, imm8
void CPUTestCases::TestOP0x0e()
{
	w.PrepareTest(IMM_8);
	w.TestInstruction(0x0e);
	assert(w.C() == w.LastImm8Arg());
}

// RRCA
void CPUTestCases::TestOP0x0f()
{

}

// STOP 0
void CPUTestCases::TestOP0x10()
{

}

// LD DE, imm16
void CPUTestCases::TestOP0x11()
{
	w.PrepareTest(IMM_16);
	w.TestInstruction(0x11);
	assert(w.DE() == w.LastImm16Arg());
}

// LD (DE), A
void CPUTestCases::TestOP0x12()
{
}

// INC DE
void CPUTestCases::TestOP0x13()
{
}

// INC D
void CPUTestCases::TestOP0x14()
{
	w.PrepareTest(NO_INPUT);
	w.D() = 0x00;
	w.ExpectFlags(RESET, RESET, RESET, IGNORE);
	w.TestInstruction(0x14);
	assert(w.D() == 0x01);

	w.PrepareTest(NO_INPUT);
	w.D() = 0x0F;
	w.ExpectFlags(RESET, RESET, SET, IGNORE);
	w.TestInstruction(0x14);
	assert(w.D() == 0x10);

	w.PrepareTest(NO_INPUT);
	w.D() = 0x2F;
	w.ExpectFlags(RESET, RESET, SET, IGNORE);
	w.TestInstruction(0x14);
	assert(w.D() == 0x30);

	w.PrepareTest(NO_INPUT);
	w.D() = 0xFF;
	w.ExpectFlags(SET, RESET, SET, IGNORE);
	w.TestInstruction(0x14);
	assert(w.D() == 0x00);
}

// DEC D
void CPUTestCases::TestOP0x15()
{
}

// LD D, imm8
void CPUTestCases::TestOP0x16()
{
}

// RLA
void CPUTestCases::TestOP0x17()
{
}

// JR S-imm8
void CPUTestCases::TestOP0x18()
{
}

// ADD HL, DE
void CPUTestCases::TestOP0x19()
{
}

// LD A, (DE)
void CPUTestCases::TestOP0x1a()
{
}

// DEC DE
void CPUTestCases::TestOP0x1b()
{
}

// INC E
void CPUTestCases::TestOP0x1c()
{
	w.PrepareTest(NO_INPUT);
	w.E() = 0x00;
	w.ExpectFlags(RESET, RESET, RESET, IGNORE);
	w.TestInstruction(0x1c);
	assert(w.E() == 0x01);

	w.PrepareTest(NO_INPUT);
	w.E() = 0x0F;
	w.ExpectFlags(RESET, RESET, SET, IGNORE);
	w.TestInstruction(0x1c);
	assert(w.E() == 0x10);

	w.PrepareTest(NO_INPUT);
	w.E() = 0x2F;
	w.ExpectFlags(RESET, RESET, SET, IGNORE);
	w.TestInstruction(0x1c);
	assert(w.E() == 0x30);

	w.PrepareTest(NO_INPUT);
	w.E() = 0xFF;
	w.ExpectFlags(SET, RESET, SET, IGNORE);
	w.TestInstruction(0x1c);
	assert(w.E() == 0x00);
}

// DEC E
void CPUTestCases::TestOP0x1d()
{
}

// LD E, imm8
void CPUTestCases::TestOP0x1e()
{
}

// RRA
void CPUTestCases::TestOP0x1f()
{
	w.PrepareTest(NO_INPUT);
	w.A() = 0x02;
	w.SetFlags(1, 1, 1, 1);
	w.ExpectFlags(RESET, RESET, RESET, RESET);
	w.TestInstruction(0x1f);
	assert(w.A() == B8(10000001));

	w.PrepareTest(NO_INPUT);
	w.A() = 0x01;
	w.SetAllFlags(1);
	w.ExpectFlags(RESET, RESET, RESET, SET);
	w.TestInstruction(0x1f);
	assert(w.A() == B8(10000000));

	w.PrepareTest(NO_INPUT);
	w.A() = 0xff;
	w.ExpectFlags(RESET, RESET, RESET, SET);
	w.TestInstruction(0x1f);
	assert(w.A() == B8(01111111));

	w.PrepareTest(NO_INPUT);
	w.A() = 0xff;
	w.SetAllFlags(1);
	w.ExpectFlags(RESET, RESET, RESET, SET);
	w.TestInstruction(0x1f);
	assert(w.A() == 0xff);
}

// JR NZ, S-imm8
void CPUTestCases::TestOP0x20()
{
}

// LD HL, imm16
void CPUTestCases::TestOP0x21()
{
}

// LD (HL+), A
void CPUTestCases::TestOP0x22()
{
}

// INC HL
void CPUTestCases::TestOP0x23()
{
}

// INC H
void CPUTestCases::TestOP0x24()
{
	w.PrepareTest(NO_INPUT);
	w.H() = 0x00;
	w.ExpectFlags(RESET, RESET, RESET, IGNORE);
	w.TestInstruction(0x24);
	assert(w.H() == 0x01);

	w.PrepareTest(NO_INPUT);
	w.H() = 0x0F;
	w.ExpectFlags(RESET, RESET, SET, IGNORE);
	w.TestInstruction(0x24);
	assert(w.H() == 0x10);

	w.PrepareTest(NO_INPUT);
	w.H() = 0x2F;
	w.ExpectFlags(RESET, RESET, SET, IGNORE);
	w.TestInstruction(0x24);
	assert(w.H() == 0x30);

	w.PrepareTest(NO_INPUT);
	w.H() = 0xFF;
	w.ExpectFlags(SET, RESET, SET, IGNORE);
	w.TestInstruction(0x24);
	assert(w.H() == 0x00);
}

// DEC H
void CPUTestCases::TestOP0x25()
{
}

// LD H, imm8
void CPUTestCases::TestOP0x26()
{
}

// DAA
void CPUTestCases::TestOP0x27()
{
}

// JR Z, S-imm8
void CPUTestCases::TestOP0x28()
{
}

// ADD HL, HL
void CPUTestCases::TestOP0x29()
{
}

// LD A, (HL+)
void CPUTestCases::TestOP0x2a()
{
}

// DEC HL
void CPUTestCases::TestOP0x2b()
{
}

// INC L
void CPUTestCases::TestOP0x2c()
{
	w.PrepareTest(NO_INPUT);
	w.L() = 0x00;
	w.ExpectFlags(RESET, RESET, RESET, IGNORE);
	w.TestInstruction(0x2c);
	assert(w.L() == 0x01);

	w.PrepareTest(NO_INPUT);
	w.L() = 0x0F;
	w.ExpectFlags(RESET, RESET, SET, IGNORE);
	w.TestInstruction(0x2c);
	assert(w.L() == 0x10);

	w.PrepareTest(NO_INPUT);
	w.L() = 0x2F;
	w.ExpectFlags(RESET, RESET, SET, IGNORE);
	w.TestInstruction(0x2c);
	assert(w.L() == 0x30);

	w.PrepareTest(NO_INPUT);
	w.L() = 0xFF;
	w.ExpectFlags(SET, RESET, SET, IGNORE);
	w.TestInstruction(0x2c);
	assert(w.L() == 0x00);
}

// DEC L
void CPUTestCases::TestOP0x2d()
{
}

// LD L, imm8
void CPUTestCases::TestOP0x2e()
{
}

// CPL
void CPUTestCases::TestOP0x2f()
{
}

// JR NC, S-imm8
void CPUTestCases::TestOP0x30()
{
}

// LD SP, imm16
void CPUTestCases::TestOP0x31()
{
}

// LD (HL-), A
void CPUTestCases::TestOP0x32()
{
}

// INC SP
void CPUTestCases::TestOP0x33()
{
}

// INC (HL)
void CPUTestCases::TestOP0x34()
{
}

// DEC (HL)
void CPUTestCases::TestOP0x35()
{
}

// LD (HL), imm8
void CPUTestCases::TestOP0x36()
{
}

// SCF
void CPUTestCases::TestOP0x37()
{
}

// JR C, S-imm8
void CPUTestCases::TestOP0x38()
{
}

// LD HL, SP
void CPUTestCases::TestOP0x39()
{
}

// LD A, (HL-)
void CPUTestCases::TestOP0x3a()
{
}

// DEC SP
void CPUTestCases::TestOP0x3b()
{
}

// INC A
void CPUTestCases::TestOP0x3c()
{
}

// DEC A
void CPUTestCases::TestOP0x3d()
{
}

// LD A, imm8
void CPUTestCases::TestOP0x3e()
{
}

// CCF
void CPUTestCases::TestOP0x3f()
{
}

// LD B, B
void CPUTestCases::TestOP0x40()
{
}

// LD B, C
void CPUTestCases::TestOP0x41()
{
}

// LD B, D
void CPUTestCases::TestOP0x42()
{
}

// LD B, E
void CPUTestCases::TestOP0x43()
{
}

// LD B, H
void CPUTestCases::TestOP0x44()
{
}

// LD B, L
void CPUTestCases::TestOP0x45()
{
}

// LD B, (HL)
void CPUTestCases::TestOP0x46()
{
}

// LD B, A
void CPUTestCases::TestOP0x47()
{
}

// LD C, B
void CPUTestCases::TestOP0x48()
{
}

// LD C, C
void CPUTestCases::TestOP0x49()
{
}

// LD C, D
void CPUTestCases::TestOP0x4a()
{
}

// LD C, E
void CPUTestCases::TestOP0x4b()
{
}

// LD C, H
void CPUTestCases::TestOP0x4c()
{
}

// LD C, L
void CPUTestCases::TestOP0x4d()
{
}

// LD C, (HL)
void CPUTestCases::TestOP0x4e()
{
}

// LD C, A
void CPUTestCases::TestOP0x4f()
{
}

// LD D, B
void CPUTestCases::TestOP0x50()
{
}

// LD D, C
void CPUTestCases::TestOP0x51()
{
}

// LD D, D
void CPUTestCases::TestOP0x52()
{
}

// LD D, E
void CPUTestCases::TestOP0x53()
{
}

// LD D, H
void CPUTestCases::TestOP0x54()
{
}

// LD D, L
void CPUTestCases::TestOP0x55()
{
}

// LD D, (HL)
void CPUTestCases::TestOP0x56()
{
}

// LD D, A
void CPUTestCases::TestOP0x57()
{
}

// LD E, B
void CPUTestCases::TestOP0x58()
{
}

// LD E, C
void CPUTestCases::TestOP0x59()
{
}

// LD E, D
void CPUTestCases::TestOP0x5a()
{
}

// LD E, E
void CPUTestCases::TestOP0x5b()
{
}

// LD E, H
void CPUTestCases::TestOP0x5c()
{
}

// LD E, L
void CPUTestCases::TestOP0x5d()
{
}

// LD E, (HL)
void CPUTestCases::TestOP0x5e()
{
}

// LD E, A
void CPUTestCases::TestOP0x5f()
{
}

// LD H, B
void CPUTestCases::TestOP0x60()
{
}

// LD H, C
void CPUTestCases::TestOP0x61()
{
}

// LD H, D
void CPUTestCases::TestOP0x62()
{
}

// LD H, E
void CPUTestCases::TestOP0x63()
{
}

// LD H, H
void CPUTestCases::TestOP0x64()
{
}

// LD H, L
void CPUTestCases::TestOP0x65()
{
}

// LD H, (HL)
void CPUTestCases::TestOP0x66()
{
}

// LD H, A
void CPUTestCases::TestOP0x67()
{
}

// LD L, B
void CPUTestCases::TestOP0x68()
{
}

// LD L, C
void CPUTestCases::TestOP0x69()
{
}

// LD L, D
void CPUTestCases::TestOP0x6a()
{
}

// LD L, E
void CPUTestCases::TestOP0x6b()
{
}

// LD L, H
void CPUTestCases::TestOP0x6c()
{
}

// LD L, L
void CPUTestCases::TestOP0x6d()
{
}

// LD L, (HL)
void CPUTestCases::TestOP0x6e()
{
}

// LD L, A
void CPUTestCases::TestOP0x6f()
{
}

// LD (HL), B
void CPUTestCases::TestOP0x70()
{
}

// LD (HL), C
void CPUTestCases::TestOP0x71()
{
}

// LD (HL), D
void CPUTestCases::TestOP0x72()
{
}

// LD (HL), E
void CPUTestCases::TestOP0x73()
{
}

// LD (HL), H
void CPUTestCases::TestOP0x74()
{
}

// LD (HL), L
void CPUTestCases::TestOP0x75()
{
}

// HALT
void CPUTestCases::TestOP0x76()
{
}

// LD (HL), A
void CPUTestCases::TestOP0x77()
{
}

// LD A, B
void CPUTestCases::TestOP0x78()
{
}

// LD A, C
void CPUTestCases::TestOP0x79()
{
}

// LD A, D
void CPUTestCases::TestOP0x7a()
{
}

// LD A, E
void CPUTestCases::TestOP0x7b()
{
}

// LD A, H
void CPUTestCases::TestOP0x7c()
{
}

// LD A, L
void CPUTestCases::TestOP0x7d()
{
}

// LD A, (HL)
void CPUTestCases::TestOP0x7e()
{
}

// LD A, A
void CPUTestCases::TestOP0x7f()
{
}

// ADD A, B
void CPUTestCases::TestOP0x80()
{
}

// ADD A, C
void CPUTestCases::TestOP0x81()
{
}

// ADD A, D
void CPUTestCases::TestOP0x82()
{
}

// ADD A, E
void CPUTestCases::TestOP0x83()
{
}

// ADD A, H
void CPUTestCases::TestOP0x84()
{
}

// ADD A, L
void CPUTestCases::TestOP0x85()
{
}

// ADD A, (HL)
void CPUTestCases::TestOP0x86()
{
}

// ADD A, A
void CPUTestCases::TestOP0x87()
{
}

// ADC A, B
void CPUTestCases::TestOP0x88()
{
}

// ADC A, C
void CPUTestCases::TestOP0x89()
{
}

// ADC A, D
void CPUTestCases::TestOP0x8a()
{
}

// ADC A, E
void CPUTestCases::TestOP0x8b()
{
}

// ADC A, H
void CPUTestCases::TestOP0x8c()
{
}

// ADC A, L
void CPUTestCases::TestOP0x8d()
{
}

// ADC A, (HL)
void CPUTestCases::TestOP0x8e()
{
}

// ADC A, A
void CPUTestCases::TestOP0x8f()
{
}

// SUB B
void CPUTestCases::TestOP0x90()
{
}

// SUB C
void CPUTestCases::TestOP0x91()
{
}

// SUB D
void CPUTestCases::TestOP0x92()
{
}

// SUB E
void CPUTestCases::TestOP0x93()
{
}

// SUB H
void CPUTestCases::TestOP0x94()
{
}

// SUB L
void CPUTestCases::TestOP0x95()
{
}

// SUB (HL)
void CPUTestCases::TestOP0x96()
{
}

// SUB A
void CPUTestCases::TestOP0x97()
{
}

// SBC A, B
void CPUTestCases::TestOP0x98()
{
}

// SBC A, C
void CPUTestCases::TestOP0x99()
{
}

// SBC A, D
void CPUTestCases::TestOP0x9a()
{
}

// SBC A, E
void CPUTestCases::TestOP0x9b()
{
}

// SBC A, H
void CPUTestCases::TestOP0x9c()
{
}

// SBC A, L
void CPUTestCases::TestOP0x9d()
{
}

// SUB A, (HL)
void CPUTestCases::TestOP0x9e()
{
}

// SBC A, A
void CPUTestCases::TestOP0x9f()
{
}

// AND B
void CPUTestCases::TestOP0xa0()
{
}

// AND C
void CPUTestCases::TestOP0xa1()
{
}

// AND D
void CPUTestCases::TestOP0xa2()
{
}

// AND E
void CPUTestCases::TestOP0xa3()
{
}

// AND H
void CPUTestCases::TestOP0xa4()
{
}

// AND L
void CPUTestCases::TestOP0xa5()
{
}

// AND (HL)
void CPUTestCases::TestOP0xa6()
{
}

// AND A
void CPUTestCases::TestOP0xa7()
{
}

// XOR B
void CPUTestCases::TestOP0xa8()
{
}

// XOR C
void CPUTestCases::TestOP0xa9()
{
}

// XOR D
void CPUTestCases::TestOP0xaa()
{
}

// XOR E
void CPUTestCases::TestOP0xab()
{
}

// XOR H
void CPUTestCases::TestOP0xac()
{
}

// XOR L
void CPUTestCases::TestOP0xad()
{
}

// XOR (HL)
void CPUTestCases::TestOP0xae()
{
}

// XOR A
void CPUTestCases::TestOP0xaf()
{
}

// OR B
void CPUTestCases::TestOP0xb0()
{
}

// OR C
void CPUTestCases::TestOP0xb1()
{
}

// OR D
void CPUTestCases::TestOP0xb2()
{
}

// OR E
void CPUTestCases::TestOP0xb3()
{
}

// OR H
void CPUTestCases::TestOP0xb4()
{
}

// OR L
void CPUTestCases::TestOP0xb5()
{
}

// OR (HL)
void CPUTestCases::TestOP0xb6()
{
}

// OR A
void CPUTestCases::TestOP0xb7()
{
}

// CP B
void CPUTestCases::TestOP0xb8()
{
}

// CP C
void CPUTestCases::TestOP0xb9()
{
}

// CP D
void CPUTestCases::TestOP0xba()
{
}

// CP E
void CPUTestCases::TestOP0xbb()
{
}

// CP H
void CPUTestCases::TestOP0xbc()
{
}

// CP L
void CPUTestCases::TestOP0xbd()
{
}

// CP (HL)
void CPUTestCases::TestOP0xbe()
{
}

// CP A
void CPUTestCases::TestOP0xbf()
{
}

// RET NZ
void CPUTestCases::TestOP0xc0()
{
}

// POP BC
void CPUTestCases::TestOP0xc1()
{
}

// JP NZ, imm16
void CPUTestCases::TestOP0xc2()
{
}

// JP imm16
void CPUTestCases::TestOP0xc3()
{
}

// CALL NZ, imm16
void CPUTestCases::TestOP0xc4()
{
}

// PUSH BC
void CPUTestCases::TestOP0xc5()
{
}

// ADD A, imm8
void CPUTestCases::TestOP0xc6()
{
}

// RST 0x00
void CPUTestCases::TestOP0xc7()
{
}

// RET Z
void CPUTestCases::TestOP0xc8()
{
}

// RET
void CPUTestCases::TestOP0xc9()
{
}

// JP Z, imm16
void CPUTestCases::TestOP0xca()
{
}

// PREFIX CB
void CPUTestCases::TestOP0xcb()
{
}

// CALL Z, imm16
void CPUTestCases::TestOP0xcc()
{
}

// CALL imm16
void CPUTestCases::TestOP0xcd()
{
}

// ADC A, imm8
void CPUTestCases::TestOP0xce()
{
	w.PrepareTest(IMM_8);
	w.A() = 0x01;
	w.SetImm8TestVal(0x01);
	w.ExpectAllFlags(RESET);
	w.TestInstruction(0xce);
	assert(w.A() == 0x02);

	w.PrepareTest(IMM_8);
	w.A() = 0xfe;
	w.SetImm8TestVal(0x01);
	w.SetFlags(0, 0, 0, 1);
	w.ExpectFlags(SET, RESET, SET, SET);
	w.TestInstruction(0xce);
	assert(w.A() == 0x00);

	w.PrepareTest(IMM_8);
	w.A() = 0x0d;
	w.SetImm8TestVal(0x02);
	w.SetFlags(0, 0, 0, 1);
	w.ExpectFlags(RESET, RESET, SET, RESET);
	w.TestInstruction(0xce);
	assert(w.A() == 0x10);
}

// RST 0x08
void CPUTestCases::TestOP0xcf()
{
}

// RET NC
void CPUTestCases::TestOP0xd0()
{
}

// POP DE
void CPUTestCases::TestOP0xd1()
{
}

// JP NC, imm16
void CPUTestCases::TestOP0xd2()
{
}

// NO INSTRUCTION
void CPUTestCases::TestOP0xd3()
{
}

// CALL NC, imm16
void CPUTestCases::TestOP0xd4()
{
}

// PUSH DE
void CPUTestCases::TestOP0xd5()
{
}

// SUB imm8
void CPUTestCases::TestOP0xd6()
{
}

// RST 0x10
void CPUTestCases::TestOP0xd7()
{
}

// RET C
void CPUTestCases::TestOP0xd8()
{
}

// RETI
void CPUTestCases::TestOP0xd9()
{
}

// JP C, imm16
void CPUTestCases::TestOP0xda()
{
}

// NO INSTRUCTION
void CPUTestCases::TestOP0xdb()
{
}

// CALL C, imm16
void CPUTestCases::TestOP0xdc()
{
}

// NO INSTRUCTION
void CPUTestCases::TestOP0xdd()
{
}

// SBC A, imm8
void CPUTestCases::TestOP0xde()
{
}

// RST 0x018
void CPUTestCases::TestOP0xdf()
{
}

// LDH (imm8), A
void CPUTestCases::TestOP0xe0()
{
}

// POP HL
void CPUTestCases::TestOP0xe1()
{
}

// LD (C), A
void CPUTestCases::TestOP0xe2()
{
}

// NO INSTRUCTION
void CPUTestCases::TestOP0xe3()
{
}

// NO INSTRUCTION
void CPUTestCases::TestOP0xe4()
{
}

// PUSH HL
void CPUTestCases::TestOP0xe5()
{
}

// AND imm8
void CPUTestCases::TestOP0xe6()
{
}

// RST 0x020
void CPUTestCases::TestOP0xe7()
{
}

// ADD SP, S-imm8
void CPUTestCases::TestOP0xe8()
{
}

// JP (HL)
void CPUTestCases::TestOP0xe9()
{
}

// LD (imm16), A
void CPUTestCases::TestOP0xea()
{
}

// NO INSTRUCTION
void CPUTestCases::TestOP0xeb()
{
}

// NO INSTRUCTION
void CPUTestCases::TestOP0xec()
{
}

// NO INSTRUCTION
void CPUTestCases::TestOP0xed()
{
}

// XOR imm8
void CPUTestCases::TestOP0xee()
{
}

// RST 0x028
void CPUTestCases::TestOP0xef()
{
}

// LDH A, (imm8)
void CPUTestCases::TestOP0xf0()
{
}

// POP AF
void CPUTestCases::TestOP0xf1()
{
}

// LD A, (C)
void CPUTestCases::TestOP0xf2()
{
}

// DI
void CPUTestCases::TestOP0xf3()
{
}

// NO INSTRUCTION
void CPUTestCases::TestOP0xf4()
{
}

// PUSH AF
void CPUTestCases::TestOP0xf5()
{
}

// OR imm8
void CPUTestCases::TestOP0xf6()
{
}

// RST 0x30
void CPUTestCases::TestOP0xf7()
{
}

// LD HL, SP + S-imm8
void CPUTestCases::TestOP0xf8()
{
}

// LD SP, HL
void CPUTestCases::TestOP0xf9()
{
}

// LD A, (imm16)
void CPUTestCases::TestOP0xfa()
{
}

// EI
void CPUTestCases::TestOP0xfb()
{
}

// NO INSTRUCTION
void CPUTestCases::TestOP0xfc()
{
}

// NO INSTRUCTION
void CPUTestCases::TestOP0xfd()
{
}

// CP imm8
void CPUTestCases::TestOP0xfe()
{
}

// RST 0x38
void CPUTestCases::TestOP0xff()
{
}

// RLC B
void CPUTestCases::TestOP0x100()
{
}

// RLC C
void CPUTestCases::TestOP0x101()
{
}

// RLC D
void CPUTestCases::TestOP0x102()
{
}

// RLC E
void CPUTestCases::TestOP0x103()
{
}

// RLC H
void CPUTestCases::TestOP0x104()
{
}

// RLC L
void CPUTestCases::TestOP0x105()
{
}

// RLC (HL)
void CPUTestCases::TestOP0x106()
{
}

// RLC A
void CPUTestCases::TestOP0x107()
{
}

// RRC B
void CPUTestCases::TestOP0x108()
{
}

// RRC C
void CPUTestCases::TestOP0x109()
{
}

// RRC D
void CPUTestCases::TestOP0x10a()
{
}

// RRC E
void CPUTestCases::TestOP0x10b()
{
}

// RRC H
void CPUTestCases::TestOP0x10c()
{
}

// RRC L
void CPUTestCases::TestOP0x10d()
{
}

// RRC (HL)
void CPUTestCases::TestOP0x10e()
{
}

// RRC A
void CPUTestCases::TestOP0x10f()
{
}

// RL B
void CPUTestCases::TestOP0x110()
{
}

// RL C
void CPUTestCases::TestOP0x111()
{
}

// RL D
void CPUTestCases::TestOP0x112()
{
}

// RL E
void CPUTestCases::TestOP0x113()
{
}

// RL H
void CPUTestCases::TestOP0x114()
{
}

// RL L
void CPUTestCases::TestOP0x115()
{
}

// RL (HL)
void CPUTestCases::TestOP0x116()
{
}

// RL A
void CPUTestCases::TestOP0x117()
{
}

// RR B
void CPUTestCases::TestOP0x118()
{
}

// RR C
void CPUTestCases::TestOP0x119()
{
	w.PrepareTest(NO_INPUT);
	w.C() = 0x02;
	w.SetFlags(1, 1, 1, 1);
	w.ExpectFlags(RESET, RESET, RESET, RESET);
	w.TestInstruction(0x119);
	assert(w.C() == B8(10000001));

	w.PrepareTest(NO_INPUT);
	w.C() = 0x01;
	w.SetAllFlags(1);
	w.ExpectFlags(RESET, RESET, RESET, SET);
	w.TestInstruction(0x119);
	assert(w.C() == B8(10000000));

	w.PrepareTest(NO_INPUT);
	w.C() = 0xff;
	w.ExpectFlags(RESET, RESET, RESET, SET);
	w.TestInstruction(0x119);
	assert(w.C() == B8(01111111));

	w.PrepareTest(NO_INPUT);
	w.C() = 0xff;
	w.SetAllFlags(1);
	w.ExpectFlags(RESET, RESET, RESET, SET);
	w.TestInstruction(0x119);
	assert(w.C() == 0xff);
}

// RR D
void CPUTestCases::TestOP0x11a()
{
	w.PrepareTest(NO_INPUT);
	w.D() = 0x02;
	w.SetFlags(1, 1, 1, 1);
	w.ExpectFlags(RESET, RESET, RESET, RESET);
	w.TestInstruction(0x11a);
	assert(w.D() == B8(10000001));

	w.PrepareTest(NO_INPUT);
	w.D() = 0x01;
	w.SetAllFlags(1);
	w.ExpectFlags(RESET, RESET, RESET, SET);
	w.TestInstruction(0x11a);
	assert(w.D() == B8(10000000));

	w.PrepareTest(NO_INPUT);
	w.D() = 0xff;
	w.ExpectFlags(RESET, RESET, RESET, SET);
	w.TestInstruction(0x11a);
	assert(w.D() == B8(01111111));

	w.PrepareTest(NO_INPUT);
	w.D() = 0xff;
	w.SetAllFlags(1);
	w.ExpectFlags(RESET, RESET, RESET, SET);
	w.TestInstruction(0x11a);
	assert(w.D() == 0xff);
}

// RR E
void CPUTestCases::TestOP0x11b()
{
}

// RR H
void CPUTestCases::TestOP0x11c()
{
}

// RR L
void CPUTestCases::TestOP0x11d()
{
}

// RR (HL)
void CPUTestCases::TestOP0x11e()
{
}

// RR A
void CPUTestCases::TestOP0x11f()
{
}

// SLA B
void CPUTestCases::TestOP0x120()
{
}

// SLA C
void CPUTestCases::TestOP0x121()
{
}

// SLA D
void CPUTestCases::TestOP0x122()
{
}

// SLA E
void CPUTestCases::TestOP0x123()
{
}

// SLA H
void CPUTestCases::TestOP0x124()
{
}

// SLA L
void CPUTestCases::TestOP0x125()
{
}

// SLA (HL)
void CPUTestCases::TestOP0x126()
{
}

// SLA A
void CPUTestCases::TestOP0x127()
{
}

// SRA B
void CPUTestCases::TestOP0x128()
{
}

// SRA C
void CPUTestCases::TestOP0x129()
{
}

// SRA D
void CPUTestCases::TestOP0x12a()
{
}

// SRA E
void CPUTestCases::TestOP0x12b()
{
}

// SRA H
void CPUTestCases::TestOP0x12c()
{
}

// SRA L
void CPUTestCases::TestOP0x12d()
{
}

// SRA (HL)
void CPUTestCases::TestOP0x12e()
{
}

// SRA A
void CPUTestCases::TestOP0x12f()
{
}

// SWAP B
void CPUTestCases::TestOP0x130()
{
}

// SWAP C
void CPUTestCases::TestOP0x131()
{
}

// SWAP D
void CPUTestCases::TestOP0x132()
{
}

// SWAP E
void CPUTestCases::TestOP0x133()
{
}

// SWAP H
void CPUTestCases::TestOP0x134()
{
}

// SWAP L
void CPUTestCases::TestOP0x135()
{
}

// SWAP (HL)
void CPUTestCases::TestOP0x136()
{
}

// SWAP A
void CPUTestCases::TestOP0x137()
{
}

// SRL B
void CPUTestCases::TestOP0x138()
{
	w.PrepareTest(NO_INPUT);
	w.B() = 0x01;
	w.ExpectFlags(SET, RESET, RESET, SET);
	w.TestInstruction(0x138);
	assert(w.B() == 0);

	w.PrepareTest(NO_INPUT);
	w.B() = 0xff;
	w.ExpectFlags(RESET, RESET, RESET, SET);
	w.TestInstruction(0x138);
	assert(w.B() == B8(01111111));
}

// SRL C
void CPUTestCases::TestOP0x139()
{
}

// SRL D
void CPUTestCases::TestOP0x13a()
{
}

// SRL E
void CPUTestCases::TestOP0x13b()
{
}

// SRL H
void CPUTestCases::TestOP0x13c()
{
}

// SRL L
void CPUTestCases::TestOP0x13d()
{
}

// SRL (HL)
void CPUTestCases::TestOP0x13e()
{
}

// SRL A
void CPUTestCases::TestOP0x13f()
{
}

// BIT 0 B
void CPUTestCases::TestOP0x140()
{
}

// BIT 0 C
void CPUTestCases::TestOP0x141()
{
}

// BIT 0 D
void CPUTestCases::TestOP0x142()
{
}

// BIT 0 E
void CPUTestCases::TestOP0x143()
{
}

// BIT 0 H
void CPUTestCases::TestOP0x144()
{
}

// BIT 0 L
void CPUTestCases::TestOP0x145()
{
}

// BIT 0 (HL)
void CPUTestCases::TestOP0x146()
{
}

// BIT 0 A
void CPUTestCases::TestOP0x147()
{
}

// BIT 1 B
void CPUTestCases::TestOP0x148()
{
}

// BIT 1 C
void CPUTestCases::TestOP0x149()
{
}

// BIT 1 D
void CPUTestCases::TestOP0x14a()
{
}

// BIT 1 E
void CPUTestCases::TestOP0x14b()
{
}

// BIT 1 H
void CPUTestCases::TestOP0x14c()
{
}

// BIT 1 L
void CPUTestCases::TestOP0x14d()
{
}

// BIT 1 (HL)
void CPUTestCases::TestOP0x14e()
{
}

// BIT 1 A
void CPUTestCases::TestOP0x14f()
{
}

// BIT 2 B
void CPUTestCases::TestOP0x150()
{
}

// BIT 2 C
void CPUTestCases::TestOP0x151()
{
}

// BIT 2 D
void CPUTestCases::TestOP0x152()
{
}

// BIT 2 E
void CPUTestCases::TestOP0x153()
{
}

// BIT 2 H
void CPUTestCases::TestOP0x154()
{
}

// BIT 2 L
void CPUTestCases::TestOP0x155()
{
}

// BIT 2 (HL)
void CPUTestCases::TestOP0x156()
{
}

// BIT 2 A
void CPUTestCases::TestOP0x157()
{
}

// BIT 3 B
void CPUTestCases::TestOP0x158()
{
}

// BIT 3 C
void CPUTestCases::TestOP0x159()
{
}

// BIT 3 D
void CPUTestCases::TestOP0x15a()
{
}

// BIT 3 E
void CPUTestCases::TestOP0x15b()
{
}

// BIT 3 H
void CPUTestCases::TestOP0x15c()
{
}

// BIT 3 L
void CPUTestCases::TestOP0x15d()
{
}

// BIT 3 (HL)
void CPUTestCases::TestOP0x15e()
{
}

// BIT 3 A
void CPUTestCases::TestOP0x15f()
{
}

// BIT 4 B
void CPUTestCases::TestOP0x160()
{
}

// BIT 4 C
void CPUTestCases::TestOP0x161()
{
}

// BIT 4 D
void CPUTestCases::TestOP0x162()
{
}

// BIT 4 E
void CPUTestCases::TestOP0x163()
{
}

// BIT 4 H
void CPUTestCases::TestOP0x164()
{
}

// BIT 4 L
void CPUTestCases::TestOP0x165()
{
}

// BIT 4 (HL)
void CPUTestCases::TestOP0x166()
{
}

// BIT 4 A
void CPUTestCases::TestOP0x167()
{
}

// BIT 5 B
void CPUTestCases::TestOP0x168()
{
}

// BIT 5 C
void CPUTestCases::TestOP0x169()
{
}

// BIT 5 D
void CPUTestCases::TestOP0x16a()
{
}

// BIT 5 E
void CPUTestCases::TestOP0x16b()
{
}

// BIT 5 H
void CPUTestCases::TestOP0x16c()
{
}

// BIT 5 L
void CPUTestCases::TestOP0x16d()
{
}

// BIT 5 (HL)
void CPUTestCases::TestOP0x16e()
{
}

// BIT 5 A
void CPUTestCases::TestOP0x16f()
{
}

// BIT 6 B
void CPUTestCases::TestOP0x170()
{
}

// BIT 6 C
void CPUTestCases::TestOP0x171()
{
}

// BIT 6 D
void CPUTestCases::TestOP0x172()
{
}

// BIT 6 E
void CPUTestCases::TestOP0x173()
{
}

// BIT 6 H
void CPUTestCases::TestOP0x174()
{
}

// BIT 6 L
void CPUTestCases::TestOP0x175()
{
}

// BIT 6 (HL)
void CPUTestCases::TestOP0x176()
{
}

// BIT 6 A
void CPUTestCases::TestOP0x177()
{
}

// BIT 7 B
void CPUTestCases::TestOP0x178()
{
}

// BIT 7 C
void CPUTestCases::TestOP0x179()
{
}

// BIT 7 D
void CPUTestCases::TestOP0x17a()
{
}

// BIT 7 E
void CPUTestCases::TestOP0x17b()
{
}

// BIT 7 H
void CPUTestCases::TestOP0x17c()
{
}

// BIT 7 L
void CPUTestCases::TestOP0x17d()
{
}

// BIT 7 (HL)
void CPUTestCases::TestOP0x17e()
{
}

// BIT 7 A
void CPUTestCases::TestOP0x17f()
{
}

// RES 0 B
void CPUTestCases::TestOP0x180()
{
}

// RES 0 C
void CPUTestCases::TestOP0x181()
{
}

// RES 0 D
void CPUTestCases::TestOP0x182()
{
}

// RES 0 E
void CPUTestCases::TestOP0x183()
{
}

// RES 0 H
void CPUTestCases::TestOP0x184()
{
}

// RES 0 L
void CPUTestCases::TestOP0x185()
{
}

// RES 0 (HL)
void CPUTestCases::TestOP0x186()
{
}

// RES 0 A
void CPUTestCases::TestOP0x187()
{
}

// RES 1 B
void CPUTestCases::TestOP0x188()
{
}

// RES 1 C
void CPUTestCases::TestOP0x189()
{
}

// RES 1 D
void CPUTestCases::TestOP0x18a()
{
}

// RES 1 E
void CPUTestCases::TestOP0x18b()
{
}

// RES 1 H
void CPUTestCases::TestOP0x18c()
{
}

// RES 1 L
void CPUTestCases::TestOP0x18d()
{
}

// RES 1 (HL)
void CPUTestCases::TestOP0x18e()
{
}

// RES 1 A
void CPUTestCases::TestOP0x18f()
{
}

// RES 2 B
void CPUTestCases::TestOP0x190()
{
}

// RES 2 C
void CPUTestCases::TestOP0x191()
{
}

// RES 2 D
void CPUTestCases::TestOP0x192()
{
}

// RES 2 E
void CPUTestCases::TestOP0x193()
{
}

// RES 2 H
void CPUTestCases::TestOP0x194()
{
}

// RES 2 L
void CPUTestCases::TestOP0x195()
{
}

// RES 2 (HL)
void CPUTestCases::TestOP0x196()
{
}

// RES 2 A
void CPUTestCases::TestOP0x197()
{
}

// RES 3 B
void CPUTestCases::TestOP0x198()
{
}

// RES 3 C
void CPUTestCases::TestOP0x199()
{
}

// RES 3 D
void CPUTestCases::TestOP0x19a()
{
}

// RES 3 E
void CPUTestCases::TestOP0x19b()
{
}

// RES 3 H
void CPUTestCases::TestOP0x19c()
{
}

// RES 3 L
void CPUTestCases::TestOP0x19d()
{
}

// RES 3 (HL)
void CPUTestCases::TestOP0x19e()
{
}

// RES 3 A
void CPUTestCases::TestOP0x19f()
{
}

// RES 4 B
void CPUTestCases::TestOP0x1a0()
{
}

// RES 4 C
void CPUTestCases::TestOP0x1a1()
{
}

// RES 4 D
void CPUTestCases::TestOP0x1a2()
{
}

// RES 4 E
void CPUTestCases::TestOP0x1a3()
{
}

// RES 4 H
void CPUTestCases::TestOP0x1a4()
{
}

// RES 4 L
void CPUTestCases::TestOP0x1a5()
{
}

// RES 4 (HL)
void CPUTestCases::TestOP0x1a6()
{
}

// RES 4 A
void CPUTestCases::TestOP0x1a7()
{
}

// RES 5 B
void CPUTestCases::TestOP0x1a8()
{
}

// RES 5 C
void CPUTestCases::TestOP0x1a9()
{
}

// RES 5 D
void CPUTestCases::TestOP0x1aa()
{
}

// RES 5 E
void CPUTestCases::TestOP0x1ab()
{
}

// RES 5 H
void CPUTestCases::TestOP0x1ac()
{
}

// RES 5 L
void CPUTestCases::TestOP0x1ad()
{
}

// RES 5 (HL)
void CPUTestCases::TestOP0x1ae()
{
}

// RES 5 A
void CPUTestCases::TestOP0x1af()
{
}

// RES 6 B
void CPUTestCases::TestOP0x1b0()
{
}

// RES 6 C
void CPUTestCases::TestOP0x1b1()
{
}

// RES 6 D
void CPUTestCases::TestOP0x1b2()
{
}

// RES 6 E
void CPUTestCases::TestOP0x1b3()
{
}

// RES 6 H
void CPUTestCases::TestOP0x1b4()
{
}

// RES 6 L
void CPUTestCases::TestOP0x1b5()
{
}

// RES 6 (HL)
void CPUTestCases::TestOP0x1b6()
{
}

// RES 6 A
void CPUTestCases::TestOP0x1b7()
{
}

// RES 7 B
void CPUTestCases::TestOP0x1b8()
{
}

// RES 7 C
void CPUTestCases::TestOP0x1b9()
{
}

// RES 7 D
void CPUTestCases::TestOP0x1ba()
{
}

// RES 7 E
void CPUTestCases::TestOP0x1bb()
{
}

// RES 7 H
void CPUTestCases::TestOP0x1bc()
{
}

// RES 7 L
void CPUTestCases::TestOP0x1bd()
{
}

// RES 7 (HL)
void CPUTestCases::TestOP0x1be()
{
}

// RES 7 A
void CPUTestCases::TestOP0x1bf()
{
}

// SET 0 B
void CPUTestCases::TestOP0x1c0()
{
}

// SET 0 C
void CPUTestCases::TestOP0x1c1()
{
}

// SET 0 D
void CPUTestCases::TestOP0x1c2()
{
}

// SET 0 E
void CPUTestCases::TestOP0x1c3()
{
}

// SET 0 H
void CPUTestCases::TestOP0x1c4()
{
}

// SET 0 L
void CPUTestCases::TestOP0x1c5()
{
}

// SET 0 (HL)
void CPUTestCases::TestOP0x1c6()
{
}

// SET 0 A
void CPUTestCases::TestOP0x1c7()
{
}

// SET 1 B
void CPUTestCases::TestOP0x1c8()
{
}

// SET 1 C
void CPUTestCases::TestOP0x1c9()
{
}

// SET 1 D
void CPUTestCases::TestOP0x1ca()
{
}

// SET 1 E
void CPUTestCases::TestOP0x1cb()
{
}

// SET 1 H
void CPUTestCases::TestOP0x1cc()
{
}

// SET 1 L
void CPUTestCases::TestOP0x1cd()
{
}

// SET 1 (HL)
void CPUTestCases::TestOP0x1ce()
{
}

// SET 1 A
void CPUTestCases::TestOP0x1cf()
{
}

// SET 2 B
void CPUTestCases::TestOP0x1d0()
{
}

// SET 2 C
void CPUTestCases::TestOP0x1d1()
{
}

// SET 2 D
void CPUTestCases::TestOP0x1d2()
{
}

// SET 2 E
void CPUTestCases::TestOP0x1d3()
{
}

// SET 2 H
void CPUTestCases::TestOP0x1d4()
{
}

// SET 2 L
void CPUTestCases::TestOP0x1d5()
{
}

// SET 2 (HL)
void CPUTestCases::TestOP0x1d6()
{
}

// SET 2 A
void CPUTestCases::TestOP0x1d7()
{
}

// SET 3 B
void CPUTestCases::TestOP0x1d8()
{
}

// SET 3 C
void CPUTestCases::TestOP0x1d9()
{
}

// SET 3 D
void CPUTestCases::TestOP0x1da()
{
}

// SET 3 E
void CPUTestCases::TestOP0x1db()
{
}

// SET 3 H
void CPUTestCases::TestOP0x1dc()
{
}

// SET 3 L
void CPUTestCases::TestOP0x1dd()
{
}

// SET 3 (HL)
void CPUTestCases::TestOP0x1de()
{
}

// SET 3 A
void CPUTestCases::TestOP0x1df()
{
}

// SET 4 B
void CPUTestCases::TestOP0x1e0()
{
}

// SET 4 C
void CPUTestCases::TestOP0x1e1()
{
}

// SET 4 D
void CPUTestCases::TestOP0x1e2()
{
}

// SET 4 E
void CPUTestCases::TestOP0x1e3()
{
}

// SET 4 H
void CPUTestCases::TestOP0x1e4()
{
}

// SET 4 L
void CPUTestCases::TestOP0x1e5()
{
}

// SET 4 (HL)
void CPUTestCases::TestOP0x1e6()
{
}

// SET 4 A
void CPUTestCases::TestOP0x1e7()
{
}

// SET 5 B
void CPUTestCases::TestOP0x1e8()
{
}

// SET 5 C
void CPUTestCases::TestOP0x1e9()
{
}

// SET 5 D
void CPUTestCases::TestOP0x1ea()
{
}

// SET 5 E
void CPUTestCases::TestOP0x1eb()
{
}

// SET 5 H
void CPUTestCases::TestOP0x1ec()
{
}

// SET 5 L
void CPUTestCases::TestOP0x1ed()
{
}

// SET 5 (HL)
void CPUTestCases::TestOP0x1ee()
{
}

// SET 5 A
void CPUTestCases::TestOP0x1ef()
{
}

// SET 6 B
void CPUTestCases::TestOP0x1f0()
{
}

// SET 6 C
void CPUTestCases::TestOP0x1f1()
{
}

// SET 6 D
void CPUTestCases::TestOP0x1f2()
{
}

// SET 6 E
void CPUTestCases::TestOP0x1f3()
{
}

// SET 6 H
void CPUTestCases::TestOP0x1f4()
{
}

// SET 6 L
void CPUTestCases::TestOP0x1f5()
{
}

// SET 6 (HL)
void CPUTestCases::TestOP0x1f6()
{
}

// SET 6 A
void CPUTestCases::TestOP0x1f7()
{
}

// SET 7 B
void CPUTestCases::TestOP0x1f8()
{
}

// SET 7 C
void CPUTestCases::TestOP0x1f9()
{
}

// SET 7 D
void CPUTestCases::TestOP0x1fa()
{
}

// SET 7 E
void CPUTestCases::TestOP0x1fb()
{
}

// SET 7 H
void CPUTestCases::TestOP0x1fc()
{
}

// SET 7 L
void CPUTestCases::TestOP0x1fd()
{
}

// SET 7 (HL)
void CPUTestCases::TestOP0x1fe()
{
}

// SET 7 A
void CPUTestCases::TestOP0x1ff()
{
}