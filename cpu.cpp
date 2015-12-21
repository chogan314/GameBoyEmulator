#include "cpu.h"
#include "instruction.h"
#include "instruction_factory.h"
#include <iostream>
#include "utils.h"
#include <fstream>
#include "hex_printing.h"

CPU::CPU(MemBlock *memory) :
	A(0x01),
	F(0xB0),
	B(0x00),
	C(0x13),
	D(0x00),
	E(0xD8),
	H(0x01),
	L(0x4D),
	SP(0xFFFE),
	PC(0x0100),
	memory(memory),
	interruptMasterEnable(true),
	shouldEnableInterrupts(false),
	shouldDisableInterrupts(false),
	timerCounter(1024),
	dividerRegister(0),
	disableIMEAfterNextInstruction(false),
	enableIMEAfterNextInstruction(false),
	scanlineCounter(456)
{
	memory->WriteByte(0xFF10, 0x80);
	memory->WriteByte(0xFF11, 0xBF);
	memory->WriteByte(0xFF12, 0xF3);
	memory->WriteByte(0xFF14, 0xBF);
	memory->WriteByte(0xFF16, 0x3F);
	memory->WriteByte(0xFF19, 0xBF);
	memory->WriteByte(0xFF1A, 0x7F);
	memory->WriteByte(0xFF1B, 0xFF);
	memory->WriteByte(0xFF1C, 0x9F);
	memory->WriteByte(0xFF1E, 0xBF);
	memory->WriteByte(0xFF20, 0xFF);
	memory->WriteByte(0xFF23, 0xBF);
	memory->WriteByte(0xFF24, 0x77);
	memory->WriteByte(0xFF25, 0xF3);
	memory->WriteByte(0xFF26, 0xF1);
	memory->WriteByte(0xFF40, 0x91);
	memory->WriteByte(0xFF47, 0xFC);
	memory->WriteByte(0xFF48, 0xFF);
	memory->WriteByte(0xFF49, 0xFF);

	memoryDirect = memory->GetMemory();

	for (int y = 0; y < 144; y++)
	{
		for (int x = 0; x < 160; x++)
		{
			int index = y * 160 * 3 + x * 3;
			screenData[index] = 0x99;
			screenData[index + 1] = 0x99;
			screenData[index + 2] = 0x99;
		}
	}

	PopulateInstructionList();
}

CPU::~CPU()
{
	//delete[] instructions;
}

void CPU::Update()
{
	const int MAXCYCLES = 70221;
	int cyclesThisUpdate = 0;

	while (cyclesThisUpdate < MAXCYCLES)
	{

		if (shouldDisableInterrupts)
		{
			interruptMasterEnable = false;
			shouldDisableInterrupts = false;
		}

		if (shouldEnableInterrupts)
		{
			interruptMasterEnable = true;
			shouldEnableInterrupts = false;
		}

		Instruction *instruction = InvokeInstruction(ReadByte(PC));
		int cycles = instruction->GetDuration();

		cyclesThisUpdate += cycles;
		UpdateTimers(cycles);
		UpdateGraphics(cycles);
		HandleInterrupts();
	}
}

void CPU::PrintMemory()
{
	std::ofstream file;
	file.open("memory.txt");

	for (int i = 0; i < 0x10000; i++)
	{
		file << int_to_hex(i) << "\t" << int_to_hex(ReadByte(i)) << std::endl;
	}

	file.close();
}

void CPU::PrintRegisters()
{
	std::ofstream file;
	file.open("registers.txt", std::ios::app | std::ios::out);

	file << "---PC:\t" << int_to_hex(PC) << std::endl;
	file << "A:\t" << int_to_hex(A) << std::endl;
	file << "B:\t" << int_to_hex(B) << std::endl;
	file << "C:\t" << int_to_hex(C) << std::endl;
	file << "D:\t" << int_to_hex(D) << std::endl;
	file << "E:\t" << int_to_hex(E) << std::endl;
	file << "F:\t" << int_to_hex(F) << std::endl;
	file << "H:\t" << int_to_hex(H) << std::endl;
	file << "L:\t" << int_to_hex(L) << std::endl;
	file << "SP:\t" << int_to_hex(SP) << std::endl << std::endl << std::endl;

	file.close();
}

void CPU::InsertCartridge(Cartridge *cartridge)
{
	this->cartridge = cartridge;
}

