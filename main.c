#include "stm32l476xx.h"
#include "ports.h"
#include "render.h"
#include "game.h"
#include "LCD.h"
#include <stdio.h>

// PB0 -> Red Button
// PB1 -> Green Button
// PB2 -> Yellow Button
// PB3 -> Blue Button

static unsigned int bit = 0;
static unsigned int timer = 200;

void EXTI_Init(void);
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
// int TimeDelay = 0;

void SysTick_Handler(void);
void SysTick_Init(uint32_t ticks);
void LED_Init(void);


int main(void){
	
	RCC->CR |= RCC_CR_HSION;
	while((RCC->CR & RCC_CR_HSIRDY) == 0);

	// enable systick clock
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN; 
	
	// enable clock for GPIO B and C
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN | RCC_AHB2ENR_GPIOBEN;
	
	set_pins_output(GPIOC, 4, P0, P1, P2, P3);
	set_pins_input(GPIOB, 4, P0, P1, P2, P3);
	set_pins_pull_down(GPIOB, 4, P0, P1, P2, P3);
	set_pins_output(GPIOB, 1, P4);
	
	LED_Init();

	game_init();

	// it is necessary to init the LCD first I think
	LCD_Init();
	LCD_Clear();
	
	//LCD_PrintEach("Hello", "World");

	SysTick_Init(10000);
	
	while(1);
}

void SysTick_Init(uint32_t ticks)
{
	SysTick->CTRL = 0;
	SysTick->LOAD = ticks - 1;
	NVIC_SetPriority(SysTick_IRQn, (1 << __NVIC_PRIO_BITS) - 1);
	SysTick->VAL = 0;
	SysTick->CTRL |= 7;
}

void SysTick_Handler(void)
{
	next_game_frame();
}

void LED_Init(void)
{
	sendCommand(uint48of1(0x0C01)); // Set to normal operation mode
	sendCommand(uint48of1(0x0900)); // No Font B decoding (this would only be for a 7 segment display)
	sendCommand(uint48of1(0x0A00)); // Set intensity to lowest value
	sendCommand(uint48of1(0x0B07)); // Enable all 8 rows
}
