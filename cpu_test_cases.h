#ifndef CPU_TEST_CASES_H
#define CPU_TEST_CASES_H

#include "cpu_wrapper.h"

class CPUTestCases
{
public:
	CPUTestCases();

	// NOP
	void TestOP0x00();

	// LD BC, imm16
	void TestOP0x01();

	// LD (BC), A
	void TestOP0x02();

	// INC BC
	void TestOP0x03();

	// INC B
	void TestOP0x04();

	// DEC B
	void TestOP0x05();

	// LD B, imm8
	void TestOP0x06();

	// RLCA
	void TestOP0x07();

	// LD (imm16), SP
	void TestOP0x08();

	// ADD HL, BC
	void TestOP0x09();

	// LD A, (BC)
	void TestOP0x0a();

	// DEC BC
	void TestOP0x0b();

	// INC C
	void TestOP0x0c();

	// DEC C
	void TestOP0x0d();

	// LD C, imm8
	void TestOP0x0e();

	// RRCA
	void TestOP0x0f();

	// STOP 0
	void TestOP0x10();

	// LD DE, imm16
	void TestOP0x11();

	// LD (DE), A
	void TestOP0x12();

	// INC DE
	void TestOP0x13();

	// INC D
	void TestOP0x14();

	// DEC D
	void TestOP0x15();

	// LD D, imm8
	void TestOP0x16();

	// RLA
	void TestOP0x17();

	// JR S-imm8
	void TestOP0x18();

	// ADD HL, DE
	void TestOP0x19();

	// LD A, (DE)
	void TestOP0x1a();

	// DEC DE
	void TestOP0x1b();

	// INC E
	void TestOP0x1c();

	// DEC E
	void TestOP0x1d();

	// LD E, imm8
	void TestOP0x1e();

	// RRA
	void TestOP0x1f();

	// JR NZ, S-imm8
	void TestOP0x20();

	// LD HL, imm16
	void TestOP0x21();

	// LD (HL+), A
	void TestOP0x22();

	// INC HL
	void TestOP0x23();

	// INC H
	void TestOP0x24();

	// DEC H
	void TestOP0x25();

	// LD H, imm8
	void TestOP0x26();

	// DAA
	void TestOP0x27();

	// JR Z, S-imm8
	void TestOP0x28();

	// ADD HL, HL
	void TestOP0x29();

	// LD A, (HL+)
	void TestOP0x2a();

	// DEC HL
	void TestOP0x2b();

	// INC L
	void TestOP0x2c();

	// DEC L
	void TestOP0x2d();

	// LD L, imm8
	void TestOP0x2e();

	// CPL
	void TestOP0x2f();

	// JR NC, S-imm8
	void TestOP0x30();

	// LD SP, imm16
	void TestOP0x31();

	// LD (HL-), A
	void TestOP0x32();

	// INC SP
	void TestOP0x33();

	// INC (HL)
	void TestOP0x34();

	// DEC (HL)
	void TestOP0x35();

	// LD (HL), imm8
	void TestOP0x36();

	// SCF
	void TestOP0x37();

	// JR C, S-imm8
	void TestOP0x38();

	// LD HL, SP
	void TestOP0x39();

	// LD A, (HL-)
	void TestOP0x3a();

	// DEC SP
	void TestOP0x3b();

	// INC A
	void TestOP0x3c();

	// DEC A
	void TestOP0x3d();

	// LD A, imm8
	void TestOP0x3e();

	// CCF
	void TestOP0x3f();

	// LD B, B
	void TestOP0x40();

	// LD B, C
	void TestOP0x41();

	// LD B, D
	void TestOP0x42();

	// LD B, E
	void TestOP0x43();

	// LD B, H
	void TestOP0x44();

	// LD B, L
	void TestOP0x45();

	// LD B, (HL)
	void TestOP0x46();

	// LD B, A
	void TestOP0x47();

	// LD C, B
	void TestOP0x48();

	// LD C, C
	void TestOP0x49();

	// LD C, D
	void TestOP0x4a();

	// LD C, E
	void TestOP0x4b();

	// LD C, H
	void TestOP0x4c();

	// LD C, L
	void TestOP0x4d();

	// LD C, (HL)
	void TestOP0x4e();

	// LD C, A
	void TestOP0x4f();

	// LD D, B
	void TestOP0x50();

	// LD D, C
	void TestOP0x51();

	// LD D, D
	void TestOP0x52();

	// LD D, E
	void TestOP0x53();

	// LD D, H
	void TestOP0x54();