Instruction *CPU::InvokeInstruction(int opcode)
{
	Instruction *instruction;

	if (opcode == 0xcb)
	{
		opcode = 0x100 + ReadByte(PC + 1);
	}

	instruction = instructions[opcode];

	// std::string pcStr = int_to_hex(PC);

	instruction->Call();

	instrCounter++;

	/*std::ofstream file;
	file.open("outputPKMN.txt", std::ios::app | std::ios::out);
	file << pcStr << "\t" << instruction->ToString() << std::endl;
	file.close();*/

	return instruction;
}

void CPU::PrintInstructions()
{

}

void CPU::SetZeroFlag(bool set)
{
	uchar bit = set;
	bit <<= 7;
	F &= ~(1 << 7);
	F |= bit;
}

bool CPU::GetZeroFlag()
{
	return (F & (1 << 7)) != 0;
}

void CPU::SetSubtractFlag(bool set)
{
	uchar bit = set;
	bit <<= 6;
	F &= ~(1 << 6);
	F |= bit;
}

bool CPU::GetSubtractFlag()
{
	return (F & (1 << 6)) != 0;
}

void CPU::SetHalfCarryFlag(bool set)
{
	uchar bit = set;
	bit <<= 5;
	F &= ~(1 << 5);
	F |= bit;
}

bool CPU::GetHalfCarryFlag()
{
	return (F & (1 << 5)) != 0;
}

void CPU::SetCarryFlag(bool set)
{
	uchar bit = set;
	bit <<= 4;
	F &= ~(1 << 4);
	F |= bit;
}

bool CPU::GetCarryFlag()
{
	return (F & (1 << 4)) != 0;
}

uchar CPU::ReadImm8Arg()
{
	return ReadByte(PC + 1);
}

ushort CPU::ReadImm16Arg()
{
	return ReadShort(PC + 1);
}

uchar CPU::ReadByte(ushort address)
{
	// reading from cartridge fixed memory
	if (address < 0x4000)
	{
		return cartridge->ReadFromMemory(address);
	}

	// reading from cartridge switchable ROM
	else if (address >= 0x4000 && address < 0x8000)
	{
		ushort adjustedAddress = address - 0x4000;
		return cartridge->ReadFromROMBank(adjustedAddress);
	}
	
	// reading from cartridge RAM
	else if (address >= 0xA000 && address < 0xC000)
	{
		ushort adjustedAddress = address - 0xA000;
		return cartridge->ReadFromRAM(adjustedAddress);
	}

	else
	{
		//return memory->ReadByte(address);
		return memoryDirect[address];
	}
}

ushort CPU::ReadShort(ushort address)
{
	ushort data = 0;

	uchar msb = ReadByte(address + 1);
	uchar lsb = ReadByte(address);

	data = msb;
	data = data << 8;
	data |= lsb;

	return data;
}

void CPU::WriteByte(ushort address, uchar data)
{
	// writing to cartridge ROM; swaps ROM banks
	if (address < 0x8000)
	{
		cartridge->WriteToMemory(address, data);
	}

	// writing to cartridge RAM
	else if (address >= 0xA000 && address < 0xC000)
	{
		ushort adjustedAddress = address - 0xA000;
		cartridge->WriteToRAM(adjustedAddress, data);
	}

	// writing to ECHO; also write to RAM
	else if (address >= 0xE000 && address < 0xFE00)
	{
		memory->WriteByte(address, data);
		memory->WriteByte(address - 0x2000, data);
	}

	// restricted
	else if (address >= 0xFEA0 && address < 0xFEFF)
	{
		// do nothing
	}

	// writing to TMC
	else if (address == TMC)
	{
		memory->WriteByte(address, data);
		SetClockFrequency();
	}

	// writing to DIV
	else if (address == 0xFF04)
	{
		memory->WriteByte(address, 0);
	}

	// writing to scanline register
	else if (address == 0xFF44)
	{
		memory->WriteByte(address, 0);
	}

	// writing to DMA trigger
	else if (address == 0xff46)
	{
		DMATransfer(data);
	}

	else
	{
		memory->WriteByte(address, data);
	}
}

void CPU::WriteShort(ushort address, ushort data)
{
	uchar msb = (data >> 8) & 0xff;
	uchar lsb = data & 0xff;
	
	WriteByte(address, lsb);
	WriteByte(address + 1, msb);
}

void CPU::PushByte(uchar data)
{
	SP -= 1;
	WriteByte(SP, data);
}

void CPU::PushShort(ushort data)
{
	SP -= 2;
	WriteShort(SP, data);
}

uchar CPU::PopByte()
{
	uchar data = ReadByte(SP);
	SP += 1;
	return data;
}

