/* 
 * File:   LCD.c
 * Authors: Arohan Subramonia and Gino La
 *
 * Created on 01 March 2018, 15:41
 */

#include <xc.h>
#include "LCD.h"
//Toggle the send bit on and off
void E_TOG(void){
    
     PORTAbits.RA6 = 1;
     __delay_us(5);
     PORTAbits.RA6 = 0;
     __delay_us(5);
     } 

//Send information across the 4 bit channel
void LCDout(unsigned char number){
    PORTCbits.RC0 = (number & 0b0001);
    PORTCbits.RC1 = (number & 0b0010) >> 1;
    PORTDbits.RD0 = (number & 0b0100) >> 2;
    PORTDbits.RD1 = (number & 0b1000) >> 3;
    E_TOG();
    __delay_us(5);
}

//Function to send information or data to LCD
void SendLCD(unsigned char Byte, char type){
    PORTAbits.RA7 = type;       // type=1 for data, type=0 for instruction
    
    LCDout(Byte >> 4);          //send high bits of Byte using LCDout function
    __delay_us(10);
    LCDout(Byte);               //send low bits of Byte using LCDout function
    __delay_us(50);
}

//Function to send and display a string on the LCD
void LCD_String(char *string) {
    while(*string != 0) {
        SendLCD(*string++,1);   //send each bit at a time from address
        __delay_us(50);        
    }   
}

//Function to initialize LCD screen
void LCDinit(void){
    //Set tristate registers
    TRISAbits.RA6 = 0;
    TRISAbits.RA7 = 0;
    TRISCbits.RC1 = 0;
    TRISCbits.RC0 = 0;
    TRISDbits.RD1 = 0;
    TRISDbits.RD0 = 0;

    // Reset LED inputs
    LATAbits.LATA6 = 0;
    LATAbits.LATA7 = 0;
    LATCbits.LATC0 = 0;
    LATCbits.LATC1 = 0;
    LATDbits.LATD0 = 0;
    LATDbits.LATD1 = 0;
    
    __delay_ms(15);         //delay 15ms
    LCDout(0b0011);   
    __delay_ms(5);          //delay 5ms          
    LCDout(0b0011);
    __delay_us(200);        //delay 200ms
    LCDout(0b0011);         
    __delay_us(50);         //delay 50ms
    LCDout(0b0010);
    __delay_us(50);         //delay 50ms
    
    //Now use SendLCD to send whole bytes
    SendLCD (0b00101000, 0);    //Set function set
    __delay_ms(2);
    SendLCD(0b00001000, 0);     //Display Off
    __delay_ms(2); 
    SendLCD(0b00000001, 0);     //Display Clear
    __delay_ms(2);
    SendLCD(0b00000110, 0);     //Entry mode set
    __delay_ms(2);
    SendLCD(0b00001111, 0);     //Display On
    __delay_ms(2);
}

//Function to set the top.bottom line on the LCD
void SetLine(char line) {
    //Set Line to top line
    if (line==1) {
        SendLCD(0x80,0);
    }
    //Set Line to bottom line
    if (line == 2) {
        SendLCD(0xC0,0);
    }
    __delay_us(50);
}