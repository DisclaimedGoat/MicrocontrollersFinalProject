
#include <stm32l476xx.h>

enum Pin {
	P0 = 1,
	P1 = 2,
	P2 = 4,
	P3 = 8,
	P4 = 16,
	P5 = 32,
	P6 = 64,
	P7 = 128,
	P8 = 256,
	P9 = 512,
	P10 = 1024,
	P11 = 2048,
	P12 = 4096
};

// Set the provided pins in the given channel as input
void set_pins_input(GPIO_TypeDef* channel, int num, ...);

// Set the provided pins in the given channel as output
void set_pins_output(GPIO_TypeDef* channel, int num, ...);