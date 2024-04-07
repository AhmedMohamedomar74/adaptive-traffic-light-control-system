#include "SPI.h"
void SPI_Master_Init()
{
    /* Set MOSI and SCK output, all others input */
    DDRB_Ptr |= (1 << MOSI) | (1 << SCK) | (1 << SS);
    DDRB_Ptr &= ~(1 << MISO);
    PORTB_Ptr |= (1 << SS);
    /* Enable SPI, Master, set clock rate fck/16 */
    SPCR |= (1 << MSTR) | (1 << SPE) | (1 << SPR0);
    SPCR &= ~(1 << SPR1);
    /* Disable speed doubler */
    SPSR &= ~(1 << SPI2X);
}

void SPI_Slave_Init()
{
    /*Enable Slave*/
    SPCR &= ~(1 << MSTR);
    /*Enable SPI*/
    SPCR |= (1 << SPE);
    /*Set MOSI and SCK input*/
    DDRB_Ptr &= ~(1 << MOSI);
    DDRA_Ptr &= ~(1 << SCK);
    DDRB_Ptr &= ~(1 << SS);
    /*Set MISO output*/
    DDRB_Ptr |= (1 << MISO);
}

void SPI_MasterTransmit(char data)
{
    PORTB_Ptr &=~(1<<SS);
	SPDR = data;			/* Write data to SPI data register */
	while(!(SPSR & (1<<SPIF)));	/* Wait till transmission complete */
    PORTB_Ptr |=(1<<SS);
}

char SPI_SlaveReceive(void)
{
    /* Wait for reception complete */
    while (!(SPSR & (1 << SPIF)))
        ;
    /* Return data register */
    return SPDR;
}