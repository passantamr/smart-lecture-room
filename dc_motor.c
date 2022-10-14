/*
 * dc_motor.c
 *	description: source file for ATmega32 dc motor driver
 *  Created on: Oct 4, 2022
 *      Author: Bassant Amr
 */
#include "dc_motor.h"
#include "common_macros.h"
#include "PWM_timer0.h" /*create PWM to control speed of dc motor*/
#include <avr/io.h>
/*
 * description: The Function responsible for setup the direction for the two
	motor pins through the GPIO driver
	no argument & no return
 * */
void DcMotor_Init(MOTOR_def *motor_ptr){
	/*two pins o/p pin*/
	GPIO_setupPinDirection(motor_ptr->DC_MOTOR_PORT,motor_ptr->DC_MOTOR_PIN1,PIN_OUTPUT);
	GPIO_setupPinDirection(motor_ptr->DC_MOTOR_PORT,motor_ptr->DC_MOTOR_PIN2,PIN_OUTPUT);
	/*stop motor*/
	GPIO_writePin(motor_ptr->DC_MOTOR_PORT,motor_ptr->DC_MOTOR_PIN1,LOGIC_LOW);
	GPIO_writePin(motor_ptr->DC_MOTOR_PORT,motor_ptr->DC_MOTOR_PIN2,LOGIC_LOW);
}
/*
 * description: select speed and state of motor
 * */
void DcMotor_Rotate(MOTOR_def *motor_ptr,DcMotor_State state,uint8 speed){
	switch (state){
	case stop:
		/*stop motor*/
		GPIO_writePin(motor_ptr->DC_MOTOR_PORT,motor_ptr->DC_MOTOR_PIN1,LOGIC_LOW);
		GPIO_writePin(motor_ptr->DC_MOTOR_PORT,motor_ptr->DC_MOTOR_PIN2,LOGIC_LOW);
		break;
	case CW:
		/*clock-wise motor*/
		GPIO_writePin(motor_ptr->DC_MOTOR_PORT,motor_ptr->DC_MOTOR_PIN1,LOGIC_HIGH);
		GPIO_writePin(motor_ptr->DC_MOTOR_PORT,motor_ptr->DC_MOTOR_PIN2,LOGIC_LOW);
		break;
	case A_CW:
		/*anti-clockwisw motor*/
		GPIO_writePin(motor_ptr->DC_MOTOR_PORT,motor_ptr->DC_MOTOR_PIN1,LOGIC_LOW);
		GPIO_writePin(motor_ptr->DC_MOTOR_PORT,motor_ptr->DC_MOTOR_PIN2,LOGIC_HIGH);
	}
	PWM_Timer0_Start(speed); /*set speed of motor*/
}
