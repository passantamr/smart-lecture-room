/*
 * PWM_timer0.c
 * description: source file of ATmega32 PWM with timer0
 *  Created on: Oct 4, 2022
 *      Author: BASSANT AMR
 *
 *       */
#include "PWM_timer0.h"
#include <avr/io.h>
#include "gpio.h"
#include "common_macros.h"
/*
 * initalize fast pwm mode with timer0
 * take one parameter duty cycle of pwm
 * and no return
 * */
void PWM_Timer0_Start(uint8 duty_cycle){
	TCCR0 = 0;/*initialze register*/
	/*selsect fast PWM*/
	SET_BIT(TCCR0,WGM01);
	SET_BIT(TCCR0,WGM00);
	/*non-inverting*/
	SET_BIT(TCCR0,COM01);
	/*f_cpu/8*/
	SET_BIT(TCCR0, CS01);
	TCNT0=0;/*start count from this value*/
	OCR0 = ((uint8)(((float)duty_cycle/100)*MAX_COUNT_VALUE)); /*calculate duty cycle and assign it to register*/
	GPIO_setupPinDirection(PWM_TIMER0_PORT,PWM_TIMER0_PIN,PIN_OUTPUT); /*PB3 o/p pin*/
}

