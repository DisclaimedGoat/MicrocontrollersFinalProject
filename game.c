#include "stm32l476xx.h"
#include "render.h"
#include "game.h"
#include "screens.h"
#include "stdlib.h"
#include "time.h"

#define NONE  0
#define LEFT  1
#define RIGHT 2

#define STOP  0
#define RUN   1
#define OVER  2

#define TIME  10

unsigned int* game_array;
// static hArray* space_array;
// static hArray* player_array; 
unsigned int* space_array;
unsigned int* player_array;
static int state = 0;
static int direction = NONE;
static int speed = 8;
static int timer = 10;

void game_init(void)
{
    game_array   = (unsigned int*) malloc(sizeof(int) * SIZEX);
    space_array  = (unsigned int*) malloc(sizeof(int) * SIZEX);
    player_array = (unsigned int*) malloc(sizeof(int) * SIZEX);
    for (int i = 0; i < SIZEX; i++)
    {
        game_array[i]   = TEST_HORIZONTAL_SCREEN[i];
        space_array[i]  = EMPTY_SCREEN_H[i];
        player_array[i] = PLAYER_SCREEN_H[i];
    }
    // game_array   = TEST_HORIZONTAL_SCREEN;
    // // game_array   = EMPTY_SCREEN_H;
    // space_array  = EMPTY_SCREEN_H;
    // player_array = PLAYER_SCREEN_H;
	// // game_array = &xPLAYER_SCREEN_H;

    state = RUN;

    srand(10000); 

    // hArray frame;

    // for (int i = 0; i < SIZEX; i++)
    // {
    //     frame[i] = (*space_array)[i] | (*player_array)[i];
    // }
    renderScreenHorizontal(game_array);
}

void next_game_frame(void)
{
    check_inputs();

    if (state == RUN)
    {
        timer--;
        int checkBit = 0;
        for (int i = 0; i < SIZEX; i++)
        {
            checkBit |= space_array[i];
        }
        if (!(checkBit >> 20)) // Need a new obstacle
        {
            int obstacle = (int) rand() % 4;
            for (int i = 0; i < SIZEX; i++)
            {
                switch(obstacle)
                {
                    case 0: 
                            space_array[i] |= RIGHT_OBSTACLE_SCREEN_H[i];
                            break;
                    case 1: 
                            space_array[i] |= LEFT_OBSTACLE_SCREEN_H[i];
                            break;
                    case 2: 
                            space_array[i] |= MID_OBSTACLE_SCREEN_H[i];
                            break;
                    case 3: 
                            space_array[i] |= BOTH_OBSTACLE_SCREEN_H[i];
                            break;            
                }   
            }
        }
				
        switch(direction)
        {
            case LEFT:
                if (player_array[SIZEX - 1] == 0)
                {
                    for (int i = SIZEX - 1; i > 0; i--)
                        player_array[i] = player_array[i - 1];
                    player_array[0] = 0;
                }
                break;
            case RIGHT:
                if (player_array[0] == 0)
                {
                    for (int i = 0; i < SIZEX - 1; i++)
                        player_array[i] = player_array[i + 1];
                    player_array[SIZEX - 1] = 0;
                }
                break;
            case NONE:
                break;
        }

        for (int i = 0; i < SIZEX; i++)
        {
            if (timer == speed)
            {
                space_array[i] >>= 1;
            }
            game_array[i] = space_array[i] | player_array[i];
            if (space_array[i] & player_array[i])
            {
                state = OVER;
            }
        }
    } 

    direction = NONE;
		if (state == OVER)
		{
				renderScreenHorizontal(TEST_HORIZONTAL_SCREEN);
		}
		else
		{
				renderScreenHorizontal(game_array);
		}
		if (timer == speed)
		{
			  timer = TIME;
		}
}

void check_inputs(void)
{
    if (GPIOC->IDR | !15)
    {
        if (!(GPIOC->IDR & 1)) // Red Button
        {
            state = STOP;
        }
        if (!(GPIOC->IDR & 2)) // Green Button
        {
            state = RUN;
        }
        if (!(GPIOC->IDR & 4)) // Yellow Button
        {
            direction = LEFT;
        }
        if (!(GPIOC->IDR & 8)) // Blue Button
        {
            direction = RIGHT;
        }
    }
}

void red_button_pressed(void) {
	state = STOP;
}

void green_button_pressed(void) {
	state = RUN;
}

void yellow_button_pressed(void) {
	direction = LEFT;
}

void blue_button_pressed(void) {
	direction = RIGHT;
}