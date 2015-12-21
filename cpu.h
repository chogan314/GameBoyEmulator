#ifndef CPU_H
#define CPU_H

#include "mem_block.h"
#include "instruction_args.h"
#include "cartridge.h"

typedef unsigned short ushort;
typedef unsigned char uchar;

class Instruction;
template <typename T>
class ParamInstruction;
class NoParamInstruction;

class CPU
{
	enum class Color
	{
		WHITE,
		LIGHT_GRAY,
		DARK_GRAY,
		BLACK
	};

	friend class Instruction;
	friend class InstructionFactory;
	friend class CPUWrapper;

	// INSTRUCTION onCall FUNCTIONS:

	/*******************************
	******** Loads & Moves *********
	********************************/
	friend void LdReg8Imm8(ParamInstruction<Reg8Param> &instruction);					// LD reg8, imm8
	friend void LdReg8Reg8(ParamInstruction<Reg8Reg8Param> &instruction);				// LD reg8, reg8
	friend void LdReg8AddrReg8(ParamInstruction<Reg8Reg8Param> &instruction);			// LD reg8, (reg8)
	friend void LdReg8AddrImm16(ParamInstruction<Reg8Param> &instruction);				// LD reg8, (imm16)
	friend void LdReg8AddrReg16(ParamInstruction<Reg16Reg8Param> &instruction);			// LD reg8, (reg16)
	friend void LdReg8AddrIncReg16(ParamInstruction<Reg16Reg8Param> &instruction);		// LD reg8, (reg16+)
	friend void LdReg8AddrDecReg16(ParamInstruction<Reg16Reg8Param> &instruction);		// LD reg8, (reg16-)
	friend void LdAddrReg8Reg8(ParamInstruction<Reg8Reg8Param> &instruction);			// LD (reg8), reg8
	friend void LdAddrReg16Imm8(ParamInstruction<Reg16Param> &instruction);				// LD (reg16), imm8
	friend void LdAddrReg16Reg8(ParamInstruction<Reg16Reg8Param> &instruction);			// LD (reg16), reg8
	friend void LdAddrIncReg16Reg8(ParamInstruction<Reg16Reg8Param> &instruction);		// LD (reg16+), reg8
	friend void LdAddrDecReg16Reg8(ParamInstruction<Reg16Reg8Param> &instruction);		// LD (reg16-), reg8
	friend void LdAddrImm16Reg8(ParamInstruction<Reg8Param> &instruction);				// LD (imm16), reg8
	friend void LdReg16Imm16(ParamInstruction<Reg16Param> &instruction);				// LD reg16, imm16
	friend void LdReg16Reg16AddImm8S(ParamInstruction<Reg16Reg16Param> &instruction);	// LD reg16, reg16 + S-imm8
	friend void LdAddrImm16Reg16(ParamInstruction<Reg16Param> &instruction);			// LD (imm16), reg16
	friend void LdHAddrImm8Reg8(ParamInstruction<Reg8Param> &instruction);				// LDH (imm8), reg8
	friend void LdHReg8AddrImm8(ParamInstruction<Reg8Param> &instruction);				// LDH reg8, (imm8)
	friend void PopReg16(ParamInstruction<Reg16Param> &instruction);					// POP reg16
	friend void PushReg16(ParamInstruction<Reg16Param> &instruction);					// PUSH reg16

