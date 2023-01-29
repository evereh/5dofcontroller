/*
 * motor.c
 *
 * Created: 11.08.2021 20:19:57
 *  Author: pawel
 */ 
#include "motor.h"
#include <avr/io.h>

#define MOTOR_SEL0 (1<<4)
#define MOTOR_INA (1<<5)
#define MOTOR_INB (1<<6)
#define MOTOR_PWM (1<<7)

enum MotorState motorState;

void motorInit()
{
	DDRB |= MOTOR_INA | MOTOR_INB | MOTOR_PWM | MOTOR_SEL0;  //setting pins as output
	PORTB |= MOTOR_SEL0; //
	
	//configurate OC1C
	TCCR1A |=0b00001011; // 23 bits as clear on compare , Fast pwm 10 bit 10
	TCCR1B |=0b00000010; // 43 fast pwm 10, 210 prescaler 8
	motorState = MOTOR_STOP;
}
void motorRight()
{
	PORTB |= MOTOR_INA;
	PORTB &= ~MOTOR_INB;
	OCR1C = 1023;
	motorState = MOTOR_RIGHT;
	//PORTB |= MOTOR_PWM;
}
void motorLeft()
{
	PORTB |= MOTOR_INB;
	PORTB &= ~MOTOR_INA;
	OCR1C = 1023;
	motorState = MOTOR_LEFT;
	//PORTB &= MOTOR_PWM;
}
void motorStop()
{
	PORTB &= ~MOTOR_INB;
	PORTB &= ~MOTOR_INA;
	OCR1C = 0;
	motorState = MOTOR_STOP;
}
void motorPWM(int pwm)
{
	if(pwm == 0)
	{
		motorStop();
	}
	else if(pwm>0)
	{
		if(pwm>1023) pwm = 1023;
		PORTB |= MOTOR_INA;
		PORTB &= ~MOTOR_INB;
		OCR1C = pwm;
		motorState = MOTOR_RIGHT_PWM;
	}
	else
	{
		pwm = -pwm;
		if(pwm>1023) pwm = 1023;
		PORTB |= MOTOR_INB;
		PORTB &= ~MOTOR_INA;
		OCR1C = pwm;
		motorState = MOTOR_LEFT_PWM;
	}
	
}

enum MotorState getMotorState()
{
	return motorState;
}