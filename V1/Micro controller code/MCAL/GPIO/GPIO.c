#include "GPIO.h"

Error_state GPIO_setPortValue(u8 portId, u8 value)
{
    Error_state local_err = Unvalid_Port;
    if ((PORTA != portId) && (PORTB != portId) && (PORTC != portId) && (PORTD != portId))
    {
        local_err = Unvalid_Port;
    }
    else
    {
        local_err = Valid_Port;
        switch (portId)
        {
        case PORTA:
            PORTA_Ptr = value;
            break;
        case PORTB:
            PORTB_Ptr = value;
            break;
        case PORTC:
            PORTC_Ptr = value;
            break;
        case PORTD:
            PORTD_Ptr = value;
            break;
        default:
            break;
        }
    }
    return local_err;
}

Error_state GPIO_setPinValue(u8 portId, u8 PinId, u8 value)
{
    Error_state local_err = Unvalid_Port;
    if ((PORTA != portId) && (PORTB != portId) && (PORTC != portId) && (PORTD != portId))
    {
        local_err = Unvalid_Port;
    }
    else
    {
        if (PinId > MAX_PIN)
        {
            local_err = Unvalid_pin;
        }
        else
        {
            local_err = Valid_pin;
            if (value == high_value)
            {
                switch (portId)
                {
                case PORTA:
                    GPIO_setPindDirection(portId, PinId, Output_direction);
                    PORTA_Ptr = PORTA_Ptr | (value << PinId);
                    break;
                case PORTB:
                    GPIO_setPindDirection(portId, PinId, Output_direction);
                    PORTB_Ptr = PORTB_Ptr | (value << PinId);
                    break;
                case PORTC:
                    GPIO_setPindDirection(portId, PinId, Output_direction);
                    PORTC_Ptr = PORTC_Ptr | (value << PinId);
                    break;
                case PORTD:
                    GPIO_setPindDirection(portId, PinId, Output_direction);
                    PORTD_Ptr = PORTD_Ptr | (value << PinId);
                    break;
                default:
                    GPIO_setPindDirection(portId, PinId, Output_direction);
                    PORTA_Ptr = PORTA_Ptr | 0x00;
                    PORTA_Ptr = PORTA_Ptr | 0x00;
                    PORTA_Ptr = PORTA_Ptr | 0x00;
                    PORTD_Ptr = PORTD_Ptr | 0x00;
                    break;
                }
            }
            else if (value == low_value)
            {
                switch (portId)
                {
                case PORTA:

                    PORTA_Ptr = PORTA_Ptr & ~(1 << PinId);
                    break;
                case PORTB:
                    PORTB_Ptr = PORTB_Ptr & ~(1 << PinId);
                    break;
                case PORTC:
                    PORTC_Ptr = PORTC_Ptr & ~(1 << PinId);
                    break;
                case PORTD:
                    PORTD_Ptr = PORTD_Ptr & ~(1 << PinId);
                    break;
                default:
                    PORTA_Ptr = PORTA_Ptr | 0x00;
                    PORTA_Ptr = PORTA_Ptr | 0x00;
                    PORTA_Ptr = PORTA_Ptr | 0x00;
                    PORTD_Ptr = PORTD_Ptr | 0x00;
                    break;
                }
            }
            else
            {
                local_err = Can_not_assign_to_pin;
            }
        }
    }
    return local_err;
}

Error_state GPIO_setPortDirection(u8 portId, u8 PortDirectionValue)
{
    Error_state local_err = Unvalid_Port;
    if ((PORTA != portId) && (PORTB != portId) && (PORTC != portId) && (PORTD != portId))
    {
        local_err = Unvalid_Port;
    }
    else
    {
        local_err = Valid_Port;
        switch (portId)
        {
        case PORTA:
            DDRA_Ptr = PortDirectionValue;
            break;
        case PORTB:
            DDRB_Ptr = PortDirectionValue;
            break;
        case PORTC:
            DDRC_Ptr = PortDirectionValue;
            break;
        case PORTD:
            DDRD_Ptr = PortDirectionValue;
            break;
        default:
            DDRA_Ptr |= (0x00);
            DDRB_Ptr |= (0x00);
            DDRC_Ptr |= (0x00);
            DDRD_Ptr |= (0x00);
            break;
        }
    }
    return local_err;
}

