#include "instruction_factory.h"
#include "cpu.h"

void LoadCReg16Imm16(ParamInstruction<CReg16Param> &instruction)
{
	instruction.params.reg.GetMemory() = 
		instruction.processor->memory->ReadShort(instruction.processor->PC + 8);

	instruction.params.reg.Finalize();
}

InstructionFactory::InstructionFactory(CPU *processor) : 
	processor(processor)
{

}

// LD BC, d16
Instruction *InstructionFactory::MakeOp0x01()
{
	CReg16Param param(processor->B, processor->C);
	return new ParamInstruction<CReg16Param>(processor, "LD BC, d16", 3, 12, param, LoadCReg16Imm16);
}