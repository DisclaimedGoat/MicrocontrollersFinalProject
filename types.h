#pragma once

#define SIZEX 16
#define SIZEY 24

typedef unsigned short array[24];

typedef struct uint48 {
	unsigned short top16;
	unsigned short mid16;
	unsigned short bot16;
} uint48;

static const uint48 EMPTY48 = {0};

uint48 uint48of3(unsigned short top, unsigned short mid, unsigned short bot);
uint48 uint48of1(unsigned short copy);