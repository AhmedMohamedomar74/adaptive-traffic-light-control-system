#include "KEY_PAD.h"
/*
 * KEY_PAD.c
 *
 *  Created on: Aug 27, 2023
 *      Author: ahmedomar
 */

static const u8 keybad_values[ROW_NUMBERS][COL_NUMBERS] = {{'7', '8', '9', '/'}, /* Row0 */
                                                           {'4', '5', '6', '*'}, /* Row1 */
                                                           {'1', '2', '3', '-'}, /* Row2 */
                                                           {'C', '0', '=', '+'} /* Row3 */};

/*Error_state keypad_init()
{
    Error_state local_err = Unvalid_Port;
    if ((PORTA != KEYPAD_PORT) && (PORTB != KEYPAD_PORT) && (PORTC != KEYPAD_PORT) && (PORTD != KEYPAD_PORT))
    {
        local_err = Unvalid_Port;
    }
    else
    {
        local_err = Valid_Port;
        GPIO_setPin_PUll_UP(KEYPAD_PORT, Col_0);
        GPIO_setPin_PUll_UP(KEYPAD_PORT, Row_1);
        GPIO_setPin_PUll_UP(KEYPAD_PORT, Row_2);
        GPIO_setPin_PUll_UP(KEYPAD_PORT, Row_3);
        GPIO_setPindDirection(KEYPAD_PORT, Row_0, Output_direction);
        GPIO_setPindDirection(KEYPAD_PORT, Col_1, Output_direction);
        GPIO_setPindDirection(KEYPAD_PORT, Col_2, Output_direction);
        GPIO_setPindDirection(KEYPAD_PORT, Col_3, Output_direction);
        GPIO_setPinValue(KEYPAD_PORT, Row_0, high_value);
        GPIO_setPinValue(KEYPAD_PORT, Col_1, high_value);
        GPIO_setPinValue(KEYPAD_PORT, Col_2, high_value);
        GPIO_setPinValue(KEYPAD_PORT, Col_3, high_value);
    }

    return local_err;
}

Error_state return_char_keypad(u8 *r_char)
{
    Error_state local_err;
    if (Valid_Port == keypad_init())
    {
        local_err = Unvalid_Port;
        *r_char = NOT_PRESSED;
        u8 loop_iterator_coulmn = 0;
        u8 loop_iterator_row = 0;
        for (loop_iterator_coulmn = 0 + COL_INIT; loop_iterator_coulmn < COL_END; loop_iterator_coulmn++)
        {
            GPIO_setPinValue(KEYPAD_PORT, loop_iterator_coulmn, low_value);
            for (loop_iterator_row = 0 + ROW_INIT; loop_iterator_row < ROW_END; loop_iterator_row++)
            {
                GPIO_getPIN(KEYPAD_PORT, loop_iterator_row, r_char); // the pointer points to ?
                if (*r_char == low_value)
                {
                    _delay_ms(50); // delay for bouncing
                    r_char = &keybad_values[loop_iterator_row - ROW_INIT][loop_iterator_coulmn - COL_INIT];
                }
                GPIO_getPIN(KEYPAD_PORT, loop_iterator_row, r_char);
                while (low_value == *r_char)
                {
                    GPIO_getPIN(KEYPAD_PORT, loop_iterator_row, r_char);
                }
                break;
            }
            GPIO_setPinValue(KEYPAD_PORT, loop_iterator_coulmn, high_value);
        }
    }
    else
    {
        local_err = keypad_init();
        r_char = NULL;
    }
    return local_err;
}*/

Error_state keypad_init(KEY_PAD_t *keypad_opj)
{
    Error_state local_err = Unvalid_Port;
    u8 loop_iterator_rows = 0;    // output
    u8 loop_iterator_columns = 0; // input
    //u8 local_val = (keypad_opj->keypad_row_pins[loop_iterator_rows].logic);
    if (NULL == keypad_opj)
    {
        local_err = NULL_POINTER;
    }
    else
    {
        for (loop_iterator_rows = 0; loop_iterator_rows < ROW_NUMBERS; loop_iterator_rows++)
        {
            local_err = GPIO_setPinValue((keypad_opj->keypad_row_pins[loop_iterator_rows].port), (keypad_opj->keypad_row_pins[loop_iterator_rows].pin), (keypad_opj->keypad_row_pins[loop_iterator_rows].logic));
        	//local_err = GPIO_setPinValue(PORTD,PIN0,Out_Port_direction);
        }
        for (loop_iterator_columns = 0; loop_iterator_columns < COL_NUMBERS; loop_iterator_columns++)
        {
            local_err = GPIO_setPin_PUll_UP((keypad_opj->key_pad_columns_pins[loop_iterator_columns].port), (keypad_opj->keypad_row_pins[loop_iterator_columns].pin));
        }
    }

    return local_err;
}

Error_state return_char_keypad(KEY_PAD_t *keypad_opj, u8 *r_char)
{
    u8 loop_iterator_rows = 0;    // output
    u8 loop_iterator_columns = 0; // input
    Error_state local_err = Unvalid_Port;
    u8 local_val = NOT_PRESSED;
    keypad_opj = &keypad_opj1;
    if ((NULL == keypad_opj) || (NULL == r_char))
    {
        local_err = NULL_POINTER;
    }
    else
    {

        for (loop_iterator_rows =0; loop_iterator_rows<ROW_NUMBERS;loop_iterator_rows++)
        {
            for (u8 i = 0; i < ROW_NUMBERS; i++)
            {
                local_err = GPIO_setPinValue((keypad_opj->keypad_row_pins[i].port),(keypad_opj->keypad_row_pins[i].pin),low_value);
            }
            GPIO_setPinValue((keypad_opj->keypad_row_pins[loop_iterator_rows].port),(keypad_opj->keypad_row_pins[loop_iterator_rows].pin),high_value);
            for(loop_iterator_columns =0;loop_iterator_columns<COL_NUMBERS;loop_iterator_columns++)
            {
                local_err = GPIO_getPIN((keypad_opj->key_pad_columns_pins[loop_iterator_columns].port),(keypad_opj->key_pad_columns_pins[loop_iterator_columns].pin),&local_val);
                if (high_value == local_val)
                {
                        *r_char = keybad_values[loop_iterator_rows][loop_iterator_columns];
                }
                
            }
        }
    }

    return local_err;
}

/*Error_state keypad_init(KEY_PAD_t keypad_opj)
{
    return Error_state();
}

Error_state return_char_keypad(KEY_PAD_t keypad_opj, u8 *r_char)
{
    return Error_state();0

}*/
