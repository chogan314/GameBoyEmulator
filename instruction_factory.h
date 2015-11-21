#ifndef INSTRUCTION_FACTORY_H
#define INSTRUCTION_FACTORY_H

#include "instruction.h"
class CPU;

class InstructionFactory
{
public:
	InstructionFactory(CPU *processor);

	/*******************************
	******** Loads & Moves *********
	********************************/
	// LD reg8, imm8
	Instruction *MakeLdReg8Imm8(uchar &reg8);

	// LD reg8, reg8
	Instruction *MakeLdReg8Reg8(uchar &lhs, uchar &rhs);

	// LD reg8, (reg8)
	Instruction *MakeLdReg8AddrReg8(uchar &lhs, uchar &rhs);

	// LD reg8, (imm16)
	Instruction *MakeLdReg8AddrImm16(uchar &reg8);

	// LD reg8, (reg16)
	Instruction *MakeLdReg8AddrReg16(CompositeRegister *reg16, uchar &reg8);

	// LD reg8, (reg16+)
	Instruction *MakeLdReg8AddrIncReg16(CompositeRegister *reg16, uchar &reg8);

	// LD reg8, (reg16-)
	Instruction *MakeLdReg8AddrDecReg16(CompositeRegister *reg16, uchar &reg8);

	// LD (reg8), reg8
	Instruction *MakeLdAddrReg8Reg8(uchar &lhs, uchar &rhs);

	// LD (reg16), imm8
	Instruction *MakeLdAddrReg16Imm8(CompositeRegister *reg16);

	// LD (reg16), reg8
	Instruction *MakeLdAddrReg16Reg8(CompositeRegister *reg16, uchar &reg8);

	// LD (reg16+), reg8
	Instruction *MakeLdAddrIncReg16Reg8(CompositeRegister *reg16, uchar &reg8);

	// LD (reg16-), reg8
	Instruction *MakeLdAddrDecReg16Reg8(CompositeRegister *reg16, uchar &reg8);

	// LD (imm16), reg8
	Instruction *MakeLdAddrImm16Reg8(uchar &reg8);

	// LD reg16, imm16
	Instruction *MakeLdReg16Imm16(CompositeRegister *reg16);

	// LD reg16, reg16 + S-imm8
	Instruction *MakeLdReg16Reg16AddImm8S(CompositeRegister *lhs, CompositeRegister *rhs);

	// LD (imm16), reg16
	Instruction *MakeLdAddrImm16Reg16(CompositeRegister *reg16);


	// LDH (imm8), reg8
	Instruction *MakeLdHAddrImm8Reg8(uchar &reg8);

	// LDH reg8, (imm8)
	Instruction *MakeLdHReg8AddrImm8(uchar &reg8);


	// POP reg16
	Instruction *MakePopReg16(CompositeRegister *reg16);

	// PUSH reg16
	Instruction *MakePushReg16(CompositeRegister *reg16);

	/*******************************
	********* Math & Logic *********
	********************************/
	// INC reg8
	Instruction *MakeIncReg8(uchar &reg8);

	// INC (reg16) ; 8-bit
	Instruction *MakeIncAddrReg16(CompositeRegister *reg16);

	// INC reg16
	Instruction *MakeIncReg16(CompositeRegister *reg16);


	// DEC reg8
	Instruction *MakeDecReg8(uchar &reg8);

	// DEC (reg16) ; 8-bit
	Instruction *MakeDecAddrReg16(CompositeRegister *reg16);

	// DEC reg16
	Instruction *MakeDecReg16(CompositeRegister *reg16);


	// ADD reg8, imm8
	Instruction *MakeAddReg8Imm8(uchar &reg8);

	// ADD reg8, reg8
	Instruction *MakeAddReg8Reg(uchar &lhs, uchar &rhs);

	// ADD reg8, (reg16)
	Instruction *MakeAddReg8AddrReg16(CompositeRegister *reg16, uchar &reg8);

	// ADD reg16, reg16
	Instruction *MakeAddReg16Reg16(CompositeRegister *lhs, CompositeRegister *rhs);

