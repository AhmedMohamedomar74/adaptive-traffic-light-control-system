/*
 * LED_Config.h
 *
 *  Created on: Aug 22, 2023
 *      Author: ahmedomar
 */

#ifndef LED_CONFIG_H_
#define LED_CONFIG_H_
#include "../../MCAL/GPIO/GPIO.h"

#define LED_PORT0 PORTA
#define LED_PORT1 PORTB
#define LED_PORT2 PORTC
#define LED_PORT3 PORTD

#define LED_PIN0 PIN0
#define LED_PIN1 PIN1
#define LED_PIN2 PIN2
#define LED_PIN3 PIN3
#define LED_PIN4 PIN4
#define LED_PIN5 PIN5
#define LED_PIN6 PIN6
#define LED_PIN7 PIN7

typedef struct LED_Config
{
    u8 LED_ID;
    u8 PORT;
    u8 PIN;
    u8 PIN_VAL;
}LED_T;

extern u8 NumberOfLeds;
extern LED_T Arr_Leds[];

#endif /* LED_CONFIG_H_ */
