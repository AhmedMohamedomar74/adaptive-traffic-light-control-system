/*
 * config.h
 *
 *  Created on: Aug 29, 2023
 *      Author: ahmedomar
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include "../../MCAL/GPIO/GPIO.h"

// f=0  DL =0 4bit N=0 one line display
#define lcd_Clear 0x01           /* replace all characters with ASCII 'space'                       */
#define lcd_Home 0x02            /* return cursor to first position on first line                   */
#define lcd_EntryMode 0x06       // shift cursor from left to right on read/write
#define lcd_DisplayOff 0x08      // turn display off
#define lcd_DisplayOn 0x0C       // display on, cursor off, don't blink character
#define lcd_FunctionReset 0x30   // reset the LCD
#define lcd_FunctionSet8bit 0x38 // 8-bit data, 2-line display, 5 x 7 font
#define lcd_SetCursor_firstLine 0x80       // Force the cursor to the beginning of the 1st line
#define lcd_SetCursor_secodLine 0xC0       //  Force the cursor to the beginning of the 2nd line
#define Address_SGRAM_init 0x40   
typedef struct config
{
    u8 lcd_data_port;
    u8 lcd_control_port;
    u8 lcd_rs_pin;
    u8 lcd_E_pin;
    u8 lcd_rw_pin;
} lcd_t;

extern lcd_t lcd_1;

#endif /* CONFIG_H_ */
