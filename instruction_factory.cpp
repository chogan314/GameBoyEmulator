#include "instruction_factory.h"
#include "cpu.h"

// INC reg8
void IncReg8(ParamInstruction<Reg8Param> &instruction)
{
	uchar &reg = instruction.params.reg;
	instruction.processor->SetSubtractFlag(0);
	instruction.processor->SetZeroFlag(reg == 0xff);
	instruction.processor->SetHalfCarryFlag(reg == 0xff);

	reg++;
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

// INC reg16
void IncReg16(ParamInstruction<Reg16Param> &instruction)
{
	instruction.params.reg->GetMemory()++;
	instruction.params.reg->Finalize();
}

// DEC reg16
void DecReg16(ParamInstruction<Reg16Param> &instruction)
{
	instruction.params.reg->GetMemory()--;
	instruction.params.reg->Finalize();
}

// LD reg16, imm16
void LdReg16Imm16(ParamInstruction<Reg16Param> &instruction)
{
	instruction.params.reg->GetMemory() = instruction.processor->ReadImm16Arg();

	instruction.params.reg->Finalize();
}

// ADD reg16, reg16
void AddReg16Reg16(ParamInstruction<Reg16Reg16Param> &instruction)
{

}

// INC (reg16)
void IncAddrReg16(ParamInstruction<Reg16Param> &instruction)
{
	CompositeRegister *reg = instruction.params.reg;
	instruction.processor->SetSubtractFlag(0);

	MemBlock *memory = instruction.processor->memory;
	ushort memVal = memory->ReadShort(reg->GetMemory());
	instruction.processor->SetZeroFlag(memVal == 0xffff);
	instruction.processor->SetHalfCarryFlag(memVal == 0xffff);

	memory->WriteShort(reg->GetMemory(), memVal++);
}

// DEC (reg16)
void DecAddrReg16(ParamInstruction<Reg16Param> &instruction)
{
	CompositeRegister *reg = instruction.params.reg;
	instruction.processor->SetSubtractFlag(1);

	MemBlock *memory = instruction.processor->memory;
	ushort memVal = memory->ReadShort(reg->GetMemory());
	instruction.processor->SetZeroFlag(memVal == 0x0001);
	instruction.processor->SetHalfCarryFlag(memVal == 0x0000);

	memory->WriteShort(reg->GetMemory(), memVal--);
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

// LD (imm16), reg16
void LdAddrImm16Reg16(ParamInstruction<Reg16Param> &instruction)
{
	MemBlock *memory = instruction.processor->memory;

	memory->WriteShort(instruction.processor->ReadImm16Arg(),
		instruction.params.reg->GetMemory());
}

InstructionFactory::InstructionFactory(CPU *processor) : 
	processor(processor)
{

}