	// LD D, L
	void TestOP0x55();

	// LD D, (HL)
	void TestOP0x56();

	// LD D, A
	void TestOP0x57();

	// LD E, B
	void TestOP0x58();

	// LD E, C
	void TestOP0x59();

	// LD E, D
	void TestOP0x5a();

	// LD E, E
	void TestOP0x5b();

	// LD E, H
	void TestOP0x5c();

	// LD E, L
	void TestOP0x5d();

	// LD E, (HL)
	void TestOP0x5e();

	// LD E, A
	void TestOP0x5f();

	// LD H, B
	void TestOP0x60();

	// LD H, C
	void TestOP0x61();

	// LD H, D
	void TestOP0x62();

	// LD H, E
	void TestOP0x63();

	// LD H, H
	void TestOP0x64();

	// LD H, L
	void TestOP0x65();

	// LD H, (HL)
	void TestOP0x66();

	// LD H, A
	void TestOP0x67();

	// LD L, B
	void TestOP0x68();

	// LD L, C
	void TestOP0x69();

	// LD L, D
	void TestOP0x6a();

	// LD L, E
	void TestOP0x6b();

	// LD L, H
	void TestOP0x6c();

	// LD L, L
	void TestOP0x6d();

	// LD L, (HL)
	void TestOP0x6e();

	// LD L, A
	void TestOP0x6f();

	// LD (HL), B
	void TestOP0x70();

	// LD (HL), C
	void TestOP0x71();

	// LD (HL), D
	void TestOP0x72();

	// LD (HL), E
	void TestOP0x73();

	// LD (HL), H
	void TestOP0x74();

	// LD (HL), L
	void TestOP0x75();

	// HALT
	void TestOP0x76();

	// LD (HL), A
	void TestOP0x77();

	// LD A, B
	void TestOP0x78();

	// LD A, C
	void TestOP0x79();

	// LD A, D
	void TestOP0x7a();

	// LD A, E
	void TestOP0x7b();

	// LD A, H
	void TestOP0x7c();

	// LD A, L
	void TestOP0x7d();

	// LD A, (HL)
	void TestOP0x7e();

	// LD A, A
	void TestOP0x7f();

	// ADD A, B
	void TestOP0x80();

	// ADD A, C
	void TestOP0x81();

	// ADD A, D
	void TestOP0x82();

	// ADD A, E
	void TestOP0x83();

	// ADD A, H
	void TestOP0x84();

	// ADD A, L
	void TestOP0x85();

	// ADD A, (HL)
	void TestOP0x86();

	// ADD A, A
	void TestOP0x87();

	// ADC A, B
	void TestOP0x88();

	// ADC A, C
	void TestOP0x89();

	// ADC A, D
	void TestOP0x8a();

	// ADC A, E
	void TestOP0x8b();

	// ADC A, H
	void TestOP0x8c();

	// ADC A, L
	void TestOP0x8d();

	// ADC A, (HL)
	void TestOP0x8e();

	// ADC A, A
	void TestOP0x8f();

	// SUB B
	void TestOP0x90();

	// SUB C
	void TestOP0x91();

	// SUB D
	void TestOP0x92();

	// SUB E
	void TestOP0x93();

	// SUB H
	void TestOP0x94();

	// SUB L
	void TestOP0x95();

	// SUB (HL)
	void TestOP0x96();

	// SUB A
	void TestOP0x97();

	// SBC A, B
	void TestOP0x98();

	// SBC A, C
	void TestOP0x99();

	// SBC A, D
	void TestOP0x9a();

	// SBC A, E
	void TestOP0x9b();

	// SBC A, H
	void TestOP0x9c();

	// SBC A, L
	void TestOP0x9d();

	// SUB A, (HL)
	void TestOP0x9e();

	// SBC A, A
	void TestOP0x9f();

	// AND B
	void TestOP0xa0();

	// AND C
	void TestOP0xa1();

	// AND D
	void TestOP0xa2();

	// AND E
	void TestOP0xa3();

	// AND H
	void TestOP0xa4();

	// AND L
	void TestOP0xa5();

	// AND (HL)
	void TestOP0xa6();

	// AND A
	void TestOP0xa7();

	// XOR B
	void TestOP0xa8();

	// XOR C
	void TestOP0xa9();

	// XOR D
	void TestOP0xaa();

	// XOR E
	void TestOP0xab();

	// XOR H
	void TestOP0xac();

	// XOR L
	void TestOP0xad();

