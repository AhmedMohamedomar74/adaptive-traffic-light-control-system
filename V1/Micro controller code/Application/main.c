#include "../MCAL/I2C_electronicwings/I2C_electronicwings.h"
#include "../MCAL/GPIO/GPIO.h"
#include "../MCAL/UART/UART.h"
#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>


// master programm

// #define Slave_one_Write_Address		0x20
// #define Slave_one_Read_Address		0x21
// #define Slave_two_Write_Address		0x30
// #define Slave_two_Read_Address		0x31
// #define Slave_three_Write_Address	0x40
// #define Slave_three_Read_Address	0x41
// #define Slave_four_Write_Address	0x50
// #define Slave_four_Read_Address		0x51
// #define Slave_five_Write_Address	0x60
// #define Slave_five_Read_Address		0x61
// #define	count				4

// void master_read (u8 address_read , u8 * arr_recived);
// void MC_SEND_MODEL(u8 * PRT,u8 length);
// void check (u8 * PTR);
// int main()
// {
// 	I2C_Init();
//     UART_init(9600);
//     char c = 0;
// 	u8 arr_one_recived [4] = {0,0,0,0};
// 	u8 arr_two_recived [4] = {0,0,0,0};
// 	u8 arr_three_recived [4] = {0,0,0,0};
// 	u8 arr_four_recived [4] = {0,0,0,0};
// 	u8 arr_five_recived [4] = {0,0,0,0};
// 	while (1)
// 	{
// 		master_read(Slave_one_Read_Address,arr_one_recived);
// 		master_read(Slave_two_Read_Address,arr_two_recived);
// 		master_read(Slave_three_Read_Address,arr_three_recived);
// 		master_read(Slave_four_Read_Address,arr_four_recived);
// 		master_read(Slave_five_Read_Address,arr_five_recived);
//         c = UART_RxChar();
// 		if ('S' == c)
// 		{
// 			switch (UART_RxChar())
// 			{
// 				case 0:
// 					MC_SEND_MODEL(arr_one_recived,4);
// 					break;
// 				case 1:
// 					MC_SEND_MODEL(arr_two_recived,4);
// 					break;
// 				case 2:
// 					MC_SEND_MODEL(arr_three_recived,4);
// 					break;
// 				case 4:
// 					MC_SEND_MODEL(arr_five_recived,4);
// 					break;
// 				case 3:
// 					MC_SEND_MODEL(arr_four_recived,4);
// 					break;			
// 				default:
// 					break;
// 			}
// 		}
// 		// check (arr_one_recived);
// 		// check (arr_two_recived);
// 		// check (arr_three_recived);
// 		// check (arr_four_recived);
// 		// check (arr_five_recived);
// 		// _delay_ms(5);
// 	}
// }

// void master_read (u8 address_read , u8 * arr_recived)
// {
// 	I2C_start(address_read);
// 	_delay_ms(5);
// 	for (u8 i = 0; i < count; i++)
// 		{
// 			if (i < count -1)
// 			{
// 				arr_recived[i] = I2C_Read_ACK();
// 			}
// 			else
// 			{
// 				arr_recived[i] = I2C_Read_Nack();
// 			}
// 			// _delay_ms(500);
// 		}
// 	I2C_Stop();
// }

// void check (u8 * PTR)
// {
// 	for (u8 i = 0; i < 4; i++)
// 	{
// 		GPIO_setPortDirection(0,PTR[i]);
// 		GPIO_setPortValue(0,PTR[i]);
// 		_delay_ms(1000);
// 	}
	
// }
// void MC_SEND_MODEL(u8 * PRT,u8 length)
// {
// 	UART_TxChar(length);
// 	for (u8 i = 0; i < length; i++)
// 	{
// 		UART_TxChar(PRT[i]);
// 	}
	
// }

// void MC_SEND_MODEL(u8 * PRT,u8 length);
// void MC_recieve_From_model (u8 *PTR);

