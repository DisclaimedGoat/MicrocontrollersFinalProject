#pragma once

#include "types.h"

static const hArray TEST_HORIZONTAL_SCREEN = {
    0b010101010101010101010101,
    0b101010101010101010101010,
    0b010101010101010101010101,
    0b101010101010101010101010,
    0b010101010101010101010101,
    0b101010101010101010101010,
    0b010101010101010101010101,
    0b101010101010101010101010,
    0b010101010101010101010101,
    0b101010101010101010101010,
    0b010101010101010101010101,
    0b101010101010101010101010,
    0b010101010101010101010101,
    0b101010101010101010101010,
    0b010101010101010101010101,
    0b101010101010101010101010,
};

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

static const array PLAYER_SCREEN = { 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0b0000000110000000, // Row 19
    0b0000001001000000, // Row 20
    0b0000010000100000, // Row 21
	0, 0, 0
};

static const array LEFT_OBSTACLE_SCREEN = {
    0b0011000000000000,
    0b0111100000000000,
    0b0111100000000000,
    0b0111100000000000,
    0b0111100000000000,
    0b0011000000000000,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

static const array MID_OBSTACLE_SCREEN = {
    0b0000000110000000,
    0b0000001111000000,
    0b0000001111000000,
    0b0000001111000000,
    0b0000001111000000,
    0b0000000110000000,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

static const array RIGHT_OBSTACLE_SCREEN = {
    0b0000000000001100,
    0b0000000000011110,
    0b0000000000011110,
    0b0000000000011110,
    0b0000000000011110,
    0b0000000000001100,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

static const array BOTH_OBSTACLE_SCREEN = {
    0b0011000000001100,
    0b0111100000011110,
    0b0111100000011110,
    0b0111100000011110,
    0b0111100000011110,
    0b0011000000001100,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};