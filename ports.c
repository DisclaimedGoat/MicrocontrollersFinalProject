
#include <stdarg.h>

#include "ports.h"

// Credits for va_list information:
//	https://www.tutorialspoint.com/cprogramming/c_variable_arguments.htm


void set_pins_input(GPIO_TypeDef* channel, int num, ...) {
	va_list valist;
	va_start(valist, num);
	
	// iterate over each pin and set its moder
	for (int i = 0; i < num; i++) {
		int pin = va_arg(valist, int);
		int mode_pin = pin * pin;
		
		// INPUT: set moder to 0 for the pin
		channel->MODER &= ~mode_pin;
		channel->MODER &= ~(mode_pin << 1);
   }
	
	va_end(valist);
}

void set_pins_pull_down(GPIO_TypeDef* channel, int num, ...) {
	va_list valist;
	va_start(valist, num);
	
	// iterate over each pin and set its moder
	for (int i = 0; i < num; i++) {
		int pin = va_arg(valist, int);
		int mode_pin = pin * pin;
		
		// INPUT: set pupdr to 10 for the pin (pull down resistor)
		channel->PUPDR &= ~mode_pin;
		channel->PUPDR &= ~(mode_pin << 1);
		channel->PUPDR |= mode_pin << 1;
   }
	
	va_end(valist);
}

void set_pins_pull_up(GPIO_TypeDef* channel, int num, ...) {
	va_list valist;
	va_start(valist, num);
	
	// iterate over each pin and set its moder
	for (int i = 0; i < num; i++) {
		int pin = va_arg(valist, int);
		int mode_pin = pin * pin;
		
		// INPUT: set pupdr to 01 for the pin (pull up resistor)
		channel->PUPDR &= ~mode_pin;
		channel->PUPDR &= ~(mode_pin << 1);
		channel->PUPDR |= mode_pin;
   }
	
	va_end(valist);
}

void set_pins_output(GPIO_TypeDef* channel, int num, ...) {
	va_list valist;
	va_start(valist, num);
	
	// iterate over each pin and set its moder
	for (int i = 0; i < num; i++) {
		int pin = va_arg(valist, int);
		int mode_pin = pin * pin;
		
		// OUTPUT: set moder to 1 for the pin
		channel->MODER &= ~mode_pin;
		channel->MODER &= ~(mode_pin << 1);
		channel->MODER |= mode_pin;
   }
	
	va_end(valist);
}