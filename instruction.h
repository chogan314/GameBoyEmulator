#include <functional>
#include <string>

class CPU;
template <typename T>
class ParamInstruction;
class NoParamInstruction;

typedef unsigned char uchar;
template <typename T>
using ParamOnCall = void(*)(ParamInstruction<T> &instruction);
using NoParamOnCall = void(*)(NoParamInstruction &instruction);

/*******************************
*******Instruction Params*******
********************************/
struct Reg8Reg8Param
{
	uchar &regA;
	uchar &regB;

	Reg8Reg8Param(uchar &regA, uchar &regB) :
		regA(regA),
		regB(regB)
	{ }
};

// comp reg16, imm16

// comp reg16, reg8

// reg8

// reg8, imm8

// imm16, reg16

// comp reg16, comp reg16

// reg8, comp reg16

// reg16

// imm16

/*******************************
**********Instruction***********
********************************/
class Instruction
{
public:
	Instruction(CPU *processor, std::string mnemonic,
		int size, int duration);

	virtual ~Instruction() { }

	virtual void Call();
protected:
	std::string mnemonic;
	// affects memory?
	// flags affected?
	int size;		// in bytes
	int duration;	// in cpu cycles
	CPU *processor;
};

/*******************************
*******NoParamInstruction*******
********************************/
class NoParamInstruction : public Instruction
{
public:
	NoParamInstruction(CPU *processor, std::string mnemonic,
		int size, int duration, NoParamOnCall onCall);

	void Call();
private:
	NoParamOnCall onCall;
};

/*******************************
********ParamInstruction********
********************************/
template <typename T>
class ParamInstruction : public Instruction
{
	friend Instruction *MakeInstruction(CPU *processor);
public:
	ParamInstruction(CPU *processor, std::string mnemonic,
		int size, int duration, T params, ParamOnCall<T> onCall);

	void Call();
private:
	T params;
	ParamOnCall<T> onCall;
};