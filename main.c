/*
 * main.c
 * description: file include main to start from
 *  Created on: Oct 4, 2022
 *      Author: BASSANT AMR
 */
#include "ldr.h"
#include "pir.h"
#include "gpio.h"
#include "relay.h"
#include <util/delay.h>
#include "lcd.h"
#include "adc.h"
#include "lm35.h"
#include "dc_motor.h"

int main(){
	/*initalize two PIR sensor one for enter*/
	PIR_init(PORTD_ID,PIN2_ID);
	PIR_init(PORTD_ID,PIN3_ID);
	RELAY_init(PORTD_ID,PIN4_ID); /*initalize relay to led on*/
	/*create structure of type ADC_ConfigType to select VREF & Prescaller*/
	ADC_ConfigType ADC_status={AVCC,PRE8};
	/*create structure of type MOTOR_def to select port num & two pins*/
	MOTOR_def MOTOR_config = {PORTB_ID,PIN0_ID,PIN1_ID};
	/*initilize LCD & dc motor & ADC*/
	LCD_init();
	DcMotor_Init(&MOTOR_config);
	ADC_init(&ADC_status);
	while(1){
		/*take reading of two PIR sensor*/
		PIR_numOfstudent(PORTD_ID,PIN2_ID,0);
		PIR_numOfstudent(PORTD_ID,PIN3_ID,1);
		uint8 temp = LM35_getTemp(); /*take temp sensor reading*/
		LCD_displayString("Fan is "); /*display on lcd*/
		/*if there is student led on else led off*/
		if(LDR_read(0)>=512 && g_numOfStudent){
			RELAY_write(PORTD_ID,PIN4_ID,LOGIC_HIGH);
		}else{
			RELAY_write(PORTD_ID,PIN4_ID,LOGIC_LOW);
		}
		/*check temp*/
		if(!g_numOfStudent) {/*check if there is no student*/
			LCD_displayString("OFF");
			DcMotor_Rotate(&MOTOR_config,stop,0);
		}
		else if(temp<30){ /*if reading is less than 30 */
			/*fan is off*/
			LCD_displayString("OFF");
			DcMotor_Rotate(&MOTOR_config,stop,0);
		}else if(temp>=30 && g_numOfStudent){/*if larger than 30*/
			/*fan is on*/
			LCD_displayString("ON ");
			/*select speed of dc motor depend on reading of temp sensor*/
			if(temp>=120){
				DcMotor_Rotate(&MOTOR_config,CW,100); /*max speed*/
			}else if(temp>=90){
				DcMotor_Rotate(&MOTOR_config,CW,75); /*75% of its max speed*/
			}else if(temp>=60){
				DcMotor_Rotate(&MOTOR_config,CW,50); /*50% of its max speed*/
			}else if(temp>=30){
				DcMotor_Rotate(&MOTOR_config,CW,25); /*25% of its max speed*/
			}
		}
		/*display temp*/
		LCD_moveCursor(ROW2,0); /*move cursor to row1*/
		LCD_displayString("Temp = "); /*first display*/
		/*display reading(num)*/
		if(temp >= 100)
		{
			LCD_intgerToString(temp);
		}
		else
		{
			LCD_intgerToString(temp);
			/* In case the digital value is two or one digits print space in the next digit place */
			LCD_displayCharacter(' ');
		}
		LCD_displayCharacter('c');
		LCD_moveCursor(ROW1,0);

		_delay_ms(500);
	}
}