	// XOR (HL)
	void TestOP0xae();

	// XOR A
	void TestOP0xaf();

	// OR B
	void TestOP0xb0();

	// OR C
	void TestOP0xb1();

	// OR D
	void TestOP0xb2();

	// OR E
	void TestOP0xb3();

	// OR H
	void TestOP0xb4();

	// OR L
	void TestOP0xb5();

	// OR (HL)
	void TestOP0xb6();

	// OR A
	void TestOP0xb7();

	// CP B
	void TestOP0xb8();

	// CP C
	void TestOP0xb9();

	// CP D
	void TestOP0xba();

	// CP E
	void TestOP0xbb();

	// CP H
	void TestOP0xbc();

	// CP L
	void TestOP0xbd();

	// CP (HL)
	void TestOP0xbe();

	// CP A
	void TestOP0xbf();

	// RET NZ
	void TestOP0xc0();

	// POP BC
	void TestOP0xc1();

	// JP NZ, imm16
	void TestOP0xc2();

	// JP imm16
	void TestOP0xc3();

	// CALL NZ, imm16
	void TestOP0xc4();

	// PUSH BC
	void TestOP0xc5();

	// ADD A, imm8
	void TestOP0xc6();

	// RST 0x00
	void TestOP0xc7();

	// RET Z
	void TestOP0xc8();

	// RET
	void TestOP0xc9();

	// JP Z, imm16
	void TestOP0xca();

	// PREFIX CB
	void TestOP0xcb();

	// CALL Z, imm16
	void TestOP0xcc();

	// CALL imm16
	void TestOP0xcd();

	// ADC A, imm8
	void TestOP0xce();

	// RST 0x08
	void TestOP0xcf();

	// RET NC
	void TestOP0xd0();

	// POP DE
	void TestOP0xd1();

	// JP NC, imm16
	void TestOP0xd2();

	// NO INSTRUCTION
	void TestOP0xd3();

	// CALL NC, imm16
	void TestOP0xd4();

	// PUSH DE
	void TestOP0xd5();

	// SUB imm8
	void TestOP0xd6();

	// RST 0x10
	void TestOP0xd7();

	// RET C
	void TestOP0xd8();

	// RETI
	void TestOP0xd9();

	// JP C, imm16
	void TestOP0xda();

	// NO INSTRUCTION
	void TestOP0xdb();

	// CALL C, imm16
	void TestOP0xdc();

	// NO INSTRUCTION
	void TestOP0xdd();

	// SBC A, imm8
	void TestOP0xde();

	// RST 0x018
	void TestOP0xdf();

	// LDH (imm8), A
	void TestOP0xe0();

	// POP HL
	void TestOP0xe1();

	// LD (C), A
	void TestOP0xe2();

	// NO INSTRUCTION
	void TestOP0xe3();

	// NO INSTRUCTION
	void TestOP0xe4();

	// PUSH HL
	void TestOP0xe5();

	// AND imm8
	void TestOP0xe6();

	// RST 0x020
	void TestOP0xe7();

	// ADD SP, S-imm8
	void TestOP0xe8();

	// JP (HL)
	void TestOP0xe9();

	// LD (imm16), A
	void TestOP0xea();

	// NO INSTRUCTION
	void TestOP0xeb();

	// NO INSTRUCTION
	void TestOP0xec();

	// NO INSTRUCTION
	void TestOP0xed();

	// XOR imm8
	void TestOP0xee();

	// RST 0x028
	void TestOP0xef();

	// LDH A, (imm8)
	void TestOP0xf0();

	// POP AF
	void TestOP0xf1();

	// LD A, (C)
	void TestOP0xf2();

	// DI
	void TestOP0xf3();

	// NO INSTRUCTION
	void TestOP0xf4();

	// PUSH AF
	void TestOP0xf5();

	// OR imm8
	void TestOP0xf6();

	// RST 0x30
	void TestOP0xf7();

	// LD HL, SP + S-imm8
	void TestOP0xf8();

	// LD SP, HL
	void TestOP0xf9();

	// LD A, (imm16)
	void TestOP0xfa();

	// EI
	void TestOP0xfb();

	// NO INSTRUCTION
	void TestOP0xfc();

	// NO INSTRUCTION
	void TestOP0xfd();

	// CP imm8
	void TestOP0xfe();

	// RST 0x38
	void TestOP0xff();

	// RLC B
	void TestOP0x100();

	// RLC C
	void TestOP0x101();

	// RLC D
	void TestOP0x102();

