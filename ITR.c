/* 
 * File:   ITR.c
 * Authors: Arohan Subramonia and Gino La
 *
 * Created on 01 March 2018, 14:59
 */

#include <xc.h>
#include "ITR.h"

//Function to initialize interrupts as required
void ITRinit(char high, char low, char ext, char ipen, char rcie, char peie, char rc1ip, char int1ip) {
    // Enable Global interrupts and high priority interrupt
    INTCONbits.GIEH=high;
    //Enable low priority interrupt
    INTCONbits.GIEL=low;
    //INT1 External Interrupt Enable bit
    INTCON3bits.INT1IE=ext;
    //Enable interrupt priorities
    RCONbits.IPEN = ipen;          
    //EUSART RX Interrupt enable
    PIE1bits.RCIE=rcie;
    //Peripheral interrupt enable
    INTCONbits.PEIE=peie;
    //Set EUSART priority
    IPR1bits.RC1IP=rc1ip;           
    //INT1 priority
    INTCON3bits.INT1IP=int1ip;       
}