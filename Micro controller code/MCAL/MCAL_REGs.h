/*
 * MCAL_REGs.h
 *
 *  Created on: Aug 21, 2023
 *      Author: ahmedomar
 */

#ifndef MCAL_REGS_H_
#define MCAL_REGS_H_
#include "../LIB/STD.h"

#define MAX_PIN 7

/***************************
 * base address
 **************************/
// Group A
#define PORTA_BASE 0X3B
#define DDRA_BASE 0x3A
#define PINA_BASE 0X39
// Group B
#define PORTB_BASE 0X38
#define DDRB_BASE 0x37
#define PINB_BASE 0X36
// Group C
#define PORTC_BASE 0X35
#define DDRC_BASE 0x34
#define PINC_BASE 0X33
// Group D
#define PORTD_BASE 0X32
#define DDRD_BASE 0x31
#define PIND_BASE 0X30

// Timer 0
#define TCCR0_BASE 0x53
#define TCNT0_BASE 0x52
#define TIFR_BASE 0x58
#define TIMSK_BASE 0x59

//Interrupt registers
#define MCUCR_BASE 0x55
#define MCUCSR_BASE 0x54
#define GICR_BASE 0x5B
#define GIFR_BASE 0x5A

//status register 
#define SREG_BASE 0x5F

// POINTER FOR GROUPS
#define PORTA_Ptr *((volatile u8 *)PORTA_BASE) //(volatile u8*) it used for casting
#define DDRA_Ptr *((volatile u8 *)DDRA_BASE)   // volatile it used to avoid optmization
#define PINA_Ptr *((volatile u8 *)PINA_BASE)
#define PORTB_Ptr *((volatile u8 *)PORTB_BASE)
#define DDRB_Ptr *((volatile u8 *)DDRB_BASE)
#define PINB_Ptr *((volatile u8 *)PINB_BASE)
#define PORTC_Ptr *((volatile u8 *)PORTC_BASE)
#define DDRC_Ptr *((volatile u8 *)DDRC_BASE)
#define PINC_Ptr *((volatile u8 *)PINC_BASE)
#define PORTD_Ptr *((volatile u8 *)PORTD_BASE)
#define DDRD_Ptr *((volatile u8 *)DDRD_BASE)
#define PIND_Ptr *((volatile u8 *)PIND_BASE)
#define TCCR0_Ptr *((volatile u8 *)TCCR0_BASE)
#define TCNT0_Ptr *((volatile u8 *)TCNT0_BASE)
#define TIFR_Ptr *((volatile u8 *)TIFR_BASE)
#define TIMSK_Ptr *((volatile u8 *)TIMSK_BASE)
#define UDR_T *((volatile u8 *)0x2C)
#define UDR_R *((volatile u8 *)0x2C)
#define UCSRA *((volatile u8 *)0x2B)
#define UCSRB *((volatile u8 *)0x2A)
#define UCSRC *((volatile u8 *)0x40)
#define UBRRL *((volatile u8 *)0x29)
#define UBRRH *((volatile u8 *)0x40)
/*****************I2C registers***************/
#define TWBR    *((volatile u8 *)0x20)
#define TWSR    *((volatile u8 *)0x21)
#define TWAR    *((volatile u8 *)0x22)
#define TWDR    *((volatile u8 *)0x23)
#define TWCR    *((volatile u8 *)0x56)
/*****************ADC registers***************/
#define ADMUX   *((volatile u8 *)0x27)
#define ADCSRA  *((volatile u8 *)0x26)
#define ADCH    *((volatile u8 *)0x25)
#define ADCL    *((volatile u8 *)0x24)
/*****************SPI registers***************/
#define SPCR   *((volatile u8*)0x2D)
#define SPSR   *((volatile u8*)0x2E)
#define SPDR   *((volatile u8*)0x2F)
/*****************status register***************/
#define SREG_Ptr *((volatile u8 *)SREG_BASE)
/**********************************/
#define MCUCR *((volatile u8 *)MCUCR_BASE)
#define MCUCSR *((volatile u8 *)MCUCSR_BASE)
#define GICR *((volatile u8 *)GICR_BASE)
#define GIFR *((volatile u8 *)GIFR_BASE)

/*******************APIs Declaration******************/ 
typedef enum 
{
    C,
    Z,
    N,
    V,
    S,
    H,
    T,
    I,
}SERG_PIN_t; 
#endif /* MCAL_REGS_H_ */
