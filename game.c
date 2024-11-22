#include "stm32l476xx.h"
#include "render.h"
#include "game.h"
#include "types.h"

array startScreen;

void gameLoop(void)
{
// Game logic stuffs

    renderScreen(&startScreen);
}

void gameScreens_Init(void)
{
    startScreen = (array) malloc(sizeof(short) * SIZEY);
    startScreen = {
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
}