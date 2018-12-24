/* 
 * File:   RFD.c
 * Authors: Arohan Subramonia and Gino La
 *
 * Created on 13 March 2018, 09:50
 */

#include <xc.h>
#include "RFD.h"
#include "LCD.h"
#include "SRL.h"

//Function to read the RFID and checksum
void RFIDchecksum(){
    int i = 0;      //Counter for checksum code
    char Correctdata[12];   
    char ASCIIdata[12];
    char HexNumbers[6];
    char Result; 
    
    char text = getCharSerial();                //Reads the first value of data byte in sequence

            if (text == 0x02) {

            while (i <= 11) {               
                //Reading the next 12 data bytes containing Data ASCII and Checksum ASCII bytes 
                //Saving ASCII data from Card to data array
                ASCIIdata[i] = getCharSerial();             
                SendLCD(ASCIIdata[i], 1);
                if (ASCIIdata[i] >= 48 & ASCIIdata[i] <= 57) {
                    Correctdata[i] = ASCIIdata[i] - 48;                     //Converting ASCII numbers to Dec (Using ASCII tables online)
                }
                if (ASCIIdata[i] >= 65 & ASCIIdata[i] <= 70) {              //Converting ASCII letters to Dec (Using ASCII tables online)
                    Correctdata[i] = ASCIIdata[i] - 55;
                }
                i++;
            }
}
   //XORing every other bit, XORing something with itself should give 0, so if both are equal (to zero) checksum is valid
   //XORing all even bits, and then XORing all odd bits
    if (((Correctdata[0]^Correctdata[2]^Correctdata[4]^Correctdata[6]^Correctdata[8]^Correctdata[10])==0)&((Correctdata[1]^Correctdata[3]^Correctdata[5]^Correctdata[7]^Correctdata[9]^Correctdata[11])==0)) {
        SetLine(2);
        LCD_String("VALID");
    } else {
        SetLine(2);
        LCD_String("FALSE");
    }    
}