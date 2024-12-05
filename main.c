#include "stm32l476xx.h"
#include "ports.h"
#include "render.h"
#include "game.h"
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
	
	LED_Init();

	game_init();
	
	// EXTI_Init();

	// it is necessary to init the LCD first I think
//	LCD_Init();
//	LCD_Clear();

	SysTick_Init(80000);
	
	while(1);
}

void EXTI_Init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI0 & ~SYSCFG_EXTICR1_EXTI1 & ~SYSCFG_EXTICR1_EXTI2 & ~SYSCFG_EXTICR1_EXTI3;
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PB | SYSCFG_EXTICR1_EXTI1_PB | SYSCFG_EXTICR1_EXTI2_PB | SYSCFG_EXTICR1_EXTI3_PB;

	EXTI->RTSR1 |= EXTI_RTSR1_RT0 | EXTI_RTSR1_RT1 | EXTI_RTSR1_RT2 | EXTI_RTSR1_RT3;
	EXTI->FTSR1 &= ~EXTI_FTSR1_FT0 & ~EXTI_FTSR1_FT1 & ~EXTI_FTSR1_FT2 & ~EXTI_FTSR1_FT3;
	EXTI->IMR1 |= EXTI_IMR1_IM0 | EXTI_IMR1_IM1 | EXTI_IMR1_IM2 | EXTI_IMR1_IM3;

	NVIC_SetPriority(EXTI0_IRQn, 1);
	NVIC_SetPriority(EXTI1_IRQn, 2);
	NVIC_SetPriority(EXTI2_IRQn, 3);
	NVIC_SetPriority(EXTI3_IRQn, 4);

	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI1_IRQn);
	NVIC_EnableIRQ(EXTI2_IRQn);
	NVIC_EnableIRQ(EXTI3_IRQn);
}

// Extern handler for Red Button
void EXTI0_IRQHandler(void)
{
	if ((EXTI->PR1 & EXTI_PR1_PIF0) != 0)
	{
		red_button_pressed();
		EXTI->PR1 |= EXTI_PR1_PIF0;
	}
}

// Extern handler for Green Button
void EXTI1_IRQHandler(void)
{
	if ((EXTI->PR1 & EXTI_PR1_PIF1) == EXTI_PR1_PIF1)
	{
		green_button_pressed();
		EXTI->PR1 |= EXTI_PR1_PIF1;
	}
}

// Extern handler for Yellow Button
void EXTI2_IRQHandler(void)
{
	if ((EXTI->PR1 & EXTI_PR1_PIF2) == EXTI_PR1_PIF2)
	{
		yellow_button_pressed();
		EXTI->PR1 |= EXTI_PR1_PIF2;
	}
}

// Extern handler for Blue Button
void EXTI3_IRQHandler(void)
{
	if ((EXTI->PR1 & EXTI_PR1_PIF3) == EXTI_PR1_PIF3)
	{
		blue_button_pressed();
		EXTI->PR1 |= EXTI_PR1_PIF3;
	}
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
