/*
 * limitSwitches.c
 *
 * Created: 29.10.2021 22:20:51
 *  Author: pawel
 */ 
#include "limitSwitches.h"
#include <avr/io.h>

volatile enum LimitSwitchesState limitSwitchesState;

void limitSwitchesInit()
{
	EICRB |= 0b00001111;
	EIMSK |= 0b00110000;
	limitSwitchesState = LIMIT_SWITCHES_NO;
}

void procesLimitSwitchesUp()
{
	limitSwitchesState = LIMIT_SWITCHES_UP;
}

void procesLimitSwitchesDown()
{
	limitSwitchesState = LIMIT_SWITCHES_DOWN;
}

enum LimitSwitchesState getLimitSwitchesState()
{
	return limitSwitchesState;
}

void clearLimitSwitchesState()
{
	limitSwitchesState = LIMIT_SWITCHES_NO;
}