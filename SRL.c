/* 
 * File:   SRL.c
 * Authors: Arohan Subramonia and Gino La
 *
 * Created on 09 March 2018, 16:07
 */

#include <xc.h>
#include "SRL.h"

//Receive a value from the serial port
char getCharSerial(void){
    while (!PIR1bits.RCIF); //EUSART Receive Interrupt Flag bit 
    return RCREG;
}

//Transmit a value from the serial port
void sendCharSerial(char charToSend){
    while (!PIR1bits.TXIF); //EUSART Transmit Interrupt Flag bit 
    TXREG=charToSend;
}

//Initialize the EUSART/serial connection
void initEUSART(int baud){
    
    TRISCbits.TRISC7 = 1;       //set RX pin as input
    
    //Baud should be set to 205 (baud rate to ~9700) or 102 (baud rate to ~19600)
    SPBRG=baud;                 //Lower 8 bits of register
    SPBRGH=baud >> 8;           //Upper 8 bits of register
    
    BAUDCONbits.BRG16=1;        //16 bit baud rate generator enable
    TXSTAbits.BRGH = 1;         //High speed baud rate (asynchronous mode)
    RCSTAbits.CREN = 1;         //Continuous receive enable bit
    RCSTAbits.RX9 = 0;          //8 bit receive enable bit
    RCSTAbits.SPEN = 1;         //Serial port enable bit
    TXSTAbits.TXEN = 1;         //Transmit enable bit
}