#ifndef COMPOSITE_REGISTER_H
#define COMPOSITE_REGISTER_H

typedef unsigned char uchar;
typedef unsigned short ushort;

class CompositeRegister
{
public:
	virtual ushort &GetMemory() = 0;

	virtual void Finalize() = 0;
protected:
	ushort memory;
};

class CReg16Bit : public CompositeRegister
{
public:
	CReg16Bit(ushort &reg);

	ushort &GetMemory();

	void Finalize();
private:
	ushort &reg;
};

class CReg8Bit8Bit : public CompositeRegister
{
public:
	CReg8Bit8Bit(uchar &msb, uchar &lsb);

	ushort &GetMemory();
	
	void Finalize();
private:
	uchar &msb;
	uchar &lsb;
};

#endif