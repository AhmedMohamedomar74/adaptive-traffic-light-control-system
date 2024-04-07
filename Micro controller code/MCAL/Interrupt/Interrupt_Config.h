#ifndef _INTERRUPT_CONFIG_H
#define _INTERRUPT_CONFIG_H

#include "../MCAL_REGs.h"

typedef enum
{
    ISC00,
    ISC01,
    ISC10,
    ISC11,
} MCUCR_Pin_t;

typedef enum
{
    ISC2 = 6,
} MCUCSR_Pin_t;

typedef enum
{
    INT2_Enable = 5,
    INT0_Enable = 6,
    INT1_Enable = 7,
}GICR_Pin_t;

typedef enum
{
    INTF2 =5,
    INTF0,
    INTF1,
}GIFR_Pin_t;

typedef enum
{
    INT0,
    INT1,
    INT2,
} EXT_INT_Number;


typedef enum
{
    INT0_low_level = (0 << ISC01) | (0 << ISC00),
    INT0_logical_change = (0 << ISC01) | (1 << ISC00),
    INT0_falling_edge = (1 << ISC01) | (0 << ISC00),
    INT0_rising_edge = (1 << ISC01) | (1 << ISC00),
}INT0_Sense_Control;

typedef enum
{
    INT1_low_level = (0 << ISC11) | (0 << ISC10),
    INT1_logical_change = (0 << ISC11) | (1 << ISC10),
    INT1_falling_edge = (1 << ISC11) | (0 << ISC10),
    INT1_rising_edge = (1 << ISC11) | (1 << ISC10),
}INT1_Sense_Control;

typedef enum
{
    INT2_falling_edge = (0 << ISC2),
    INT2_rising_edge = (1 << ISC2),
}INT2_Sense_Control;

typedef enum
{
    
    low_level,
    logical_change,
    falling_edge,
    rising_edge,
    
} INT_Sense_Control;

typedef struct Interrupt_EXT
{
    void (*Call_back_fun) (void);
    EXT_INT_Number INT_NUM;
    INT_Sense_Control INT_CONTROL;
} Interrupt_EXT_t;
#endif