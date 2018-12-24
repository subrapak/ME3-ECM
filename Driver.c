/*
 * File:   Motion.c
 * Author: as10415
 *
 * Created on 12 March 2018, 17:22
 */

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

// Configure the internal clock and set clock speed
#pragma config OSC = IRCIO, WDTEN = OFF //internal oscillator, WDT off 
#define _XTAL_FREQ 8000000

volatile int a = -1;       
volatile int scan = 1;
signed int movementlog[50];

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
 
void interrupt high_priority ExternalInterrupt() {
    if (INTCON3bits.INT1IF) {
        if (PORTCbits.RC4) {
            if (PORTCbits.RC4) {
                if (PORTCbits.RC4) {
                    a=-a;
                    INTCON3bits.INT1IF=0;
                    
                }
            }
        }
    }
}

void interrupt low_priority InterruptHandlerHigh() {
    scan=0;
    RFIDchecksum();
    __delay_ms(89);
    __delay_ms(89);
    __delay_ms(89);
    __delay_ms(89);
    __delay_ms(89);
}

void main(void) {
    //Initialise the internal clock
    OSCCON = 0x72; // Set clock to 2MHz
    while (!OSCCONbits.IOFS);

    //Define variables
    char buf1[16];
    int med;

    //Initialising components
    initPWM();                  //PWM
    LCD_Init();                 //LCD
    CAP1init();                 //CAP1
    CAP2init();                 //CAP2
    LEDinit();                  //LED
    TRISCbits.RC4 = 1;          //Pin RC3
    initEUSART(205);            //EUSART
    ITRinit(1,1,1);
    TMR5Init();
    RCONbits.IPEN = 1;          //Enable interrupt priority
  
    //EUSART
    PIE1bits.RCIE=1;            //EUSART RX enable
    INTCONbits.PEIE=1;          //Peripheral/Low priority enable
    IPR1bits.RC1IP=0;           //High priority enabled
    
    //Button
    INTCON3bits.INT1IP=1;       //INT1 priority
    
    //CAP1 and 2 16 bit registers
    CAP1BUFH = 0;
    CAP1BUFL = 0;
    CAP2BUFH = 0;
    CAP2BUFL = 0;
    
    struct DC_motor motorL;     //Define motor pins
        motorL.speed=0;
        motorL.direction=1;
        motorL.dutyLowByte=(unsigned char*)(&PDC1L);
        motorL.dutyHighByte=(unsigned char*)(&PDC1H);
        motorL.dir_pin=2;
        motorL.PWMperiod=PWMcycle;
        
    struct DC_motor motorR;
        motorR.speed=0;
        motorR.direction=1;
        motorR.dutyLowByte=(unsigned char*)(&PDC0L);
        motorR.dutyHighByte=(unsigned char*)(&PDC0H);
        motorR.dir_pin=0;
        motorR.PWMperiod=PWMcycle;

        int std;
        int size;
        int j = 0; 

      while(1) {
            
       while (a==-1) {
           j = 0; 
           stop(&motorL,&motorR);
           
       }
       
        //Forward Code
            while ((a==1) & (scan==1)) {              
                SetLine(2);
                sprintf(buf1, "Attempt %u", j);
                LCD_String(buf1);
                delay_hs(1);
                med = getdiff();
                std = medstd(med, j, &movementlog);
                move(std,1,&motorL,&motorR);
                size = j;
                j++;
            }

            //Backwards Code
            while ((a==1) & (scan==0)) {
                SendLCD(0b00000001, 0); //Clear LCD
                
            for (j = size; j > 0; j--) {
                SetLine(2);
                sprintf(buf1, "Attempt %u", j);
                LCD_String(buf1);
                delay_hs(1);
                move(((-1)*(movementlog[j])),0,&motorL,&motorR);
                }
                
                a=-1;
                scan=1;
                
                }
       
        }
}



