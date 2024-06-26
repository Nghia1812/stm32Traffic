/*
 * timer.h
 *
 *  Created on: Mar 20, 2024
 *      Author: NGHIA
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

extern int timer0_flag;
extern int timer1_flag;
extern int timer2_flag;
extern int timer3_flag;
extern int timer4_flag;
extern int timer5_flag;
extern int timer6_flag;

void setTimer0(int duration);
void setTimer1(int duration);
void setTimer2(int duration);
void setTimer3(int duration);
void setTimer4(int duration);
void setTimer5(int duration);
void setTimer6(int duration);


void timer_run();

#endif /* INC_TIMER_H_ */
