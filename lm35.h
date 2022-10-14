/*
 * adc_EX2.h
 *	description: header file of LM35
 *  Created on: Oct 3, 2022
 *      Author: BASSANT AMR
 */

#ifndef LM35_H_
#define LM35_H_
#include "std_types.h"
/*******************************************
 *              defintions
 *******************************************
 ********************************************/
#define MAX_SENSOR_VOLT 1.5
#define MAX_SENSOR_TEMP 150
#define CHANNEL 2 /*static configration on pin used of Analog pins*/

/*
 * Description :
 * Function responsible for calculate the temperature from the ADC digital value.
 */
uint8 LM35_getTemp(void);


#endif /* LM35_H_ */
