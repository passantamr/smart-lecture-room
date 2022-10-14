/******************************************
 * lcd.h
 * Description: Header file for the LCD driver
 *  Created on: Sep 30, 2022
 *      Author: BASSANT AMR
 ******************************************/

#ifndef LCD_H_
#define LCD_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define LCD_DATA_BIT_MODE 8  /*mode lcd*/
#define NUM_LINES 2  /*num of rows of lcd*/
#define NUM_COL 16  /*num of colums*/
/*defines number of rows */
#define ROW1 0
#define ROW2 1
#if(NUM_LINES==4)
#define ROW3 2
#define ROW4 3
#endif

#define LCD_RS_PORT PORTD_ID /*define port of RS*/
#define LCD_RS_PIN PIN0_ID /*define pin of RS*/
#define LCD_RS_SEND_COMMAND LOGIC_LOW /*define logic to send command*/
#define LCD_RS_SEND_DATA LOGIC_HIGH /*define logic to send data*/

#define LCD_E_PORT PORTD_ID /*define port of Enable*/
#define LCD_E_PIN  PIN1_ID /*define pin of Enable*/

#if(LCD_DATA_BIT_MODE==8)
	#define LCD_DB8 PORTC_ID  /*port of 8 bit data bus*/
#elif(LCD_DATA_BIT_MODE==4)
/*define port for each pin of 4 bit data bus*/
	#define LCD_DB4_PORT PORTA_ID
	#define LCD_DB5_PORT PORTA_ID
	#define LCD_DB6_PORT PORTA_ID
	#define LCD_DB7_PORT PORTA_ID
/*define pins for each pin of 4 bit data bus*/
	#define LCD_DB4_PIN PIN3_ID
	#define LCD_DB5_PIN PIN4_ID
	#define LCD_DB6_PIN PIN5_ID
	#define LCD_DB7_PIN PIN6_ID
#endif
/* LCD Commands */
#define LCD_TWOL_BIT8_MODE 0x38
#define LCD_TWOL_BIT4_MODE 0x28
#define LCD_CURSOR_OFF 0x0c
#define LCD_CLEAR 0x01
#define LCD_TWOL_BIT4_MODE_INIT1   0x33
#define LCD_TWOL_BIT4_MODE_INIT2   0x32
#define LCD_CURSOR_LOCATION 0x80  /*set 7-bit to move cursor to spesific address*/
/*********************************/
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Initialize the LCD:
 * 1. Setup the LCD pins directions by use the GPIO driver.
 * 2. Setup the LCD Data Mode 4-bits or 8-bits.
 */
void LCD_init();
/*
 * Description :
 * Send the required command to the screen
 */
void LCD_sendCommand(uint8 a_command);
/*
 * Description :
 * Display the required character on the screen
 */
void LCD_displayCharacter(uint8 data);

/*
 * Description :
 * Display the required string on the screen
 */
void LCD_displayString(const char *Str);

/*
 * Description :
 * Move the cursor to a specified row and column index on the screen
 */
void LCD_moveCursor(uint8 row,uint8 col);

/*
 * Description :
 * Display the required string in a specified row and column index on the screen
 */
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str);

/*
 * Description :
 * Display the required decimal value on the screen
 */
void LCD_intgerToString(int data);

/*
 * Description :
 * Send the clear screen command
 */
void LCD_clearScreen(void);

#endif /* LCD_H_ */
