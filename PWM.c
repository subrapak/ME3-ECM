/* 
 * File:   PWM.c
 * Authors: Arohan Subramonia and Gino La
 *
 * Created on 01 March 2018, 16:22
 */

#include <xc.h>
#include "PWM.h"

//Function to initialize PWM signal
void PWMinit(void) {
    LATBbits.LATB0=0;
    LATBbits.LATB1=0;
    LATBbits.LATB2=0;
    LATBbits.LATB3=0;
    
    TRISBbits.TRISB0=0; //PWM0-PWM3 enabled
    TRISBbits.TRISB1=0; //PWM0-PWM3 enabled
    TRISBbits.TRISB2=0; //PWM0-PWM3 enabled
    TRISBbits.TRISB3=0; //PWM0-PWM3 enabled

    PTCON0=0b00000000; //free running mode, 1:1 prescaler
    PTCON1=0b10000000; //enable PWM timer
    
    PWMCON0=0b01101111; //PWM0-PWM3 enabled, all independent mode
    PWMCON1=0x00; //special features, all 0 (default)
    
    PTPERL=0b11000111; //base PWM period low byte (199)
    PTPERH=0b0000; //base PWM period high byte  
    
    //Initially set all values to 0
    PDC0L = 0;      
    PDC0H = 0;
    PDC1L = 0;
    PDC1H = 0;   
}