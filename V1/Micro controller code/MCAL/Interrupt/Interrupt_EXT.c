#include "Interrupt_EXT.h"
#include "../GPIO/GPIO.h"

static void (*INT0_Interrupt_Handler)(void) = NULL;
static void (*INT1_Interrupt_Handler)(void) = NULL;
static void (*INT2_Interrupt_Handler)(void) = NULL;

static Error_state Set_INT0_Interrupt_Handler(void (*Interrupt_Handler)(void));
static Error_state Set_INT1_Interrupt_Handler(void (*Interrupt_Handler)(void));
static Error_state Set_INT2_Interrupt_Handler(void (*Interrupt_Handler)(void));

Interrupt_EXT_t *POINTER;

Error_state Test_Enable_init(Interrupt_EXT_t *POINTER)
{
    Error_state ret = Not_Working;
    if (NULL == POINTER)
    {
        ret = NULL_POINTER;
    }
    else
    {
        SREG_Ptr =SREG_Ptr | (1 << I);
        switch (POINTER->INT_NUM)
        {
        case INT0:
            GPIO_setPin_PUll_UP(PORTD, PIN2);
            /* GPIO_setPindDirection(PORTD,PIN2,Input_direction);
            GPIO_setPin_PUll_UP(PORTD,PIN2); */
            Set_Interrupt_Handler(POINTER);
            GICR =GICR | (1 << INT0_Enable);
            if (POINTER->INT_CONTROL == falling_edge)
            {
                MCUCR =MCUCR | INT0_falling_edge;
                ret = Valid_control;
            }
            else if (POINTER->INT_CONTROL == rising_edge)
            {
                MCUCR =MCUCR | INT0_rising_edge;
                ret = Valid_control;
            }
            else if (POINTER->INT_CONTROL == low_level)
            {
                MCUCR =MCUCR |INT0_low_level;
                ret = Valid_control;
            }
            else if (POINTER->INT_CONTROL == logical_change)
            {
                MCUCR =MCUCR | INT0_logical_change;
                ret = Valid_control;
            }
            else
            {
                ret = Unvalid_control;
            }
        case INT1:
            GPIO_setPin_PUll_UP(PORTD, PIN3);
            /* GPIO_setPindDirection(PORTD,PIN2,Input_direction);
            GPIO_setPin_PUll_UP(PORTD,PIN2); */
            Set_Interrupt_Handler(POINTER);
            GICR = GICR |(1 << INT1_Enable);
            if (POINTER->INT_CONTROL == falling_edge)
            {
                MCUCR =MCUCR |INT1_falling_edge;
                ret = Valid_control;
            }
            else if (POINTER->INT_CONTROL == rising_edge)
            {
                MCUCR =MCUCR | INT1_rising_edge;
                ret = Valid_control;
            }
            else if (POINTER->INT_CONTROL == low_level)
            {
                MCUCR =MCUCR | INT1_low_level;
                ret = Valid_control;
            }
            else if (POINTER->INT_CONTROL == logical_change)
            {
                MCUCR =MCUCR | INT1_logical_change;
                ret = Valid_control;
            }
            else
            {
                ret = Unvalid_control;
            }
            break;
        case INT2:
            GPIO_setPin_PUll_UP(PORTB, PIN2);
            /* GPIO_setPindDirection(PORTD,PIN2,Input_direction);
            GPIO_setPin_PUll_UP(PORTD,PIN2); */
            Set_Interrupt_Handler(POINTER);
            GICR =GICR | (1 << INT2_Enable);
            if (POINTER->INT_CONTROL == falling_edge)
            {
                MCUCR = MCUCR | INT2_falling_edge;
                ret = Valid_control;
            }
            else if (POINTER->INT_CONTROL == rising_edge)
            {
                MCUCR = MCUCR | INT2_rising_edge;
                ret = Valid_control;
            }
            else
            {
                ret = Unvalid_control;
            }
        default:
            ret = Unvalid_control;
            break;
        }
    }

    return ret;
}

