typedef unsigned short ushort;
typedef unsigned char uchar;

class Instruction;

class CPU
{
	friend class Instruction;
	friend Instruction *MakeInstruction(CPU *processor);
public:
	CPU();
private:
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
};