	// ADD reg16, S-imm8
	Instruction *MakeAddReg16Imm8S(CompositeRegister *reg16);


	// ADC reg8, imm8
	Instruction *MakeAdcReg8Imm8(uchar &reg8);

	// ADC reg8, reg8
	Instruction *MakeAdcReg8Reg8(uchar &lhs, uchar &rhs);

	// ADC reg8, (reg16)
	Instruction *MakeAdcReg8AddrReg16(CompositeRegister *reg16, uchar &reg8);


	// SUB imm8
	Instruction *MakeSubImm8();

	// SUB reg8
	Instruction *MakeSubReg8(uchar &reg8);

	// SUB (reg16)
	Instruction *MakeSubAddrReg16(CompositeRegister *reg16);


	// SBC reg8, imm8
	Instruction *MakeSbcReg8Imm8(uchar &reg8);

	// SBC reg8, reg8
	Instruction *MakeSbcReg8Reg8(uchar &lhs, uchar &rhs);

	// SBC reg8, (reg16)
	Instruction *MakeSbcReg8AddrReg16(CompositeRegister *reg16, uchar &reg8);


	// AND imm8
	Instruction *MakeAndImm8();

	// AND reg8
	Instruction *MakeAndReg8(uchar &reg8);

	// AND (reg16)
	Instruction *MakeAndAddrReg16(CompositeRegister *reg16);


	// XOR imm8
	Instruction *MakeXorImm8();

	// XOR reg8
	Instruction *MakeXorReg8(uchar &reg8);

	// XOR (reg16)
	Instruction *MakeXorAddrReg16(CompositeRegister *reg16);


	// OR imm8
	Instruction *MakeOrImm8();

	// OR reg8
	Instruction *MakeOrReg8(uchar &reg8);

	// OR (reg16)
	Instruction *MakeOrAddrReg16(CompositeRegister *reg16);


	// CP imm8
	Instruction *MakeCpImm8();

	// CP reg8
	Instruction *MakeCpReg8(uchar &reg8);

	// CP (reg16)
	Instruction *MakeCpAddrReg16(CompositeRegister *reg16);


	// DAA
	Instruction *MakeDAA();

	// CPL
	Instruction *MakeCPL();

	// SCF
	Instruction *MakeSCF();

	// CCF
	Instruction *MakeCCF();

	/*******************************
	****** Shifts & Rotations ******
	********************************/
	// RLCA
	Instruction *MakeRLCA();

	// RRCA
	Instruction *MakeRRCA();

	// RRA
	Instruction *MakeRRA();

	// RLA
	Instruction *MakeRLA();


	// RLC reg8
	Instruction *MakeRlcReg8(uchar &reg8);

	// RLC (reg16)
	Instruction *MakeRlcAddrReg16(CompositeRegister *reg16);


	// RRC reg8
	Instruction *MakeRrcReg8(uchar &reg8);

	// RRC (reg16)
	Instruction *MakeRrcAddrReg16(CompositeRegister *reg16);


	// RL reg8
	Instruction *MakeRlReg8(uchar &reg8);

	// RL (reg16)
	Instruction *MakeRlAddrReg16(CompositeRegister *reg16);


	// RR reg8
	Instruction *MakeRrReg8(uchar &reg8);

	// RR (reg16)
	Instruction *MakeRrAddrReg16(CompositeRegister *reg16);


	// SLA reg8
	Instruction *MakeSlaReg8(uchar &reg8);

	// SLA (reg16)
	Instruction *MakeSlaAddrReg16(CompositeRegister *reg16);


	// SRA reg8
	Instruction *MakeSraReg8(uchar &reg8);

	// SRA (reg16)
	Instruction *MakeSraAddrReg16(CompositeRegister *reg16);


	// SWAP reg8
	Instruction *MakeSwapReg8(uchar &reg8);

	// SWAP (reg16)
	Instruction *MakeSwapAddrReg16(CompositeRegister *reg16);


	// SRL reg8
	Instruction *MakeSrlReg8(uchar &reg8);

	// SRL (reg16)
	Instruction *MakeSrlAddrReg16(CompositeRegister *reg16);