Error_state Test_Enable_Deinit(Interrupt_EXT_t *POINTER)
{
    Error_state ret = Not_Working;
    if (NULL == POINTER)
    {
        ret = NULL_POINTER;
    }
    else
    {
        SREG_Ptr &= ~(1 << I);
        ret = Working;
        switch (POINTER->INT_NUM)
        {
        case INT0:
            // GPIO_setPin_PUll_UP(PORTD, PIN2);
            /* GPIO_setPindDirection(PORTD,PIN2,Input_direction);
            GPIO_setPin_PUll_UP(PORTD,PIN2); */
            // Set_Interrupt_Handler(POINTER);
            GICR &= ~(1 << INT0_Enable);
        case INT1:
            // GPIO_setPin_PUll_UP(PORTD, PIN3);
            /* GPIO_setPindDirection(PORTD,PIN2,Input_direction);
            GPIO_setPin_PUll_UP(PORTD,PIN2); */
            // Set_Interrupt_Handler(POINTER);
            GICR &= ~(1 << INT1_Enable);
            break;
        case INT2:
            // GPIO_setPin_PUll_UP(PORTB, PIN2);
            /* GPIO_setPindDirection(PORTD,PIN2,Input_direction);
            GPIO_setPin_PUll_UP(PORTD,PIN2); */
            // Set_Interrupt_Handler(POINTER);
            GICR &= ~(1 << INT2_Enable);
            break;
        default:
            ret = Unvalid_control;
            break;
        }
    }

    return ret;
}

static Error_state Set_INT0_Interrupt_Handler(void (*Interrupt_Handler)(void))
{
    Error_state ret = Not_Working;
    if (Interrupt_Handler)
    {
        ret = Working;
        INT0_Interrupt_Handler = Interrupt_Handler;
    }
    else
    {
        ret = NULL_POINTER;
    }

    return ret;
}

static Error_state Set_INT1_Interrupt_Handler(void (*Interrupt_Handler)(void))
{
    Error_state ret = Not_Working;
    if (Interrupt_Handler)
    {
        ret = Working;
        INT1_Interrupt_Handler = Interrupt_Handler;
    }
    else
    {
        ret = NULL_POINTER;
    }

    return ret;
}

static Error_state Set_INT2_Interrupt_Handler(void (*Interrupt_Handler)(void))
{
    Error_state ret = Not_Working;
    if (Interrupt_Handler)
    {
        ret = Working;
        INT2_Interrupt_Handler = Interrupt_Handler;
    }
    else
    {
        ret = NULL_POINTER;
    }

    return ret;
}

Error_state Set_Interrupt_Handler(Interrupt_EXT_t *POINTER)
{
    Error_state ret = Not_Working;
    if (NULL == POINTER)
    {
        ret = NULL_POINTER;
    }

    else
    {
        switch (POINTER->INT_NUM)
        {
        case INT0:
            ret = Set_INT0_Interrupt_Handler(POINTER->Call_back_fun);
            break;
        case INT1:
            ret = Set_INT1_Interrupt_Handler(POINTER->Call_back_fun);
            break;
        case INT2:
            ret = Set_INT2_Interrupt_Handler(POINTER->Call_back_fun);
            break;
        default:
            break;
        }
    }

    return ret;
}

void INT0_ISR()
{
    // Clear flag of the interrupt
    // GIFR &= ~(1 << INTF0);
    // Execute the code
    if (INT0_Interrupt_Handler)
    {
        INT0_Interrupt_Handler();
    }
}

void INT1_ISR()
{
    // Clear flag of the interrupt
    // GIFR &= ~(1 << INTF0);
    // Execute the code
    if (INT1_Interrupt_Handler)
    {
        INT1_Interrupt_Handler();
    }
}

void INT2_ISR()
{
    // Clear flag of the interrupt
    // GIFR &= ~(1 << INTF0);
    // Execute the code
    if (INT2_Interrupt_Handler)
    {
        INT2_Interrupt_Handler();
    }
}

void __vector_1(void) __attribute__((signal));
void __vector_1(void)
{
    INT0_ISR();
}

void __vector_2(void) __attribute__((signal));
void __vector_2(void)
{
    INT1_ISR();
}

void __vector_3(void) __attribute__((signal));
void __vector_3(void)
{
    INT2_ISR();
}
