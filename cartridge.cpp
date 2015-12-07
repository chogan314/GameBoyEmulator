#include "cartridge.h"
#include <fstream>
#include <iostream>
#include "hex_printing.h"
#include <iomanip>
#include "utils.h"

Cartridge::Cartridge(const std::string &filePath) :
	memory(0x200000),
	RAMBanks(0x8000),
	currentROMBank(1),
	currentRAMBank(0)
{
	memory.CopyFromFile(filePath);

	uchar data = memory.ReadByte(0x147);

	switch (data)
	{
	case 1:
	case 2:
	case 3:
		cartType = CartType::MBC_1;
		break;
	case 5:
	case 6:
		cartType = CartType::MBC_2;
		break;
	default:
		cartType = CartType::NO_BANK;
		break;
	}
}

uchar Cartridge::ReadFromMemory(ushort address)
{
	return memory.ReadByte(address);
}

uchar Cartridge::ReadFromROMBank(ushort address)
{
	return memory.ReadByte(address + currentROMBank * 0x4000);
}

uchar Cartridge::ReadFromRAM(ushort address)
{
	return RAMBanks.ReadByte(address + currentRAMBank * 0x2000);
}

void Cartridge::WriteToMemory(ushort address, uchar data)
{
	HandleBanking(address, data);
}

void Cartridge::WriteToRAM(ushort address, uchar data)
{
	if (enableRAM)
	{
		RAMBanks.WriteByte(address + currentRAMBank * 0x2000, data);
	}
}

void Cartridge::HandleBanking(ushort address, uchar data)
{
	// do RAM enabling
	if (address < 0x2000)
	{
		if (cartType != CartType::NO_BANK)
		{
			DoRamBankEnable(address, data);
		}
	}

	// do low ROM bank change
	else if (address >= 0x2000 && address < 0x4000)
	{
		if (cartType != CartType::NO_BANK)
		{
			DoChangeLoROMBank(data);
		}
	}

	// do hi ROM or RAM bank change
	else if (address >= 0x4000 && address < 0x6000)
	{
		if (cartType == CartType::MBC_1)
		{
			if (ROMBanking)
			{
				DoChangeHiROMBank(data);
			}
			else
			{
				DoChangeRAMBank(data);
			}
		}
	}

	// change ROM / RAM banking mode
	else if (address >= 0x6000 && address < 0x8000)
	{
		if (cartType == CartType::MBC_1)
		{
			DoChangeROMRAMMode(data);
		}
	}
}

void Cartridge::DoRamBankEnable(ushort address, uchar data)
{
	if (cartType == CartType::MBC_2 && TestBit(address, 4))
	{
		return;
	}

	uchar lowerNibble = data & 0x0f;
	if (lowerNibble == 0x0a)
	{
		enableRAM = true;
	}
	else if (lowerNibble = 0x00)
	{
		enableRAM = false;
	}
}

void Cartridge::DoChangeLoROMBank(uchar data)
{
	if (cartType == CartType::MBC_2)
	{
		currentROMBank = data & 0x0f;
		if (currentROMBank == 0)
		{
			currentROMBank++;
		}
		return;
	}

	uchar lowerFive = data & 31;
	currentROMBank &= 224;
	currentROMBank |= lowerFive;
	if (currentROMBank == 0)
	{
		currentROMBank++;
	}
}

void Cartridge::DoChangeHiROMBank(uchar data)
{
	currentROMBank &= 31;
	data &= 224;
	currentROMBank |= data;
	if (currentROMBank == 0)
	{
		currentROMBank++;
	}
}

void Cartridge::DoChangeRAMBank(uchar data)
{
	currentRAMBank = data & 0x3;
}

void Cartridge::DoChangeROMRAMMode(uchar data)
{
	uchar adjustedData = data & 0x1;

	if (adjustedData == 0)
	{
		ROMBanking = true;
		currentRAMBank = 0;
	}
	else
	{
		ROMBanking = false;
	}

}
