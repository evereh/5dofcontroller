/*
 * fifo.h
 *
 * Created: 31.10.2021 19:22:31
 *  Author: pawel
 */


#ifndef FIFO_H_
#define FIFO_H_

#define BUFFOR_SIZE 63
#define END_OF_TRANS (';')

typedef struct FIFO{
	char buffer[BUFFOR_SIZE + 1];
	unsigned int head;
	unsigned int tail;
	unsigned char wordsCounter;
}FIFO;

void FIFO_init(FIFO *fifo);
int FIFO_push(FIFO *fifo, char data);
int FIFO_pop(FIFO *fifo, char *data);
void FIFO_empty(FIFO *fifo);
unsigned char FIFO_isAnyWord(FIFO *fifo);
int FIFO_readSignedInteger(FIFO *fifo, int *data);
int FIFO_writeSignedInteger(FIFO *fifo, int data);
int FIFO_writeChar(FIFO *fifo, char data);

#endif /* FIFO_H_ */
