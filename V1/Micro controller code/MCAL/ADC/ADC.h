/*
 * ADC.h
 *
 *  Created on: Sep 19, 2023
 *      Author: ahmedomar
 */
#include "../MCAL_REGs.h"
#include "ADC_config.h"

extern ADC_Init_t ADC1;

void INIT_ADC (ADC_Init_t * PTR);
u16 ADC_Read_test ();