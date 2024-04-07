/*
 * SEVEN_SEG_Config.c
 *
 *  Created on: Aug 25, 2023
 *      Author: ahmedomar
 */
#include "SEVEN_SEG_Config.h"
// if you need to add seven segment give it id first 
// give it im this enum ---> seven_segment_id_t
//then add the the specs of it in the array-->seven_segments 
typedef enum {
    seven_segment0,
    seven_segment1,
	number_of_seven_segments,
}seven_segment_id_t;

SEVEN_SEG_t seven_segments_arr [] = {
    {seven_segment0,PORTA,comman_cathode,{PORTB,PIN0,low_value}},{seven_segment1,PORTA,comman_cathode,{PORTB,PIN1,low_value}}};
u8 legnth= number_of_seven_segments;

