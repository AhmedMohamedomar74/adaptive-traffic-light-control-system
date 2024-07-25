#include "../MCAL_REGs.h"

/*UCSRB*/
/**
 * Controll regiseter
 */


typedef enum
{
    TXB8 = 0,   /*Transmit Data Bit 8*/
    RXB8,       /*Receive Data Bit 8*/
    UCSZ2,      /*Character Size*/
    TXEN,       /*Transmitter Enable*/
    RXEN,       /*Receiver Enable*/
    UDRIE,      /*USART Data Register Empty Interrupt Enable*/
    TXCIE,      /*TX Complete Interrupt Enable*/
    RXCIE,      /*RX Complete Interrupt Enable*/  
}UCSRB_pin_t;


typedef enum
{
    MPCM = 0,   /*Multi-processor Communication Mode*/
    U2X,        /*Double the USART Transmission Speed*/
    PE,         /*Parity Error*/
    DOR,        /*Data OverRun*/
    FE,         /*Frame Error*/
    UDRE,       /*USART Data Register Empty*/
    TXC,        /*USART Transmit Complete*/
    RXC,        /*USART Receive Complete*/  
}UCSRA_pin_t;

typedef enum
{
    UCPOL = 0,   /*Clock Polarity*/
    UCSZ0,       /*Character Size*/
    UCSZ1,      /*Character Size*/
    USBS,       /*Stop Bit Select*/
    UPM0,       /*Parity Mode*/
    UPM1,       /*Parity Mode*/
    UMSEL,      /*USART Mode Select*/
    URSEL,      /*Register Select*/  
}UCSRC_pin_t;

void UART_init(long USART_BAUDRATE);
unsigned char UART_RxChar();
void UART_TxChar(char ch);
void UART_SendString(char *str);
void adv_UART_RxChar(u8 *ptr);