	// BIT imm8, reg8
	Instruction *MakeBitImm8Reg8(uchar imm8, uchar &reg8);

	// BIT imm8, (reg16)
	Instruction *MakeBitImm8AddrReg16(uchar imm8, CompositeRegister *reg16);


	// RES imm8, reg8
	Instruction *MakeResImm8Reg8(uchar imm8, uchar &reg8);

	// RES imm8, (reg16)
	Instruction *MakeResImm8AddrReg16(uchar imm8, CompositeRegister *reg16);


	// SET imm8, reg8
	Instruction *MakeSetImm8Reg8(uchar imm8, uchar &reg8);

	// SET imm8, (reg16)
	Instruction *MakeSetImm8AddrReg16(uchar imm8, CompositeRegister *reg16);

	/*******************************
	******** Jumps & Calls *********
	********************************/
	// JR S-imm8
	Instruction *MakeJrImm8S();

	// JR CONDITION, S-imm8
	Instruction *MakeJrCondImm8S(uchar flagOffset, bool expectedValue);


	// JP imm16
	Instruction *MakeJpImm16();

	// JP CONDITION, imm16
	Instruction *MakeJpCondImm16(uchar flagOffset, bool expectedValue);

	// JP (reg16)
	Instruction *MakeJpAddrReg16(CompositeRegister *reg16);


	// CALL imm16
	Instruction *MakeCallImm16();

	// CALL CONDITION, imm16
	Instruction *MakeCallCondImm16(uchar flagOffset, bool expectedValue);


	// RET
	Instruction *MakeRET();

	// RET CONDITION
	Instruction *MakeRetCond(uchar flagOffset, bool expectedValue);


	// RETI
	Instruction *MakeRETI();


	// RST imm8
	Instruction *MakeRstImm8(uchar imm8);

	/*******************************
	******** Misc & Control ********
	********************************/
	// NOP
	Instruction *MakeNOP();

	// STOP 0
	Instruction *MakeStop0();

	// HALT
	Instruction *MakeHALT();

	// PREFIX CB
	Instruction *MakePrefixCB();

	// DI
	Instruction *MakeDI();

	// EI
	Instruction *MakeEI();
private:
	CPU *processor;
};

// INSTRUCTION onCall FUNCTIONS:

/*******************************
******** Loads & Moves *********
********************************/
void LdReg8Imm8(ParamInstruction<Reg8Param> &instruction);					// LD reg8, imm8
void LdReg8Reg8(ParamInstruction<Reg8Reg8Param> &instruction);				// LD reg8, reg8
void LdReg8AddrReg8(ParamInstruction<Reg8Reg8Param> &instruction);			// LD reg8, (reg8)
void LdReg8AddrImm16(ParamInstruction<Reg8Param> &instruction);				// LD reg8, (imm16)
void LdReg8AddrReg16(ParamInstruction<Reg16Reg8Param> &instruction);		// LD reg8, (reg16)
void LdReg8AddrIncReg16(ParamInstruction<Reg16Reg8Param> &instruction);		// LD reg8, (reg16+)
void LdReg8AddrDecReg16(ParamInstruction<Reg16Reg8Param> &instruction);		// LD reg8, (reg16-)
void LdAddrReg8Reg8(ParamInstruction<Reg8Reg8Param> &instruction);			// LD (reg8), reg8
void LdAddrReg16Imm8(ParamInstruction<Reg16Param> &instruction);			// LD (reg16), imm8
void LdAddrReg16Reg8(ParamInstruction<Reg16Reg8Param> &instruction);		// LD (reg16), reg8
void LdAddrIncReg16Reg8(ParamInstruction<Reg16Reg8Param> &instruction);		// LD (reg16+), reg8
void LdAddrDecReg16Reg8(ParamInstruction<Reg16Reg8Param> &instruction);		// LD (reg16-), reg8
void LdAddrImm16Reg8(ParamInstruction<Reg8Param> &instruction);				// LD (imm16), reg8
void LdReg16Imm16(ParamInstruction<Reg16Param> &instruction);				// LD reg16, imm16
void LdReg16Reg16AddImm8S(ParamInstruction<Reg16Reg16Param> &instruction);	// LD reg16, reg16 + S-imm8
void LdAddrImm16Reg16(ParamInstruction<Reg16Param> &instruction);			// LD (imm16), reg16
void LdHAddrImm8Reg8(ParamInstruction<Reg8Param> &instruction);				// LDH (imm8), reg8
void LdHReg8AddrImm8(ParamInstruction<Reg8Param> &instruction);				// LDH reg8, (imm8)
void PopReg16(ParamInstruction<Reg16Param> &instruction);					// POP reg16
void PushReg16(ParamInstruction<Reg16Param> &instruction);					// PUSH reg16

