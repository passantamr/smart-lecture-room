/*
 * lcd.c
 * Description: Source file for the LCD driver
 *  Created on: Sep 30, 2022
 *      Author: BASSANT Amr
 */
#include "lcd.h"
#include "gpio.h"
#include "common_macros.h"/* For GET_BIT Macro */
#include <util/delay.h>/* For the delay functions */
#include <stdlib.h>
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Initialize the LCD:
 * 1. Setup the LCD pins directions by use the GPIO driver.
 * 2. Setup the LCD Data Mode 4-bits or 8-bits.
 */
void LCD_init(){
	/* Configure the direction for RS and E pins as output pins */
	GPIO_setupPinDirection(LCD_RS_PORT,LCD_RS_PIN,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_E_PORT,LCD_E_PIN,PIN_OUTPUT);
	_delay_ms(20);/* LCD Power ON delay always > 15ms */
#if(LCD_DATA_BIT_MODE==8)
	/* Configure the data port as output port */
	GPIO_setupPortDirection(LCD_DB8,PORT_OUTPUT);

	/* use 2-lines LCD + 8-bits Data Mode + 5*7 dot display Mode */
	LCD_sendCommand(LCD_TWOL_BIT8_MODE);
#elif(LCD_DATA_BIT_MODE==4)
	/* Configure 4 pins in the data port as output pins */
	GPIO_setupPinDirection(LCD_DB4_PORT,LCD_DB4_PIN,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DB5_PORT,LCD_DB5_PIN,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DB6_PORT,LCD_DB6_PIN,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DB7_PORT,LCD_DB7_PIN,PIN_OUTPUT);

	/* Send for 4 bit initialization of LCD  */
	LCD_sendCommand(LCD_TWOL_BIT4_MODE_INIT1);
	LCD_sendCommand(LCD_TWOL_BIT4_MODE_INIT2);

	/* use 2-lines LCD + 4-bits Data Mode + 5*7 dot display Mode */
	LCD_sendCommand(LCD_TWOL_BIT4_MODE);
#endif
	LCD_sendCommand(LCD_CURSOR_OFF); /*cursor off*/
	LCD_sendCommand(LCD_CLEAR);/*clear screen*/
}

/*
 * Description :
 * Send the required command to the screen
 */
void LCD_sendCommand(uint8 a_command){
	GPIO_writePin(LCD_RS_PORT,LCD_RS_PIN,LCD_RS_SEND_COMMAND);/* Instruction Mode RS=0 */
	_delay_ms(1);/*delay to set enable*/
	GPIO_writePin(LCD_E_PORT,LCD_E_PIN,LOGIC_HIGH); /*E = 1*/
	_delay_ms(1);/*delay to send command*/
#if(LCD_DATA_BIT_MODE==8)
	GPIO_writePort(LCD_DB8,a_command);/*8bit mode write command on port*/
#elif(LCD_DATA_BIT_MODE==4)
	/*send MSB first on 4bit mode*/
	GPIO_writePin(LCD_DB4_PORT,LCD_DB4_PIN,GET_BIT(a_command,PIN4_ID));
	GPIO_writePin(LCD_DB5_PORT,LCD_DB5_PIN,GET_BIT(a_command,PIN5_ID));
	GPIO_writePin(LCD_DB6_PORT,LCD_DB6_PIN,GET_BIT(a_command,PIN6_ID));
	GPIO_writePin(LCD_DB7_PORT,LCD_DB7_PIN,GET_BIT(a_command,PIN7_ID));
	_delay_ms(1);/*delay to clear enable*/
	GPIO_writePin(LCD_E_PORT,LCD_E_PIN,LOGIC_LOW);/*E = 0*/
	_delay_ms(1);/*delay to set enable */
	GPIO_writePin(LCD_E_PORT,LCD_E_PIN,LOGIC_HIGH);/*E = 1*/
	_delay_ms(1);/*delay to write command*/
	/*then send LSB */
	GPIO_writePin(LCD_DB4_PORT,LCD_DB4_PIN,GET_BIT(a_command,PIN0_ID));
	GPIO_writePin(LCD_DB5_PORT,LCD_DB5_PIN,GET_BIT(a_command,PIN1_ID));
	GPIO_writePin(LCD_DB6_PORT,LCD_DB6_PIN,GET_BIT(a_command,PIN2_ID));
	GPIO_writePin(LCD_DB7_PORT,LCD_DB7_PIN,GET_BIT(a_command,PIN3_ID));
#endif
	_delay_ms(1);/*delay to clear enable*/
	GPIO_writePin(LCD_E_PORT,LCD_E_PIN,LOGIC_LOW);/*E = 0*/
	_delay_ms(1);/*delay to ensure that command is sent*/
}
/*
 * Description :
 * Display the required character on the screen
 */
