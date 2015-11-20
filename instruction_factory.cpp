#include "instruction_factory.h"
#include "cpu.h"

// INSTRUCTION onCall FUNCTIONS:

/*******************************
******** Loads & Moves *********
********************************/
// LD reg8, imm8
void LdReg8Imm8(ParamInstruction<Reg8Param> &instruction)
{
	instruction.params.reg = instruction.processor->ReadImm8Arg();
}

// LD reg8, reg8
void LdReg8Reg8(ParamInstruction<Reg8Reg8Param> &instruction)
{
	instruction.params.lhs = instruction.params.rhs;
}

// LD reg8, (reg8)
void LdReg8AddrReg8(ParamInstruction<Reg8Reg8Param> &instruction)
{

}

// LD reg8, (imm16)
void LdReg8AddrImm16(ParamInstruction<Reg8Param> &instruction)
{

}

// LD reg8, (reg16)
void LdReg8AddrReg16(ParamInstruction<Reg16Reg8Param> &instruction)
{
	MemBlock *memory = instruction.processor->memory;

	instruction.params.reg8 = memory->ReadByte(instruction.params.reg16->GetMemory());
}

// LD reg8, (reg16+)
void LdReg8AddrIncReg16(ParamInstruction<Reg16Reg8Param> &instruction)
{
	MemBlock *memory = instruction.processor->memory;

	instruction.params.reg8 = memory->ReadByte(instruction.params.reg16->GetMemory());

	instruction.params.reg16->GetMemory()++;
	instruction.params.reg16->Finalize();
}

// LD reg8, (reg16-)
void LdReg8AddrDecReg16(ParamInstruction<Reg16Reg8Param> &instruction)
{

}

// LD (reg8), reg8
void LdAddrReg8Reg8(ParamInstruction<Reg8Reg8Param> &instruction)
{

}

// LD (reg16), imm8
void LdAddrReg16Imm8(ParamInstruction<Reg16Param> &instruction)
{
	MemBlock *memory = instruction.processor->memory;

	memory->WriteByte(instruction.params.reg->GetMemory(),
		instruction.processor->ReadImm8Arg());
}

// LD (reg16), reg8
void LdAddrReg16Reg8(ParamInstruction<Reg16Reg8Param> &instruction)
{
	MemBlock *memory = instruction.processor->memory;

	memory->WriteByte(instruction.params.reg16->GetMemory(),
		instruction.params.reg8);
}

// LD (reg16+), reg8
void LdAddrIncReg16Reg8(ParamInstruction<Reg16Reg8Param> &instruction)
{
	MemBlock *memory = instruction.processor->memory;

	memory->WriteByte(instruction.params.reg16->GetMemory(),
		instruction.params.reg8);

	instruction.params.reg16->GetMemory()++;
	instruction.params.reg16->Finalize();
}

// LD (reg16-), reg8
void LdAddrDecReg16Reg8(ParamInstruction<Reg16Reg8Param> &instruction)
{
	MemBlock *memory = instruction.processor->memory;

	memory->WriteByte(instruction.params.reg16->GetMemory(),
		instruction.params.reg8);

	instruction.params.reg16->GetMemory()--;
	instruction.params.reg16->Finalize();
}

// LD (imm16), reg8
void LdAddrImm16Reg8(ParamInstruction<Reg8Param> &instruction)
{

}

// LD reg16, imm16
void LdReg16Imm16(ParamInstruction<Reg16Param> &instruction)
{
	instruction.params.reg->GetMemory() = instruction.processor->ReadImm16Arg();

	instruction.params.reg->Finalize();
}

// LD reg16, reg16 + S-imm8
void LdReg16Reg16AddImm8S(ParamInstruction<Reg16Reg16Param> &instruction)
{

}

// LD (imm16), reg16
void LdAddrImm16Reg16(ParamInstruction<Reg16Param> &instruction)
{
	MemBlock *memory = instruction.processor->memory;

	memory->WriteShort(instruction.processor->ReadImm16Arg(),
		instruction.params.reg->GetMemory());
}


// LDH (imm8), reg8
void LdHAddrImm8Reg8(ParamInstruction<Reg8Param> &instruction)
{

}

// LDH reg8, (imm8)
void LdHReg8AddrImm8(ParamInstruction<Reg8Param> &instruction)
{

}


// POP reg16
void PopReg16(ParamInstruction<Reg16Param> &instruction)
{

}

// PUSH reg16
void PushReg16(ParamInstruction<Reg16Param> &instruction)
{

}