	// RLC E
	void TestOP0x103();

	// RLC H
	void TestOP0x104();

	// RLC L
	void TestOP0x105();

	// RLC (HL)
	void TestOP0x106();

	// RLC A
	void TestOP0x107();

	// RRC B
	void TestOP0x108();

	// RRC C
	void TestOP0x109();

	// RRC D
	void TestOP0x10a();

	// RRC E
	void TestOP0x10b();

	// RRC H
	void TestOP0x10c();

	// RRC L
	void TestOP0x10d();

	// RRC (HL)
	void TestOP0x10e();

	// RRC A
	void TestOP0x10f();

	// RL B
	void TestOP0x110();

	// RL C
	void TestOP0x111();

	// RL D
	void TestOP0x112();

	// RL E
	void TestOP0x113();

	// RL H
	void TestOP0x114();

	// RL L
	void TestOP0x115();

	// RL (HL)
	void TestOP0x116();

	// RL A
	void TestOP0x117();

	// RR B
	void TestOP0x118();

	// RR C
	void TestOP0x119();

	// RR D
	void TestOP0x11a();

	// RR E
	void TestOP0x11b();

	// RR H
	void TestOP0x11c();

	// RR L
	void TestOP0x11d();

	// RR (HL)
	void TestOP0x11e();

	// RR A
	void TestOP0x11f();

	// SLA B
	void TestOP0x120();

	// SLA C
	void TestOP0x121();

	// SLA D
	void TestOP0x122();

	// SLA E
	void TestOP0x123();

	// SLA H
	void TestOP0x124();

	// SLA L
	void TestOP0x125();

	// SLA (HL)
	void TestOP0x126();

	// SLA A
	void TestOP0x127();

	// SRA B
	void TestOP0x128();

	// SRA C
	void TestOP0x129();

	// SRA D
	void TestOP0x12a();

	// SRA E
	void TestOP0x12b();

	// SRA H
	void TestOP0x12c();

	// SRA L
	void TestOP0x12d();

	// SRA (HL)
	void TestOP0x12e();

	// SRA A
	void TestOP0x12f();

	// SWAP B
	void TestOP0x130();

	// SWAP C
	void TestOP0x131();

	// SWAP D
	void TestOP0x132();

	// SWAP E
	void TestOP0x133();

	// SWAP H
	void TestOP0x134();

	// SWAP L
	void TestOP0x135();

	// SWAP (HL)
	void TestOP0x136();

	// SWAP A
	void TestOP0x137();

	// SRL B
	void TestOP0x138();

	// SRL C
	void TestOP0x139();

	// SRL D
	void TestOP0x13a();

	// SRL E
	void TestOP0x13b();

	// SRL H
	void TestOP0x13c();

	// SRL L
	void TestOP0x13d();

	// SRL (HL)
	void TestOP0x13e();

	// SRL A
	void TestOP0x13f();

	// BIT 0 B
	void TestOP0x140();

	// BIT 0 C
	void TestOP0x141();

	// BIT 0 D
	void TestOP0x142();

	// BIT 0 E
	void TestOP0x143();

	// BIT 0 H
	void TestOP0x144();

	// BIT 0 L
	void TestOP0x145();

	// BIT 0 (HL)
	void TestOP0x146();

	// BIT 0 A
	void TestOP0x147();

	// BIT 1 B
	void TestOP0x148();

	// BIT 1 C
	void TestOP0x149();

	// BIT 1 D
	void TestOP0x14a();

	// BIT 1 E
	void TestOP0x14b();

	// BIT 1 H
	void TestOP0x14c();

	// BIT 1 L
	void TestOP0x14d();

	// BIT 1 (HL)
	void TestOP0x14e();

	// BIT 1 A
	void TestOP0x14f();

	// BIT 2 B
	void TestOP0x150();

	// BIT 2 C
	void TestOP0x151();

	// BIT 2 D
	void TestOP0x152();

	// BIT 2 E
	void TestOP0x153();

	// BIT 2 H
	void TestOP0x154();

	// BIT 2 L
	void TestOP0x155();

	// BIT 2 (HL)
	void TestOP0x156();

	// BIT 2 A
	void TestOP0x157();

	// BIT 3 B
	void TestOP0x158();

	// BIT 3 C
	void TestOP0x159();

	// BIT 3 D
	void TestOP0x15a();

	// BIT 3 E
	void TestOP0x15b();

	// BIT 3 H
	void TestOP0x15c();

	// BIT 3 L
	void TestOP0x15d();

