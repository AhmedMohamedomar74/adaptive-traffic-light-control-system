/*
 * ADC_config.h
 *
 *  Created on: Sep 19, 2023
 *      Author: ahmedomar
 */

typedef enum
{
    MUX0 = 0,
    MUX1,
    MUX2,
    MUX3,
    MUX4,
    ADLAR,
    REFS0,
    REFS1
} ADMUX_Pin_t;

typedef enum
{
    AREF = (0 << REFS0) | (0 << REFS1),
    AVCC = (1 << REFS0) | (0 << REFS1),
    Reserved = (0 << REFS0) | (1 << REFS1),
    Internal_2_56 = (1 << REFS0) | (1 << REFS1),
} voltage_reference_t;

typedef enum
{
    right_Adjustment = (0 << ADLAR),
    left_Adjustment = (1 << ADLAR),
} Data_Adjustment_t;

typedef enum
{
    CHANNEL_0 = (0 << MUX4) | (0 << MUX3) | (0 << MUX2) | (0 << MUX1) | (0 << MUX0),
    CHANNEL_1 = (0 << MUX4) | (0 << MUX3) | (0 << MUX2) | (0 << MUX1) | (1 << MUX0),
    CHANNEL_2 = (0 << MUX4) | (0 << MUX3) | (0 << MUX2) | (1 << MUX1) | (0 << MUX0),
    CHANNEL_3 = (0 << MUX4) | (0 << MUX3) | (0 << MUX2) | (1 << MUX1) | (1 << MUX0),
    CHANNEL_4 = (0 << MUX4) | (0 << MUX3) | (1 << MUX2) | (0 << MUX1) | (0 << MUX0),
    CHANNEL_5 = (0 << MUX4) | (0 << MUX3) | (1 << MUX2) | (0 << MUX1) | (1 << MUX0),
    CHANNEL_6 = (0 << MUX4) | (0 << MUX3) | (1 << MUX2) | (1 << MUX1) | (0 << MUX0),
    CHANNEL_7 = (0 << MUX4) | (0 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0),
} ADC_Channel_t;

typedef enum
{
    ADPS0 = 0,
    ADPS1,
    ADPS2,
    ADIE,
    ADIF,
    ADATE,
    ADSC,
    ADEN
} ADCSRA_Pin_t;

typedef enum
{
    Division_Factor_2 = (0 << ADPS2) | (0 << ADPS1) | (0 << ADPS0),
    //Division_Factor_2 = (0 << ADPS2) | (0 << ADPS1) | (1 << ADPS0),
    Division_Factor_4 = (0 << ADPS2) | (1 << ADPS1) | (0 << ADPS0),
    Division_Factor_8 = (0 << ADPS2) | (1 << ADPS1) | (1 << ADPS0),
    Division_Factor_16 = (1 << ADPS2) | (0 << ADPS1) | (0 << ADPS0),
    Division_Factor_32 = (1 << ADPS2) | (0 << ADPS1) | (1 << ADPS0),
    Division_Factor_64 = (1 << ADPS2) | (1 << ADPS1) | (0 << ADPS0),
    Division_Factor_128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0),
} ADC_Prescaler_t;

typedef struct ADC
{
    voltage_reference_t V_ref_select;
    Data_Adjustment_t Data_Adj;
    ADC_Channel_t channel_selcted;
    ADC_Prescaler_t Division_factor_selcted;
} ADC_Init_t;