/* 
 * File:   MTR.c
 * Authors: Arohan Subramonia and Gino La
 *
 * Created on 05 March 2018, 15:35
 */

#include <xc.h>
#include "MTR.h"
#include "LCD.h"

//Function to set PWM output from the values in the motor structure
void setMotorPWM(struct DC_motor *m) {
	int PWMduty; //temp variable to store PWM duty cycle

	if (m->direction){ //if forward
		// low time increases with power
		PWMduty=m->PWMperiod - ((int)(m->speed)*(m->PWMperiod))/100;
	}
	else { //if reverse
		// high time increases with power
		PWMduty=((int)(m->speed)*(m->PWMperiod))/100;
	}

	PWMduty = (PWMduty << 2);	// two LSBs are reserved for other things
	*(m->dutyLowByte) = PWMduty & 0xFF; //set low duty cycle byte
	*(m->dutyHighByte) = (PWMduty >> 8) & 0x3F; //set high duty cycle byte
        
	if (m->direction){ // if direction is high
		LATB=LATB | (1<<(m->dir_pin)); // set dir_pin bit in LATB to high without changing other bits
	} else {
		LATB=LATB & (~(1<<(m->dir_pin))); // set dir_pin bit in LATB to low without changing other bits
	}
}

//Function to gradually set motor to full speed
void setMotorFullSpeed(struct DC_motor *m) {
    for(m->speed; (m->speed)<=100; (m->speed)++) {
        setMotorPWM(m);
    }    
}

//Function to stop a motor gradually
void stopMotor(struct DC_motor *m) {
    for(m->speed; (m->speed)> 0; (m->speed)--) {
        setMotorPWM(m);
    }    
}

//Stop the robot
void stop(struct DC_motor *mL, struct DC_motor *mR) {
    stopMotor(mL);
    stopMotor(mR);
}
   
//Function to make the robot turn left
void turnLeft(struct DC_motor *mL, struct DC_motor *mR) {
        stopMotor(mL);
        stopMotor(mR);
        mL->direction = 1;
        mR->direction = 0;
        setMotorFullSpeed(mL);
        setMotorFullSpeed(mR);   
}

//Function to make the robot turn left
void turnRight(struct DC_motor *mL, struct DC_motor *mR) {
        stopMotor(mL);
        stopMotor(mR);
        mL->direction = 0;
        mR->direction = 1;
        setMotorFullSpeed(mR);
        setMotorFullSpeed(mL);   
}

//Go full speed either forwards or backwards dependent on int dir (direction)
void fullSpeed(struct DC_motor *mL, struct DC_motor *mR, int dir) {
    mL->direction = dir;
    mR->direction = dir;
    setMotorFullSpeed(mL);
    setMotorFullSpeed(mR);
}

//Function which moves the robot based on standardized values
void move(int std, int dir, struct DC_motor *mL, struct DC_motor *mR, int counter) {
     //Turn Right
     if (std == 1) {                
        turnRight(mL, mR);
        __delay_ms(89);
        __delay_ms(89);
        __delay_ms(89);
        stop(mL, mR);
        
        fullSpeed(mL, mR, dir);
        __delay_ms(89);  
        __delay_ms(89);
        __delay_ms(89);  
        stop(mL, mR);
    }
        //Turn Left
        else if (std == -1) {
        turnLeft(mL, mR);
        __delay_ms(89);
        __delay_ms(89);
        __delay_ms(89);
        stop(mL, mR);
        
        fullSpeed(mL,mR, dir);
         __delay_ms(89);
         __delay_ms(89);
         __delay_ms(89);
        stop(mL, mR);
    }
        //Move Forward
        else if (std == 2) {
        fullSpeed(mL, mR, 1);
        __delay_ms(89);
        __delay_ms(89);
        __delay_ms(89);
        __delay_ms(89);
        __delay_ms(89);
        __delay_ms(89);
        __delay_ms(89);
        __delay_ms(89);
        stop(mL, mR);    
    }
        //Move Backward
        else if (std == -2) {
        fullSpeed(mL, mR, 0);
        __delay_ms(89);
        __delay_ms(89);
        __delay_ms(89);
        __delay_ms(89);
        __delay_ms(89);
        __delay_ms(89);
        __delay_ms(89);
        __delay_ms(89);
        stop(mL, mR);
    }   
}