	/*******************************
	********* Math & Logic *********
	********************************/
	friend void IncReg8(ParamInstruction<Reg8Param> &instruction);						// INC reg8
	friend void IncAddrReg16(ParamInstruction<Reg16Param> &instruction);				// INC (reg16) ; 8-bit
	friend void IncReg16(ParamInstruction<Reg16Param> &instruction);					// INC reg16
	friend void DecReg8(ParamInstruction<Reg8Param> &instruction);						// DEC reg8
	friend void DecAddrReg16(ParamInstruction<Reg16Param> &instruction);				// DEC (reg16) ; 8-bit
	friend void DecReg16(ParamInstruction<Reg16Param> &instruction);					// DEC reg16
	friend void AddReg8Imm8(ParamInstruction<Reg8Param> &instruction);					// ADD reg8, imm8
	friend void AddReg8Reg8(ParamInstruction<Reg8Reg8Param> &instruction);				// ADD reg8, reg8
	friend void AddReg8AddrReg16(ParamInstruction<Reg16Reg8Param> &instruction);		// ADD reg8, (reg16)
	friend void AddReg16Reg16(ParamInstruction<Reg16Reg16Param> &instruction);			// ADD reg16, reg16
	friend void AddReg16Imm8S(ParamInstruction<Reg16Param> &instruction);				// ADD reg16, S-imm8
	friend void AdcReg8Imm8(ParamInstruction<Reg8Param> &instruction);					// ADC reg8, imm8
	friend void AdcReg8Reg8(ParamInstruction<Reg8Reg8Param> &instruction);				// ADC reg8, reg8
	friend void AdcReg8AddrReg16(ParamInstruction<Reg16Reg8Param> &instruction);		// ADC reg8, (reg16)
	friend void SubImm8(NoParamInstruction &instruction);								// SUB imm8
	friend void SubReg8(ParamInstruction<Reg8Param> &instruction);						// SUB reg8
	friend void SubAddrReg16(ParamInstruction<Reg16Param> &instruction);				// SUB (reg16)
	friend void SbcReg8Imm8(ParamInstruction<Reg8Param> &instruction);					// SBC reg8, imm8
	friend void SbcReg8Reg8(ParamInstruction<Reg8Reg8Param> &instruction);				// SBC reg8, reg8
	friend void SbcReg8AddrReg16(ParamInstruction<Reg16Reg8Param> &instruction);		// SBC reg8, (reg16)
	friend void AndImm8(NoParamInstruction &instruction);								// AND imm8
	friend void AndReg8(ParamInstruction<Reg8Param> &instruction);						// AND reg8
	friend void AndAddrReg16(ParamInstruction<Reg16Param> &instruction);				// AND (reg16)
	friend void XorImm8(NoParamInstruction &instruction);								// XOR imm8
	friend void XorReg8(ParamInstruction<Reg8Param> &instruction);						// XOR reg8
	friend void XorAddrReg16(ParamInstruction<Reg16Param> &instruction);				// XOR (reg16)
	friend void OrImm8(NoParamInstruction &instruction);								// OR imm8
	friend void OrReg8(ParamInstruction<Reg8Param> &instruction);						// OR reg8
	friend void OrAddrReg16(ParamInstruction<Reg16Param> &instruction);					// OR (reg16)
	friend void CpImm8(NoParamInstruction &instruction);								// CP imm8
	friend void CpReg8(ParamInstruction<Reg8Param> &instruction);						// CP reg8
	friend void CpAddrReg16(ParamInstruction<Reg16Param> &instruction);					// CP (reg16)
	friend void DAA(NoParamInstruction &instruction);									// DAA
	friend void CPL(NoParamInstruction &instruction);									// CPL
	friend void SCF(NoParamInstruction &instruction);									// SCF
	friend void CCF(NoParamInstruction &instruction);									// CCF

	/*******************************
	****** Shifts & Rotations ******
	********************************/
	friend void RLCA(NoParamInstruction &instruction);									// RLCA
	friend void RRCA(NoParamInstruction &instruction);									// RRCA
	friend void RRA(NoParamInstruction &instruction);									// RRA
	friend void RLA(NoParamInstruction &instruction);									// RLA
	friend void RlcReg8(ParamInstruction<Reg8Param> &instruction);						// RLC reg8
	friend void RlcAddrReg16(ParamInstruction<Reg16Param> &instruction);				// RLC (reg16)
	friend void RrcReg8(ParamInstruction<Reg8Param> &instruction);						// RRC reg8
	friend void RrcAddrReg16(ParamInstruction<Reg16Param> &instruction);				// RRC (reg16)
	friend void RlReg8(ParamInstruction<Reg8Param> &instruction);						// RL reg8
	friend void RlAddrReg16(ParamInstruction<Reg16Param> &instruction);					// RL (reg16)
	friend void RrReg8(ParamInstruction<Reg8Param> &instruction);						// RR reg8
	friend void RrAddrReg16(ParamInstruction<Reg16Param> &instruction);					// RR (reg16)
	friend void SlaReg8(ParamInstruction<Reg8Param> &instruction);						// SLA reg8
	friend void SlaAddrReg16(ParamInstruction<Reg16Param> &instruction);				// SLA (reg16)
	friend void SraReg8(ParamInstruction<Reg8Param> &instruction);						// SRA reg8
	friend void SraAddrReg16(ParamInstruction<Reg16Param> &instruction);				// SRA (reg16)
	friend void SwapReg8(ParamInstruction<Reg8Param> &instruction);						// SWAP reg8
	friend void SwapAddrReg16(ParamInstruction<Reg16Param> &instruction);				// SWAP (reg16)
	friend void SrlReg8(ParamInstruction<Reg8Param> &instruction);						// SRL reg8
	friend void SrlAddrReg16(ParamInstruction<Reg16Param> &instruction);				// SRL (reg16)
	friend void BitImm8Reg8(ParamInstruction<Imm8Reg8Param> &instruction);				// BIT imm8, reg8
	friend void BitImm8AddrReg16(ParamInstruction<Imm8Reg16Param> &instruction);		// BIT imm8, (reg16)
	friend void ResImm8Reg8(ParamInstruction<Imm8Reg8Param> &instruction);				// RES imm8, reg8
	friend void ResImm8AddrReg16(ParamInstruction<Imm8Reg16Param> &instruction);		// RES imm8, (reg16)
	friend void SetImm8Reg8(ParamInstruction<Imm8Reg8Param> &instruction);				// SET imm8, reg8
	friend void SetImm8AddrReg16(ParamInstruction<Imm8Reg16Param> &instruction);		// SET imm8, (reg16)

