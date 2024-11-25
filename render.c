#include "stm32l476xx.h"
#include "render.h"
#include "types.h"

void renderScreen(const array* screen)
{
		unsigned long long bit = 0x1;
    for (unsigned long long col = 1; col <= 8; col++)
    {
			  uint48 leftLine =  { col << 8, col << 8, col << 8 };
				uint48 rightLine = { col << 8, col << 8, col << 8 };
        for (unsigned int row = 0, col_bit = 8; row < 8; row++, col_bit--)
        {
            leftLine.top16 +=  (*screen)[row]     & ((bit << (col + 7)) >> (col - row + 8));
            rightLine.top16 += (*screen)[row]     & (bit << (col - 1)); 
            leftLine.mid16 +=  (*screen)[row + 8] & ((bit << (col + 7)) >> 8);
            rightLine.mid16 += (*screen)[row + 8] & (bit << (col - 1)); 
            leftLine.bot16 +=  (*screen)[row + 16] & ((bit << (col + 7)) >> 8);
            rightLine.bot16 += (*screen)[row + 16] & (bit << (col - 1)); 
        }
        sendLine(leftLine, rightLine);
    }
}

void sendLine(uint48 leftLine, uint48 rightLine) // Send 12 bits starting with MSB first (first 4 bits don't matter)
{
	unsigned int botTemp = rightLine.bot16 << 1;
	unsigned int midTemp = rightLine.bot16 << 1;
	unsigned int topTemp = rightLine.bot16 << 1;
	for (int d = 15; d >= 0; d--)
	{
		GPIOC->ODR &= 0xFFFC;
		GPIOC->ODR |= ((leftLine.bot16 >> d) & 0x1) | ((botTemp >> d) & 0x2);
		toggleCLK();
	}
	for (int d = 15; d >= 0; d--)
	{
		GPIOC->ODR &= 0xFFFC;
		GPIOC->ODR |= ((leftLine.bot16 >> d) & 0x1) | ((midTemp >> d) & 0x2);
		toggleCLK();
	}
	for (int d = 15; d >= 0; d--)
	{
		GPIOC->ODR &= 0xFFFC;
		GPIOC->ODR |= ((leftLine.bot16 >> d) & 0x1) | ((topTemp >> d) & 0x2);
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