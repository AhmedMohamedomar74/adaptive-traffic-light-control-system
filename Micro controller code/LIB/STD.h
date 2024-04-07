#ifndef _STD_H_
#define _STD_H_
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short int u16;
typedef signed short int s16;
typedef unsigned long int u32;
typedef signed long int s32;
typedef  float float_32;
typedef double float_6f;
#include "stdio.h"
#include <stdlib.h>
#include <avr/delay.h>
typedef enum
{
    Valid_Port,
    Unvalid_Port,
    Valid_pin,
    Unvalid_pin,
    Can_not_assign_to_pin,
    Can_not_assign_to_Port,
	NULL_POINTER,
	LED_VALID,
	LED_NOT_VALID,
	Working,
	Not_Working,
    Can_not_assign_to_SS,
    SS_valid,
    SS_not_valid,
    can_not_assign_to_multiplix,
    keypad_valid,
    keypad_not_valid,
    unvalid_type_keypad,
    Unvalid_control,
    Valid_control,
}Error_state;


#endif
