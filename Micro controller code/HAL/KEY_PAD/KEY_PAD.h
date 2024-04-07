/*
 * KEY_PAD.h
 *
 *  Created on: Aug 27, 2023
 *      Author: ahmedomar
 */

#ifndef KEY_PAD_H_
#define KEY_PAD_H_

#include "KEY_PAD_config.h"

#define NOT_PRESSED 0XFF

Error_state keypad_init (KEY_PAD_t *keypad_opj);
Error_state return_char_keypad(KEY_PAD_t  *keypad_opj,u8 *r_char);
#endif /* KEY_PAD_H_ */
