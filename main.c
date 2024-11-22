#include "stm32l476xx.h"
#include "LCD.h"
#include "ports.h"
#include "render.h"
#include <stdio.h>

#define STOP 0
#define GO 1

// PB0 -> Reset
// PB1 -> Pause
// PB2 -> Start

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
	
	// enable GPIO C clock
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN | RCC_AHB2ENR_GPIOBEN;
	
	set_pins_output(GPIOC, 4, P0, P1, P2, P3);
	
	// set pins PC0-2 to open-drain
	// GPIOC->OTYPER |= 0x00000007;
	
	GPIOC->ODR &= 0xFFF8;
	
	GPIOC->ODR |= 0x0002;
	GPIOC->ODR &= 0xFFFD;
	
	LED_Init();
	

	
//	EXTI_Init();

	// it is necessary to init the LCD first I think
//	LCD_Init();
//	LCD_Clear();

	// SysTick_Init(16);
	SysTick_Init(16);
}

void EXTI_Init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI0 & ~SYSCFG_EXTICR1_EXTI1 & ~SYSCFG_EXTICR1_EXTI2;
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PB | SYSCFG_EXTICR1_EXTI1_PB | SYSCFG_EXTICR1_EXTI2_PB;

	EXTI->RTSR1 |= EXTI_RTSR1_RT0 | EXTI_RTSR1_RT1 | EXTI_RTSR1_RT2;
	EXTI->FTSR1 &= ~EXTI_FTSR1_FT0 & ~EXTI_FTSR1_FT1 & ~EXTI_FTSR1_FT2;
	EXTI->IMR1 |= EXTI_IMR1_IM0 | EXTI_IMR1_IM1 | EXTI_IMR1_IM2;

	NVIC_SetPriority(EXTI0_IRQn, 1);
	NVIC_SetPriority(EXTI1_IRQn, 2);
	NVIC_SetPriority(EXTI2_IRQn, 3);

	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI1_IRQn);
	NVIC_EnableIRQ(EXTI2_IRQn);
}

void EXTI0_IRQHandler(void)
{
	if ((EXTI->PR1 & EXTI_PR1_PIF0) == EXTI_PR1_PIF0)
	{

		EXTI->PR1 |= EXTI_PR1_PIF0;
	}
}

void EXTI1_IRQHandler(void)
{
	if ((EXTI->PR1 & EXTI_PR1_PIF1) == EXTI_PR1_PIF1)
	{

		EXTI->PR1 |= EXTI_PR1_PIF1;
	}
}

void EXTI2_IRQHandler(void)
{
	if ((EXTI->PR1 & EXTI_PR1_PIF2) == EXTI_PR1_PIF2)
	{

		EXTI->PR1 |= EXTI_PR1_PIF2;
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
	if (timer)
	{
		timer--;
	}
	else 
	{
		bit = ~bit;
		timer = 50;
	}
	// renderScreen(array);
}

void LED_Init(void)
{
	sendLine(0x0C010C010C01); // Set to normal operation mode
	sendLine(0x090009000900); // No Font B decoding (this would only be for a 7 segment display)
	sendLine(0x0A000A000A00); // Set intensity to lowest value
	sendLine(0x0B070B070B07); // Enable all 8 rows
}
