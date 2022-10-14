/*
 * relay.h
 *
 *  Created on: Oct 5, 2022
 *      Author: HP
 */

#ifndef RELAY_H_
#define RELAY_H_

#include "std_types.h"

void RELAY_init(uint8 a_PORT,uint8 a_pin);
void RELAY_write(uint8 a_PORT,uint8 a_pin,uint8 state);

#endif /* RELAY_H_ */
