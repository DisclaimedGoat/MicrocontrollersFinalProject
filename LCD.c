#include "stm32l476xx.h"

#include "LCD.h"
#include "ports.h"

#include "stdbool.h"

# define DELAY 4000

# define OUT GPIOC
# define E_PIN P4
# define RS_PIN P5
# define D0_PIN P6
# define D1_PIN P7
# define D2_PIN P8
# define D3_PIN P9

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
	put_odr_bit(OUT, D0_PIN, 0);
	put_odr_bit(OUT, D1_PIN, 0);
	put_odr_bit(OUT, D2_PIN, 0);
	put_odr_bit(OUT, D3_PIN, 0);
	
	put_odr_bit(OUT, D0_PIN, nybble);
	put_odr_bit(OUT, D1_PIN, nybble >> 1);
	put_odr_bit(OUT, D2_PIN, nybble >> 2);
	put_odr_bit(OUT, D3_PIN, nybble >> 3);
}

void LCD_Pulse(void) {
  put_odr_bit(OUT, E_PIN, 1);
  wait(10);
  put_odr_bit(OUT, E_PIN, 0);
  wait(10);
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
	
	set_pins_output(GPIOC, 6, E_PIN, RS_PIN, D0_PIN, D1_PIN, D2_PIN, D3_PIN);
  
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

void LCD_DisplayString(unsigned int line, unsigned char *ptr) {
  if (line == 0)
    LCD_WriteCom(0x80);
  else if (line == 1)
    LCD_WriteCom(0x80 + 0x40);
  
  
	for (unsigned char *t = ptr; *t != '\0'; t++) {
    LCD_WriteData(*t);
  }
}
