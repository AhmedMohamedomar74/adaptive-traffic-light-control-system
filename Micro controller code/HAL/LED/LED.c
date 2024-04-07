#include "LED.h"

/*
 * LED.c
 *
 *  Created on: Aug 22, 2023
 *      Author: ahmedomar
 */

Error_state LED_ON(LED_T * LED_PTR)
{
    // make local variables for error and pointer
    Error_state local_error = NULL_POINTER;
    // if the devloper in hal layer need to change the index
    // LED_T *LED_PTR = &Arr_Leds[1];
    // first check the null pointer
    if (NULL == LED_PTR)
    {
        local_error = NULL_POINTER;
    }
    else
    {
        // check led is valid
        for (u8 LoopIteratorOne = 0; LoopIteratorOne < NumberOfLeds; LoopIteratorOne++)
        {
            if (LoopIteratorOne == LED_PTR->LED_ID)
            {
                local_error = LED_VALID;
                break;
            }
            else
            {
                local_error = LED_NOT_VALID;
            }
        }
        if (LED_VALID == local_error)
        {
            local_error = Not_Working;
            LED_PTR->PIN_VAL = high_value;
            GPIO_setPindDirection(LED_PTR->PORT, LED_PTR->PIN, Output_direction);
            GPIO_setPinValue(LED_PTR->PORT, LED_PTR->PIN, LED_PTR->PIN_VAL);
            local_error = Working;
        }
        else
        {
        }
    }

    return local_error;
}

Error_state LED_OFF(LED_T * LED_PTR)
{
    // make local variables for error and pointer
    Error_state local_error = NULL_POINTER;
    // if the devloper in hal layer need to change the index
    // LED_T *LED_PTR = &Arr_Leds[1];
    // first check the null pointer
    if (NULL == LED_PTR)
    {
        local_error = NULL_POINTER;
    }
    else
    {
        // check led is valid                           //length
        for (u8 LoopIteratorOne = 0; LoopIteratorOne < NumberOfLeds; LoopIteratorOne++)
        {
            if (LoopIteratorOne == LED_PTR->LED_ID)
            {
                local_error = LED_VALID;
                break;
            }
            else
            {
                local_error = LED_NOT_VALID;
            }
        }
        if (LED_VALID == local_error)
        {
            local_error = Working;
            LED_PTR->PIN_VAL = low_value;
            GPIO_setPindDirection(LED_PTR->PORT, LED_PTR->PIN, Output_direction);
            GPIO_setPinValue(LED_PTR->PORT, LED_PTR->PIN, LED_PTR->PIN_VAL);
            local_error = Not_Working;
        }
        else
        {
        }
    }

    return local_error;
}

Error_state Toggel_LED(LED_T * LED_PTR)
{
	// make local variables for error and pointer
    Error_state local_error = NULL_POINTER;
    // if the devloper in hal layer need to change the index
    // LED_T *LED_PTR = &Arr_Leds[1];
    // first check the null pointer
    if (NULL == LED_PTR)
    {
        local_error = NULL_POINTER;
    }
    else
    {
        if (high_value == LED_PTR->PIN_VAL)
        {
            local_error = LED_OFF(LED_PTR);
        }
        else if (low_value == LED_PTR->PIN_VAL)
        {
            local_error = LED_ON(LED_PTR);
        }
        
    }
    

    return local_error;
}
