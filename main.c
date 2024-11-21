#include <stm32l476xx.h>

#include "ports.h"

int main() {
	// set the clock to HSI, 16MHz
	RCC->CR |= RCC_CR_HSION; // set the clock control register to have the HSI on bit enabled
	while((RCC->CR & RCC_CR_HSIRDY) == 0); // loop until the HSI clock is ready
	
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOBEN;
	
	set_pins_output(GPIOA, 4, P0, P1, P2, P3);
	set_pins_input(GPIOB, 3, P1, P5, P8);
	
	// Wait indefinitely
	while(1);
}