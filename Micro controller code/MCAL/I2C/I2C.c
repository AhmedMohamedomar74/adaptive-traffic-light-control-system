#include "I2C.h"

void MASTER_INIT(u8 SL_ADD)
{
    /*Set SCL frequency to 400kHz, with 8Mhz system frequency*/
    TWBR = 2;
    TWSR |= (0 << TWPS0) | (0 << TWPS1);
    /*SET MSTER ADDRESS*/
    if (SL_ADD != NULL)
    {
        TWAR = (SL_ADD << 1);
    }
    TWCR |= (1 << TWEA) | (1 << TWEN);
}

void SLAVE_INIT(u8 SL_ADD)
{
    /*SET SLAVE ADDRESS*/
    if (SL_ADD != NULL)
    {
        TWAR = (SL_ADD << 1);
    }
    TWCR |= (1 << TWEA) | (1 << TWEN) | (1 << TWINT);
}

I2C_Error_State START_CONDTION_SEND()
{

    I2C_Error_State local_err = I2C_OK;
    /* Send Start Condition */
    TWCR |= (1 << TWSTA);
    /* Clear Flag */
    TWCR |= (1 << TWINT);
    /* Polling on The Flag */
    while (((TWCR >> TWINT) & 1) == 0)
        ;
    u8 status = TWSR & MODE_CHECK;
    /* Check on ACK */
    if (status != I2C_START_MODE)
    {
        local_err = START_CONDITION_FAIL;
    }
    return local_err;
}

I2C_Error_State REPEATED_START_CONDTION_SEND()
{
    I2C_Error_State local_err = I2C_OK;
    /* Send Start Condition */
    TWCR |= (1 << TWSTA);
    /* Clear Flag */
    TWCR |= (1 << TWINT);
    /* Polling on The Flag */
    while (((TWCR >> TWINT) & 1) == 0)
        ;
    u8 status = TWSR & MODE_CHECK;
    /* Check on ACK */
    if (status != I2C_REPEATED_START_MODE)
    {
        local_err = REPEATED_START_CONDITION_FAIL;
    }
    return local_err;
}

I2C_Error_State M_SEND_SLAVE_ADD_W(u8 SL_ADD)
{
    I2C_Error_State local_err = I2C_OK;
    if (SL_ADD != NULL)
    {
        // the address is 7  bit
        TWDR = (SL_ADD << 1);
        // make the first bit is 0 (write operation)
        TWDR &= ~(1 << TWD0);
        // clear start bit
        TWCR &= ~(1 << TWSTA);
        /* Clear Flag */
        TWCR |= (1 << TWINT);
        /* Polling on The Flag */
        while (((TWCR >> TWINT) & 1) == 0)
            ;
        u8 status = TWSR & MODE_CHECK;
        /* Check on ACK */
        if (status == MT_SLA_W_ACK_MODE)
        {
            local_err = MASTER_TRANSMIT_ADDREES_ACK;
        }
        else if (status == MT_SLA_W_NACK_MODE)
        {
            local_err = MASTER_TRANSMIT_ADDREES_NACK;
        }
        else
        {
            local_err = MASTER_TRANSMIT_ADDREES_FAILED;
        }
    }
    else
    {
        local_err = UNVALID_ADD;
    }

    return local_err;
}

I2C_Error_State M_SEND_SLAVE_ADD_R(u8 SL_ADD)
{
    I2C_Error_State local_err = I2C_OK;
    if (SL_ADD != NULL)
    {
        // the address is 7  bit
        TWDR = (SL_ADD << 1);
        // make the first bit is 0 (write operation)
        TWDR &= ~(1 << TWD0);
        // clear start bit
        TWCR &= ~(1 << TWSTA);
        /* Clear Flag */
        TWCR |= (1 << TWINT);
        /* Polling on The Flag */
        while (((TWCR >> TWINT) & 1) == 0)
            ;
        u8 status = TWSR & MODE_CHECK;
        /* Check on ACK */
        if (status == MR_SLA_R_ACK_MODE)
        {
            local_err = MASTER_RECIVE_ADDREES_ACK;
        }
        else if (status == MR_SLA_R_NACK_MODE)
        {
            local_err = MASTER_RECIVE_ADDREES_NACK;
        }
        else
        {
            local_err = MASTER_RECIEVE_ADDREES_FAILED;
        }
    }
    else
    {
        local_err = UNVALID_ADD;
    }

    return local_err;
}

I2C_Error_State M_SEND_SLAVE_DATA_W(u8 SEND_BYTE)
{
    I2C_Error_State local_err = I2C_OK;
    // Write data
    TWDR = SEND_BYTE;
    /* Clear Flag */
    TWCR |= (1 << TWINT);
    /* Polling on The Flag */
    while (((TWCR >> TWINT) & 1) == 0)
        ;
    u8 status = TWSR & MODE_CHECK;
    /* Check on ACK */
    if (status == MT_SLD_W_ACK_MODE)
    {
        local_err = MASTER_TRANSMIT_DATA_ACK;
    }
    else if (status == MT_SLD_W_NACK_MODE)
    {
        local_err = MASTER_TRANSMIT_DATA_NACK;
    }
    else
    {
        local_err = MASTER_TRANSMIT_DATA_FAILED;
    }

    return local_err;
}

I2C_Error_State M_SEND_SLAVE_DATA_R(u8 *SEND_BYTE)
{
    I2C_Error_State local_err = I2C_OK;
    if (SEND_BYTE != NULL)
    {

        /* Clear Flag */
        TWCR |= (1 << TWINT);
        /* Polling on The Flag */
        while (((TWCR >> TWINT) & 1) == 0)
            ;
        u8 status = TWSR & MODE_CHECK;
        /* Check on ACK */
        if (status == MR_SLD_W_ACK_MODE)
        {
            *SEND_BYTE = TWDR;
            local_err = MASTER_RECIVE_DATA_ACK;
        }
        else if (status == MR_SLD_W_NACK_MODE)
        {
            local_err = MASTER_RECIVE_DATA_NACK;
        }
        else
        {
            local_err = MASTER_RECIEVE_DATA_FAILED;
        }
    }
    else
    {
        local_err = UNVALID_DATA;
    }

    return local_err;
}

void STOP_CONDTION_SEND()
{
    TWCR |= (1 << TWSTO);
    /* Clear Flag */
    TWCR |= (1 << TWINT);
}

I2C_Error_State Slave_Transmitt_data(u8 data)
{
    I2C_Error_State local_err = I2C_OK;
    TWDR = data;
    TWCR |= (1 << TWEA) | (1 << TWEN) | (1 << TWINT);
    /* Polling on The Flag */
    while (((TWCR >> TWINT) & 1) == 0)
        ;
    u8 status = TWSR & MODE_CHECK;
    if (SL_STOP_CONDITION_MODE == status)
    {
        TWCR|=(1<<TWINT);
        local_err = SLAVE_STOP_CONDITION_DETEC;
    }
    /*else if (SLR_DATA_ACK_MODE == status)
    {
        local_err = SLAVE_RECIVE_DATA_ACK;
    }*/
    
    return local_err;
}