// int main()
// {
// 	char c = 0;
// 	UART_init(9600);
// 	u8 Arr_Send_1[4] = 	{12,11,16,13};
// 	u8 Arr_Send_2[4] = 	{12,8,10,13};
// 	u8 Arr_Send_3[4] = 	{1,2,3,4};
// 	u8 Arr_Send_4[4] = 	{13,15,4,13};
// 	u8 Arr_Send_5[4] = 	{12,8,10,13};
// 	// u8 length;
// 	u8 x;
// 	u8 y;
// 	u8 z;
// 	u8 f;
// 	u8 u;
// 	while(1)
// 	{
// 		c = UART_RxChar();
// 		x = c;
// 		if ('S' == c)
// 		{
// 			switch (UART_RxChar())
// 			{
// 				case 0:
// 					MC_SEND_MODEL(Arr_Send_1,4);
// 					break;
// 				case 1:
// 					MC_SEND_MODEL(Arr_Send_2,4);
// 					break;
// 				case 2:
// 					MC_SEND_MODEL(Arr_Send_3,4);
// 					break;
// 				case 4:
// 					MC_SEND_MODEL(Arr_Send_5,4);
// 					break;
// 				case 3:
// 					MC_SEND_MODEL(Arr_Send_4,4);
// 					break;			
// 				default:
// 					break;
// 			}
// 		}

// 		else if ('W' == c)
// 		{
// 			switch (UART_RxChar())
// 			{
// 				case 0:
					
// 					adv_UART_RxChar(&x);
// 					UDR_T = 0;
// 					break;
// 				case 1:
					
// 					adv_UART_RxChar(&y);
// 					UDR_T = 0;
// 					break;
// 				case 2:
					
// 					adv_UART_RxChar(&z);
// 					UDR_T = 0;
// 					break;
// 				case 3:
					
// 					adv_UART_RxChar(&f);
// 					UDR_T = 0;
// 					break;
// 				case 4:
					
// 					adv_UART_RxChar(&u);
// 					UDR_T = 0;
// 					break;
// 				default:
// 					break;
// 			}
// 		}
// 		GPIO_setPortDirection(PORTA,x);
// 		GPIO_setPortValue(PORTA,x);
// 		GPIO_setPortDirection(PORTB,y);
// 		GPIO_setPortValue(PORTB,y);
// 		GPIO_setPortDirection(PORTC,z);
// 		GPIO_setPortValue(PORTC,z);
// 	}
// }




// void MC_recieve_From_model (u8 *PTR)
// {
// 	u8 legnth =UART_RxChar();
// 	for (u8 i = 0; i < legnth; i++)
// 	{
// 		PTR[i] = UART_RxChar();
// 	}
	
// }

// slave_one programm

// #define Slave_Address		0x20
// int main()
// {
// 	// char buffer[10];
//     s8 count = 0;
// 	u8 counter = 0;
//     s8 Ack_status;
// 	u8 send_arr[4] = {1,2,3,4};
// 	// generateRandomArray(send_arr);
// 	I2C_Slave_Init(Slave_Address);

// 	while (1)
// 	{
// 		switch (I2C_Slave_Lestin())
// 		{
// 		case 0:
// 			do
// 			{
// 				count = I2C_Slave_Receive();
// 				counter ++;
// 			} while (counter < 4);
// 			count = 0;
// 			break;
// 		case 1:
// 			do
// 			{
// 				Ack_status = I2C_Slave_Transmit(send_arr[count]);
// 				count++;
// 			} while (Ack_status == 0);
// 			count = 0;
// 			break;
// 		case 3:
// 			break;	
			
// 		default:
// 			break;
// 		}
// 	}
	
// }

// void MC_SEND_MODEL(u8 * PRT,u8 length)
// {
// 	UART_TxChar(length);
// 	for (u8 i = 0; i < length; i++)
// 	{
// 		UART_TxChar(PRT[i]);
// 	}
	
// }

// slave_two programm

// #define Slave_Address		0x30
// // void generateRandomArray(u8 *ptr);
// int main()
// {
// 	// char buffer[10];
//     s8 count = 0;
// 	u8 counter = 0;
//     s8 Ack_status;
// 	u8 send_arr[4] = {5,6,7,8};
// 	// generateRandomArray(send_arr);
// 	I2C_Slave_Init(Slave_Address);

// 	while (1)
// 	{
// 		switch (I2C_Slave_Lestin())
// 		{
// 		case 0:
// 			do
// 			{
// 				count = I2C_Slave_Receive();
// 				counter ++;
// 			} while (counter < 4);
// 			count = 0;
// 			break;
// 		case 1:
// 			do
// 			{
// 				Ack_status = I2C_Slave_Transmit(send_arr[count]);
// 				count++;
// 			} while (Ack_status == 0);
// 			count = 0;
// 			break;
// 		case 3:
// 			break;	
			
