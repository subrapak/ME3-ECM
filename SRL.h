/* 
 * File:   SRL.h
 * Authors: Arohan Subramonia and Gino La
 *
 * Created on 09 March 2018, 16:07
 */

#ifndef SRL_H
#define	SRL_H

//See SRL.c for function explanation
char getCharSerial(void);

void sendCharSerial(char charToSend);

void initEUSART(int baud);

#endif	/* SRL_H */