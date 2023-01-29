/*
 * led.h
 *
 * Created: 11.08.2021 18:31:42
 *  Author: pawel
 */ 


#ifndef LED_H_
#define LED_H_

void diodeInit();
void turnOnDiode();
void turnOffDiode();
void changeStateDiode();
unsigned char checkDiode();

#endif /* LED_H_ */