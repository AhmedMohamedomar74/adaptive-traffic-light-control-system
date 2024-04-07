/*
 * KEY_PAD_config.h
 *
 *  Created on: Aug 27, 2023
 *      Author: ahmedomar
 */

#ifndef KEY_PAD_CONFIG_H_
#define KEY_PAD_CONFIG_H_

#include "../../MCAL/GPIO/GPIO.h"

#define ROW_NUMBERS 4
#define COL_NUMBERS 4

typedef struct KEY_PAD
{
    GPIO_pin_t  keypad_row_pins[ROW_NUMBERS];
    GPIO_pin_t  key_pad_columns_pins[COL_NUMBERS];
}KEY_PAD_t;


extern KEY_PAD_t keypad_opj1;
#endif /* KEY_PAD_CONFIG_H_ */
