/*
 * LED.h
 *
 *  Created on: Aug 22, 2023
 *      Author: ahmedomar
 */

#ifndef LED_H_
#define LED_H_

#include "LED_Config.h"


Error_state LED_ON(LED_T * LED_PTR);
Error_state LED_OFF(LED_T * LED_PTR);
Error_state Toggel_LED(LED_T * LED_PTR);

extern Error_state local_error;

#endif /* LED_H_ */
