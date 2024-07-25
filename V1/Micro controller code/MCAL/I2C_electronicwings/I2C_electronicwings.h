#ifndef _I2C_ELECTRONICWINGS_H
#define _I2C_ELECTRONICWINGS_H

#include "../MCAL_REGs.h"

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

void I2C_Init();
u8 I2C_start(u8 slave_add);
u8 I2C_Rebeated_start(u8 slave_add);
u8 I2C_MASTER_WRITE (u8 data);
u8 I2C_Read_ACK();
u8 I2C_Read_Nack();
void I2C_Slave_Init(u8 address);
u8 I2C_Slave_Lestin (); 
s8 I2C_Slave_Transmit(u8 data);
s8 I2C_Slave_Receive();
void I2C_Stop()	;
#endif