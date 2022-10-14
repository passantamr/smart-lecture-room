/*
 * adc.c
 *	Description: source file for the ATmega16 ADC driver
 *  Created on: Oct 1, 2022
 *      Author: BASSANT AMR
 */
#include "adc.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include <avr/io.h> /* To use the ADC Registers */
#include <avr/interrupt.h>
/*******************************************************************************
 *                          Global Variables                                   *
 *******************************************************************************/
uint16 g_resultOfConversion;
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */
void ADC_init(ADC_ConfigType * Config_Ptr){
	/* ADMUX Register Bits Description:
	 * REFS1:0 = 00 to choose to connect external reference voltage by input this voltage through AREF pin
	 * ADLAR   = 0 right adjusted
	 * MUX4:0  = 00000 to choose channel 0 as initialization
	*/
	ADMUX=0;
	ADMUX=ROR(Config_Ptr->ref_volt,2);/*select vref*/
	/* ADCSRA Register Bits Description:
	 * ADEN    = 1 Enable ADC
	 * ADIE    = 1 Enable ADC Interrupt
	 * ADATE   = 0 Disable Auto Trigger
	 * ADPS2:0 = 011 to choose ADC_Clock = F_CPU/8 = 1Mhz/8 = 125Khz --> ADC must operate in range 50-200Khz
	*/
	SET_BIT(ADCSRA,ADEN);/*enable adc*/
#ifndef ADC_INTERRUPT_ENABLE
	CLEAR_BIT(ADCSRA,ADIE);/*disable interrupt*/
#else
	SET_BIT(ADCSRA,ADIE); /*enable interrupt*/
#endif
	/*select Prescaler*/
	ADCSRA |= Config_Ptr->prescaler;
}
/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
void ADC_readChannel(uint8 a_channelNum){
	ADMUX = (ADMUX & 0xE0) | (a_channelNum & 0x07); /*select channel*/
	SET_BIT(ADCSRA,ADSC);/*start conversion*/
#ifndef ADC_INTERRUPT_ENABLE
	while(!GET_BIT(ADCSRA,ADIF));/*POLLING tech*/
	SET_BIT(ADCSRA,ADIF); /*clear flag bit*/
	g_resultOfConversion=ADC;
#endif
}
/*******************************************************************************
 *                          ISR's Definitions                                  *
 *******************************************************************************/
#ifdef ADC_INTERRUPT_ENABLE
ISR(ADC_vect){
	g_resultOfConversion=ADC;
}
#endif
