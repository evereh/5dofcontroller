/*
 * encoder.c
 *
 * Created: 11.08.2021 21:38:21
 *  Author: pawel
 */ 
#include "encoder.h"
#include <avr/io.h>

volatile int encoderCounter;

void encoderInit()
{
	EICRB |= 0b01010000;
	EIMSK |= 0b11000000;
	encoderCounter = 0;
}
void procesEncoderSignalA()
{
	unsigned char En;
	En = (PINE & 0b11000000); //maska do wyluskania sygnalu z pinow enkodera
	switch (En)
	{
		case 0b01000000:
		{
			encoderCounter++;
		}
		break;
		case 0b10000000:
		{
			encoderCounter++;
		}
		break;
		case 0b11000000:
		{
			encoderCounter--;
		}
		break;
		case 0b00000000:
		{
			encoderCounter--;
		}
		break;
	}
}
void procesEncoderSignalB()
{
	unsigned char En;
	En = (PINE & 0b11000000); //maska do wyluskania sygnalu z pinow enkodera
	switch (En)
	{
		case 0b11000000:
		{
			encoderCounter++;
		}
		break;
		case 0b00000000:
		{
			encoderCounter++;
		}
		break;
		case 0b10000000:
		{
			encoderCounter--;
		}
		break;
		case 0b01000000:
		{
			encoderCounter--;
		}
		break;
	}
}

int getEncoderCoutner()
{
	return encoderCounter;
}