/*******************************
********* Math & Logic *********
********************************/
void IncReg8(ParamInstruction<Reg8Param> &instruction);						// INC reg8
void IncAddrReg16(ParamInstruction<Reg16Param> &instruction);				// INC (reg16) ; 8-bit
void IncReg16(ParamInstruction<Reg16Param> &instruction);					// INC reg16
void DecReg8(ParamInstruction<Reg8Param> &instruction);						// DEC reg8
void DecAddrReg16(ParamInstruction<Reg16Param> &instruction);				// DEC (reg16) ; 8-bit
void DecReg16(ParamInstruction<Reg16Param> &instruction);					// DEC reg16
void AddReg8Imm8(ParamInstruction<Reg8Param> &instruction);					// ADD reg8, imm8
void AddReg8Reg(ParamInstruction<Reg8Reg8Param> &instruction);				// ADD reg8, reg8
void AddReg8AddrReg16(ParamInstruction<Reg16Reg8Param> &instruction);		// ADD reg8, (reg16)
void AddReg16Reg16(ParamInstruction<Reg16Reg16Param> &instruction);			// ADD reg16, reg16
void AddReg16Imm8S(ParamInstruction<Reg16Param> &instruction);				// ADD reg16, S-imm8
void AdcReg8Imm8(ParamInstruction<Reg8Param> &instruction);					// ADC reg8, imm8
void AdcReg8Reg8(ParamInstruction<Reg8Reg8Param> &instruction);				// ADC reg8, reg8
void AdcReg8AddrReg16(ParamInstruction<Reg16Reg8Param> &instruction);		// ADC reg8, (reg16)
void SubImm8(NoParamInstruction &instruction);								// SUB imm8
void SubReg8(ParamInstruction<Reg8Param> &instruction);						// SUB reg8
void SubAddrReg16(ParamInstruction<Reg16Param> &instruction);				// SUB (reg16)
void SbcReg8Imm8(ParamInstruction<Reg8Param> &instruction);					// SBC reg8, imm8
void SbcReg8Reg8(ParamInstruction<Reg8Reg8Param> &instruction);				// SBC reg8, reg8
void SbcReg8AddrReg16(ParamInstruction<Reg16Reg8Param> &instruction);		// SBC reg8, (reg16)
void AndImm8(NoParamInstruction &instruction);								// AND imm8
void AndReg8(ParamInstruction<Reg8Param> &instruction);						// AND reg8
void AndAddrReg16(ParamInstruction<Reg16Param> &instruction);				// AND (reg16)
void XorImm8(NoParamInstruction &instruction);								// XOR imm8
void XorReg8(ParamInstruction<Reg8Param> &instruction);						// XOR reg8
void XorAddrReg16(ParamInstruction<Reg16Param> &instruction);				// XOR (reg16)
void OrImm8(NoParamInstruction &instruction);								// OR imm8
void OrReg8(ParamInstruction<Reg8Param> &instruction);						// OR reg8
void OrAddrReg16(ParamInstruction<Reg16Param> &instruction);				// OR (reg16)
void CpImm8(NoParamInstruction &instruction);								// CP imm8
void CpReg8(ParamInstruction<Reg8Param> &instruction);						// CP reg8
void CpAddrReg16(ParamInstruction<Reg16Param> &instruction);				// CP (reg16)
void DAA(NoParamInstruction &instruction);									// DAA
void CPL(NoParamInstruction &instruction);									// CPL
void SCF(NoParamInstruction &instruction);									// SCF
void CCF(NoParamInstruction &instruction);									// CCF

