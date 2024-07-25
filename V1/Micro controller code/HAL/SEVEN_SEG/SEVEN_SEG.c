/*
 * SEVEN_SEG.c
 *
 *  Created on: Aug 25, 2023
 *      Author: ahmedomar
 */
#include "SEVEN_SEG.h"
SEVEN_SEG_t *Glopal_ptr = NULL;
// Array of values for Common Anode seven-segment display
const u8 CA_SevenSegmentValues[] = {
    0xC0, // 0
    0xF9, // 1
    0xA4, // 2
    0xB0, // 3
    0x99, // 4
    0x92, // 5
    0x82, // 6
    0xF8, // 7
    0x80, // 8
    0x90, // 9
};

// Array of values for Common Cathode seven-segment display
const u8 CC_SevenSegmentValues[] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F  // 9
};
Error_state Seven_Segment(u8 numebr, u8 seven_seg_id)
{
    Error_state local_err = Unvalid_Port;
    Glopal_ptr = NULL;
    for (u8 LoopIteratorOne = 0; LoopIteratorOne < legnth; LoopIteratorOne++)
    {
        if (LoopIteratorOne == seven_seg_id)
        {
        	local_err = SS_valid;
            break;
        }
        else
        {
        	local_err = SS_not_valid;
        }
    }
    Glopal_ptr = &seven_segments_arr[seven_seg_id];
    if (Glopal_ptr == NULL)
    {
        local_err = NULL_POINTER;
    }
    else
    {
        if (numebr > 9)
        {
            local_err = Can_not_assign_to_SS;
        }
        else
        {
            if ((PORTA != Glopal_ptr->PORT) && (PORTB != Glopal_ptr->PORT) && (PORTC != Glopal_ptr->PORT) && (PORTD != Glopal_ptr->PORT))
            {
                local_err = Unvalid_Port;
            }
            else
            {
                for (u8 LoopIteratorOne = 0; LoopIteratorOne < legnth; LoopIteratorOne++)
                {
                    if (LoopIteratorOne == Glopal_ptr->SEVEN_SEG_ID)
                    {
                        local_err = SS_valid;
                        break;
                    }
                    else
                    {
                        local_err = SS_not_valid;
                    }
                }
                if (SS_valid == local_err)
                {
                    if (comman_anode == Glopal_ptr->SEVEN_SEG_type)
                    {
                        GPIO_setPindDirection(Glopal_ptr->SEVEN_SEG_Enable.port,Glopal_ptr->SEVEN_SEG_Enable.pin,Out_Port_direction);
                        GPIO_setPinValue(Glopal_ptr->SEVEN_SEG_Enable.port,Glopal_ptr->SEVEN_SEG_Enable.pin,Glopal_ptr->SEVEN_SEG_Enable.value);
                        GPIO_setPortDirection(Glopal_ptr->PORT, 0xff);
                        GPIO_setPortValue(Glopal_ptr->PORT, CA_SevenSegmentValues[numebr]);
                    }
                    else if (comman_cathode == Glopal_ptr->SEVEN_SEG_type)
                    {
                        GPIO_setPindDirection(Glopal_ptr->SEVEN_SEG_Enable.port,Glopal_ptr->SEVEN_SEG_Enable.pin,Out_Port_direction);
                        GPIO_setPinValue(Glopal_ptr->SEVEN_SEG_Enable.port,Glopal_ptr->SEVEN_SEG_Enable.pin,Glopal_ptr->SEVEN_SEG_Enable.value);
                        GPIO_setPortDirection(Glopal_ptr->PORT, 0xff);
                        GPIO_setPortValue(Glopal_ptr->PORT, CC_SevenSegmentValues[numebr]);
                    }
                }
                else
                {
                }
            }
        }
    }

    return local_err;
}

Error_state Seven_Segment_Mul(u8 number)
{
    Error_state local_err = Unvalid_Port;
    if (number > 99)
    {
        local_err = can_not_assign_to_multiplix;
    }
    else
    {
        local_err = Valid_Port;
        u8 i=0;
    	while (i<50)
        {
            Seven_Segment(number/10,0);
            i++;
        }
        
        _delay_ms(30);
        GPIO_setPinValue(Glopal_ptr->SEVEN_SEG_Enable.port,Glopal_ptr->SEVEN_SEG_Enable.pin,!(Glopal_ptr->SEVEN_SEG_Enable.value));
        i =0;
        while (i < 150)
        {
            Seven_Segment(number%10,1);
            i++;
        }
        i=0;
        GPIO_setPinValue(Glopal_ptr->SEVEN_SEG_Enable.port,Glopal_ptr->SEVEN_SEG_Enable.pin,!(Glopal_ptr->SEVEN_SEG_Enable.value));


    }
    
    return local_err;   
}