void LCD_displayCharacter(uint8 a_character){
	GPIO_writePin(LCD_RS_PORT,LCD_RS_PIN,LCD_RS_SEND_DATA);/* Instruction Mode RS=1 */
	_delay_ms(1);/*delay to set enable*/
	GPIO_writePin(LCD_E_PORT,LCD_E_PIN,LOGIC_HIGH); /*E = 1*/
	_delay_ms(1);/*delay to send data*/
#if(LCD_DATA_BIT_MODE==8)
		GPIO_writePort(LCD_DB8,a_character);/*8bit mode write data on port*/
#elif(LCD_DATA_BIT_MODE==4)
		/*send MSB first on 4bit mode*/
		GPIO_writePin(LCD_DB4_PORT,LCD_DB4_PIN,GET_BIT(a_character,PIN4_ID));
		GPIO_writePin(LCD_DB5_PORT,LCD_DB5_PIN,GET_BIT(a_character,PIN5_ID));
		GPIO_writePin(LCD_DB6_PORT,LCD_DB6_PIN,GET_BIT(a_character,PIN6_ID));
		GPIO_writePin(LCD_DB7_PORT,LCD_DB7_PIN,GET_BIT(a_character,PIN7_ID));
		_delay_ms(1);/*delay to clear enable*/
		GPIO_writePin(LCD_E_PORT,LCD_E_PIN,LOGIC_LOW);/*E = 0*/
		_delay_ms(1);/*delay to set enable */
		GPIO_writePin(LCD_E_PORT,LCD_E_PIN,LOGIC_HIGH);/*E = 1*/
		_delay_ms(1);/*delay to write data*/
		/*then send LSB */
		GPIO_writePin(LCD_DB4_PORT,LCD_DB4_PIN,GET_BIT(a_character,PIN0_ID));
		GPIO_writePin(LCD_DB5_PORT,LCD_DB5_PIN,GET_BIT(a_character,PIN1_ID));
		GPIO_writePin(LCD_DB6_PORT,LCD_DB6_PIN,GET_BIT(a_character,PIN2_ID));
		GPIO_writePin(LCD_DB7_PORT,LCD_DB7_PIN,GET_BIT(a_character,PIN3_ID));
#endif
		_delay_ms(1);/*delay to clear enable*/
		GPIO_writePin(LCD_E_PORT,LCD_E_PIN,LOGIC_LOW);/*E = 0*/
		_delay_ms(1);/*delay to ensure that data is sent*/
}
/*
 * Description :
 * Display the required string on the screen
 */
void LCD_displayString(const char *a_string){
	uint8 i = 0;
	for(i=0;a_string[i]!='\0';i++){
		LCD_displayCharacter(a_string[i]);
	}
}
/*
 * Description :
 * Send the clear screen command
 */
void LCD_clearScreen(){
	LCD_sendCommand(LCD_CLEAR);
}
/*
 * Description :
 * Display the required decimal value on the screen
 */
void LCD_intgerToString(int a_data){
	char buffer[NUM_COL]; /* String to hold the ascii result */
	itoa(a_data,buffer,10);/* Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
	/**************************another method***************/
	/******************************************************/
	/*while(a_data!=0){
		buffer[i]=(a_data%10)+48;
		i++;
		a_data/=10;
	}
	buffer[i]='\0';*/
	/******************************************************/
	LCD_displayString(buffer);/*Display the string*/
}
/*
 * Description :
 * Display the required string in a specified row and column index on the screen
 */
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str){
	LCD_moveCursor(row,col);/* go to to the required LCD position */
	LCD_displayString(Str);/*display string*/
}
/*
 * Description :
 * Move the cursor to a specified row and column index on the screen
 */
void LCD_moveCursor(uint8 row,uint8 col){
	uint8 address = LCD_CURSOR_LOCATION+col; /*address of bulk that cursor will stand*/
	/* Calculate the required address in the LCD DDRAM */
	switch(row){
	case ROW2:
		address +=0x40;
		break;
#if(NUM_LINES==4)
	case ROW3:
		address +=0x10;
		break;
	case ROW4:
		address +=0x50;
#endif
	}
	/* Move the LCD cursor to this specific address */
	LCD_sendCommand(address);
}



