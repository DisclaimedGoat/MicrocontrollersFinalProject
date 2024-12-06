#include "stm32l476xx.h"

#include "LCD.h"
#include "ports.h"

#include "stdbool.h"

# define DELAY 80

# define OUT GPIOC
# define E_PIN P4
# define RS_PIN P5
# define D4_PIN P6
# define D5_PIN P7
# define D6_PIN P8
# define D7_PIN P9

void LCD_PutNibble(unsigned char nybble);
void LCD_Pulse(void);

// Delay ms milliseconds
// Retrieved from provided LCD Documentation
void wait(unsigned int t) {
	for (unsigned int i = 0; i < t; i++) {
    for (unsigned int j = 0; j < DELAY; j++) {
			
    }
  }
}

void LCD_PutNibble(unsigned char nybble) {
	put_odr_bit(OUT, D4_PIN, 0);
	put_odr_bit(OUT, D5_PIN, 0);
	put_odr_bit(OUT, D6_PIN, 0);
	put_odr_bit(OUT, D7_PIN, 0);
	
	put_odr_bit(OUT, D4_PIN, nybble);
	put_odr_bit(OUT, D5_PIN, nybble >> 1);
	put_odr_bit(OUT, D6_PIN, nybble >> 2);
	put_odr_bit(OUT, D7_PIN, nybble >> 3);
}

void LCD_Pulse(void) {
  put_odr_bit(OUT, E_PIN, 1);
  wait(2);
  put_odr_bit(OUT, E_PIN, 0);
  wait(2);
}

// Write command to LCD
// Retrieved from provided LCD Documentation
void LCD_WriteCom(unsigned char com) {
	put_odr_bit(OUT, RS_PIN, 0);
	put_odr_bit(OUT, E_PIN, 0);
  
  LCD_PutNibble(com >> 4);
  LCD_Pulse();
  
  LCD_PutNibble(com & 0x0F);
  LCD_Pulse();
  
	put_odr_bit(OUT, RS_PIN, 1);
}

void LCD_WriteData(unsigned char dat) {
  put_odr_bit(OUT, E_PIN, 0);
  
  LCD_PutNibble(dat >> 4);
  LCD_Pulse();
  
  LCD_PutNibble(dat & 0xF);
  LCD_Pulse();
}

void LCD_Init(void){
	
	set_pins_output(GPIOC, 6, E_PIN, RS_PIN, D4_PIN, D5_PIN, D6_PIN, D7_PIN);
  
  // Commands to LCD:
  // i. 4-bit bus, 2-line display mode, 5x8 dot matrix
  // ii. display on, cursor off, cursor blink off
  // iii. cursor moves left-to-right, no display scrolling
  // iv. clear display
  // v. set up CGRAM address to start at 0
  wait(30);
  LCD_WriteCom(0x30);
  wait(5);
  LCD_WriteCom(0x30);
  wait(1);
  LCD_WriteCom(0x30);
  wait(1);
  
  // Set cursor to init position
  LCD_WriteCom(0x2);
  wait(1);
  
  // Set 4-bit data mode
  LCD_WriteCom(0x28);
  wait(1);

  // Clear display
  LCD_Clear();
	wait(10);
  
  // Entry mode
  LCD_WriteCom(0x06);
  wait(1);
  LCD_WriteCom(0x0C);
  wait(1);
}

void LCD_Clear(void){
  LCD_WriteCom(0x01);
  wait(2);
}

void LCD_Print(const char* msg) {
	LCD_Clear();

	LCD_WriteCom(0x80);
	
	int charCount = 0;
	const char* t = msg;	
	for ( ; *t != '\0'; charCount++, t++) {
		if (charCount == 16) {
			LCD_WriteCom(0x80 + 0x40);
		}
		LCD_WriteData(*t);
	}
}

void LCD_PrintEach(const char* line0, const char* line1) {
	LCD_PrintLine(0, line0);
	wait(2);
	LCD_PrintLine(1, line1);
}

void LCD_PrintLine(unsigned int line, const char *ptr) {
  if (line == 0)
    LCD_WriteCom(0x80);
  else if (line == 1)
    LCD_WriteCom(0x80 + 0x40);
  
  
	for (const char *t = ptr; *t != '\0'; t++) {
    LCD_WriteData(*t);
  }
}
