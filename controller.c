/*
 * controller.c
 *
 * Created: 29.10.2021 23:12:09
 *  Author: pawel
 */ 
#include "controller.h"
#include "encoder.h"
#include "motor.h"
#include "limitSwitches.h"

#define CONTOR_P 5
#define CONTROL_kp 5
#define CONTROL_Ti 1000


#define LIMIT_SWITCHES_DOWN_MAX (-2100)
#define LIMIT_SWITCHES_UP_MAX (2100)

static int calculatePwmValue(int e, int* eLast);

static int counterGiven = 0;

void controllerPI()
{
	enum LimitSwitchesState limitSwitchesState = getLimitSwitchesState();
	if(limitSwitchesState == LIMIT_SWITCHES_NO)
	{
		int pwm, encoderCouter, e;
		static int eLast = 0; 
		encoderCouter = getEncoderCoutner();
		
		e = counterGiven - encoderCouter;
		
		pwm = calculatePwmValue(e, &eLast);
		
		motorPWM(pwm);
	}
	else if(limitSwitchesState == LIMIT_SWITCHES_UP)
	{
		int encoderCouter = getEncoderCoutner();
		if(encoderCouter < LIMIT_SWITCHES_UP_MAX)
		{
			clearLimitSwitchesState();
		}
	}
	else if(limitSwitchesState == LIMIT_SWITCHES_DOWN)
	{
		int encoderCouter = getEncoderCoutner();
		if(encoderCouter > LIMIT_SWITCHES_DOWN_MAX)
		{
			clearLimitSwitchesState();
		}
	}
	
}

void setCounterGiven(int counter)
{
	counterGiven = counter;
}

int getCounterGiven()
{
	return counterGiven;
}

void controllerP()
{
	enum LimitSwitchesState limitSwitchesState = getLimitSwitchesState();
	if(limitSwitchesState == LIMIT_SWITCHES_NO)
	{
		int pwm, encoderCouter;
		encoderCouter = getEncoderCoutner();
		
		pwm = CONTOR_P * (counterGiven - encoderCouter);
		
		motorPWM(pwm);
	}
	else if(limitSwitchesState == LIMIT_SWITCHES_UP)
	{
		int encoderCouter = getEncoderCoutner();
		if(encoderCouter < LIMIT_SWITCHES_UP_MAX)
		{
			clearLimitSwitchesState();
		}
	}
	else if(limitSwitchesState == LIMIT_SWITCHES_DOWN)
	{
		int encoderCouter = getEncoderCoutner();
		if(encoderCouter > LIMIT_SWITCHES_DOWN_MAX)
		{
			clearLimitSwitchesState();
		}
	}
	
}

static int calculatePwmValue(int e, int* eLast)
{
	int x, U;
	static long S = 0;
	
	long numerator = CONTROL_kp * CONTROL_dt_inMS * (long)e;
	long denominator = CONTROL_Ti * 1000L;
	S += numerator / denominator;
	x = CONTROL_kp * e;
	
	if (x > 1023)
	{
		x = 1023;
	} 
	else if(x < -1023)
	{
		x = -1023;
	}

	U = x + S;
	//
	/* Krok 2 z ksiazki */
	if(U > 1023)
	{
		S = 1023 - x;
		U = 1023;
	}
	/* krok 3 z ksiazki */
	else if(U < -1023)
	{
		S = -1023 - x;
		U = -1023;
	}
	//
	//    /* krok 4 z ksiazki */
	*eLast = e;

	return U;
	
	
}