#include "stm32l476xx.h"
#include "render.h"
#include "types.h"

void renderScreen(array screen)
{
    for (unsigned int col = 1; col <= 8; col++)
    {
        unsigned int left = col << 4;
        unsigned int topLeft =  0;
        unsigned int topRight = 0;
        unsigned int midLeft =  0;
        unsigned int midRight = 0;
        unsigned int botLeft =  0;
        unsigned int botRight = 0;
        for (unsigned int row = 0; row < 8; row++)
        {
            unsigned int topLeft +=  screen[row] & left;
            unsigned int topRight += screen[row] & col; 
            unsigned int midLeft +=  screen[row + 4] & left;
            unsigned int midRight += screen[row + 4] & col; 
            unsigned int botLeft +=  screen[row + 8] & left;
            unsigned int botRight += screen[row + 8] & col; 
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