#include "master.h"
void master_init_fun()
{
    SPI_Master_Init();
}

void master_transmitt(u8 Transnmitte_byte)
{
    SPI_MasterTransmit(Transnmitte_byte);
}
