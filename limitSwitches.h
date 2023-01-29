/*
 * limitSwitches.h
 *
 * Created: 29.10.2021 22:18:57
 *  Author: pawel
 */ 


#ifndef LIMITSWITCHES_H_
#define LIMITSWITCHES_H_

enum LimitSwitchesState {LIMIT_SWITCHES_NO=0, LIMIT_SWITCHES_UP=1, LIMIT_SWITCHES_DOWN=2};

void limitSwitchesInit();
void procesLimitSwitchesUp();
void procesLimitSwitchesDown();
void clearLimitSwitchesState();
enum LimitSwitchesState getLimitSwitchesState();

	




#endif /* LIMITSWITCHES_H_ */