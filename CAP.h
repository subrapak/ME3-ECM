/* 
 * File:   CAP.h
 * Authors: Arohan Subramonia and Gino La
 *
 * Created on 13 March 2018, 09:22
 */

#ifndef CAP_H
#define	CAP_H

#define _XTAL_FREQ 8000000

//See CAP.c for function explanations
void CAP1init(void);

void CAP2init(void);

int median(int n, int x[]);

int getdiff(void);

int diffstd(int value, int counter, unsigned int *movementpoint);

#endif	/* CAP_H */