/*******************************
********* Math & Logic *********
********************************/
// INC reg8
void IncReg8(ParamInstruction<Reg8Param> &instruction)
{
	uchar &reg = instruction.params.reg;
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetZeroFlag(reg == 0xff);
	instruction.processor->SetHalfCarryFlag(reg == 0xff);

	reg++;
}

// INC (reg16) ; 8-bit
void IncAddrReg16(ParamInstruction<Reg16Param> &instruction)
{

}

// INC reg16
void IncReg16(ParamInstruction<Reg16Param> &instruction)
{
	instruction.params.reg->GetMemory()++;
	instruction.params.reg->Finalize();
}


// DEC reg8
void DecReg8(ParamInstruction<Reg8Param> &instruction)
{
	uchar &reg = instruction.params.reg;
	instruction.processor->SetSubtractFlag(1);
	instruction.processor->SetZeroFlag(reg == 0x01);
	instruction.processor->SetHalfCarryFlag(reg == 0x00);

	reg--;
}

// DEC (reg16) ; 8-bit
void DecAddrReg16(ParamInstruction<Reg16Param> &instruction)
{

}

// DEC reg16
void DecReg16(ParamInstruction<Reg16Param> &instruction)
{
	instruction.params.reg->GetMemory()--;
	instruction.params.reg->Finalize();
}


// ADD reg8, imm8
void AddReg8Imm8(ParamInstruction<Reg8Param> &instruction)
{

}

// ADD reg8, reg8
void AddReg8Reg(ParamInstruction<Reg8Reg8Param> &instruction)
{

}

// ADD reg8, (reg16)
void AddReg8AddrReg16(ParamInstruction<Reg16Reg8Param> &instruction)
{

}

// ADD reg16, reg16
void AddReg16Reg16(ParamInstruction<Reg16Reg16Param> &instruction)
{

}

// ADD reg16, S-imm8
void AddReg16Imm8S(ParamInstruction<Reg16Param> &instruction)
{

}


// ADC reg8, imm8
void AdcReg8Imm8(ParamInstruction<Reg8Param> &instruction)
{

}

// ADC reg8, reg8
void AdcReg8Reg8(ParamInstruction<Reg8Reg8Param> &instruction)
{

}

// ADC reg8, (reg16)
void AdcReg8AddrReg16(ParamInstruction<Reg16Reg8Param> &instruction)
{

}


// SUB imm8
void SubImm8(NoParamInstruction &instruction)
{

}

// SUB reg8
void SubReg8(ParamInstruction<Reg8Param> &instruction)
{

}

// SUB (reg16)
void SubAddrReg16(ParamInstruction<Reg16Param> &instruction)
{

}


// SBC reg8, imm8
void SbcReg8Imm8(ParamInstruction<Reg8Param> &instruction)
{

}

// SBC reg8, reg8
void SbcReg8Reg8(ParamInstruction<Reg8Reg8Param> &instruction)
{

}

// SBC reg8, (reg16)
void SbcReg8AddrReg16(ParamInstruction<Reg16Reg8Param> &instruction)
{

}


// AND imm8
void AndImm8(NoParamInstruction &instruction)
{

}

// AND reg8
void AndReg8(ParamInstruction<Reg8Param> &instruction)
{

}

// AND (reg16)
void AndAddrReg16(ParamInstruction<Reg16Param> &instruction)
{

}


// XOR imm8
void XorImm8(NoParamInstruction &instruction)
{

}

// XOR reg8
void XorReg8(ParamInstruction<Reg8Param> &instruction)
{

}

// XOR (reg16)
void XorAddrReg16(ParamInstruction<Reg16Param> &instruction)
{

}


// OR imm8
void OrImm8(NoParamInstruction &instruction)
{

}

// OR reg8
void OrReg8(ParamInstruction<Reg8Param> &instruction)
{

}

// OR (reg16)
void OrAddrReg16(ParamInstruction<Reg16Param> &instruction)
{

}


// CP imm8
void CpImm8(NoParamInstruction &instruction)
{

}

// CP reg8
void CpReg8(ParamInstruction<Reg8Param> &instruction)
{

}

// CP (reg16)
void CpAddrReg16(ParamInstruction<Reg16Param> &instruction)
{

}


// DAA
void DAA(NoParamInstruction &instruction)
{

}

// CPL
void CPL(NoParamInstruction &instruction)
{

}

// SCF
void SCF(NoParamInstruction &instruction)
{

}

// CCF
void CCF(NoParamInstruction &instruction)
{

}

