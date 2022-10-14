/*
 * dc_motor.h
 * description: header file for the ATmega32 dc motor driver
 *  Created on: Oct 4, 2022
 *      Author: Bassant Amr
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_
#include "gpio.h"
#include "std_types.h"
/*define 3 state of motor*/
typedef enum{
	stop,CW,A_CW
}DcMotor_State;
/*static configration on port & 2 pins of motor*/
//#define DC_MOTOR_PORT PORTB_ID
//#define DC_MOTOR_PIN1 PIN0_ID
//#define DC_MOTOR_PIN2 PIN1_ID
/*structure to define port_num and pin num
 * */
typedef struct{
	uint8 DC_MOTOR_PORT:2; /*0 1 2 3*/
	uint8 DC_MOTOR_PIN1:3; /*0 1 2 3 4 5 6 7*/
	uint8 DC_MOTOR_PIN2:3; /*0 1 2 3 4 5 6 7*/
}MOTOR_def;
/*
 * description: The Function responsible for setup the direction for the two
	motor pins through the GPIO driver
 * */
void DcMotor_Init(MOTOR_def *motor_ptr);
/*
 * description: select speed and state of motor
 * */
void DcMotor_Rotate(MOTOR_def *motor_ptr,DcMotor_State state,uint8 speed);



#endif /* DC_MOTOR_H_ */
