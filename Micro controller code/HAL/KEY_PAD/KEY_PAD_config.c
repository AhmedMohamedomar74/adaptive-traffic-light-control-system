/*
 * KEY_PAD_config.c
 *
 *  Created on: Aug 27, 2023
 *      Author: ahmedomar
 */

#include "KEY_PAD_config.h"
/*
u8 port;
    u8 pin;
    u8 direction;
    u8 logic;*/
/*
u8 loop_iterator_rows =0; //output
u8 loop_iterator_columns =0;//input*/

KEY_PAD_t keypad_opj1 =
    {
        
        .key_pad_columns_pins={
            {PORTD, PIN0, Output_direction, low_value},
            {PORTD, PIN1, Output_direction, low_value},
            {PORTD, PIN2, Output_direction, low_value},
            {PORTD, PIN3, Output_direction, low_value}
        },
        .keypad_row_pins={
            {PORTD, PIN4, Input_direction, high_value},
            {PORTD, PIN5, Input_direction, high_value},
            {PORTD, PIN6, Input_direction, high_value},
            {PORTD, PIN7, Input_direction, high_value}
        }
};

