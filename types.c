#include "types.h"

uint48 uint48of3(unsigned short top, unsigned short mid, unsigned short bot) {
	uint48 toReturn = {top, mid, bot};
	return toReturn;
}

uint48 uint48of1(unsigned short copy) {
	uint48 toReturn = {copy, copy, copy};
	return toReturn;
}