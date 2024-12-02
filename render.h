#include "types.h"

void renderScreen(const array* screen);
void renderScreenHorizontal(const hArray* screen);
void sendLine(uint48 leftLine, uint48 rightLine);
void sendCommand(uint48 command);
void toggleCLK(void);