/*
 * LCD.h
 *
 *  Created on: Aug 29, 2023
 *      Author: ahmedomar
 */

#ifndef LCD_H_
#define LCD_H_
#include "config.h"
void init_lcd (void);
void send_commund (u8 command);
void LCD_vidWriteCharctr(u8 u8DataCpy);
void LCD_clear (void );
void LCD_vidWriteString(u8 *arr);
void LCD_set_cursor (u8 x, u8 y);
void displayNumberOnLCD(s32 number);
void swap(u8 *ptr1, u8 *ptr2);
void LCD_Display_special_char (u8 x, u8 y);
#endif /* LCD_H_ */
