/*
 * fifo.c
 *
 * Created: 31.10.2021 19:23:04
 *  Author: pawel
 */

#include "fifo.h"

void FIFO_init(FIFO *fifo)
{
	fifo->head = 0;
	fifo->tail = 0;
	fifo->wordsCounter = 0;
}

int FIFO_push(FIFO *fifo, char data)
{
	if ((fifo->tail - fifo->head) == 1 || (fifo->head - fifo->tail) == BUFFOR_SIZE)
	{
		return -1;
	}
	fifo->buffer[fifo->head] = data;
	fifo->head = (fifo->head + 1) & BUFFOR_SIZE;

	if(data == END_OF_TRANS)
	{
		fifo->wordsCounter++;
	}

	return 1;
}

int FIFO_pop(FIFO *fifo, char *data)
{
	if (fifo->head != fifo->tail)
	{
		*data = fifo->buffer[fifo->tail];
		fifo->tail = (fifo->tail + 1) & BUFFOR_SIZE;

		if((*data) == END_OF_TRANS)
        {
            fifo->wordsCounter--;
        }
		return 1;
	}
	return -1;
}

void FIFO_empty(FIFO *fifo)
{
	fifo->head = fifo->tail;
	fifo->wordsCounter = 0;
}

unsigned char FIFO_isAnyWord(FIFO *fifo)
{
    return fifo->wordsCounter;
}

int FIFO_readSignedInteger(FIFO *fifo, int *data)
{
    char c;
	int direction = 0;
	int result=0;
	char errorFlag = 0;

	FIFO_pop(fifo,&c);

	if(c == '+')
	{
		direction = 1;
	}
	else if(c == '-')
	{
		direction = -1;
	}

	errorFlag = FIFO_pop(fifo,&c);


	while(c != END_OF_TRANS && errorFlag != -1)
	{
		if(c >= '0' && c <= '9')
		{
			result*=10;
			result += (c - '0');
		}
		errorFlag = FIFO_pop(fifo,&c);
	}

	if(errorFlag == -1) return -1;

	result*=direction;
	*data = result;
	return 1;
}

int FIFO_writeSignedInteger(FIFO *fifo, int data)
{
    if(data>=0)
	{
		 FIFO_push(fifo,'+');
	}
	else
	{
		FIFO_push(fifo,'-');
		data *= -1;
	}

	unsigned char result[5];

	for (unsigned char i = 0; i < 5; i++)
	{
		result[i] = (data % 10) + '0';
		data /= 10;
	}

	for (unsigned char i = 5; i>0 ; i--)
	{
		FIFO_push(fifo,result[i-1]);
	}

	FIFO_push(fifo,';');
	return 1;
}

int FIFO_writeChar(FIFO *fifo, char data)
{
    FIFO_push(fifo,data);
	FIFO_push(fifo,';');
	return 1;
}
