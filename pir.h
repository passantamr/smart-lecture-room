/*
 * pir.h
 *
 *  Created on: Oct 5, 2022
 *      Author: HP
 */

#ifndef PIR_H_
#define PIR_H_
#include "std_types.h"
#include "gpio.h"
extern uint16 g_numOfStudent;
void PIR_init(uint8 PIR_PORT,uint8 PIR_PIN);
void PIR_numOfstudent(uint8 PIR_PORT,uint8 PIR_PIN,uint8 sensor_ID);
#endif /* PIR_H_ */
