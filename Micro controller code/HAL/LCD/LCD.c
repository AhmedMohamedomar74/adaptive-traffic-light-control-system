/*
 * LCD.c
 *
 *  Created on: Aug 31, 2023
 *      Author: ahmedomar
 */
#include "LCD.h"
#include "EXTRA.h"
/*
 * LCD.c
 *
 *  Created on: Aug 29, 2023
 *      Author: ahmedomar
 */

#include "LCD.h"
lcd_t *LCD_Glopal_ptr;

void init_lcd(void)
{
    LCD_Glopal_ptr = &lcd_1;
    GPIO_setPortDirection(LCD_Glopal_ptr->lcd_data_port, Out_Port_direction);
    GPIO_setPindDirection(LCD_Glopal_ptr->lcd_control_port, LCD_Glopal_ptr->lcd_E_pin, Output_direction);
    GPIO_setPindDirection(LCD_Glopal_ptr->lcd_control_port, LCD_Glopal_ptr->lcd_rw_pin, Output_direction);
    GPIO_setPindDirection(LCD_Glopal_ptr->lcd_control_port, LCD_Glopal_ptr->lcd_rs_pin, Output_direction);
    _delay_ms(30);
    send_commund(lcd_Home);
    _delay_us(15);
    send_commund(lcd_FunctionSet8bit);
    _delay_ms(1);
    send_commund(lcd_DisplayOn);
    _delay_ms(1);
    send_commund(lcd_Clear);
    _delay_ms(15);
    send_commund(lcd_EntryMode);
    _delay_ms(2);
}

void send_commund(u8 command)
{
    LCD_Glopal_ptr = &lcd_1;
    /* Set RS to LOW */
    GPIO_setPinValue((LCD_Glopal_ptr->lcd_control_port), (LCD_Glopal_ptr->lcd_rs_pin), low_value);
    /* Set R/W to LOW */
    GPIO_setPinValue((LCD_Glopal_ptr->lcd_control_port), (LCD_Glopal_ptr->lcd_rw_pin), low_value);
    /* Set E to HIGH  */
    GPIO_setPinValue((LCD_Glopal_ptr->lcd_control_port), (LCD_Glopal_ptr->lcd_E_pin), high_value);
    /* Load Command on Data bus */
    GPIO_setPortValue((LCD_Glopal_ptr->lcd_data_port), command);
    /* Set E to LOW */
    GPIO_setPinValue((LCD_Glopal_ptr->lcd_control_port), (LCD_Glopal_ptr->lcd_E_pin), low_value);
    /* Wait for E to settle */
    _delay_ms(1);
    GPIO_setPinValue((LCD_Glopal_ptr->lcd_control_port), (LCD_Glopal_ptr->lcd_E_pin), high_value);
    /* Delay for 1ms to let the LCD execute command */
    _delay_ms(1);
}

void LCD_vidWriteCharctr(u8 u8DataCpy)
{
    LCD_Glopal_ptr = &lcd_1;
    /* Set RS to LOW */
    GPIO_setPinValue((LCD_Glopal_ptr->lcd_control_port), (LCD_Glopal_ptr->lcd_rs_pin), high_value);

    /* Set R/W to LOW */
    GPIO_setPinValue((LCD_Glopal_ptr->lcd_control_port), (LCD_Glopal_ptr->lcd_rw_pin), low_value);

    /* Set E to HIGH  */
    GPIO_setPinValue((LCD_Glopal_ptr->lcd_control_port), (LCD_Glopal_ptr->lcd_E_pin), high_value);

    /* Load Command on Data bus */
    GPIO_setPortValue((LCD_Glopal_ptr->lcd_data_port), u8DataCpy);

    /* Set E to LOW */
    GPIO_setPinValue((LCD_Glopal_ptr->lcd_control_port), (LCD_Glopal_ptr->lcd_E_pin), low_value);

    /* Wait for E to settle */
    _delay_ms(1);

    /* Set E to HIGH */
    GPIO_setPinValue((LCD_Glopal_ptr->lcd_control_port), (LCD_Glopal_ptr->lcd_E_pin), high_value);

    /* Delay to let the LCD Display the character */
    _delay_ms(1);
}

void LCD_clear(void)
{
    send_commund(lcd_Clear);
}

void LCD_vidWriteString(u8 *arr)
{
    // u8 index = 0;
    while (*arr != '\0')
    {
        LCD_vidWriteCharctr(*arr);
        arr++;
        /* Delay to let the LCD Display the character */
        _delay_ms(1);
    }
}

void LCD_set_cursor(u8 x, u8 y)
{
    if (x>0 && x<=16)
	{
		switch(y)
		{
		case 1:
			send_commund(lcd_SetCursor_firstLine+x-1);
			break;
		case 2:
			send_commund(lcd_SetCursor_secodLine+x-1);
			break;
		default:
			break;
		}
	}
}

/*void LCD_vidWriteNumber(s16 Number)
{
    u8 Arr[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    s16 *digits;
    u16 length;
    //extractDigits(Number, &digits, &length);
    while (*Arr != '\0')
    {
        LCD_vidWriteCharctr(Arr[*digits]);
        digits++;
         Delay to let the LCD Display the character
        _delay_ms(1);
    }

}*/
void displayNumberOnLCD(s32 number)
{
    u8 buffer[16];
    u16 length = 0;
    if (number < 0)
    {
        //convert the number to positive
        number = -1 * number;
        // Convert the number to a string manually
        do
        {
            buffer[length++] = '0' + (number % 10);
            number /= 10;
        } while (number > 0);

        // Reverse the string in the buffer
        for (u8 i = 0, j = length - 1; i < j; i++, j--)
        {
            swap(&buffer[j], &buffer[i]);
        }
        LCD_vidWriteCharctr('-');
        LCD_vidWriteString(buffer);
    }
    else
    {
        // Convert the number to a string manually
        do
        {
            buffer[length++] = '0' + (number % 10);
            number /= 10;
        } while (number > 0);

        // Reverse the string in the buffer
        for (u8 i = 0, j = length - 1; i < j; i++, j--)
        {
            swap(&buffer[j], &buffer[i]);
        }

        LCD_vidWriteString(buffer);
    }
}

void swap(u8 *ptr1, u8 *ptr2)
{
    *ptr1 = *ptr1 ^ *ptr2;
    *ptr2 = *ptr1 ^ *ptr2;
    *ptr1 = *ptr1 ^ *ptr2;
}

void LCD_Display_special_char(u8 x, u8 y)
{
    //write data in sgram
    send_commund(Address_SGRAM_init);
    for(u8 iteration1=0 ; iteration1<sizeof(ExtraChar)/sizeof(ExtraChar[0]) ; iteration1++)
	{
		LCD_vidWriteCharctr(ExtraChar[iteration1]);
	}
    send_commund(lcd_SetCursor_secodLine);
	LCD_set_cursor(x,y);
	/*First eight character which saved at CGRAM*/
	for (u8 iteration2=0; iteration2<=4 ; iteration2++)
	{
		/* Write bytes of DDRAM */
		LCD_vidWriteCharctr(iteration2);

		_delay_ms(5);
	}
}