	/*******************************
	******** Jumps & Calls *********
	********************************/
	friend void JrImm8S(NoParamInstruction &instruction);								// JR S-imm8
	friend void JrCondImm8S(ParamInstruction<ConditionalParam> &instruction);			// JR CONDITION, S-imm8
	friend void JpImm16(NoParamInstruction &instruction);								// JP imm16
	friend void JpCondImm16(ParamInstruction<ConditionalParam> &instruction);			// JP CONDITION, imm16
	friend void JpAddrReg16(ParamInstruction<Reg16Param> &instruction);					// JP (reg16)
	friend void CallImm16(NoParamInstruction &instruction);								// CALL imm16
	friend void CallCondImm16(ParamInstruction<ConditionalParam> &instruction);			// CALL CONDITION, imm16
	friend void RET(NoParamInstruction &instruction);									// RET
	friend void RetCond(ParamInstruction<ConditionalParam> &instruction);				// RET CONDITION
	friend void RETI(NoParamInstruction &instruction);									// RETI
	friend void RstImm8(ParamInstruction<Imm8Param> &instruction);						// RST imm8

	/*******************************
	******** Misc & Control ********
	********************************/
	friend void NOP(NoParamInstruction &instruction);									// NOP
	friend void Stop0(NoParamInstruction &instruction);									// STOP 0
	friend void HALT(NoParamInstruction &instruction);									// HALT
	friend void PrefixCB(NoParamInstruction &instruction);								// PREFIX CB
	friend void DI(NoParamInstruction &instruction);									// DI
	friend void EI(NoParamInstruction &instruction);									// EI

public:
	uchar screenData[160 * 144 * 3];

	CPU(MemBlock *memory);

	~CPU();

	void Update();

	void InsertCartridge(Cartridge *cartridge);

	// register F flag manipulation
	void SetZeroFlag(bool set);
	bool GetZeroFlag();

	void SetSubtractFlag(bool set);
	bool GetSubtractFlag();

	void SetHalfCarryFlag(bool set);
	bool GetHalfCarryFlag();

	void SetCarryFlag(bool set);
	bool GetCarryFlag();


	void PrintInstructions();
	void PrintMemory();
	void PrintRegisters();

private:
	const ushort TIMA = 0xFF05;
	const ushort TMA = 0xFF06;
	const ushort TMC = 0xFF07;

	uchar A;		// accumulator
	uchar F;		// flags [Zero][Subtract][Half Carry][Carry][0][0][0][0]
					// combine for 16 bit register AF, only valid operations are push and pop

	uchar B;
	uchar C;		// combine for 16 bit register BC

	uchar D;
	uchar E;		// combine for 16 bit register DE

	uchar H;
	uchar L;		// combine for 16 bit register HL
					// for some reason has significantly more operations than other combination registers

	ushort SP;		// stack pointer
	ushort PC;		// program counter

	bool interruptMasterEnable;
	bool shouldEnableInterrupts;
	bool shouldDisableInterrupts;

	Instruction *instructions[512];

	MemBlock *memory;
	uchar *memoryDirect;

	Cartridge *cartridge;

	int timerCounter;
	int dividerRegister;

	int scanlineCounter;

	bool disableIMEAfterNextInstruction;
	bool enableIMEAfterNextInstruction;

	unsigned long instrCounter = 0;

	Instruction *InvokeInstruction(int index);

	// memory operations
	uchar ReadByte(ushort address);
	ushort ReadShort(ushort address);

	void WriteByte(ushort address, uchar data);
	void WriteShort(ushort address, ushort data);

	void PushByte(uchar data);
	void PushShort(ushort data);

	uchar PopByte();
	ushort PopShort();


	// misc
	void PopulateInstructionList();

	uchar ReadImm8Arg();
	ushort ReadImm16Arg();

	void UpdateTimers(int cycles);
	void UpdateDividerRegister(int cycles);
	bool ClockIsEnabled();
	uchar GetClockFrequency();
	void SetClockFrequency();

	void RequestInterrupt(int flag);
	void HandleInterrupts();
	void ServiceInterrupt(int flag);

	void UpdateGraphics(int cycles);
	void SetLCDStatus();
	bool LCDIsEnabled();
	void DrawScanline();

	void DMATransfer(uchar data);

	void RenderTiles();
	void RenderSprites();
	Color GetColor(int colorNum, ushort address);

};

#endif