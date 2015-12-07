#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include "mem_block.h"
#include <string>

typedef unsigned char uchar;
typedef unsigned short ushort;

class Cartridge
{
	enum class CartType
	{
		NO_BANK,
		MBC_1,
		MBC_2
	};

public:
	Cartridge(const std::string &filePath);

	uchar ReadFromMemory(ushort address);
	uchar ReadFromROMBank(ushort address);
	uchar ReadFromRAM(ushort address);

	void WriteToMemory(ushort address, uchar data);
	void WriteToRAM(ushort address, uchar data);

private:
	MemBlock memory;
	MemBlock RAMBanks;
	CartType cartType;
	uchar currentROMBank;
	uchar currentRAMBank;
	bool ROMBanking;
	bool enableRAM;

	void HandleBanking(ushort address, uchar data);
	void DoRamBankEnable(ushort address, uchar data);
	void DoChangeLoROMBank(uchar data);
	void DoChangeHiROMBank(uchar data);
	void DoChangeRAMBank(uchar data);
	void DoChangeROMRAMMode(uchar data);
};

#endif