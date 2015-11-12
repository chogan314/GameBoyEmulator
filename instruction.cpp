#include "instruction.h"
#include "cpu.h"

/*******************************
**********Instruction***********
********************************/
Instruction::Instruction(CPU *processor, std::string mnemonic,
		int size, int duration) :
	processor(processor),
	mnemonic(mnemonic),
	size(size),
	duration(duration)
{

}

void Instruction::Call()
{
	processor->PC += size;
}

/*******************************
*******NoParamInstruction*******
********************************/
NoParamInstruction::NoParamInstruction(CPU *processor, std::string mnemonic,
		int size, int duration, NoParamOnCall onCall) :
	Instruction(processor, mnemonic, size, duration),
	onCall(onCall)
{

}

void NoParamInstruction::Call()
{
	onCall(*this);
	Instruction::Call();
}

///*******************************
//******Instruction Callbacks*****
//********************************/
//
//
//void LoadCReg16Imm16(ParamInstruction<CReg16Param> &instruction)
//{
//
//}
//
//
///*******************************
//******Instruction Creation******
//********************************/
//
//// NOP
//Instruction *MakeOp0x00(CPU *processor)
//{
//	return nullptr;
//}
//
//// LD BC, d16
//Instruction *MakeOp0x01(CPU *processor)
//{
//	return nullptr;
//}
//
//// LD (BC), A
//Instruction *MakeOp0x02(CPU *processor)
//{
//	return nullptr;
//}
//
//// INC BC
//Instruction *MakeOp0x03(CPU *processor)
//{
//	return nullptr;
//}
//
//// INC B
//Instruction *MakeOp0x04(CPU *processor)
//{
//	return nullptr;
//}
//
//// DEC B
//Instruction *MakeOp0x05(CPU *processor)
//{
//	return nullptr;
//}
//
//// LD B, d8
//Instruction *MakeOp0x06(CPU *processor)
//{
//	return nullptr;
//}
//
//// RLCA
//Instruction *MakeOp0x07(CPU *processor)
//{
//	return nullptr;
//}
//
//// LD (a16), SP
//Instruction *MakeOp0x08(CPU *processor)
//{
//	return nullptr;
//}
//
//// ADD HL, BC
//Instruction *MakeOp0x09(CPU *processor)
//{
//	return nullptr;
//}
//
//// LD A, (BC)
//Instruction *MakeOp0x0A(CPU *processor)
//{
//	return nullptr;
//}
//
//// DEC BC
//Instruction *MakeOp0x0B(CPU *processor)
//{
//	return nullptr;
//}
//
//// INC C
//Instruction *MakeOp0x0C(CPU *processor)
//{
//	return nullptr;
//}
//
//// DEC C
//Instruction *MakeOp0x0D(CPU *processor)
//{
//	return nullptr;
//}
//
//// LD C, d8
//Instruction *MakeOp0x0E(CPU *processor)
//{
//	return nullptr;
//}
//
//// RRCA
//Instruction *MakeOp0x0F(CPU *processor)
//{
//	return nullptr;
//}
//
//// STOP 0
//Instruction *MakeOp0x10(CPU *processor)
//{
//	return nullptr;
//}
//
//// LD DE, d16
//Instruction *MakeOp0x11(CPU *processor)
//{
//	return nullptr;
//}
//
//// LD (DE), A
//Instruction *MakeOp0x12(CPU *processor)
//{
//	return nullptr;
//}
//
//// INC DE
//Instruction *MakeOp0x13(CPU *processor)
//{
//	return nullptr;
//}


//Instruction *MakeInstruction(CPU *processor)
//{
//	Reg8Reg8Param params(processor->B, processor->D);
//
//	ParamOnCall<Reg8Reg8Param> onCall = [](ParamInstruction<Reg8Reg8Param> &instruction)
//	{
//		instruction.params.lhs = instruction.params.rhs;
//	};
//
//	return new ParamInstruction<Reg8Reg8Param>(processor, "LD B, D", 1, 4, params, onCall);
//}