/*
 * relay.c
 *
 *  Created on: Oct 5, 2022
 *      Author: HP
 */
#include "gpio.h"
#include "relay.h"

void RELAY_init(uint8 a_PORT,uint8 a_pin){
	GPIO_setupPinDirection(a_PORT,a_pin,PIN_OUTPUT);
}
void RELAY_write(uint8 a_PORT,uint8 a_pin,uint8 state){
	GPIO_writePin(a_PORT,a_pin,state);
}