ushort CPU::PopShort()
{
	ushort data = ReadShort(SP);
	SP += 2;
	return data;
}

void CPU::UpdateTimers(int cycles)
{
	UpdateDividerRegister(cycles);

	if (ClockIsEnabled())
	{
		timerCounter -= cycles;

		if (timerCounter <= 0)
		{
			SetClockFrequency();

			if (ReadByte(TIMA) == 0xff)
			{
				WriteByte(TIMA, ReadByte(TMA));
				RequestInterrupt(2);
			}
			else
			{
				WriteByte(TIMA, ReadByte(TIMA) + 1);
			}
		}
	}
}

void CPU::UpdateDividerRegister(int cycles)
{
	dividerRegister += cycles;
	if (dividerRegister >= 0xff)
	{
		dividerRegister = 0;
		memory->WriteByte(0xff04, memory->ReadByte(0xff04) + 1);
	}
}

void CPU::RequestInterrupt(int flag)
{
	uchar IF = memory->ReadByte(0xff0f);
	SetBit(IF, flag);
	memory->WriteByte(0xff0f, IF);
}

bool CPU::ClockIsEnabled()
{
	return TestBit(ReadByte(TMC), 2);
}

uchar CPU::GetClockFrequency()
{
	return ReadByte(TMC) & 0x03;
}

void CPU::SetClockFrequency()
{
	uchar frequency = GetClockFrequency();
	switch (frequency)
	{
	case 0:
		timerCounter = 1024;
		break;
	case 1:
		timerCounter = 16;
		break;
	case 2:
		timerCounter = 64;
		break;
	case 3:
		timerCounter = 256;
		break;
	}
}

void CPU::HandleInterrupts()
{
	if (interruptMasterEnable)
	{
		uchar IF = ReadByte(0xff0f);
		uchar IE = ReadByte(0xffff);
		uchar enabledRequests = IF & IE;

		for (int i = 0; i < 5; i++)
		{
			if (TestBit(enabledRequests, i))
			{
				ServiceInterrupt(i);
			}
		}
	}
}

void CPU::ServiceInterrupt(int flag)
{
	interruptMasterEnable = false;
	uchar IF = ReadByte(0xff0f);
	ResetBit(IF, flag);
	WriteByte(0xff0f, IF);

	PushShort(PC);

	switch (flag)
	{
	case 0:
		std::cout << "PUSHING VBLANK INTERRUPT" << std::endl;
		PC = 0x40;
		break;
	case 1:
		std::cout << "PUSHING LCD INTERRUPT" << std::endl;
		PC = 0x48;
		break;
	case 2:
		std::cout << "PUSHING TIMER INTERRUPT" << std::endl;
		PC = 0x50;
		break;
	case 3:
		std::cout << "PUSHING JOYPAD INTERRUPT" << std::endl;
		PC = 0x60;
		break;
	}
}

void CPU::UpdateGraphics(int cycles)
{
	SetLCDStatus();

	if (!LCDIsEnabled())
	{
		return;
	}

	scanlineCounter -= cycles;

	if (scanlineCounter <= 0)
	{
		memory->WriteByte(0xff44, ReadByte(0xff44) + 1);
		uchar currentLine = ReadByte(0xff44);

		scanlineCounter = 456;

		if (currentLine == 144)
		{
			RequestInterrupt(0);
		}
		else if (currentLine > 153)
		{
			memory->WriteByte(0xff44, 0);
		}
		else if (currentLine < 144)
		{
			DrawScanline();
		}
	}
}

void CPU::SetLCDStatus()
{
	uchar status = memoryDirect[0xff41];

	// reset scanlineCounter and scanline register, set mode to 1
	if (!LCDIsEnabled())
	{
		scanlineCounter = 456;
		memory->WriteByte(0xff44, 0);
		status &= 252;
		SetBit(status, 0);
		WriteByte(0xff41, status);
		return;
	}

	uchar currentLine = memoryDirect[0xff44];
	uchar currentMode = status & 0x3;
	uchar mode = 0;
	bool reqInt = false;

	// if in vblank
	if (currentLine >= 144)
	{
		mode = 1;
		SetBit(status, 0);
		ResetBit(status, 1);
		reqInt = TestBit(status, 4);
	}
	else
	{
		int mode2Bounds = 456 - 80;
		int mode3Bounds = mode2Bounds - 172;

		// mode 2
		if (scanlineCounter >= mode2Bounds)
		{
			mode = 2;
			ResetBit(status, 0);
			SetBit(status, 1);
			reqInt = TestBit(status, 5);
		}

		// mode 3
		if (scanlineCounter >= mode3Bounds)
		{
			mode = 3;
			SetBit(status, 0);
			SetBit(status, 1);
		}

		// mode 0
		else
		{
			mode = 0;
			ResetBit(status, 0);
			ResetBit(status, 1);
			reqInt = TestBit(status, 3);
		}
	}

	// entered new mode
	if (reqInt && (mode != currentMode))
	{
		RequestInterrupt(1);
	}

	// check coincidence flag
	if (memoryDirect[0xff45] == currentLine)
	{
		SetBit(status, 2);
		if (TestBit(status, 6))
		{
			RequestInterrupt(1);
		}
	}
	else
	{
		ResetBit(status, 2);
	}

	WriteByte(0xff41, status);
}

