#include "slave.h"

void Slave_init_func()
{
    SPI_Slave_Init();
}

u8 Slave_recieve()
{
    return SPI_SlaveReceive();
}
