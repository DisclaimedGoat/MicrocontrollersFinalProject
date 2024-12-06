#include "stm32l476xx.h"
#include "render.h"
#include "types.h"

void renderScreen(unsigned int* screen)
{
	for (unsigned long long col = 1; col <= 8; col++)
    {
		uint48 leftLine =  { (col << 8) | ((screen[col - 1] >> 16) & 0b11111111), (col << 8) | ((screen[col - 1] >> 8) & 0b11111111), (col << 8) | (screen[col - 1] & 0b11111111) };
		uint48 rightLine = { (col << 8) | ((screen[col + 7] >> 16) & 0b11111111), (col << 8) | ((screen[col + 7] >> 8) & 0b11111111), (col << 8) | (screen[col + 7] & 0b11111111) };
		sendLine(leftLine, rightLine);
	}
}

void sendLine(uint48 leftLine, uint48 rightLine) // Send 12 bits starting with MSB first (first 4 bits don't matter)
{
	unsigned int botTemp = rightLine.bot16 << 1;
	unsigned int midTemp = rightLine.mid16 << 1;
	unsigned int topTemp = rightLine.top16 << 1;
	for (int d = 15; d >= 8; d--)
	{
		GPIOC->ODR &= 0xFFFC;
		GPIOC->ODR |= ((leftLine.bot16 >> d) & 0x1) | ((botTemp >> d) & 0x2);
		toggleCLK();
	}
	for (int d = 0; d < 8; d++)
	{
		GPIOC->ODR &= 0xFFFC;
		GPIOC->ODR |= ((leftLine.bot16 >> d) & 0x1) | ((botTemp >> d) & 0x2);
		toggleCLK();
	}
	for (int d = 15; d >= 8; d--)
	{
		GPIOC->ODR &= 0xFFFC;
		GPIOC->ODR |= ((leftLine.mid16 >> d) & 0x1) | ((midTemp >> d) & 0x2);
		toggleCLK();
	}
	for (int d = 0; d < 8; d++)
	{
		GPIOC->ODR &= 0xFFFC;
		GPIOC->ODR |= ((leftLine.mid16 >> d) & 0x1) | ((midTemp >> d) & 0x2);
		toggleCLK();
	}
	for (int d = 15; d >= 8; d--)
	{
		GPIOC->ODR &= 0xFFFC;
		GPIOC->ODR |= ((leftLine.top16 >> d) & 0x1) | ((topTemp >> d) & 0x2);
		toggleCLK();
	}
	for (int d = 0; d < 8; d++)
	{
		GPIOC->ODR &= 0xFFFC;
		GPIOC->ODR |= ((leftLine.top16 >> d) & 0x1) | ((topTemp >> d) & 0x2);
		toggleCLK();
	}
	
	// toggle pin PC2 (CS) to load line
	GPIOC->ODR |= 0x0004;
	GPIOC->ODR &= 0xFFFB;
}

void sendCommand(uint48 command) // Send 12 bits starting with MSB first (first 4 bits don't matter)
{
	unsigned int botTemp = command.bot16 << 1;
	unsigned int midTemp = command.mid16 << 1;
	unsigned int topTemp = command.top16 << 1;

	for (int d = 15; d >= 0; d--)
	{
		GPIOC->ODR &= 0xFFFC;
		GPIOC->ODR |= ((command.bot16 >> d) & 0x1) | ((botTemp >> d) & 0x2);
		toggleCLK();
	}
	for (int d = 15; d >= 0; d--)
	{
		GPIOC->ODR &= 0xFFFC;
		GPIOC->ODR |= ((command.mid16 >> d) & 0x1) | ((midTemp >> d) & 0x2);
		toggleCLK();
	}
	for (int d = 15; d >= 0; d--)
	{
		GPIOC->ODR &= 0xFFFC;
		GPIOC->ODR |= ((command.top16 >> d) & 0x1) | ((topTemp >> d) & 0x2);
		toggleCLK();
	}
	
	// toggle pin PC2 (CS) to load line
	GPIOC->ODR |= 0x0004;
	GPIOC->ODR &= 0xFFFB;
}

void toggleCLK(void)
{
	GPIOC->ODR |= 0x0008;
	GPIOC->ODR &= 0xFFF7;
}