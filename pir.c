/*
 * pir.c
 *
 *  Created on: Oct 5, 2022
 *      Author: HP
 */
#include "pir.h"
#include "gpio.h"

uint16 g_numOfStudent;
void PIR_init(uint8 PIR_PORT,uint8 PIR_PIN){
	GPIO_setupPinDirection(PIR_PORT,PIR_PIN,PIN_INPUT);
}
void PIR_numOfstudent(uint8 PIR_PORT,uint8 PIR_PIN,uint8 sensor_ID){
	if(GPIO_readPin(PIR_PORT,PIR_PIN)&& (sensor_ID==1) && g_numOfStudent==0 ){}
	else if(GPIO_readPin(PIR_PORT,PIR_PIN)&& (sensor_ID==0)){
		g_numOfStudent++;
	}else if(GPIO_readPin(PIR_PORT,PIR_PIN)&& (sensor_ID==1)){
		g_numOfStudent--;
	}
}


