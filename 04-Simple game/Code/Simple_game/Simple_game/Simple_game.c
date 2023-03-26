/*
 * Simple_game.c
 *
 * Created: 3/26/2023 4:21:31 PM
 *  Author: mohamed abdelslam
 */ 

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#define F_CPU 8000000UL
#include "DELAY.h"

#include "DIO_interface.h"
#include "Interupt_interface.h"
#include "Timer_interface.h"
#include "LCD_interface.h"
#include "KEYPAD_interface.h"
volatile u32 counter=0;
volatile u32 flag=0;


int main(void)
{
	HLCD_voidInit();
	HKEYPAD_voidInit();
	HLCD_voidSendString("Guess the number");
	HLCD_voidMoveCursor(2,1);
	HLCD_voidSendString("3+?=8");
	MTIMER0_voidInit();
	MTIMER0_voidEnableInterrupt();
	u8 status;
	do 
	{
		if (counter>=1000)
		{
			flag=1;
		}
		
		status=HKEYPAD_u8Read();
	} while ( (status==0xff) && (flag==0) );
	if (status==0xff)
	{
		HLCD_voidClearScreen();
		HLCD_voidMoveCursor(2,4);
		HLCD_voidSendString("Time over");
	}
	else if (status=='5')
	{
		HLCD_voidClearScreen();
		HLCD_voidMoveCursor(2,4);
		HLCD_voidSendString("Great");		
	}
	else
	{
		HLCD_voidClearScreen();
		HLCD_voidMoveCursor(2,1);
		HLCD_voidSendString("Try another time");		
	}
	

}
/* ISR for timer 0 compare match */
void __vector_10(void)__attribute__((signal,used));
void __vector_10(void)
{
	
	counter++;
}