	// BIT 3 (HL)
	void TestOP0x15e();

	// BIT 3 A
	void TestOP0x15f();

	// BIT 4 B
	void TestOP0x160();

	// BIT 4 C
	void TestOP0x161();

	// BIT 4 D
	void TestOP0x162();

	// BIT 4 E
	void TestOP0x163();

	// BIT 4 H
	void TestOP0x164();

	// BIT 4 L
	void TestOP0x165();

	// BIT 4 (HL)
	void TestOP0x166();

	// BIT 4 A
	void TestOP0x167();

	// BIT 5 B
	void TestOP0x168();

	// BIT 5 C
	void TestOP0x169();

	// BIT 5 D
	void TestOP0x16a();

	// BIT 5 E
	void TestOP0x16b();

	// BIT 5 H
	void TestOP0x16c();

	// BIT 5 L
	void TestOP0x16d();

	// BIT 5 (HL)
	void TestOP0x16e();

	// BIT 5 A
	void TestOP0x16f();

	// BIT 6 B
	void TestOP0x170();

	// BIT 6 C
	void TestOP0x171();

	// BIT 6 D
	void TestOP0x172();

	// BIT 6 E
	void TestOP0x173();

	// BIT 6 H
	void TestOP0x174();

	// BIT 6 L
	void TestOP0x175();

	// BIT 6 (HL)
	void TestOP0x176();

	// BIT 6 A
	void TestOP0x177();

	// BIT 7 B
	void TestOP0x178();

	// BIT 7 C
	void TestOP0x179();

	// BIT 7 D
	void TestOP0x17a();

	// BIT 7 E
	void TestOP0x17b();

	// BIT 7 H
	void TestOP0x17c();

	// BIT 7 L
	void TestOP0x17d();

	// BIT 7 (HL)
	void TestOP0x17e();

	// BIT 7 A
	void TestOP0x17f();

	// RES 0 B
	void TestOP0x180();

	// RES 0 C
	void TestOP0x181();

	// RES 0 D
	void TestOP0x182();

	// RES 0 E
	void TestOP0x183();

	// RES 0 H
	void TestOP0x184();

	// RES 0 L
	void TestOP0x185();

	// RES 0 (HL)
	void TestOP0x186();

	// RES 0 A
	void TestOP0x187();

	// RES 1 B
	void TestOP0x188();

	// RES 1 C
	void TestOP0x189();

	// RES 1 D
	void TestOP0x18a();

	// RES 1 E
	void TestOP0x18b();

	// RES 1 H
	void TestOP0x18c();

	// RES 1 L
	void TestOP0x18d();

	// RES 1 (HL)
	void TestOP0x18e();

	// RES 1 A
	void TestOP0x18f();

	// RES 2 B
	void TestOP0x190();

	// RES 2 C
	void TestOP0x191();

	// RES 2 D
	void TestOP0x192();

	// RES 2 E
	void TestOP0x193();

	// RES 2 H
	void TestOP0x194();

	// RES 2 L
	void TestOP0x195();

	// RES 2 (HL)
	void TestOP0x196();

	// RES 2 A
	void TestOP0x197();

	// RES 3 B
	void TestOP0x198();

	// RES 3 C
	void TestOP0x199();

	// RES 3 D
	void TestOP0x19a();

	// RES 3 E
	void TestOP0x19b();

	// RES 3 H
	void TestOP0x19c();

	// RES 3 L
	void TestOP0x19d();

	// RES 3 (HL)
	void TestOP0x19e();

	// RES 3 A
	void TestOP0x19f();

	// RES 4 B
	void TestOP0x1a0();

	// RES 4 C
	void TestOP0x1a1();

	// RES 4 D
	void TestOP0x1a2();

	// RES 4 E
	void TestOP0x1a3();

	// RES 4 H
	void TestOP0x1a4();

	// RES 4 L
	void TestOP0x1a5();

	// RES 4 (HL)
	void TestOP0x1a6();

	// RES 4 A
	void TestOP0x1a7();

	// RES 5 B
	void TestOP0x1a8();

	// RES 5 C
	void TestOP0x1a9();

	// RES 5 D
	void TestOP0x1aa();

	// RES 5 E
	void TestOP0x1ab();

	// RES 5 H
	void TestOP0x1ac();

	// RES 5 L
	void TestOP0x1ad();

	// RES 5 (HL)
	void TestOP0x1ae();

	// RES 5 A
	void TestOP0x1af();

	// RES 6 B
	void TestOP0x1b0();