/*******************************
****** Shifts & Rotations ******
********************************/
void RLCA(NoParamInstruction &instruction);									// RLCA
void RRCA(NoParamInstruction &instruction);									// RRCA
void RRA(NoParamInstruction &instruction);									// RRA
void RLA(NoParamInstruction &instruction);									// RLA
void RlcReg8(ParamInstruction<Reg8Param> &instruction);						// RLC reg8
void RlcAddrReg16(ParamInstruction<Reg16Param> &instruction);				// RLC (reg16)
void RrcReg8(ParamInstruction<Reg8Param> &instruction);						// RRC reg8
void RrcAddrReg16(ParamInstruction<Reg16Param> &instruction);				// RRC (reg16)
void RlReg8(ParamInstruction<Reg8Param> &instruction);						// RL reg8
void RlAddrReg16(ParamInstruction<Reg16Param> &instruction);				// RL (reg16)
void RrReg8(ParamInstruction<Reg8Param> &instruction);						// RR reg8
void RrAddrReg16(ParamInstruction<Reg16Param> &instruction);				// RR (reg16)
void SlaReg8(ParamInstruction<Reg8Param> &instruction);						// SLA reg8
void SlaAddrReg16(ParamInstruction<Reg16Param> &instruction);				// SLA (reg16)
void SraReg8(ParamInstruction<Reg8Param> &instruction);						// SRA reg8
void SraAddrReg16(ParamInstruction<Reg16Param> &instruction);				// SRA (reg16)
void SwapReg8(ParamInstruction<Reg8Param> &instruction);					// SWAP reg8
void SwapAddrReg16(ParamInstruction<Reg16Param> &instruction);				// SWAP (reg16)
void SrlReg8(ParamInstruction<Reg8Param> &instruction);						// SRL reg8
void SrlAddrReg16(ParamInstruction<Reg16Param> &instruction);				// SRL (reg16)
void BitImm8Reg8(ParamInstruction<Imm8Reg8Param> &instruction);				// BIT imm8, reg8
void BitImm8AddrReg16(ParamInstruction<Imm8Reg16Param> &instruction);		// BIT imm8, (reg16)
void ResImm8Reg8(ParamInstruction<Imm8Reg8Param> &instruction);				// RES imm8, reg8
void ResImm8AddrReg16(ParamInstruction<Imm8Reg16Param> &instruction);		// RES imm8, (reg16)
void SetImm8Reg8(ParamInstruction<Imm8Reg8Param> &instruction);				// SET imm8, reg8
void SetImm8AddrReg16(ParamInstruction<Imm8Reg16Param> &instruction);		// SET imm8, (reg16)

/*******************************
******** Jumps & Calls *********
********************************/
void JrImm8S(NoParamInstruction &instruction);								// JR S-imm8
void JrCondImm8S(ParamInstruction<ConditionalParam> &instruction);			// JR CONDITION, S-imm8
void JpImm16(NoParamInstruction &instruction);								// JP imm16
void JpCondImm16(ParamInstruction<ConditionalParam> &instruction);			// JP CONDITION, imm16
void JpAddrReg16(ParamInstruction<Reg16Param> &instruction);				// JP (reg16)
void CallImm16(NoParamInstruction &instruction);							// CALL imm16
void CallCondImm16(ParamInstruction<ConditionalParam> &instruction);		// CALL CONDITION, imm16
void RET(NoParamInstruction &instruction);									// RET
void RetCond(ParamInstruction<ConditionalParam> &instruction);				// RET CONDITION
void RETI(NoParamInstruction &instruction);									// RETI
void RstImm8(ParamInstruction<Imm8Param> &instruction);						// RST imm8

/*******************************
******** Misc & Control ********
********************************/
void NOP(NoParamInstruction &instruction);									// NOP
void Stop0(NoParamInstruction &instruction);								// STOP 0
void HALT(NoParamInstruction &instruction);									// HALT
void PrefixCB(NoParamInstruction &instruction);								// PREFIX CB
void DI(NoParamInstruction &instruction);									// DI
void EI(NoParamInstruction &instruction);									// EI

#endif