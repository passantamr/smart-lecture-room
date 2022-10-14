/*
 * adc.h
 * Description: header file for the ATmega16 ADC driver
 *  Created on: Oct 1, 2022
 *     Author: BASSANT AMR
 */


#ifndef ADC_H_
#define ADC_H_
#include "std_types.h"
#include "gpio.h"

extern uint16 g_resultOfConversion;
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define NUM_OF_BITS 10
#define ADC_MAX_DIGITAl 1023
#define ADC_OPERATING_VOLT 5

#undef ADC_INTERRUPT_ENABLE /*to enable adc with interrupt*/
#define NUM_CHANNELS 8 /*channel numbers*/
#define ADC_PORT PORTA_ID  /*PORT of channels*/
/*pins of each channel*/
#define CHANNEL1 PIN0_ID
#define CHANNEL2 PIN1_ID
#define CHANNEL3 PIN2_ID
#define CHANNEL4 PIN3_ID
#define CHANNEL5 PIN4_ID
#define CHANNEL6 PIN5_ID
#define CHANNEL7 PIN6_ID
#define CHANNEL8 PIN7_ID


/*vref of adc*/
typedef enum{
	AREF,AVCC,INTERNAL=3
}ADC_ReferenceVolatge;

/*define prescaler*/
typedef enum{
	PRESCALER2,PRE2,PRE4,PRE8,PRE16,PRE32,PRE64,PRE128
}ADC_Prescaler;
/*
 * type : structure
 * numOfMemebers : two
 * first member to select vref (AVCC - AREF - INTERNEL)
 * second memeber to set prescaler (f/2 - f/4 - f/8 - f/16 - f/32 - f/64 - f/128)*/
typedef struct{
 ADC_ReferenceVolatge ref_volt;
 ADC_Prescaler prescaler;
}ADC_ConfigType;
/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */

void ADC_init(ADC_ConfigType * Config_Ptr);
/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */

void ADC_readChannel(uint8 a_channelNum);

#endif /* ADC_H_ */
