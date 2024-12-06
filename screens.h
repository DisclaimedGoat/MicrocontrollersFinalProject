#pragma once

#include "types.h"

static const hArray TEST_SCREEN = {
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

static const hArray EMPTY_SCREEN = {
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

static const hArray PLAYER_SCREEN = {
    0,0,0,0,0,0,0,
    0b11000,
    0b11000,
    0,0,0,0,0,0,0
};

static const hArray LEFT_OBSTACLE_SCREEN = {
    0,0,0,0,0,0,0,0,0,0,0,
    0b01111000000000000000000000000000,
    0b11111100000000000000000000000000,
    0b11111100000000000000000000000000,
    0b01111000000000000000000000000000,
    0,
};

static const hArray MID_OBSTACLE_SCREEN = {
    0,0,0,0,0,0,
    0b01111000000000000000000000000000,
    0b11111100000000000000000000000000,
    0b11111100000000000000000000000000,
    0b01111000000000000000000000000000,
    0,0,0,0,0,0
};

static const hArray BOTH_OBSTACLE_SCREEN = {
    0,
    0b01111000000000000000000000000000,
    0b11111100000000000000000000000000,
    0b11111100000000000000000000000000,
    0b01111000000000000000000000000000,
    0,0,0,0,0,0,
    0b01111000000000000000000000000000,
    0b11111100000000000000000000000000,
    0b11111100000000000000000000000000,
    0b01111000000000000000000000000000,
    0,
};

static const hArray RIGHT_OBSTACLE_SCREEN = {
    0,
    0b01111000000000000000000000000000,
    0b11111100000000000000000000000000,
    0b11111100000000000000000000000000,
    0b01111000000000000000000000000000,
    0,0,0,0,0,0,0,0,0,0,0
};

static const hArray BOTH_LEFT_OBSTACLE_SCREEN = {
    0b11111100000000000000000000000000,
    0b01111000000000000000000000000000,
    0,0,0,0,0,0,
    0b01111000000000000000000000000000,
    0b11111100000000000000000000000000,
    0b11111100000000000000000000000000,
    0b01111000000000000000000000000000,
    0,0,0,0
};

static const hArray BOTH_RIGHT_OBSTACLE_SCREEN = {
    0,0,0,0,
    0b01111000000000000000000000000000,
    0b11111100000000000000000000000000,
    0b11111100000000000000000000000000,
    0b01111000000000000000000000000000,
    0,0,0,0,0,0,
    0b01111000000000000000000000000000,
    0b11111100000000000000000000000000
};

static const hArray START_SCREEN = {
    0b110101010101101010101011,
    0b111111111111111111111111,
    0b011011011000000100000010,
    0b110111011000001000000011,
    0b011110110000010000000110,
    0b110001110000100000011011,
    0b011111100001000111101010,
    0b111110000010001111110011,
    0b110000011000011111100011,
    0b010000011100011111010010,
    0b110000111100011110110011,
    0b010000110000011101100010,
    0b110000000000101011000011,
    0b010000000000110000000010,
    0b111111111111111111111111,
    0b110101010101101010101011,
};

static const hArray PLAYER_EXPLOSION_SCREENS[4] = {
{
    0,0,0,0,0,0,
    0b011000,
    0b100100,
    0b100100,
    0b011000,
    0,0,0,0,0,0
},
{
    0,0,0,0,0,
    0b0010000,
    0b0100100,
    0b0000010,
    0b1000000,
    0b0100100,
    0b0001000,
    0,0,0,0,0
},
{
    0,0,0,
    0b01000,
    0b10000,
    0,0,
    0b100000001,
    0b010000000,
    0,0,
    0b01000,
    0b10000,
    0,0,0
},
{
    0,0,
    0b10,
    0,0,
    0b1000000000,
    0,0,0,0,0,0,0,
    0b1000000,
    0,0
}};

