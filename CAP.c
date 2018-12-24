/* 
 * File:   CAP.c
 * Authors: Arohan Subramonia and Gino La
 *
 * Created on 13 March 2018, 09:22
 */

#include <xc.h>
#include "CAP.h"

//CAP1 register setup
void CAP1init(void) {
    TRISAbits.RA2 = 1;              //Set RA2 pin to input
    CAP1CONbits.CAP1REN = 1;        //Enable time base reset for TMR5
    CAP1CONbits.CAP1M = 0b0110;     //PWM measurement, falling to rising edge
    ANSEL0bits.ANS2 = 0;            //Set pin 2 to digital input
}

//CAP2 register setup
void CAP2init(void) {
    TRISAbits.RA3 = 1;              //Set RA3 pin to input
    CAP2CONbits.CAP2REN = 1;        //Enable time base reset for TMR5
    CAP2CONbits.CAP2M = 0b0110;     //PWM measurement, falling to rising edge
    ANSEL0bits.ANS3 = 0;            //Set pin 3 to digital input
}

//Finds the median of array (will be used to find the median of movementlog)
int median(int n, int x[]) {
    int temp;
    int i, j;
    // The following two loops sort the array x in ascending order
    for(i=0; i<n-1; i++) {
        for(j=i+1; j<n; j++) {
            if(x[j] < x[i]) {
                // Swap elements
                temp = x[i];
                x[i] = x[j];
                x[j] = temp;
            }
        }
    }

    if(n%2==0) {
        // If there is an even number of elements, return mean of the two elements in the middle
        return((x[n/2] + x[n/2 - 1]) / 2);
    } else {
        // Else return the element in the middle
        return x[n/2];
    }
}

//Finds the difference between two simultaneous infrared readings
int getdiff(void) {
        unsigned int CAP1Result;            
        unsigned int CAP2Result;
        int hist[15];       //History array to store values
        
            for (int i =0; i < 15; i++) {
                CAP1Result = CAP1BUFL;
                CAP1Result += ((unsigned int) CAP1BUFH << 8);
                CAP2Result = CAP2BUFL;
                CAP2Result += ((unsigned int) CAP2BUFH << 8);
                int diff = ((CAP1Result - CAP2Result));
                hist[i]=diff;
        }
    
            int med = median(15,hist);      //Outputs median 
            return med;
}

//Standardize the difference values, Only outputs -1, 1 or 2
int diffstd(int value, int counter, unsigned int *movementpoint) {
    char tolerance = 100;  
    signed int std;
    
    if (value > tolerance) {
        std = 1;                    //Turning right
    }
    if (value < -tolerance) {
        std = -1;                   //Turning left
    }
    if ((value < tolerance) & (value > -tolerance)) {
        std = 2;                    //Going forwards
    }
    
    *(movementpoint+counter) = std;
    return std;
}