Error_state GPIO_setPindDirection(u8 portId, u8 PinId, u8 PintDirectionValue)
{
    Error_state local_err = Unvalid_Port;
    if ((PORTA != portId) && (PORTB != portId) && (PORTC != portId) && (PORTD != portId))
    {
        local_err = Unvalid_Port;
    }
    else
    {
        local_err = Valid_Port;
        if (PinId > MAX_PIN)
        {
            local_err = Unvalid_pin;
        }
        else
        {
            local_err = Valid_pin;
            if (Output_direction == PintDirectionValue)
            {
                switch (portId)
                {
                case PORTA:
                    DDRA_Ptr = DDRA_Ptr | (PintDirectionValue << PinId);
                    break;
                case PORTB:
                    DDRB_Ptr = DDRB_Ptr | (PintDirectionValue << PinId);
                    break;
                case PORTC:
                    DDRC_Ptr = DDRC_Ptr | (PintDirectionValue << PinId);
                    break;
                case PORTD:
                    DDRD_Ptr = DDRD_Ptr | (PintDirectionValue << PinId);
                    break;
                default:
                    DDRA_Ptr |= (0x00);
                    DDRB_Ptr |= (0x00);
                    DDRC_Ptr |= (0x00);
                    DDRD_Ptr |= (0x00);
                    break;
                }
            }
            else if (low_value == PintDirectionValue)
            {
                switch (portId)
                {
                case PORTA:

                    DDRA_Ptr = DDRA_Ptr & ~(PintDirectionValue << PinId);
                    break;
                case PORTB:
                    DDRB_Ptr = DDRB_Ptr & ~(PintDirectionValue << PinId);
                    break;
                case PORTC:
                    DDRC_Ptr = DDRC_Ptr & ~(PintDirectionValue << PinId);
                    break;
                case PORTD:
                    DDRD_Ptr = DDRD_Ptr & ~(PintDirectionValue << PinId);
                    break;
                default:
                    DDRA_Ptr |= (0x00);
                    DDRB_Ptr |= (0x00);
                    DDRC_Ptr |= (0x00);
                    DDRD_Ptr |= (0x00);
                    break;
                }
            }
            else
            {
                local_err = Can_not_assign_to_pin;
            }
        }
    }
    return local_err;
}

Error_state GPIO_getPortValue(u8 portId, u8 *val)
{
    Error_state local_err = Unvalid_Port;
    if ((PORTA != portId) && (PORTB != portId) && (PORTC != portId) && (PORTD != portId))
    {
        local_err = Unvalid_Port;
    }
    else
    {

        local_err = Valid_pin;
        switch (portId)
        {
        case PORTA:
            *val = PINA_Ptr;
            break;
        case PORTB:
            *val = PINB_Ptr;
            break;
        case PORTC:
            *val = PINC_Ptr;
            break;
        case PORTD:
            *val = PIND_Ptr;
            break;
        default:
            break;
        }
        if (NULL == val)
        {
            local_err = NULL_POINTER;
        }
    }

    return local_err;
}

Error_state GPIO_getPIN(u8 portId, u8 PinId, u8 *val)
{
    Error_state local_err = Unvalid_Port;
    if ((PORTA != portId) && (PORTB != portId) && (PORTC != portId) && (PORTD != portId))
    {
        local_err = Unvalid_Port;
    }
    else
    {
        if (PinId > MAX_PIN)
        {
            local_err = Unvalid_pin;
        }
        else
        {
            local_err = Valid_pin;
            switch (portId)
            {
            case PORTA:
                *val = (PINA_Ptr >> PinId) & 1;
                break;
            case PORTB:
                *val = (PINB_Ptr >> PinId) & 1;
                break;
            case PORTC:
                *val = (PINC_Ptr >> PinId) & 1;
                break;
            case PORTD:
                *val = (PIND_Ptr >> PinId) & 1;
                break;
            default:
                break;
            }
            if (NULL == val)
            {
                local_err = NULL_POINTER;
            }
        }
    }

    return local_err;
}

Error_state GPIO_setPin_PUll_UP(u8 portId, u8 PinId)
{
    Error_state local_err = Unvalid_Port;
    if ((PORTA != portId) && (PORTB != portId) && (PORTC != portId) && (PORTD != portId))
    {
        local_err = Unvalid_Port;
    }
    else
    {
        if (PinId > MAX_PIN)
        {
            local_err = Unvalid_pin;
        }
        else
        {
            local_err = Valid_pin;
            GPIO_setPindDirection(portId, PinId, Input_direction);
            GPIO_setPinValue(portId, PinId, high_value);
        }
    }

    return local_err;
}