// 		default:
// 			break;
// 		}
// 	}
	
// }

// slave_three programm

// #define Slave_Address		0x40
// // void generateRandomArray(u8 *ptr);
// int main()
// {
// 	char buffer[10];
//     s8 count = 0;
// 	u8 counter = 0;
//     s8 Ack_status;
// 	u8 legnth ;
// 	u8 send_arr[4] = {0,0,0,0};
// 	I2C_Slave_Init(Slave_Address);
// 	UART_init(9600);
// 	while (1)
// 	{
		
		
// 		switch (I2C_Slave_Lestin())
// 		{
// 			case 0:
// 				do
// 				{
// 					count = I2C_Slave_Receive();
// 					counter ++;
// 				} while (counter < 4);
// 				count = 0;
// 				break;
// 			case 1:
// 				do
// 				{
// 					Ack_status = I2C_Slave_Transmit(send_arr[count]);
// 					count++;
// 				} while (Ack_status == 0);
// 				count = 0;
// 				break;
// 			case 3:
// 				break;	
				
// 			default:
// 				break;
// 		}
//         switch (UART_RxChar())
// 		{
// 			case 0x57:
// 				UART_TxChar('R');
// 				legnth = UART_RxChar();
// 				if (legnth >= 0)
// 				{
// 					for (u8 i = 0; i < legnth; i++)
// 					{
// 						send_arr[i] = UART_RxChar();
// 					}
// 				}
// 				break;
			
// 			default:
// 				break;
// 		}		
// 	}
	
// }

// slave_four programm

// #define Slave_Address		0x50
// // void generateRandomArray(u8 *ptr);
// int main()
// {
// 	char buffer[10];
//     s8 count = 0;
// 	u8 counter = 0;
//     s8 Ack_status;
// 	u8 legnth ;
// 	u8 send_arr[4] = {0,0,0,0};
// 	I2C_Slave_Init(Slave_Address);
// 	UART_init(9600);
// 	while (1)
// 	{
		
		
// 		switch (I2C_Slave_Lestin())
// 		{
// 			case 0:
// 				do
// 				{
// 					count = I2C_Slave_Receive();
// 					counter ++;
// 				} while (counter < 4);
// 				count = 0;
// 				break;
// 			case 1:
// 				do
// 				{
// 					Ack_status = I2C_Slave_Transmit(send_arr[count]);
// 					count++;
// 				} while (Ack_status == 0);
// 				count = 0;
// 				break;
// 			case 3:
// 				break;	
				
// 			default:
// 				break;
// 		}
//         switch (UART_RxChar())
// 		{
// 			case 0x57:
// 				UART_TxChar('R');
// 				legnth = UART_RxChar();
// 				if (legnth >= 0)
// 				{
// 					for (u8 i = 0; i < legnth; i++)
// 					{
// 						send_arr[i] = UART_RxChar();
// 					}
// 				}
// 				break;
			
// 			default:
// 				break;
// 		}		
// 	}
	
// }

// slave_five programm

#define Slave_Address		0x60
int main()
{
	char buffer[10];
    s8 count = 0;
	u8 counter = 0;
    s8 Ack_status;
	u8 legnth ;
	u8 send_arr[4] = {0,0,0,0};
	I2C_Slave_Init(Slave_Address);
	UART_init(9600);
	while (1)
	{
		
		
		switch (I2C_Slave_Lestin())
		{
			case 0:
				do
				{
					count = I2C_Slave_Receive();
					counter ++;
				} while (counter < 4);
				count = 0;
				break;
			case 1:
				do
				{
					Ack_status = I2C_Slave_Transmit(send_arr[count]);
					count++;
				} while (Ack_status == 0);
				count = 0;
				break;
			case 3:
				break;	
				
			default:
				break;
		}
        switch (UART_RxChar())
		{
			case 0x57:
				UART_TxChar('R');
				legnth = UART_RxChar();
				if (legnth >= 0)
				{
					for (u8 i = 0; i < legnth; i++)
					{
						send_arr[i] = UART_RxChar();
					}
				}
				break;
			
			default:
				break;
		}		
	}
	
}



