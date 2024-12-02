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
static int RUNNING = 0;
static int DIRECTION = NONE;

void game_init(void)
{
    game_array   = (hArray*) malloc(sizeof(int) * SIZEX);
    //space_array  = (hArray*) malloc(sizeof(int) * SIZEX);
    //player_array = (hArray*) malloc(sizeof(int) * SIZEX);
    game_array   = &TEST_HORIZONTAL_SCREEN;
    //space_array  = &EMPTY_SCREEN_H;
    //player_array = &PLAYER_SCREEN_H;
	// game_array = &xPLAYER_SCREEN_H;

    srand(time(NULL)); 
}

void next_game_frame(void)
{
    // if ((*space_array)[11] == 0) // Need a new obstacle
    // {
    //     for (int i = 0; i < SIZEX; i++)
    //     {
    //         switch((int) rand() % 4)
    //         {
    //             case 0: (*space_array)[i] |= RIGHT_OBSTACLE_SCREEN_H[i];
    //                 break;
    //             case 1: (*space_array)[i] |= LEFT_OBSTACLE_SCREEN_H[i];
    //                 break;
    //             case 2: (*space_array)[i] |= MID_OBSTACLE_SCREEN_H[i];
    //                 break;
    //             case 3: (*space_array)[i] |= BOTH_OBSTACLE_SCREEN_H[i];
    //                 break;            
    //         }   
    //     }
    // }

    // for (int i = 0; i < SIZEX; i++)
    // {
    //    (*game_array)[i] = (*space_array)[i] | (*player_array)[i];
    // }

    // renderScreen(game_array);
    renderScreenHorizontal(game_array);
}

void red_button_pressed(void) {
	
}

void green_button_pressed(void) {
	
}

void yellow_button_pressed(void) {
	
}

void blue_button_pressed(void) {
	
}