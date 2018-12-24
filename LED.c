/* 
 * File:   LED.c
 * Authors: Arohan Subramonia and Gino La
 *
 * Created on 28 February 2018, 10:39
 */

#include <xc.h>
#include "LED.h"

//Initialize the LED
void LEDinit(void) {
    //Set relevant tristate register to output
    TRISDbits.TRISD6 = 0;
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD4 = 0;
    TRISCbits.TRISC7 = 0;
    TRISCbits.TRISC6 = 0;
    TRISCbits.TRISC5 = 0;
    TRISCbits.TRISC4 = 0;
    TRISDbits.TRISD3 = 0;
    TRISDbits.TRISD2 = 0; 
}

//Display binary values on the LED
void LEDout(int i) {   
    LATC=(i&0b000111100)<<2;
    LATD=(i&0b000000011)<<2 | (i&0b111000000)>>2;        
}