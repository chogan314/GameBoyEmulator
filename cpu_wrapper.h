#ifndef CPU_WRAPPER_H
#define CPU_WRAPPER_H

#include <assert.h>
#include "cpu.h"

enum TestType
{
	IMM_8, IMM_16, NO_INPUT
};

enum FlagState
{
	SET, RESET, IGNORE
};

class CPUWrapper
{
public:
	static const int Z_FLAG = 0x01;
	static const int N_FLAG = 0x02;
	static const int H_FLAG = 0x04;
	static const int C_FLAG = 0x08;
	static const ushort IMM_8_TEST_ADDRESS = 0xD000;
	static const ushort IMM_16_TEST_ADDRESS = 0xD010;
	static const ushort NO_INPUT_ADDRESS = 0xD020;
	static const ushort EIGHT_BIT_WRITE_ADDRESS = 0xD100;
	static const ushort SIXTEEN_BIT_WRITE_ADDRESS = 0xD200;
	static const ushort EIGHT_BIT_READ_ADDRESS = IMM_8_TEST_ADDRESS + 1;
	static const ushort SIXTEEN_BIT_READ_ADDRESS = IMM_16_TEST_ADDRESS + 1;

	CPUWrapper();

	uchar &A();
	uchar &F();
	uchar &B();
	uchar &C();
	uchar &D();
	uchar &E();
	uchar &H();
	uchar &L();

	ushort AF();
	ushort BC();
	ushort DE();
	ushort HL();

	ushort &SP();
	ushort &PC();

	bool &IME();

	void ExpectCyclesVarying(int cycles);
	void ExpectPCJump(int memAddress);

	void ExpectFlags(FlagState Z, FlagState N, FlagState H, FlagState C);
	void ExpectAllFlags(FlagState flags);

	void PrepareTest(TestType testType);

	void TestInstruction(int opcode);
	void TestJump(int opcode);

	void SetFlags(bool zSet, bool nSet, bool hSet, bool cSet);
	void SetAllFlags(bool set);

	uchar ReadByte(ushort address);
	ushort ReadShort(ushort address);

	uchar LastImm8Arg();
	ushort LastImm16Arg();

	void Write16BitReg(uchar &msb, uchar &lsb, ushort val);

	void SetImm8TestVal(uchar val);
	void SetImm16TestVal(ushort val);

private:
	CPU *processor;
	MemBlock memory;
	Cartridge cartridge;

	TestType testType;

	int expectedCycles[512];
	int expectedPCAdvance[512];

	int expectedCyclesVarying;
	int expectedPC;

	FlagState expectedFlags[4];

	uchar lastImm8Arg;
	ushort lastImm16Arg;

	std::string testDescription;

	void Init();
	void ResetState();
	void CheckFlags();
};

#endif