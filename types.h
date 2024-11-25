#pragma once

#define SIZEX 16
#define SIZEY 24

typedef unsigned short array[24];

typedef struct uint48 {
	unsigned short top16;
	unsigned short mid16;
	unsigned short bot16;
} uint48;