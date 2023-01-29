/*
 * Plytkakomunikacja.c
 *
 * Created: 06.08.2021 16:19:52
 * Author : pawel
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "led.h"
#include "timer4AConfig.h"
#include "motor.h"
#include "encoder.h"
#include "limitSwitches.h"
#include "rs232.h"
#include "controller.h"

volatile unsigned char controlFlag;
volatile unsigned int counter = 0;

int main(void)
{
    /* Replace with your application code */
	
	diodeInit();
	//turnOnDiode();
	timer4AConfig();
	motorInit();
	encoderInit();
	limitSwitchesInit();
	rs232Init();
	controlFlag = 0;

	// 
	/*UCSR2A |= 0b00000010;
	UCSR2B |= 0b10011000;
	UCSR2C |= 0b00000110;
	DDRH |= 0b00000100;
	PORTH &= 0b11111011;
	UBRR2 = 16;*/
	
	//bezposrednio przed while w³aczam przerwania
	sei();


    while (1) 
    {
		interpretReadWords();
		if(getLimitSwitchesState()==LIMIT_SWITCHES_DOWN)
		{
			//turnOnDiode();
		}
		else if (getLimitSwitchesState()==LIMIT_SWITCHES_UP)
		{
			//turnOffDiode();
		}
		
		if(controlFlag)
		{
			//controllerP();
		}
    }
}


ISR(TIMER4_COMPA_vect)  //przerwanie od przepe³nienia licznika timer0
{
	if(waitOpenTimeMS(CONTROL_dt_inMS))
	{	
		//controlFlag = 1;
		controllerPI();
	}
	
	if(counter>=25)
	{
		counter = 0;
		writeChar('c');
		//writeInt(getEncoderCoutner());
		//writeInt(getCounterGiven());
		//writeInt(getCounterGiven());
		//writeChar('\n');
		
	}
	else
	{
		counter++;
	}

	
}

ISR(INT4_vect)
{
	procesLimitSwitchesDown();
	motorStop();
}

ISR(INT5_vect)
{
	procesLimitSwitchesUp();
	motorStop();
}

ISR(INT6_vect) //przerwamie zewenetrze od enkodera
{
	 procesEncoderSignalA();
}

ISR(INT7_vect) //przerwamie zewenetrze od enkodera
{
	 procesEncoderSignalB();
}

ISR(USART0_RX_vect)  //przerwanie od odbioru
{
	char c=UDR0;
	read(c);
	//UDR0 = c;
}

ISR(USART0_UDRE_vect)		//przerwanie po wyslaniu 1 UDR0
{
	write();
}

ISR(USART0_TX_vect)				//przerwanie od zakonczonej transmisji
{
	UCSR0B&=0b10111111;			//wy?aczenie przerwania od zakonczonej transmisji
}

ISR(USART2_RX_vect)  //przerwanie od odbioru
{
	char c = UDR2;
	//if(c=='c')
	//{
	//	PORTH |= 1<<5;
	//}
	
	
		writeChar('c');
	
	
	
	//UDR0 = c;
}
