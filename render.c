#include "stm32l476xx.h"
#include "render.h"
#include "types.h"

void renderScreen(const array* screen)
{
    for (unsigned long long col = 1; col <= 8; col++)
    {
        unsigned long long left = col << 4;
        unsigned long long topLeft =  0;
        unsigned long long topRight = 0;
        unsigned long long midLeft =  0;
        unsigned long long midRight = 0;
        unsigned long long botLeft =  0;
        unsigned long long botRight = 0;
        for (unsigned int row = 0; row < 8; row++)
        {
            topLeft +=  (*screen)[row] & left;
            topRight += (*screen)[row] & col; 
            midLeft +=  (*screen)[row + 4] & left;
            midRight += (*screen)[row + 4] & col; 
            botLeft +=  (*screen)[row + 8] & left;
            botRight += (*screen)[row + 8] & col; 
        }
        unsigned long long leftLine =  (col << 8) + (col << 24) + (col << 40) + (botLeft << 32)  + (midLeft << 16)  + topLeft;
        unsigned long long rightLine = (col << 8) + (col << 24) + (col << 40) + (botRight << 32) + (midRight << 16) + topRight;
    }
}

void sendLine(unsigned long long leftLine, unsigned long long rightLine) // Send 12 bits starting with MSB first (first 4 bits don't matter)
{
	for (int d = 48; d >= 0; d--)
	{
		GPIOC->ODR &= 0xFFFC; 			                                        // Set PC0 and PC1 to low
		GPIOC->ODR |= ((leftLine >> d) & 0x1) | ((rightLine >> (d - 1)) & 0x2); // Set bits
		toggleCLK();											                // Load bit
	}
	
	// toggle pin PC1 (CS) to load line
	GPIOC->ODR |= 0x0004;
	GPIOC->ODR &= 0xFFFB;
}

void toggleCLK(void)
{
	GPIOC->ODR |= 0x0008;
	GPIOC->ODR &= 0xFFF7;
}