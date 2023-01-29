/*
 * led.c
 *
 * Created: 11.08.2021 18:34:15
 *  Author: pawel
 */ 
#include "led.h"
#include <avr/io.h>

void diodeInit()
{
	DDRH |= 1<<5;
}
void turnOnDiode()
{
	PORTH |= 1<<5;
}
void turnOffDiode()
{
	PORTH &= ~(1<<5);
}
unsigned char checkDiode()
{
	return PORTH & 1<<5; // 1<<5 = 0b00100000
}
void changeStateDiode()
{
	
	if(checkDiode())
	{
		turnOffDiode();
	}
	else{
		turnOnDiode();
	}
}


