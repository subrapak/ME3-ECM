/* 
 * File:   MTR.h
 * Authors: Arohan Subramonia and Gino La
 *
 * Created on 05 March 2018, 15:35
 */

#ifndef MTR_H
#define _XTAL_FREQ 8000000
#define PWMcycle 199

struct DC_motor {
    char speed; //Speed 0-10
    char direction;     //Forward=1. Backward=0
    unsigned char *dutyLowByte;
    unsigned char *dutyHighByte;
    char dir_pin;   //Pin that controls direction at PortB0/2
    int PWMperiod; //PWM period
};

//See MTR.c for function explanations
void setMotorPWM(struct DC_motor *m);

void setMotorFullSpeed(struct DC_motor *m);

void stopMotor(struct DC_motor *m);

void stop(struct DC_motor *mL, struct DC_motor *mR);
   
void turnLeft(struct DC_motor *mL, struct DC_motor *mR);

void turnRight(struct DC_motor *mL, struct DC_motor *mR);

void fullSpeed(struct DC_motor *mL, struct DC_motor *mR, int dir);

void move(int std, int dir, struct DC_motor *mL, struct DC_motor *mR, int counter);

#endif	/* MTR_H */