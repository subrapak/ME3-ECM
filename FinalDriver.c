/*
 * File:   FinalDriver.c
 * Authors: Arohan Subramonia and Gino La
 *
 * Created on 12 March 2018, 17:22
 */

//Header Files
#include <xc.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include "LED.h"
#include "LCD.h"
#include "TMR5.h"
#include "PWM.h"
#include "MTR.h"
#include "CAP.h"
#include "SRL.h"
#include "RFD.h"
#include "ITR.h"

//Configure the internal clock and set clock speed
#pragma config OSC = IRCIO, WDTEN = OFF //Internal oscillator, WDT off 
#define _XTAL_FREQ 8000000

//Global Variables
volatile int buttonpress = -1;      //Initially, button has not been pressed   
volatile int scan = 1;              //Initally, RFID has not been scanned
signed int movementlog[50];         //Log of moves - maximum 50

//Delay for multiples of half a second
void delay_hs(int half_seconds) {
    for (int i = 0; i < half_seconds; i++) {
        __delay_ms(89);
        __delay_ms(89);
        __delay_ms(89);
        __delay_ms(89);
        __delay_ms(89);
        __delay_ms(55);
    }
} 

//Button press interrupt to begin search
void interrupt high_priority ExternalInterrupt() {
    if (INTCON3bits.INT1IF) {
        if (PORTCbits.RC4) {
            if (PORTCbits.RC4) {
                if (PORTCbits.RC4) {
                    buttonpress=-buttonpress;
                    INTCON3bits.INT1IF=0;
                }
            }
        }
    }
}

//RFID reader interrupt to end search
void interrupt low_priority InterruptHandlerHigh() {
    scan=0;                    //RFID has been scanned
    RFIDchecksum();            //Do checksum calculation
}

void main(void) {
    //Initialize the internal clock
    OSCCON = 0x72;              // Set clock to 8MHz
    while (!OSCCONbits.IOFS);   //Wait for clock to stabilize

    //Initializing all modules and pins
    PWMinit();                  //Initialize PWM
    LCDinit();                  //Initialize LCD
    TMR5Init();                 //Initialize Timer
    CAP1init();                 //Initialize CAP1
    CAP2init();                 //Initialize CAP2
    LEDinit();                  //Initialize LED
    initEUSART(205);            //Initialize EUSART
    TRISCbits.RC4 = 1;          //Initialize Pin RC4
    ITRinit(1,1,1,1,1,1,0,1);   //Initialize Interrupts
    
    //Defining motor structures
    struct DC_motor motorL;     //Define motor left properties
        motorL.speed=0;
        motorL.direction=1;
        motorL.dutyLowByte=(unsigned char*)(&PDC1L);
        motorL.dutyHighByte=(unsigned char*)(&PDC1H);
        motorL.dir_pin=2;
        motorL.PWMperiod=PWMcycle;
        
    struct DC_motor motorR;     //Define motor right properties
        motorR.speed=0;
        motorR.direction=1;
        motorR.dutyLowByte=(unsigned char*)(&PDC0L);
        motorR.dutyHighByte=(unsigned char*)(&PDC0H);
        motorR.dir_pin=0;
        motorR.PWMperiod=PWMcycle;

        //Define variables
        int difference;     //Difference between simultaneous readings
        int std;            //Standardized difference
        int size;           //Total number of moves to find beacon
        int counter = 0;    //Index of each move

    while (1) {
        stop(&motorL,&motorR);
        //Trigger main loop to begin
        while (buttonpress == 1) {
            
            //Forwards Search Routine
            while ((scan == 1)) {
                SetLine(1);
                difference = getdiff();                             //Finds the difference between IR sensor readings
                std = diffstd(difference, counter, &movementlog);   //Standardize the values obtained
                move(std, 1, &motorL, &motorR, counter);            //Instructs movement motion
                
                if (counter > 25) {
                    delay_hs(1);        //Delay after 25 moves (closer to beacon) to improve accuracy
                }
                size = counter; //size of the movementlog array
                counter++;
            }

            //Backwards Return Routine
            for (counter = size; counter > 0; counter--) {
                move(((-1)*(movementlog[counter])), 0, &motorL, &motorR, counter); //Times by -1 to change directions of motion
            }
                //Set variables to stop main loop
                scan = 2;
                buttonpress = -1;
                //Default stop position
            while (scan == 2) {
                stop(&motorL,&motorR);
                }
        }
    }
}