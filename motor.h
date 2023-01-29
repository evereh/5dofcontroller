/*
 * motor.h
 *
 * Created: 11.08.2021 20:20:13
 *  Author: pawel
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

enum MotorState {MOTOR_STOP=0, MOTOR_RIGHT=1, MOTOR_LEFT=2, MOTOR_RIGHT_PWM=3, MOTOR_LEFT_PWM=4};

void motorInit();
void motorRight();
void motorLeft();
void motorStop();
void motorPWM(int pwm);
enum MotorState getMotorState();





#endif /* MOTOR_H_ */