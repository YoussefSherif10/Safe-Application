/*
 * safe.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Yousuf
 */

#include"STD_TYPES.h"
#include"DIO.h"
#include"LCD_NEW.h"
#include"KEYPAD.h"
#define F_CPU 1000000UL
#include"util/delay.h"
#include"BIT_MATH.h"

char array[8];									// array to hold the password of 8 digits
int i , password1 = 0 , password2 = 0 ;			// password digit counters

typedef enum pass {confirm , wrong}t_e_pass;	// check confirmation password variables
t_e_pass status ;

int main()
{
	DIO_INIT();
	LCD_INIT();
	KPD_INIT();
	while(1)
	{
		
	while(password1 < 8)						// wait for the end of the first password
	{
		char x = 0;
		while (x == 0)
		{
		x= KPD_GETKEY();						// get digits from the keypad
		}
		LCD_WRITE_CHAR(x);						// write the digit on the LCD
		for(i = 0 ; i < 8 ; i++)
		{
			array[i] = x ;
		}
		password1++ ;
	}
	LCD_SEND_CMD(LCD_CLR);						// clear the LCD
	while(password2 < 8)						// wait for the confirmation password
	{
		char x = 0;
		while(x == 0)
		{
			x = KPD_GETKEY();
		}
		LCD_WRITE_CHAR(x);
		for(i = 0 ; i < 8 ; i++)
		{
			if( x == array [i])
			{
				status = confirm ;
			}
			else if(x != array[i])
			{
				status = wrong ;
				break ;
			}
		}

		password2++;
	}
	LCD_SEND_CMD(LCD_CLR);						// open the safe
	if (status == confirm)
		{
			DIO_SETPIN(PORT_C , DIO_PIN_1 , DIO_HIGH);
			DIO_SETPIN(PORT_C , DIO_PIN_2 , DIO_LOW);
			DIO_SETPIN(PORT_C , DIO_PIN_3 , DIO_HIGH);
		}
	else if(status == wrong)					// close the safe
		{
			DIO_SETPIN(PORT_C , DIO_PIN_1 , DIO_LOW);
			DIO_SETPIN(PORT_C , DIO_PIN_2 , DIO_HIGH);
			DIO_SETPIN(PORT_C , DIO_PIN_3 , DIO_HIGH);
		}
		_delay_ms(3000);						// wait for 3 seconds
	}
	return 0 ;
}
