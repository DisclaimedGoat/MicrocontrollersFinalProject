#include "stm32l476xx.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "render.h"
#include "game.h"
#include "screens.h"
#include "LCD.h"

#define LCD_REFRESH_TICKS 25

#define NONE  0
#define LEFT  1
#define RIGHT 2

#define TIME  10

#define START 0
#define RUN   1
#define PAUSE 2
#define OVER  3
#define HIGH  4

unsigned int* game_array;
unsigned int* space_array;
unsigned int* player_array;
static int state = 0;
static int direction = NONE;
static int player_delay = 0;
static int speed = 5;
static int timer = 10;
static unsigned int score = 0;
static unsigned int high_score = 0;

static int lcd_refresh_count = 0;

void game_init(void)
{
    game_array   = (unsigned int*) malloc(sizeof(int) * SIZEX);
    space_array  = (unsigned int*) malloc(sizeof(int) * SIZEX);
    player_array = (unsigned int*) malloc(sizeof(int) * SIZEX);
    for (int i = 0; i < SIZEX; i++)
    {
        game_array[i]   = START_SCREEN[i];
        space_array[i]  = EMPTY_SCREEN[i];
        player_array[i] = PLAYER_SCREEN[i];
    }

    state = START;

    srand(10000); 
}

void update_lcd() {
	// Only update every 'LCD_REFRESH_TICKS'
	if (++lcd_refresh_count % LCD_REFRESH_TICKS != 0) return;
	
	char* buff;
	snprintf(buff, 32, "Count: %d", lcd_refresh_count);
	LCD_Print(buff);
}

void next_game_frame(void)
{
	check_inputs();
	
	
								
	switch(state)
	{
			case START:
					// Level select
					break;
			case RUN:
					timer--;
					int checkBit = 0;
					for (int i = 0; i < SIZEX; i++)
					{
							checkBit |= space_array[i];
					}
					if (!(checkBit >> 20)) // Need a new obstacle
					{
							int obstacle = (int) rand() % 6;
							for (int i = 0; i < SIZEX; i++)
							{
									switch(obstacle)
									{
											case 0: 
															space_array[i] |= RIGHT_OBSTACLE_SCREEN[i];
															break;
											case 1: 
															space_array[i] |= LEFT_OBSTACLE_SCREEN[i];
															break;
											case 2: 
															space_array[i] |= MID_OBSTACLE_SCREEN[i];
															break;
											case 3: 
															space_array[i] |= BOTH_OBSTACLE_SCREEN[i];
															break;
											case 4: 
															space_array[i] |= BOTH_LEFT_OBSTACLE_SCREEN[i];
															break;
											case 5: 
															space_array[i] |= BOTH_RIGHT_OBSTACLE_SCREEN[i];
															break;            
									}   
							}
					}
									
					switch(direction)
					{
							case LEFT:
									if (player_array[0] == 0 && player_delay <= 0)
									{
											for (int i = 0; i < SIZEX - 1; i++)
													player_array[i] = player_array[i + 1];
											player_array[SIZEX - 1] = 0;
											player_delay = 2;
									}
									break;
							case RIGHT:
									if (player_array[SIZEX - 1] == 0 && player_delay <= 0)
									{
											for (int i = SIZEX - 1; i > 0; i--)
													player_array[i] = player_array[i - 1];
											player_array[0] = 0;
											player_delay = 2;
									}
									break;
							case NONE:
									player_delay = 0;
									break;
					}
					player_delay--;

					for (int i = 0; i < SIZEX; i++)
					{
							if (timer == speed)
							{
									space_array[i] >>= 1;
									if ((checkBit & 1) && (checkBit & 2) == 0)
									{
											score++;   
											if ((score % 5) == 0 && speed < timer)
													speed++;
									}
							}
							game_array[i] = space_array[i] | player_array[i];
							if (space_array[i] & player_array[i])
							{
									state = OVER;
							}
					}
					break;
			case PAUSE:
					break;
			case OVER:
					for (int i = 0; i < SIZEX; i++)
					{
							game_array[i]   = START_SCREEN[i]; // change this to explosion later
					} 
					if (score > high_score)
							state = HIGH;
					else
							state = START;
					break;
			case HIGH:
					// put in name
					state = START;
					break;
	} 

	renderScreen(game_array);

	direction = NONE;
			
	if (timer == speed)
			timer = TIME;
	
	update_lcd();
}

void check_inputs(void)
{
    if (GPIOB->IDR & 15)
    {
        if (GPIOB->IDR & 1) // Red Button
        {
            state = PAUSE;
			return;
        }
        if (GPIOB->IDR & 2) // Green Button
        {
            state = RUN;
			return;
        }
        if (GPIOB->IDR & 4) // Yellow Button
        {
            direction = LEFT;
			return;
        }
        if (GPIOB->IDR & 8) // Blue Button
        {
            direction = RIGHT;
			return;
        }
    }
}