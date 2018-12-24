/* 
 * File:   TMR5.c
 * Authors: Arohan Subramonia and Gino La
 *
 * Created on 13 March 2018, 09:20
 */

#include <xc.h>
#include "TMR5.h"

//Timer5 setup
void TMR5Init(void) {
    
    T5CONbits.TMR5ON = 1;       //Timer5 is enabled 
    T5CONbits.RESEN = 1;        //Special Event Trigger Reset is disabled
    T5CONbits.T5MOD = 0;        //Continuous clock mode is enabled
    T5CONbits.T5PS=0b11;        //Prescaler of 1:8
    T5CONbits.TMR5CS = 0;       //Use internal clock
}