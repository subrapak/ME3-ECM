/* 
 * File:   LCD.h
 * Authors: Arohan Subramonia and Gino La
 *
 * Created on 01 March 2018, 15:41
 */

#ifndef LCD_H
#define	LCD_H

#define _XTAL_FREQ 8000000

//See LCD.c for function explanations
void E_TOG(void);

void LCDout(unsigned char number);

void SendLCD(unsigned char Byte, char type);

void LCDinit(void);

void LCD_String(char *string);

void SetLine(char line);

#endif	/* LCD_H */