/*
 * controller.h
 *
 * Created: 29.10.2021 23:11:48
 *  Author: pawel
 */ 


#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#define CONTROL_dt_inMS 10

void controllerP();
void controllerPI();
void setCounterGiven(int counter);
int getCounterGiven();





#endif /* CONTROLLER_H_ */