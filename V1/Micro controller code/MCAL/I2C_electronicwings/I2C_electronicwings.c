#include "I2C_electronicwings.h"

void I2C_Init()
{
    // This numbers for 100K bit per second
    TWBR = 32;
    TWSR &=252;
}

u8 I2C_start(u8 slave_add)
{
    u8 status;
    TWCR |= (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);

    while (!(TWCR&(1<<TWINT))); /* Wait until I2C finish its current job */
    status = TWSR & 0xF8;
    if (0x08 != status)         /* Check weather START transmitted or not? */
    {
        return 0;
    }
        TWDR = slave_add;
        TWCR = (1<<TWINT) | (1<<TWEN);
        while (!(TWCR & (1<<TWINT))); /* Wait until I2C finish its current job */
        status = TWSR & 0xF8;
        if(status==0x18)		/* Check for SLA+W transmitted &ack received */
        return 1;			/* Return 1 to indicate ack received */
        if(status==0x20)		/* Check for SLA+W transmitted &nack received */
        return 2;			/* Return 2 to indicate nack received */
        else
        return 3;
    
}

u8 I2C_Rebeated_start(u8 slave_add)
{
    u8 status;
    TWCR |= (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);

    while (!(TWCR&(1<<TWINT))); /* Wait until I2C finish its current job */
    status = TWSR & 0xF8;
    if(status!=0x10)		/* Check for repeated start transmitted */
    return 0;               /* Return 0 for repeated start condition fail */
    TWDR = slave_add;
    TWCR = (1<<TWINT) | (1<<TWEN);
    while (!(TWCR & (1<<TWINT))); /* Wait until I2C finish its current job */
    status = TWSR & 0xF8;
    if(status==0x40)		/* Check for SLA+R transmitted &ack received */
    return 1;			/* Return 1 to indicate ack received */
    if(status==0x48)		/* Check for SLA+R transmitted &nack received */
    return 2;			/* Return 2 to indicate nack received */
    else
    return 3;
}

u8 I2C_MASTER_WRITE(u8 data)
{
   u8 status;
    TWDR = data;
    TWCR |=(1<<TWEN)|(1<<TWINT);
    while (!(TWCR&(1<<TWINT))); /* Wait until I2C finish its current job */
    status = TWSR & 0xF8; 
    if(status==0x28)		/* Check for data transmitted &ack received */
    return 0;			/* Return 0 to indicate ack received */
    if(status==0x30)		/* Check for data transmitted &nack received */
    return 1;			/* Return 1 to indicate nack received */
    else
    return 2;			/* Else return 2 for data transmission failure */

}

u8 I2C_Read_ACK()
{
    TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWEA); /* Enable TWI, generation of ack */
    while(!(TWCR&(1<<TWINT)));	/* Wait until TWI finish its current job */
    return TWDR;			/* Return received data */
}

u8 I2C_Read_Nack()		/* I2C read nack function */
{
    TWCR=(1<<TWEN)|(1<<TWINT);	/* Enable TWI and clear interrupt flag */
    while(!(TWCR&(1<<TWINT)));	/* Wait until TWI finish its current job */
    return TWDR;		/* Return received data */
}

void I2C_Slave_Init(u8 address)
{
    TWAR = address;
    TWCR |=(1 << TWEN) | (1 << TWINT) | (1 << TWEA);
}

u8 I2C_Slave_Lestin()
{
    while (1)
    {
        u8 status;
        while (!(TWCR&(1<<TWINT))); 
        status = 0xF8 & TWSR;
        if ((status == 0x60) || (status == 0x68) || (status == 0x80) || (status == 0x88))
        {
            // this means slave recieve with ack or nack
            // 0x80 and 0x86 for previous addressed 
            return 0;
        }
        if ((status == 0xA8) || (status == 0xB0))
        {
            // this means slave transmite with ack or nack
            return 1;
        }
        if(status==0x70||status==0x78)
        {
            // this means slave sense genral call
            return 2;
        }
        if ((status == 0xA0))
        {
            // A STOP condition or repeated START condition has been received while still addressed as slave
            return 3;
            break;
        }
        
        else
        {
            continue;
        }
        
    }
    
}

s8 I2C_Slave_Transmit(u8 data)
{
    u8 status;
    TWDR=data;	
    TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWEA);
    while(!(TWCR&(1<<TWINT)));
    status=TWSR & 0xF8;
    //still can not understand
    if(status==0xA0)		/* Check for STOP/REPEATED START received */
     {
	    TWCR|=(1<<TWINT);	/* Clear interrupt flag & return -1 */
	    return -1;
     }
    if(status==0xB8)		/* Check for data transmitted &ack received */
        return 0;			/* If yes then return 0 */
    if(status==0xC0)		/* Check for data transmitted &nack received */
     {
	    TWCR|=(1<<TWINT);	/* Clear interrupt flag & return -2 */
	return -2;
     }
    if(status==0xC8)		/* Last byte transmitted with ack received */
        return -3;			/* If yes then return -3 */
    else			/* else return -4 */
        return -4;
}

s8 I2C_Slave_Receive()
{
    s8 status;		/* Declare variable */
    TWCR=(1<<TWEN)|(1<<TWEA)|(1<<TWINT);/* Enable TWI & generation of ack */
    while(!(TWCR&(1<<TWINT)));	/* Wait until TWI finish its current job */
    status=TWSR&0xF8;		/* Read TWI status register */
    if(status==0x80||status==0x90)/* Check for data received &ack returned */
        return TWDR;		/* If yes then return received data */
    /* Check for data received, nack returned & switched to not addressed slave mode */
    if(status==0x88||status==0x98)
        return TWDR;		/* If yes then return received data */
    if(status==0xA0)		/* Check wether STOP/REPEATED START */
     {
        TWCR|=(1<<TWINT);	/* Clear interrupt flag & return -1 */
        return -1;
     }
    else
        return -2;	
}

void I2C_Stop()			/* I2C stop function */
{
    TWCR=(1<<TWSTO)|(1<<TWINT)|(1<<TWEN);/* Enable TWI, generate stop */
    while(TWCR&(1<<TWSTO));	/* Wait until stop condition execution */
}
