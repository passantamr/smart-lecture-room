/*
 * ldr.c
 *
 *  Created on: Oct 5, 2022
 *      Author: HP
 */
#include "adc.h"
#include "ldr.h"
uint16 LDR_read(uint8 channel){
	 ADC_readChannel(channel);
	 return g_resultOfConversion;
}

