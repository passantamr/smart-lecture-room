/*
 * adc_EX2.c
 * description: source file for LM35 sensor
 *  Created on: Oct 3, 2022
 *      Author: BASSANT AMR
 */
#include "lm35.h"

#include "adc.h"/*to convert sensor reading to digital*/

/*
 *discription: get temp by using sensor
 */
uint8 LM35_getTemp(){
	uint8 temp_value = 0;
	ADC_readChannel(CHANNEL);  /*convert sensor reading into digital*/
	/* Calculate the temperature from the ADC value*/
	temp_value = (uint8)(((float)g_resultOfConversion*MAX_SENSOR_TEMP*ADC_OPERATING_VOLT)/(ADC_MAX_DIGITAl*MAX_SENSOR_VOLT));
	return temp_value;
}


