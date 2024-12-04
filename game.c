#include "stm32l476xx.h"
#include "render.h"
#include "game.h"
#include "screens.h"
#include "stdlib.h"
#include "time.h"

#define NONE  0
#define LEFT  1
#define RIGHT 2

static hArray* game_array;
static hArray* space_array;
static hArray* player_array; 
static int running = 0;
static int direction = NONE;

void game_init(void)
{
    game_array   = (hArray*) malloc(sizeof(int) * SIZEX);
    space_array  = (hArray*) malloc(sizeof(int) * SIZEX);
    player_array = (hArray*) malloc(sizeof(int) * SIZEX);
    // game_array   = &TEST_HORIZONTAL_SCREEN;
    game_array   = &EMPTY_SCREEN_H;
    space_array  = &EMPTY_SCREEN_H;
    player_array = &PLAYER_SCREEN_H;
	// game_array = &xPLAYER_SCREEN_H;

    running = 1;

    srand(time(NULL)); 

    hArray frame;

    for (int i = 0; i < SIZEX; i++)
    {
        frame[i] = (*space_array)[i] | (*player_array)[i];
    }
    renderScreenHorizontal(&frame);
}

void next_game_frame(void)
{
    hArray frame;
    if (running)
    {
        if ((*space_array)[11] == 0) // Need a new obstacle
        {
            for (int i = 0; i < SIZEX; i++)
            {
                switch((int) rand() % 4)
                {
                    case 0: 
                        (*space_array)[i] |= RIGHT_OBSTACLE_SCREEN_H[i];
                        (*space_array)[i] >> 1;
                        break;
                    case 1: 
                        (*space_array)[i] |= LEFT_OBSTACLE_SCREEN_H[i];
                        (*space_array)[i] >> 1;
                        break;
                    case 2: 
                        (*space_array)[i] |= MID_OBSTACLE_SCREEN_H[i];
                        (*space_array)[i] >> 1;
                        break;
                    case 3: 
                        (*space_array)[i] |= BOTH_OBSTACLE_SCREEN_H[i];
                        (*space_array)[i] >> 1;
                        break;            
                }   
            }
        }

        switch(direction)
        {
            case LEFT:
                if ((*player_array)[SIZEX - 1] == 0)
                {
                    for (int i = SIZEX - 1; i > 0; i--)
                        (*player_array)[i] = (*player_array)[i - 1];
                    (*player_array)[0] = 0;
                }
                break;
            case RIGHT:
                if ((*player_array)[0] == 0)
                {
                    for (int i = 0; i < SIZEX - 1>; i++)
                        (*player_array)[i] = (*player_array)[i + 1];
                    (*player_array)[SIZEX - 1] = 0;
                }
                break;
            case NONE:
                break;
        }

        for (int i = 0; i < SIZEX; i++)
        {
            frame[i] = (*space_array)[i] | (*player_array)[i];
            if ((*space_array)[i] & (*player_array)[i])
            {
                game_over();
            }
        }
    } 

    direction = NONE;
    renderScreenHorizontal(&frame);
}

void game_over(void)
{
    renderScreenHorizontal(&TEST_HORIZONTAL_SCREEN);
    running = 0;
}

void red_button_pressed(void) {
	running = 0;
}

void green_button_pressed(void) {
	running = 1;
}

void yellow_button_pressed(void) {
	direction = LEFT;
}

void blue_button_pressed(void) {
	direction = RIGHT;
}