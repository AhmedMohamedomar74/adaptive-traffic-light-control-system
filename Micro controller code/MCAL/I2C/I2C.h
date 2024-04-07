/*
 * I2C.h
 *
 *  Created on: Sep 17, 2023
 *      Author: ahmedomar
 */

#ifndef _I2C_H
#define _I2C_H
#include "../MCAL_REGs.h"

/*TWSR*/
/**
 * Prescaller control
 */
typedef enum
{
    TWPS0 = 0,
    TWPS1,
} TWSR_pin_t;

/*TWCR*/
/**
 * Controll regiseter
 */
typedef enum
{
    TWIE = 0, /*TWI Interrupt Enable*/
    TWEN = 2, /*TWI Enable Bit*/
    TWWC,     /*TWI Write Collision Flag*/
    TWSTO,    /*TWI STOP Condition Bit*/
    TWSTA,    /*TWI START Condition Bit*/
    TWEA,     /*TWI Enable Acknowledge Bit*/
    TWINT,    /*TWI Interrupt Flag*/

} TWCR_pin_t;

typedef enum
{
    TWD0 = 0,
} TWDR_pin_t;

typedef enum
{
    MODE_CHECK = 0XF8,
    /**********MASETER********/
    I2C_START_MODE = 0x08,
    I2C_REPEATED_START_MODE = 0x10,
    /*********MASETER_Transmitter*********/
    MT_SLA_W_ACK_MODE = 0x18,
    MT_SLA_W_NACK_MODE = 0x20,
    MT_SLD_W_ACK_MODE = 0x28,
    MT_SLD_W_NACK_MODE = 0x30,
    /*********MASETER_Receiver*********/
    MR_SLA_R_ACK_MODE = 0x40,
    MR_SLA_R_NACK_MODE = 0x48,
    MR_SLD_W_ACK_MODE = 0x50,
    MR_SLD_W_NACK_MODE = 0x58,
    /**********SLAVE********/
    SL_STOP_CONDITION_MODE = 0xA0,
    /*********SLAVE_Transmitter*********/
    SLT_OWN_A_ACK_MODE = 0xA8,
    SLT_OWN_A_ACK_ARIBTRATION_MODE = 0xB0,
    SLT_DATA_ACK_MODE = 0xB8,
    /*********SLAVE_Receiver*********/
    SLR_OWN_A_ACK_MODE = 0x60,
    SLR_OWN_A_ACK_ARIBTRATION_MODE = 0x68,

} mode_t;

typedef enum
{
    /******unvalid data/address********/
    UNVALID_ADD,
    UNVALID_DATA,
    /******valid data/address********/
    I2C_OK,
    /**********MASETER********/
    START_CONDITION_FAIL,
    REPEATED_START_CONDITION_FAIL,
    /*********MASETER_Transmitter*********/
    MASTER_TRANSMIT_ADDREES_ACK,
    MASTER_TRANSMIT_ADDREES_NACK,
    MASTER_TRANSMIT_DATA_ACK,
    MASTER_TRANSMIT_DATA_NACK,
    /*********MASETER_Receiver*********/
    MASTER_RECIVE_ADDREES_ACK,
    MASTER_RECIVE_ADDREES_NACK,
    MASTER_RECIVE_DATA_ACK,
    MASTER_RECIVE_DATA_NACK,
    /**********SLAVE********/
    SLAVE_STOP_CONDITION_DETEC,
    /**********SLAVE_Transmitter********/
    SLAVE_TRANSMITTER_ADDRESS_ACK,
    /**********SLAVE_Receiver********/
    SLAVE_RECIVE_ADDRESS_ACK,
    SLAVE_RECIVE_DATA_ACK,
    /**********FAILED***********/
    MASTER_TRANSMIT_ADDREES_FAILED,
    MASTER_RECIEVE_ADDREES_FAILED,
    MASTER_TRANSMIT_DATA_FAILED,
    MASTER_RECIEVE_DATA_FAILED,
} I2C_Error_State;

/**
 * this function intilaize master and set the bit rate
 */

void MASTER_INIT(u8 M_ADD);
/**
 * this function intilaize slave and set the bit rate
 */
void SLAVE_INIT(u8 SL_ADD);
/**
 * this function make master send start condtion
 */
I2C_Error_State START_CONDTION_SEND();
/**
 * this function make master send repeated-start condtion
 */
I2C_Error_State REPEATED_START_CONDTION_SEND();
/**
 * this function make master send slave add for write operation (master in transmiiter mode)
 */
I2C_Error_State M_SEND_SLAVE_ADD_W(u8 SL_ADD);
/**
 * this function make master send slave add for read operation (master in transmiiter mode)
 */
I2C_Error_State M_SEND_SLAVE_ADD_R(u8 SL_ADD);
/**
 * this function make master send slave byte for write operation (master in transmiiter mode)
 */
I2C_Error_State M_SEND_SLAVE_DATA_W(u8 SEND_BYTE);
/**
 * this function make master recieve slave byte for write operation (master in transmiiter mode)
 */
I2C_Error_State M_SEND_SLAVE_DATA_R(u8 *RECIEVED_BYTE);
/**
 * this function make master send start condtion
 */
void STOP_CONDTION_SEND();
/****************slave_fun**********************/
I2C_Error_State Slave_Transmitt_data(u8 data);
#endif