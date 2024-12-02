#include "stm32l476xx.h"
#include "render.h"
#include "game.h"
#include "screens.h"
#include "stdlib.h"

#define NONE  0
#define LEFT  1
#define RIGHT 2

static hArray* game_array;
static int RUNNING = 0;
static int DIRECTION = NONE;

void game_init(void)
{
    game_array = (hArray*) malloc(sizeof(int) * SIZEX);
    game_array = &TEST_HORIZONTAL_SCREEN;
}

void next_game_frame(void)
{
    if (game_array[12] == 0)
    {
        //
    }

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