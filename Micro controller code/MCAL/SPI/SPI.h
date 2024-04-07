/*
 * I2C.h
 *
 *  Created on: Oct 21, 2023
 *      Author: ahmedomar
*/
#ifndef _SPI_H
#define _SPI_H
#include "../MCAL_REGs.h"

typedef enum{
    SPR0 = 0,   //data rate control bit
    SPR1,       //data rate control bit
    CPHA,       //Clock Phase
    CPOL,       //Clock Polarity
    MSTR,       //Master/Slave Select
    DORD,       //Data Order
    SPE,        //SPI Enable
    SPIE,       //SPI Interrupt Enable
}SPCR_Pin_t;

typedef enum
{
    SPI2X = 0,  //Double SPI Speed Bit
    WCOL = 6,   //Write COLlision Flag
    SPIF,       //SPI Interrupt Flag
}SPSR_Pin_t;

typedef enum
{
    SS=4,   //Selave Select
    MOSI,
    MISO,
    SCK,
}SPI_PINs_t;

void SPI_Master_Init();
void SPI_Slave_Init();
void SPI_MasterTransmit(char cData);
char SPI_SlaveReceive(void);
#endif