	// RES 6 C
	void TestOP0x1b1();

	// RES 6 D
	void TestOP0x1b2();

	// RES 6 E
	void TestOP0x1b3();

	// RES 6 H
	void TestOP0x1b4();

	// RES 6 L
	void TestOP0x1b5();

	// RES 6 (HL)
	void TestOP0x1b6();

	// RES 6 A
	void TestOP0x1b7();

	// RES 7 B
	void TestOP0x1b8();

	// RES 7 C
	void TestOP0x1b9();

	// RES 7 D
	void TestOP0x1ba();

	// RES 7 E
	void TestOP0x1bb();

	// RES 7 H
	void TestOP0x1bc();

	// RES 7 L
	void TestOP0x1bd();

	// RES 7 (HL)
	void TestOP0x1be();

	// RES 7 A
	void TestOP0x1bf();

	// SET 0 B
	void TestOP0x1c0();

	// SET 0 C
	void TestOP0x1c1();

	// SET 0 D
	void TestOP0x1c2();

	// SET 0 E
	void TestOP0x1c3();

	// SET 0 H
	void TestOP0x1c4();

	// SET 0 L
	void TestOP0x1c5();

	// SET 0 (HL)
	void TestOP0x1c6();

	// SET 0 A
	void TestOP0x1c7();

	// SET 1 B
	void TestOP0x1c8();

	// SET 1 C
	void TestOP0x1c9();

	// SET 1 D
	void TestOP0x1ca();

	// SET 1 E
	void TestOP0x1cb();

	// SET 1 H
	void TestOP0x1cc();

	// SET 1 L
	void TestOP0x1cd();

	// SET 1 (HL)
	void TestOP0x1ce();

	// SET 1 A
	void TestOP0x1cf();

	// SET 2 B
	void TestOP0x1d0();

	// SET 2 C
	void TestOP0x1d1();

	// SET 2 D
	void TestOP0x1d2();

	// SET 2 E
	void TestOP0x1d3();

	// SET 2 H
	void TestOP0x1d4();

	// SET 2 L
	void TestOP0x1d5();

	// SET 2 (HL)
	void TestOP0x1d6();

	// SET 2 A
	void TestOP0x1d7();

	// SET 3 B
	void TestOP0x1d8();

	// SET 3 C
	void TestOP0x1d9();

	// SET 3 D
	void TestOP0x1da();

	// SET 3 E
	void TestOP0x1db();

	// SET 3 H
	void TestOP0x1dc();

	// SET 3 L
	void TestOP0x1dd();

	// SET 3 (HL)
	void TestOP0x1de();

	// SET 3 A
	void TestOP0x1df();

	// SET 4 B
	void TestOP0x1e0();

	// SET 4 C
	void TestOP0x1e1();

	// SET 4 D
	void TestOP0x1e2();

	// SET 4 E
	void TestOP0x1e3();

	// SET 4 H
	void TestOP0x1e4();

	// SET 4 L
	void TestOP0x1e5();

	// SET 4 (HL)
	void TestOP0x1e6();

	// SET 4 A
	void TestOP0x1e7();

	// SET 5 B
	void TestOP0x1e8();

	// SET 5 C
	void TestOP0x1e9();

	// SET 5 D
	void TestOP0x1ea();

	// SET 5 E
	void TestOP0x1eb();

	// SET 5 H
	void TestOP0x1ec();

	// SET 5 L
	void TestOP0x1ed();

	// SET 5 (HL)
	void TestOP0x1ee();

	// SET 5 A
	void TestOP0x1ef();

	// SET 6 B
	void TestOP0x1f0();

	// SET 6 C
	void TestOP0x1f1();

	// SET 6 D
	void TestOP0x1f2();

	// SET 6 E
	void TestOP0x1f3();

	// SET 6 H
	void TestOP0x1f4();

	// SET 6 L
	void TestOP0x1f5();

	// SET 6 (HL)
	void TestOP0x1f6();

	// SET 6 A
	void TestOP0x1f7();

	// SET 7 B
	void TestOP0x1f8();

	// SET 7 C
	void TestOP0x1f9();

	// SET 7 D
	void TestOP0x1fa();

	// SET 7 E
	void TestOP0x1fb();

	// SET 7 H
	void TestOP0x1fc();

	// SET 7 L
	void TestOP0x1fd();

	// SET 7 (HL)
	void TestOP0x1fe();

	// SET 7 A
	void TestOP0x1ff();

private:
	CPUWrapper w;
};

#endif