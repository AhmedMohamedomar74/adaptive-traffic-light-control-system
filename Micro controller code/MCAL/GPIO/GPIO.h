#ifndef _GPIO_H
#define _GPIO_H
// Includes
#include "../MCAL_REGs.h"

// defines
//@ref ports
#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3
//@ref pins
#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7
//@ref pin value
#define low_value 0
#define high_value 1
//@ref pin direction
#define Input_direction 0
#define Output_direction 1
//@ref pin state
#define state_low 0
#define state_high 1
//@ref port dicrection 
#define Input_Port_direction 0x00
#define Out_Port_direction 0xff
//@ref port value 
#define Low_Port_value 0
#define High_Port_value 1
// API

typedef struct GPIO
{
    u8 port;
    u8 pin;
    u8 direction;
    u8 logic;
}GPIO_pin_t;


Error_state GPIO_setPortValue(u8 portId, u8 value);
Error_state GPIO_setPinValue(u8 portId, u8 PinId, u8 value);
Error_state GPIO_setPortDirection(u8 portId, u8 PortDirectionValue);
Error_state GPIO_setPindDirection(u8 portId, u8 PinId, u8 PintDirectionValue);
Error_state GPIO_getPortValue(u8 portId,u8 * val);//return the input value by pointers
Error_state GPIO_getPIN (u8 portId,u8 PinId,u8 * val);//return the input value by pointer
Error_state GPIO_setPin_PUll_UP (u8 portId, u8 PinId);
#endif
