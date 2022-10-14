/*
 * PWM_timer0.h
 *
 *  Created on: Oct 4, 2022
 *      Author: HP
 */

#ifndef PWM_TIMER0_H_
#define PWM_TIMER0_H_
#include "std_types.h"
#define MAX_COUNT_VALUE 0xff  /*max timer0 can reach in normal mode*/
/*static configration on port and pin*/
#define PWM_TIMER0_PORT PORTB_ID
#define PWM_TIMER0_PIN  PIN3_ID
/*
 * initalize fast pwm mode with timer0
 * take one parameter duty cycle of pwm
 * and no return
 * */
void PWM_Timer0_Start(uint8 duty_cycle);


#endif /* PWM_TIMER0_H_ */
