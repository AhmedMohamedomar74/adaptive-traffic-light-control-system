/*
 * SEVEN_SEG_Config.h
 *
 *  Created on: Aug 25, 2023
 *      Author: ahmedomar
 */

#ifndef SEVEN_SEG_CONFIG_H_
#define SEVEN_SEG_CONFIG_H_

#include "../../MCAL/GPIO/GPIO.h"

typedef struct 
{
    u8 port;
    u8 pin;
    u8 value;
}Enable_t;

//make a type for seven segment 
typedef struct 
{
    u8 SEVEN_SEG_ID;
    u8 PORT;
    u8 SEVEN_SEG_type;
    Enable_t SEVEN_SEG_Enable;
}SEVEN_SEG_t;

//make type-define to select the type of the seven_seg 
//comman anode - comman cathode
typedef enum
{
    comman_cathode,
    comman_anode,
}SEVEN_SEG_type_t;

//make array of seven segments with their specs
extern SEVEN_SEG_t seven_segments_arr [];
extern u8 legnth;
#endif /* SEVEN_SEG_CONFIG_H_ */
