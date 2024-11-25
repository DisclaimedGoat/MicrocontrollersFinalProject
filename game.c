#include "stm32l476xx.h"
#include "render.h"
#include "game.h"
#include "stdlib.h"

static const array START_SCREEN = {
        0b0000000000000000,
        0b0011100000000000,
        0b0100000001100000,
        0b0101110010010000,
        0b0100010010010000,
        0b0011100001100000,
        0b0000000000000000,
        0b0000011100000000,
        0b0000100000001100,
        0b0000101110010010,
        0b0000100010010010,
        0b0000011100001100,
        0b0000000000000000,
        0b0000111000000000,
        0b0001000000011000,
        0b0001011100100100,
        0b0001000100100100,
        0b0000111000011000,
        0b0000000000000000,
        0b0000001001000000,
        0b0000001001000000,
        0b0000100000010000,
        0b0000011111100000,
        0b0000000000000000
};

static const array TEST_SCREEN = {
        0b1010101010101010,
	      0b1010101010101010,
	      0b1010101010101010,
	      0b1010101010101010,
	      0b1010101010101010,
	      0b1010101010101010,
	      0b1010101010101010,
	      0b1010101010101010,
	      0b1010101010101010,
	      0b1010101010101010,
	      0b1010101010101010,
	      0b1010101010101010,
	      0b1010101010101010,
	      0b1010101010101010,
	      0b1010101010101010,
	      0b1010101010101010,
	      0b1010101010101010,
	      0b1010101010101010,
	      0b1010101010101010,
	      0b1010101010101010,
	      0b1010101010101010,
				0b1010101010101010,
				0b1010101010101010,
				0b1010101010101010
};

static array* game_array;

void game_init(void)
{
    game_array = (array*) malloc(sizeof(short) * SIZEY);
}

void next_game_frame(void)
{
// Game logic stuffs

    renderScreen(&TEST_SCREEN);
}

void set_game_screen(const array* screen) {
	
}

void red_button_pressed(void) {
	
}

void green_button_pressed(void) {
	
}

void yellow_button_pressed(void) {
	
}

void blue_button_pressed(void) {
	
}