bool CPU::LCDIsEnabled()
{
	return TestBit(ReadByte(0xff40), 7);
}

void CPU::DrawScanline()
{
	uchar control = ReadByte(0xff40);

	if (TestBit(control, 0))
	{
		RenderTiles();
	}

	if (TestBit(control, 1))
	{
		RenderSprites();
	}
}

void CPU::DMATransfer(uchar data)
{
	ushort address = data << 8;
	for (int i = 0; i < 0xA0; i++)
	{
		WriteByte(0xFE00 + i, ReadByte(address + i));
	}
}

void CPU::RenderTiles()
{
	uchar lcdControl = ReadByte(0xff40);
	ushort tileData = 0;
	ushort backgroundMemory = 0;
	bool unsign = true;

	uchar scrollY = ReadByte(0xff42);
	uchar scrollX = ReadByte(0xff43);
	uchar windowY = ReadByte(0xff4a);
	uchar windowX = ReadByte(0xff4b) - 7;

	bool usingWindow = false;

	// test if window is enabled
	if (TestBit(lcdControl, 5))
	{
		// current scanline within window's Y pos?
		usingWindow = windowY <= ReadByte(0xff44);
	}

	// select tile data
	if (TestBit(lcdControl, 4))
	{
		tileData = 0x8000;
	}
	else
	{
		tileData = 0x8800;
		unsign = false;
	}

	// select background data TODO
	if (!usingWindow)
	{
		if (TestBit(lcdControl, 3))
		{
			backgroundMemory = 0x9C00;
		}
		else
		{
			backgroundMemory = 0x9800;
		}
	}
	else
	{
		if (TestBit(lcdControl, 6))
		{
			backgroundMemory = 0x9C00;
		}
		else
		{
			backgroundMemory = 0x9800;
		}
	}

	uchar yPos = 0;

	// determines which of 32 vertical tiles scanline is drawing
	if (!usingWindow)
	{
		yPos = scrollY + ReadByte(0xff44);
	}
	else
	{
		yPos = ReadByte(0xff44) - windowY;
	}

	// determines which of 8 vertical pixels of current tile scanline is on
	ushort tileRow = ((uchar) (yPos / 8) * 32);

	// draw 160 horizontal pixels of scanline
	for (int pixel = 0; pixel < 160; pixel++)
	{
		uchar xPos = pixel + scrollX;

		// translate to window space
		if (usingWindow)
		{
			if (pixel >= windowX)
			{
				xPos = pixel - windowX;
			}
		}

		// determine of 32 horizontal tiles xPos is within
		ushort tileCol = xPos / 8;
		signed short tileNum;

		ushort tileAddress = backgroundMemory + tileRow + tileCol;
		if (unsign)
		{
			//tileNum = (uchar) ReadByte(tileAddress);
			tileNum = (uchar) memoryDirect[tileAddress];
		}
		else
		{
			//tileNum = (signed char) ReadByte(tileAddress);
			tileNum = (signed char) memoryDirect[tileAddress];
		}

		ushort tileLocation = tileData;

		if (unsign)
		{
			tileLocation += tileNum * 16;
		}
		else
		{
			tileLocation += (tileNum + 128) * 16;
		}

		// find correct vertical line on tile to get the tile data from memory
		uchar line = yPos % 8;
		line *= 2;
		/*uchar data1 = ReadByte(tileLocation + line);
		uchar data2 = ReadByte(tileLocation + line + 1);*/
		uchar data1 = memoryDirect[tileLocation + line];
		uchar data2 = memoryDirect[tileLocation + line + 1];

		int colorBit = xPos % 8;
		colorBit -= 7;
		colorBit *= -1;

		int colorNum = TestBit(data2, colorBit);
		colorNum <<= 1;
		colorNum |= TestBit(data1, colorBit);

		Color color = GetColor(colorNum, 0xff47);
		int red = 0;
		int green = 0;
		int blue = 0;

		switch (color)
		{
		case Color::WHITE:
			red = 255;
			green = 255;
			blue = 255;
			break;
		case Color::LIGHT_GRAY:
			red = 0xCC;
			green = 0xCC;
			blue = 0xCC;
			break;
		case Color::DARK_GRAY:
			red = 0x77;
			green = 0x77;
			blue = 0x77;
		}

		int fin = ReadByte(0xff44);

		if (fin < 0 ||
			fin > 143 ||
			pixel < 0 ||
			pixel > 159)
		{
			continue;
		}

		int index = fin * 160 * 3 + pixel * 3;
		screenData[index] = red;
		screenData[index + 1] = green;
		screenData[index + 2] = blue;
	}
}