/*******************************
****** Shifts & Rotations ******
********************************/
// RLCA
void RLCA(NoParamInstruction &instruction)
{

}

// RRCA
void RRCA(NoParamInstruction &instruction)
{

}

// RRA
void RRA(NoParamInstruction &instruction)
{

}

// RLA
void RLA(NoParamInstruction &instruction)
{

}


// RLC reg8
void RlcReg8(ParamInstruction<Reg8Param> &instruction)
{

}

// RLC (reg16)
void RlcAddrReg16(ParamInstruction<Reg16Param> &instruction)
{

}


// RRC reg8
void RrcReg8(ParamInstruction<Reg8Param> &instruction)
{

}

// RRC (reg16)
void RrcAddrReg16(ParamInstruction<Reg16Param> &instruction)
{

}


// RL reg8
void RlReg8(ParamInstruction<Reg8Param> &instruction)
{

}

// RL (reg16)
void RlAddrReg16(ParamInstruction<Reg16Param> &instruction)
{

}


// RR reg8
void RrReg8(ParamInstruction<Reg8Param> &instruction)
{

}

// RR (reg16)
void RrAddrReg16(ParamInstruction<Reg16Param> &instruction)
{

}


// SLA reg8
void SlaReg8(ParamInstruction<Reg8Param> &instruction)
{

}

// SLA (reg16)
void SlaAddrReg16(ParamInstruction<Reg16Param> &instruction)
{

}


// SRA reg8
void SraReg8(ParamInstruction<Reg8Param> &instruction)
{

}

// SRA (reg16)
void SraAddrReg16(ParamInstruction<Reg16Param> &instruction)
{

}


// SWAP reg8
void SwapReg8(ParamInstruction<Reg8Param> &instruction)
{

}

// SWAP (reg16)
void SwapAddrReg16(ParamInstruction<Reg16Param> &instruction)
{

}


// SRL reg8
void SrlReg8(ParamInstruction<Reg8Param> &instruction)
{

}

// SRL (reg16)
void SrlAddrReg16(ParamInstruction<Reg16Param> &instruction)
{

}


// BIT imm8, reg8
void BitImm8Reg8(ParamInstruction<Imm8Reg8Param> &instruction)
{

}

// BIT imm8, (reg16)
void BitImm8AddrReg16(ParamInstruction<Imm8Reg16Param> &instruction)
{

}


// RES imm8, reg8
void ResImm8Reg8(ParamInstruction<Imm8Reg8Param> &instruction)
{

}

// RES imm8, (reg16)
void ResImm8AddrReg16(ParamInstruction<Imm8Reg16Param> &instruction)
{

}


// SET imm8, reg8
void SetImm8Reg8(ParamInstruction<Imm8Reg8Param> &instruction)
{

}

// SET imm8, (reg16)
void SetImm8AddrReg16(ParamInstruction<Imm8Reg16Param> &instruction)
{

}

/*******************************
******** Jumps & Calls *********
********************************/
// JR S-imm8
void JrImm8S(NoParamInstruction &instruction)
{

}

// JR CONDITION, S-imm8
void JrCondImm8S(ParamInstruction<ConditionalParam> &instruction)
{

}


// JP imm16
void JpImm16(NoParamInstruction &instruction)
{

}

// JP CONDITION, imm16
void JpCondImm16(ParamInstruction<ConditionalParam> &instruction)
{

}

// JP (reg16)
void JpAddrReg16(ParamInstruction<Reg16Param> &instruction)
{

}


// CALL imm16
void CallImm16(NoParamInstruction &instruction)
{

}

// CALL CONDITION, imm16
void CallCondImm16(ParamInstruction<ConditionalParam> &instruction)
{

}


// RET
void RET(NoParamInstruction &instruction)
{

}

// RET CONDITION
void RetCond(ParamInstruction<ConditionalParam> &instruction)
{

}


// RETI
void RETI(NoParamInstruction &instruction)
{

}


// RST imm8
void RstImm8(ParamInstruction<Imm8Param> &instruction)
{

}

/*******************************
******** Misc & Control ********
********************************/
// NOP
void NOP(NoParamInstruction &instruction)
{

}

// STOP 0
void Stop0(NoParamInstruction &instruction)
{

}

// HALT
void HALT(NoParamInstruction &instruction)
{

}

// PREFIX CB
void PrefixCB(NoParamInstruction &instruction)
{

}

// DI
void DI(NoParamInstruction &instruction)
{

}

// EI
void EI(NoParamInstruction &instruction)
{

}

InstructionFactory::InstructionFactory(CPU *processor) : 
	processor(processor)
{

}