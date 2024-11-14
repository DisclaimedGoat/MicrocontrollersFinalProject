#include <stm32l476xx.h>

#include "ports.h"

int main() {
	
	set_pins_output(GPIOA, 3, P1, P2, P3);
	
	// Wait indefinitely
	while(1);
}