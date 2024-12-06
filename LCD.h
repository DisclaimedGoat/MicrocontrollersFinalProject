#ifndef __STM32L476R_NUCLEO_LCD_H
#define __STM32L476R_NUCLEO_LCD_H

void delay_ms(unsigned int ms);
void LCD_WriteCom(unsigned char com);
void LCD_WriteData(unsigned char dat);
void LCD_Init(void);
void LCD_Clear(void);


void LCD_Print(const char* msg);
void LCD_PrintEach(const char* line0, const char* line1);
void LCD_PrintLine(unsigned int line, const char *ptr);

#endif