void CPU::RenderSprites()
{
	uchar lcdControl = ReadByte(0xff40);
	bool use8x16 = TestBit(lcdControl, 2);

	for (int sprite = 0; sprite < 40; sprite++)
	{
		uchar index = sprite * 4;
		uchar yPos = ReadByte(0xfe00 + index) - 16;
		uchar xPos = ReadByte(0xfe00 + index + 1) - 8;
		uchar tileLocation = ReadByte(0xfe00 + index + 2);
		uchar attributes = ReadByte(0xfe00 + index + 3);

		bool yFlip = TestBit(attributes, 6);
		bool xFlip = TestBit(attributes, 5);

		int scanline = ReadByte(0xff44);

		int ySize = 8;
		if (use8x16)
		{
			ySize = 16;
		}

		// does sprite intercept scanline?
		if (scanline >= yPos && scanline < (yPos + ySize))
		{
			int line = scanline - yPos;

			if (yFlip)
			{
				line -= ySize;
				line *= -1;
			}

			line *= 2;

			ushort dataAddress = (0x8000 + tileLocation * 16) + line;
			uchar data1 = memoryDirect[dataAddress];
			uchar data2 = memoryDirect[dataAddress + 1];

			for (int tilePixel = 7; tilePixel >= 0; tilePixel--)
			{
				int colorBit = tilePixel;
				if (xFlip)
				{
					colorBit -= 7;
					colorBit *= -1;
				}

				int colorNum = TestBit(data2, colorBit);
				colorNum <<= 1;
				colorNum |= TestBit(data1, colorBit);

				ushort colorAddress = TestBit(attributes, 4) ? 0xff49 : 0xff48;
				Color color = GetColor(colorNum, colorAddress);

				if (color == Color::WHITE)
				{
					continue;
				}

				int red = 0;
				int green = 0;
				int blue = 0;

				switch (color)
				{
				case Color::WHITE:
					red = 255;
					green = 255;
					blue = 255;
					break;
				case Color::LIGHT_GRAY:
					red = 0xCC;
					green = 0xCC;
					blue = 0xCC;
					break;
				case Color::DARK_GRAY:
					red = 0x77;
					green = 0x77;
					blue = 0x77;
				}

				int xPix = 0 - tilePixel;
				xPix += 7;
				int pixel = xPos + xPix;

				if (scanline < 0 ||
					scanline > 143 ||
					pixel < 0 ||
					pixel > 159)
				{
					continue;
				}

				int index = scanline * 160 * 3 + pixel * 3;
				screenData[index] = red;
				screenData[index + 1] = green;
				screenData[index + 2] = blue;
			}
		}
	}
}

CPU::Color CPU::GetColor(int colorNum, ushort address)
{
	Color res = Color::WHITE;
	uchar palette = memoryDirect[address];
	int high = 0;
	int low = 0;

	switch (colorNum)
	{
	case 0:
		high = 1;
		low = 0;
		break;
	case 1:
		high = 3;
		low = 2;
		break;
	case 2:
		high = 5;
		low = 4;
		break;
	case 3:
		high = 7;
		low = 6;
		break;
	}

	int color = 0;
	color = TestBit(palette, high) << 1;
	color |= TestBit(palette, low);

	switch (color)
	{
	case 0:
		res = Color::WHITE;
		break;
	case 1:
		res = Color::LIGHT_GRAY;
		break;
	case 2:
		res = Color::DARK_GRAY;
		break;
	case 3:
		res = Color::BLACK;
		break;
	}

	return res;
}