#include "cpu.h"
#include "instruction_factory.h"

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
	instructions[0x0a] = factory.MakeLdReg8AddrReg16(new CReg8Bit8Bit(B, C), A, "LD A, (BC)");
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
	instructions[0x57] = factory.MakeLdReg8Reg8(D, A, "LD D, A");
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
	instructions[0x77] = factory.MakeLdAddrReg16Reg8(new CReg8Bit8Bit(H, L), A, "LD (HL), A");
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
	instructions[0xc0] = factory.MakeRetCond(7, 0, "RET NZ");
	instructions[0xc1] = factory.MakePopReg16(new CReg8Bit8Bit(B, C), "POP BC");
	instructions[0xc2] = factory.MakeJpCondImm16(7, 0, "JP NZ, imm16");
	instructions[0xc3] = factory.MakeJpImm16("JP imm16");
	instructions[0xc4] = factory.MakeCallCondImm16(7, 0, "CALL NZ, imm16");
	instructions[0xc5] = factory.MakePushReg16(new CReg8Bit8Bit(B, C), "PUSH BC");
	instructions[0xc6] = factory.MakeAddReg8Imm8(A, "ADD A, imm8");
	instructions[0xc7] = factory.MakeRstImm8(0x00U, "RST 0x00");
	instructions[0xc8] = factory.MakeRetCond(7, 1, "RET Z");
	instructions[0xc9] = factory.MakeRET("RET");
	instructions[0xca] = factory.MakeJpCondImm16(7, 1, "JP Z, imm16");
	instructions[0xcb] = factory.MakePrefixCB("PREFIX CB");
	instructions[0xcc] = factory.MakeCallCondImm16(7, 1, "CALL Z, imm16");
	instructions[0xcd] = factory.MakeCallImm16("CALL imm16");
	instructions[0xce] = factory.MakeAdcReg8Imm8(A, "ADC A, imm8");
	instructions[0xcf] = factory.MakeRstImm8(0x08, "RST 0x08");
	instructions[0xd0] = factory.MakeRetCond(4, 0, "RET NC");
	instructions[0xd1] = factory.MakePopReg16(new CReg8Bit8Bit(D, E), "POP DE");
	instructions[0xd2] = factory.MakeJpCondImm16(4, 0, "JP NC, imm16");
	instructions[0xd3] = factory.MakeNoInstruction("NO INSTRUCTION");
	instructions[0xd4] = factory.MakeCallCondImm16(4, 0, "CALL NC, imm16");
	instructions[0xd5] = factory.MakePushReg16(new CReg8Bit8Bit(D, E), "PUSH DE");
	instructions[0xd6] = factory.MakeSubImm8("SUB imm8");
	instructions[0xd7] = factory.MakeRstImm8(0x10U, "RST 0x10");
	instructions[0xd8] = factory.MakeRetCond(4, 1, "RET C");
	instructions[0xd9] = factory.MakeRETI("RETI");
	instructions[0xda] = factory.MakeJpCondImm16(4, 1, "JP C, imm16");
	instructions[0xdb] = factory.MakeNoInstruction("NO INSTRUCTION");
	instructions[0xdc] = factory.MakeCallCondImm16(4, 1, "CALL C, imm16");
	instructions[0xdd] = factory.MakeNoInstruction("NO INSTRUCTION");
	instructions[0xde] = factory.MakeSbcReg8Imm8(A, "SBC A, imm8");
	instructions[0xdf] = factory.MakeRstImm8(0x18U, "RST 0x018");
	instructions[0xe0] = factory.MakeLdHAddrImm8Reg8(A, "LDH (imm8), A");
	instructions[0xe1] = factory.MakePopReg16(new CReg8Bit8Bit(H, L), "POP HL");
	instructions[0xe2] = factory.MakeLdAddrReg8Reg8(C, A, "LD (C), A");
	instructions[0xe3] = factory.MakeNoInstruction("NO INSTRUCTION");
	instructions[0xe4] = factory.MakeNoInstruction("NO INSTRUCTION");
	instructions[0xe5] = factory.MakePushReg16(new CReg8Bit8Bit(H, L), "PUSH HL");
	instructions[0xe6] = factory.MakeAndImm8("AND imm8");
	instructions[0xe7] = factory.MakeRstImm8(0x20U, "RST 0x020");
	instructions[0xe8] = factory.MakeAddReg16Imm8S(new CReg16Bit(SP), "ADD SP, S-imm8");
	instructions[0xe9] = factory.MakeJpAddrReg16(new CReg8Bit8Bit(H, L), "JP (HL)");
	instructions[0xea] = factory.MakeLdAddrImm16Reg8(A, "LD (imm16), A");
	instructions[0xeb] = factory.MakeNoInstruction("NO INSTRUCTION");
	instructions[0xec] = factory.MakeNoInstruction("NO INSTRUCTION");
	instructions[0xed] = factory.MakeNoInstruction("NO INSTRUCTION");
	instructions[0xee] = factory.MakeXorImm8("XOR imm8");
	instructions[0xef] = factory.MakeRstImm8(0x28U, "RST 0x028");
	instructions[0xf0] = factory.MakeLdHReg8AddrImm8(A, "LDH A, (imm8)");
	instructions[0xf1] = factory.MakePopReg16(new CReg8Bit8Bit(A, F), "POP AF");
	instructions[0xf2] = factory.MakeLdReg8AddrReg8(A, C, "LD A, (C)");
	instructions[0xf3] = factory.MakeDI("DI");
	instructions[0xf4] = factory.MakeNoInstruction("NO INSTRUCTION");
	instructions[0xf5] = factory.MakePushReg16(new CReg8Bit8Bit(A, F), "PUSH AF");
	instructions[0xf6] = factory.MakeOrImm8("OR imm8");
	instructions[0xf7] = factory.MakeRstImm8(0x30U, "RST 0x30");
	instructions[0xf8] = factory.MakeLdReg16Reg16AddImm8S(new CReg8Bit8Bit(H, L), new CReg16Bit(SP), "LD HL, SP + S-imm8");
	instructions[0xf9] = factory.MakeLdReg16Reg16(new CReg16Bit(SP), new CReg8Bit8Bit(H, L), "LD SP, HL");
	instructions[0xfa] = factory.MakeLdReg8AddrImm16(A, "LD A, (imm16)");
	instructions[0xfb] = factory.MakeEI("EI");
	instructions[0xfc] = factory.MakeNoInstruction("NO INSTRUCTION");
	instructions[0xfd] = factory.MakeNoInstruction("NO INSTRUCTION");
	instructions[0xfe] = factory.MakeCpImm8("CP imm8");
	instructions[0xff] = factory.MakeRstImm8(0x38U, "RST 0x38");

	instructions[0x100] = factory.MakeRlcReg8(B, "RLC B");
	instructions[0x101] = factory.MakeRlcReg8(C, "RLC C");
	instructions[0x102] = factory.MakeRlcReg8(D, "RLC D");
	instructions[0x103] = factory.MakeRlcReg8(E, "RLC E");
	instructions[0x104] = factory.MakeRlcReg8(H, "RLC H");
	instructions[0x105] = factory.MakeRlcReg8(L, "RLC L");
	instructions[0x106] = factory.MakeRlcAddrReg16(new CReg8Bit8Bit(H, L), "RLC (HL)");
	instructions[0x107] = factory.MakeRlcReg8(A, "RLC A");
	instructions[0x108] = factory.MakeRrcReg8(B, "RRC B");
	instructions[0x109] = factory.MakeRrcReg8(C, "RRC C");
	instructions[0x10a] = factory.MakeRrcReg8(D, "RRC D");
	instructions[0x10b] = factory.MakeRrcReg8(E, "RRC E");
	instructions[0x10c] = factory.MakeRrcReg8(H, "RRC H");
	instructions[0x10d] = factory.MakeRrcReg8(L, "RRC L");
	instructions[0x10e] = factory.MakeRrcAddrReg16(new CReg8Bit8Bit(H, L), "RRC (HL)");
	instructions[0x10f] = factory.MakeRrcReg8(A, "RRC A");
	instructions[0x110] = factory.MakeRlReg8(B, "RL B");
	instructions[0x111] = factory.MakeRlReg8(C, "RL C");
	instructions[0x112] = factory.MakeRlReg8(D, "RL D");
	instructions[0x113] = factory.MakeRlReg8(E, "RL E");
	instructions[0x114] = factory.MakeRlReg8(H, "RL H");
	instructions[0x115] = factory.MakeRlReg8(L, "RL L");
	instructions[0x116] = factory.MakeRlAddrReg16(new CReg8Bit8Bit(H, L), "RL (HL)");
	instructions[0x117] = factory.MakeRlReg8(A, "RL A");
	instructions[0x118] = factory.MakeRrReg8(B, "RR B");
	instructions[0x119] = factory.MakeRrReg8(C, "RR C");
	instructions[0x11a] = factory.MakeRrReg8(D, "RR D");
	instructions[0x11b] = factory.MakeRrReg8(E, "RR E");
	instructions[0x11c] = factory.MakeRrReg8(H, "RR H");
	instructions[0x11d] = factory.MakeRrReg8(L, "RR L");
	instructions[0x11e] = factory.MakeRrAddrReg16(new CReg8Bit8Bit(H, L), "RR (HL)");
	instructions[0x11f] = factory.MakeRrReg8(A, "RR A");
	instructions[0x120] = factory.MakeSlaReg8(B, "SLA B");
	instructions[0x121] = factory.MakeSlaReg8(C, "SLA C");
	instructions[0x122] = factory.MakeSlaReg8(D, "SLA D");
	instructions[0x123] = factory.MakeSlaReg8(E, "SLA E");
	instructions[0x124] = factory.MakeSlaReg8(H, "SLA H");
	instructions[0x125] = factory.MakeSlaReg8(L, "SLA L");
	instructions[0x126] = factory.MakeSlaAddrReg16(new CReg8Bit8Bit(H, L), "SLA (HL)");
	instructions[0x127] = factory.MakeSlaReg8(A, "SLA A");
	instructions[0x128] = factory.MakeSraReg8(B, "SRA B");
	instructions[0x129] = factory.MakeSraReg8(C, "SRA C");
	instructions[0x12a] = factory.MakeSraReg8(D, "SRA D");
	instructions[0x12b] = factory.MakeSraReg8(E, "SRA E");
	instructions[0x12c] = factory.MakeSraReg8(H, "SRA H");
	instructions[0x12d] = factory.MakeSraReg8(L, "SRA L");
	instructions[0x12e] = factory.MakeSraAddrReg16(new CReg8Bit8Bit(H, L), "SRA (HL)");
	instructions[0x12f] = factory.MakeSraReg8(A, "SRA A");
	instructions[0x130] = factory.MakeSwapReg8(B, "SWAP B");
	instructions[0x131] = factory.MakeSwapReg8(C, "SWAP C");
	instructions[0x132] = factory.MakeSwapReg8(D, "SWAP D");
	instructions[0x133] = factory.MakeSwapReg8(E, "SWAP E");
	instructions[0x134] = factory.MakeSwapReg8(H, "SWAP H");
	instructions[0x135] = factory.MakeSwapReg8(L, "SWAP L");
	instructions[0x136] = factory.MakeSwapAddrReg16(new CReg8Bit8Bit(H, L), "SWAP (HL)");
	instructions[0x137] = factory.MakeSwapReg8(A, "SWAP A");
	instructions[0x138] = factory.MakeSrlReg8(B, "SRL B");
	instructions[0x139] = factory.MakeSrlReg8(C, "SRL C");
	instructions[0x13a] = factory.MakeSrlReg8(D, "SRL D");
	instructions[0x13b] = factory.MakeSrlReg8(E, "SRL E");
	instructions[0x13c] = factory.MakeSrlReg8(H, "SRL H");
	instructions[0x13d] = factory.MakeSrlReg8(L, "SRL L");
	instructions[0x13e] = factory.MakeSrlAddrReg16(new CReg8Bit8Bit(H, L), "SRL (HL)");
	instructions[0x13f] = factory.MakeSrlReg8(A, "SRL A");
	instructions[0x140] = factory.MakeBitImm8Reg8(0, B, "BIT 0 B");
	instructions[0x141] = factory.MakeBitImm8Reg8(0, C, "BIT 0 C");
	instructions[0x142] = factory.MakeBitImm8Reg8(0, D, "BIT 0 D");
	instructions[0x143] = factory.MakeBitImm8Reg8(0, E, "BIT 0 E");
	instructions[0x144] = factory.MakeBitImm8Reg8(0, H, "BIT 0 H");
	instructions[0x145] = factory.MakeBitImm8Reg8(0, L, "BIT 0 L");
	instructions[0x146] = factory.MakeBitImm8AddrReg16(0, new CReg8Bit8Bit(H, L), "BIT 0 (HL)");
	instructions[0x147] = factory.MakeBitImm8Reg8(0, A, "BIT 0 A");
	instructions[0x148] = factory.MakeBitImm8Reg8(1, B, "BIT 1 B");
	instructions[0x149] = factory.MakeBitImm8Reg8(1, C, "BIT 1 C");
	instructions[0x14a] = factory.MakeBitImm8Reg8(1, D, "BIT 1 D");
	instructions[0x14b] = factory.MakeBitImm8Reg8(1, E, "BIT 1 E");
	instructions[0x14c] = factory.MakeBitImm8Reg8(1, H, "BIT 1 H");
	instructions[0x14d] = factory.MakeBitImm8Reg8(1, L, "BIT 1 L");
	instructions[0x14e] = factory.MakeBitImm8AddrReg16(1, new CReg8Bit8Bit(H, L), "BIT 1 (HL)");
	instructions[0x14f] = factory.MakeBitImm8Reg8(1, A, "BIT 1 A");
	instructions[0x150] = factory.MakeBitImm8Reg8(2, B, "BIT 2 B");
	instructions[0x151] = factory.MakeBitImm8Reg8(2, C, "BIT 2 C");
	instructions[0x152] = factory.MakeBitImm8Reg8(2, D, "BIT 2 D");
	instructions[0x153] = factory.MakeBitImm8Reg8(2, E, "BIT 2 E");
	instructions[0x154] = factory.MakeBitImm8Reg8(2, H, "BIT 2 H");
	instructions[0x155] = factory.MakeBitImm8Reg8(2, L, "BIT 2 L");
	instructions[0x156] = factory.MakeBitImm8AddrReg16(2, new CReg8Bit8Bit(H, L), "BIT 2 (HL)");
	instructions[0x157] = factory.MakeBitImm8Reg8(2, A, "BIT 2 A");
	instructions[0x158] = factory.MakeBitImm8Reg8(3, B, "BIT 3 B");
	instructions[0x159] = factory.MakeBitImm8Reg8(3, C, "BIT 3 C");
	instructions[0x15a] = factory.MakeBitImm8Reg8(3, D, "BIT 3 D");
	instructions[0x15b] = factory.MakeBitImm8Reg8(3, E, "BIT 3 E");
	instructions[0x15c] = factory.MakeBitImm8Reg8(3, H, "BIT 3 H");
	instructions[0x15d] = factory.MakeBitImm8Reg8(3, L, "BIT 3 L");
	instructions[0x15e] = factory.MakeBitImm8AddrReg16(3, new CReg8Bit8Bit(H, L), "BIT 3 (HL)");
	instructions[0x15f] = factory.MakeBitImm8Reg8(3, A, "BIT 3 A");
	instructions[0x160] = factory.MakeBitImm8Reg8(4, B, "BIT 4 B");
	instructions[0x161] = factory.MakeBitImm8Reg8(4, C, "BIT 4 C");
	instructions[0x162] = factory.MakeBitImm8Reg8(4, D, "BIT 4 D");
	instructions[0x163] = factory.MakeBitImm8Reg8(4, E, "BIT 4 E");
	instructions[0x164] = factory.MakeBitImm8Reg8(4, H, "BIT 4 H");
	instructions[0x165] = factory.MakeBitImm8Reg8(4, L, "BIT 4 L");
	instructions[0x166] = factory.MakeBitImm8AddrReg16(4, new CReg8Bit8Bit(H, L), "BIT 4 (HL)");
	instructions[0x167] = factory.MakeBitImm8Reg8(4, A, "BIT 4 A");
	instructions[0x168] = factory.MakeBitImm8Reg8(5, B, "BIT 5 B");
	instructions[0x169] = factory.MakeBitImm8Reg8(5, C, "BIT 5 C");
	instructions[0x16a] = factory.MakeBitImm8Reg8(5, D, "BIT 5 D");
	instructions[0x16b] = factory.MakeBitImm8Reg8(5, E, "BIT 5 E");
	instructions[0x16c] = factory.MakeBitImm8Reg8(5, H, "BIT 5 H");
	instructions[0x16d] = factory.MakeBitImm8Reg8(5, L, "BIT 5 L");
	instructions[0x16e] = factory.MakeBitImm8AddrReg16(5, new CReg8Bit8Bit(H, L), "BIT 5 (HL)");
	instructions[0x16f] = factory.MakeBitImm8Reg8(5, A, "BIT 5 A");
	instructions[0x170] = factory.MakeBitImm8Reg8(6, B, "BIT 6 B");
	instructions[0x171] = factory.MakeBitImm8Reg8(6, C, "BIT 6 C");
	instructions[0x172] = factory.MakeBitImm8Reg8(6, D, "BIT 6 D");
	instructions[0x173] = factory.MakeBitImm8Reg8(6, E, "BIT 6 E");
	instructions[0x174] = factory.MakeBitImm8Reg8(6, H, "BIT 6 H");
	instructions[0x175] = factory.MakeBitImm8Reg8(6, L, "BIT 6 L");
	instructions[0x176] = factory.MakeBitImm8AddrReg16(6, new CReg8Bit8Bit(H, L), "BIT 6 (HL)");
	instructions[0x177] = factory.MakeBitImm8Reg8(6, A, "BIT 6 A");
	instructions[0x178] = factory.MakeBitImm8Reg8(7, B, "BIT 7 B");
	instructions[0x179] = factory.MakeBitImm8Reg8(7, C, "BIT 7 C");
	instructions[0x17a] = factory.MakeBitImm8Reg8(7, D, "BIT 7 D");
	instructions[0x17b] = factory.MakeBitImm8Reg8(7, E, "BIT 7 E");
	instructions[0x17c] = factory.MakeBitImm8Reg8(7, H, "BIT 7 H");
	instructions[0x17d] = factory.MakeBitImm8Reg8(7, L, "BIT 7 L");
	instructions[0x17e] = factory.MakeBitImm8AddrReg16(7, new CReg8Bit8Bit(H, L), "BIT 7 (HL)");
	instructions[0x17f] = factory.MakeBitImm8Reg8(7, A, "BIT 7 A");
	instructions[0x180] = factory.MakeResImm8Reg8(0, B, "RES 0 B");
	instructions[0x181] = factory.MakeResImm8Reg8(0, C, "RES 0 C");
	instructions[0x182] = factory.MakeResImm8Reg8(0, D, "RES 0 D");
	instructions[0x183] = factory.MakeResImm8Reg8(0, E, "RES 0 E");
	instructions[0x184] = factory.MakeResImm8Reg8(0, H, "RES 0 H");
	instructions[0x185] = factory.MakeResImm8Reg8(0, L, "RES 0 L");
	instructions[0x186] = factory.MakeResImm8AddrReg16(0, new CReg8Bit8Bit(H, L), "RES 0 (HL)");
	instructions[0x187] = factory.MakeResImm8Reg8(0, A, "RES 0 A");
	instructions[0x188] = factory.MakeResImm8Reg8(1, B, "RES 1 B");
	instructions[0x189] = factory.MakeResImm8Reg8(1, C, "RES 1 C");
	instructions[0x18a] = factory.MakeResImm8Reg8(1, D, "RES 1 D");
	instructions[0x18b] = factory.MakeResImm8Reg8(1, E, "RES 1 E");
	instructions[0x18c] = factory.MakeResImm8Reg8(1, H, "RES 1 H");
	instructions[0x18d] = factory.MakeResImm8Reg8(1, L, "RES 1 L");
	instructions[0x18e] = factory.MakeResImm8AddrReg16(1, new CReg8Bit8Bit(H, L), "RES 1 (HL)");
	instructions[0x18f] = factory.MakeResImm8Reg8(1, A, "RES 1 A");
	instructions[0x190] = factory.MakeResImm8Reg8(2, B, "RES 2 B");
	instructions[0x191] = factory.MakeResImm8Reg8(2, C, "RES 2 C");
	instructions[0x192] = factory.MakeResImm8Reg8(2, D, "RES 2 D");
	instructions[0x193] = factory.MakeResImm8Reg8(2, E, "RES 2 E");
	instructions[0x194] = factory.MakeResImm8Reg8(2, H, "RES 2 H");
	instructions[0x195] = factory.MakeResImm8Reg8(2, L, "RES 2 L");
	instructions[0x196] = factory.MakeResImm8AddrReg16(2, new CReg8Bit8Bit(H, L), "RES 2 (HL)");
	instructions[0x197] = factory.MakeResImm8Reg8(2, A, "RES 2 A");
	instructions[0x198] = factory.MakeResImm8Reg8(3, B, "RES 3 B");
	instructions[0x199] = factory.MakeResImm8Reg8(3, C, "RES 3 C");
	instructions[0x19a] = factory.MakeResImm8Reg8(3, D, "RES 3 D");
	instructions[0x19b] = factory.MakeResImm8Reg8(3, E, "RES 3 E");
	instructions[0x19c] = factory.MakeResImm8Reg8(3, H, "RES 3 H");
	instructions[0x19d] = factory.MakeResImm8Reg8(3, L, "RES 3 L");
	instructions[0x19e] = factory.MakeResImm8AddrReg16(3, new CReg8Bit8Bit(H, L), "RES 3 (HL)");
	instructions[0x19f] = factory.MakeResImm8Reg8(3, A, "RES 3 A");
	instructions[0x1a0] = factory.MakeResImm8Reg8(4, B, "RES 4 B");
	instructions[0x1a1] = factory.MakeResImm8Reg8(4, C, "RES 4 C");
	instructions[0x1a2] = factory.MakeResImm8Reg8(4, D, "RES 4 D");
	instructions[0x1a3] = factory.MakeResImm8Reg8(4, E, "RES 4 E");
	instructions[0x1a4] = factory.MakeResImm8Reg8(4, H, "RES 4 H");
	instructions[0x1a5] = factory.MakeResImm8Reg8(4, L, "RES 4 L");
	instructions[0x1a6] = factory.MakeResImm8AddrReg16(4, new CReg8Bit8Bit(H, L), "RES 4 (HL)");
	instructions[0x1a7] = factory.MakeResImm8Reg8(4, A, "RES 4 A");
	instructions[0x1a8] = factory.MakeResImm8Reg8(5, B, "RES 5 B");
	instructions[0x1a9] = factory.MakeResImm8Reg8(5, C, "RES 5 C");
	instructions[0x1aa] = factory.MakeResImm8Reg8(5, D, "RES 5 D");
	instructions[0x1ab] = factory.MakeResImm8Reg8(5, E, "RES 5 E");
	instructions[0x1ac] = factory.MakeResImm8Reg8(5, H, "RES 5 H");
	instructions[0x1ad] = factory.MakeResImm8Reg8(5, L, "RES 5 L");
	instructions[0x1ae] = factory.MakeResImm8AddrReg16(5, new CReg8Bit8Bit(H, L), "RES 5 (HL)");
	instructions[0x1af] = factory.MakeResImm8Reg8(5, A, "RES 5 A");
	instructions[0x1b0] = factory.MakeResImm8Reg8(6, B, "RES 6 B");
	instructions[0x1b1] = factory.MakeResImm8Reg8(6, C, "RES 6 C");
	instructions[0x1b2] = factory.MakeResImm8Reg8(6, D, "RES 6 D");
	instructions[0x1b3] = factory.MakeResImm8Reg8(6, E, "RES 6 E");
	instructions[0x1b4] = factory.MakeResImm8Reg8(6, H, "RES 6 H");
	instructions[0x1b5] = factory.MakeResImm8Reg8(6, L, "RES 6 L");
	instructions[0x1b6] = factory.MakeResImm8AddrReg16(6, new CReg8Bit8Bit(H, L), "RES 6 (HL)");
	instructions[0x1b7] = factory.MakeResImm8Reg8(6, A, "RES 6 A");
	instructions[0x1b8] = factory.MakeResImm8Reg8(7, B, "RES 7 B");
	instructions[0x1b9] = factory.MakeResImm8Reg8(7, C, "RES 7 C");
	instructions[0x1ba] = factory.MakeResImm8Reg8(7, D, "RES 7 D");
	instructions[0x1bb] = factory.MakeResImm8Reg8(7, E, "RES 7 E");
	instructions[0x1bc] = factory.MakeResImm8Reg8(7, H, "RES 7 H");
	instructions[0x1bd] = factory.MakeResImm8Reg8(7, L, "RES 7 L");
	instructions[0x1be] = factory.MakeResImm8AddrReg16(7, new CReg8Bit8Bit(H, L), "RES 7 (HL)");
	instructions[0x1bf] = factory.MakeResImm8Reg8(7, A, "RES 7 A");
	instructions[0x1c0] = factory.MakeSetImm8Reg8(0, B, "SET 0 B");
	instructions[0x1c1] = factory.MakeSetImm8Reg8(0, C, "SET 0 C");
	instructions[0x1c2] = factory.MakeSetImm8Reg8(0, D, "SET 0 D");
	instructions[0x1c3] = factory.MakeSetImm8Reg8(0, E, "SET 0 E");
	instructions[0x1c4] = factory.MakeSetImm8Reg8(0, H, "SET 0 H");
	instructions[0x1c5] = factory.MakeSetImm8Reg8(0, L, "SET 0 L");
	instructions[0x1c6] = factory.MakeSetImm8AddrReg16(0, new CReg8Bit8Bit(H, L), "SET 0 (HL)");
	instructions[0x1c7] = factory.MakeSetImm8Reg8(0, A, "SET 0 A");
	instructions[0x1c8] = factory.MakeSetImm8Reg8(1, B, "SET 1 B");
	instructions[0x1c9] = factory.MakeSetImm8Reg8(1, C, "SET 1 C");
	instructions[0x1ca] = factory.MakeSetImm8Reg8(1, D, "SET 1 D");
	instructions[0x1cb] = factory.MakeSetImm8Reg8(1, E, "SET 1 E");
	instructions[0x1cc] = factory.MakeSetImm8Reg8(1, H, "SET 1 H");
	instructions[0x1cd] = factory.MakeSetImm8Reg8(1, L, "SET 1 L");
	instructions[0x1ce] = factory.MakeSetImm8AddrReg16(1, new CReg8Bit8Bit(H, L), "SET 1 (HL)");
	instructions[0x1cf] = factory.MakeSetImm8Reg8(1, A, "SET 1 A");
	instructions[0x1d0] = factory.MakeSetImm8Reg8(2, B, "SET 2 B");
	instructions[0x1d1] = factory.MakeSetImm8Reg8(2, C, "SET 2 C");
	instructions[0x1d2] = factory.MakeSetImm8Reg8(2, D, "SET 2 D");
	instructions[0x1d3] = factory.MakeSetImm8Reg8(2, E, "SET 2 E");
	instructions[0x1d4] = factory.MakeSetImm8Reg8(2, H, "SET 2 H");
	instructions[0x1d5] = factory.MakeSetImm8Reg8(2, L, "SET 2 L");
	instructions[0x1d6] = factory.MakeSetImm8AddrReg16(2, new CReg8Bit8Bit(H, L), "SET 2 (HL)");
	instructions[0x1d7] = factory.MakeSetImm8Reg8(2, A, "SET 2 A");
	instructions[0x1d8] = factory.MakeSetImm8Reg8(3, B, "SET 3 B");
	instructions[0x1d9] = factory.MakeSetImm8Reg8(3, C, "SET 3 C");
	instructions[0x1da] = factory.MakeSetImm8Reg8(3, D, "SET 3 D");
	instructions[0x1db] = factory.MakeSetImm8Reg8(3, E, "SET 3 E");
	instructions[0x1dc] = factory.MakeSetImm8Reg8(3, H, "SET 3 H");
	instructions[0x1dd] = factory.MakeSetImm8Reg8(3, L, "SET 3 L");
	instructions[0x1de] = factory.MakeSetImm8AddrReg16(3, new CReg8Bit8Bit(H, L), "SET 3 (HL)");
	instructions[0x1df] = factory.MakeSetImm8Reg8(3, A, "SET 3 A");
	instructions[0x1e0] = factory.MakeSetImm8Reg8(4, B, "SET 4 B");
	instructions[0x1e1] = factory.MakeSetImm8Reg8(4, C, "SET 4 C");
	instructions[0x1e2] = factory.MakeSetImm8Reg8(4, D, "SET 4 D");
	instructions[0x1e3] = factory.MakeSetImm8Reg8(4, E, "SET 4 E");
	instructions[0x1e4] = factory.MakeSetImm8Reg8(4, H, "SET 4 H");
	instructions[0x1e5] = factory.MakeSetImm8Reg8(4, L, "SET 4 L");
	instructions[0x1e6] = factory.MakeSetImm8AddrReg16(4, new CReg8Bit8Bit(H, L), "SET 4 (HL)");
	instructions[0x1e7] = factory.MakeSetImm8Reg8(4, A, "SET 4 A");
	instructions[0x1e8] = factory.MakeSetImm8Reg8(5, B, "SET 5 B");
	instructions[0x1e9] = factory.MakeSetImm8Reg8(5, C, "SET 5 C");
	instructions[0x1ea] = factory.MakeSetImm8Reg8(5, D, "SET 5 D");
	instructions[0x1eb] = factory.MakeSetImm8Reg8(5, E, "SET 5 E");
	instructions[0x1ec] = factory.MakeSetImm8Reg8(5, H, "SET 5 H");
	instructions[0x1ed] = factory.MakeSetImm8Reg8(5, L, "SET 5 L");
	instructions[0x1ee] = factory.MakeSetImm8AddrReg16(5, new CReg8Bit8Bit(H, L), "SET 5 (HL)");
	instructions[0x1ef] = factory.MakeSetImm8Reg8(5, A, "SET 5 A");
	instructions[0x1f0] = factory.MakeSetImm8Reg8(6, B, "SET 6 B");
	instructions[0x1f1] = factory.MakeSetImm8Reg8(6, C, "SET 6 C");
	instructions[0x1f2] = factory.MakeSetImm8Reg8(6, D, "SET 6 D");
	instructions[0x1f3] = factory.MakeSetImm8Reg8(6, E, "SET 6 E");
	instructions[0x1f4] = factory.MakeSetImm8Reg8(6, H, "SET 6 H");
	instructions[0x1f5] = factory.MakeSetImm8Reg8(6, L, "SET 6 L");
	instructions[0x1f6] = factory.MakeSetImm8AddrReg16(6, new CReg8Bit8Bit(H, L), "SET 6 (HL)");
	instructions[0x1f7] = factory.MakeSetImm8Reg8(6, A, "SET 6 A");
	instructions[0x1f8] = factory.MakeSetImm8Reg8(7, B, "SET 7 B");
	instructions[0x1f9] = factory.MakeSetImm8Reg8(7, C, "SET 7 C");
	instructions[0x1fa] = factory.MakeSetImm8Reg8(7, D, "SET 7 D");
	instructions[0x1fb] = factory.MakeSetImm8Reg8(7, E, "SET 7 E");
	instructions[0x1fc] = factory.MakeSetImm8Reg8(7, H, "SET 7 H");
	instructions[0x1fd] = factory.MakeSetImm8Reg8(7, L, "SET 7 L");
	instructions[0x1fe] = factory.MakeSetImm8AddrReg16(7, new CReg8Bit8Bit(H, L), "SET 7 (HL)");
	instructions[0x1ff] = factory.MakeSetImm8Reg8(7, A, "SET 7 A");
}
