/*
 * Digital_clock.c
 *
 * Created: 3/28/2023 2:07:08 AM
 *  Author: mohamed abdelslam
 */ 



#include "STD_TYPES.h"
#include "BIT_MATH.h"
#define F_CPU 8000000UL
#include "DELAY.h"

#include "DIO_interface.h"
#include "Interupt_interface.h"
#include "Timer_interface.h"
#include "Sevensegment_interface.h"
#include "LCD_interface.h"
#include "KEYPAD_interface.h"

volatile u8 Seconds_counter=0;
u8 Minutes_counter=0;
u8 Hours_counter=0;
int main(void)
{
	u8 Local_u8KeypadValue;
	u8 Local_u8OnesDigit=0,Local_u8TensDigit=0;
	HSEVSEG_voidInit(DIOB);
	HLCD_voidInit();
	HKEYPAD_voidInit();
	/* define common pins for 7 segments as output pin */
	MDIO_voidSetPinDirection(DIOC,0,OUTPUT);
	MDIO_voidSetPinDirection(DIOC,1,OUTPUT);
	MDIO_voidSetPinDirection(DIOC,2,OUTPUT);
	MDIO_voidSetPinDirection(DIOC,3,OUTPUT);
	MDIO_voidSetPinDirection(DIOC,4,OUTPUT);
	MDIO_voidSetPinDirection(DIOC,5,OUTPUT);
	HLCD_voidSendString("Press 1 to");
	HLCD_voidMoveCursor(2,1);
	HLCD_voidSendString("set the time");
	MTIMER2_voidInit();
	MTIMER2_voidEnableInterrupt();
	
    while(1)
    {
        Local_u8KeypadValue=HKEYPAD_u8Read();
		if (Local_u8KeypadValue!=0xff)
		{
			if (Local_u8KeypadValue=='1')
			{
				HLCD_voidClearScreen();
				HLCD_voidSendString("Hours=--");
				HLCD_voidMoveCursor(1,7);
				Delay_ms(800);
				do 
				{
					Local_u8TensDigit=HKEYPAD_u8Read();
				} while (Local_u8TensDigit==0xff);
				HLCD_voidSendChar(Local_u8TensDigit);
				Delay_ms(500);
				do
				{
					Local_u8OnesDigit=HKEYPAD_u8Read();
				} while (Local_u8OnesDigit==0xff);
				HLCD_voidSendChar(Local_u8OnesDigit);
				Delay_ms(500);
				Hours_counter=( (Local_u8TensDigit-48)*10 + (Local_u8OnesDigit-48) );
				
				HLCD_voidClearScreen();
				HLCD_voidSendString("Minutes=--");
				HLCD_voidMoveCursor(1,9);
				Delay_ms(800);
				do
				{
					Local_u8TensDigit=HKEYPAD_u8Read();
				} while (Local_u8TensDigit==0xff);
				HLCD_voidSendChar(Local_u8TensDigit);
				Delay_ms(500);
				do
				{
					Local_u8OnesDigit=HKEYPAD_u8Read();
				} while (Local_u8OnesDigit==0xff);
				HLCD_voidSendChar(Local_u8OnesDigit);
				Delay_ms(500);
				Minutes_counter=( (Local_u8TensDigit-48)*10 + (Local_u8OnesDigit-48) );	
							
				HLCD_voidClearScreen();
				HLCD_voidSendString("Seconds=--");
				HLCD_voidMoveCursor(1,9);
				Delay_ms(800);
				
				do
				{
					Local_u8TensDigit=HKEYPAD_u8Read();
				} while (Local_u8TensDigit==0xff);
				HLCD_voidSendChar(Local_u8TensDigit);
				Delay_ms(500);
				do
				{
					Local_u8OnesDigit=HKEYPAD_u8Read();
				} while (Local_u8OnesDigit==0xff);
				HLCD_voidSendChar(Local_u8OnesDigit);
				Delay_ms(500);
				Seconds_counter=( (Local_u8TensDigit-48)*10 + (Local_u8OnesDigit-48) );	
				
				HLCD_voidClearScreen();			
	            HLCD_voidSendString("Press 1 to");
	            HLCD_voidMoveCursor(2,1);
	            HLCD_voidSendString("set the time");								
				
			}
			else
			{
				HLCD_voidClearScreen();	
				HLCD_voidSendString("Wrong choice");
				Delay_ms(1000);
				HLCD_voidClearScreen();
				HLCD_voidSendString("Press 1 to");
				HLCD_voidMoveCursor(2,1);
				HLCD_voidSendString("set the time");				
			}
		}
		MDIO_voidSetPinValue(DIOC,1,HIGH);
		MDIO_voidSetPinValue(DIOC,2,HIGH);
		MDIO_voidSetPinValue(DIOC,3,HIGH);
		MDIO_voidSetPinValue(DIOC,4,HIGH);
		MDIO_voidSetPinValue(DIOC,5,HIGH);
		MDIO_voidSetPinValue(DIOC,0,LOW); // Activate first 7 segment
		HSEVSEG_voidWrite(DIOB,Seconds_counter%10);
		Delay_ms(5); // For multiplexing
		
		MDIO_voidSetPinValue(DIOC,0,HIGH);
		MDIO_voidSetPinValue(DIOC,2,HIGH);
		MDIO_voidSetPinValue(DIOC,3,HIGH);
		MDIO_voidSetPinValue(DIOC,4,HIGH);
		MDIO_voidSetPinValue(DIOC,5,HIGH);
		MDIO_voidSetPinValue(DIOC,1,LOW); // Activate second 7 segment		
        HSEVSEG_voidWrite(DIOB,Seconds_counter/10);
		Delay_ms(5); // For multiplexing
				
		MDIO_voidSetPinValue(DIOC,0,HIGH);
		MDIO_voidSetPinValue(DIOC,1,HIGH);
		MDIO_voidSetPinValue(DIOC,3,HIGH);
		MDIO_voidSetPinValue(DIOC,4,HIGH);
		MDIO_voidSetPinValue(DIOC,5,HIGH);
		MDIO_voidSetPinValue(DIOC,2,LOW); // Activate third 7 segment
		HSEVSEG_voidWrite(DIOB,Minutes_counter%10);
		Delay_ms(5); // For multiplexing
		
		MDIO_voidSetPinValue(DIOC,0,HIGH);
		MDIO_voidSetPinValue(DIOC,1,HIGH);
		MDIO_voidSetPinValue(DIOC,2,HIGH);
		MDIO_voidSetPinValue(DIOC,4,HIGH);
		MDIO_voidSetPinValue(DIOC,5,HIGH);
		MDIO_voidSetPinValue(DIOC,3,LOW); // Activate fourth 7 segment
		HSEVSEG_voidWrite(DIOB,Minutes_counter/10);
		Delay_ms(5); // For multiplexing
		
		MDIO_voidSetPinValue(DIOC,0,HIGH);
		MDIO_voidSetPinValue(DIOC,1,HIGH);
		MDIO_voidSetPinValue(DIOC,2,HIGH);
		MDIO_voidSetPinValue(DIOC,3,HIGH);
		MDIO_voidSetPinValue(DIOC,5,HIGH);
		MDIO_voidSetPinValue(DIOC,4,LOW); // Activate fifth 7 segment
		HSEVSEG_voidWrite(DIOB,Hours_counter%10);
		Delay_ms(5); // For multiplexing						

		MDIO_voidSetPinValue(DIOC,0,HIGH);
		MDIO_voidSetPinValue(DIOC,1,HIGH);
		MDIO_voidSetPinValue(DIOC,2,HIGH);
		MDIO_voidSetPinValue(DIOC,3,HIGH);
		MDIO_voidSetPinValue(DIOC,4,HIGH);
		MDIO_voidSetPinValue(DIOC,5,LOW); // Activate sixth 7 segment 
		HSEVSEG_voidWrite(DIOB,Hours_counter/10);
		Delay_ms(5); // For multiplexing
		
		if (Seconds_counter>=60)
		{
			Seconds_counter=0;
			Minutes_counter++;
		}
		if (Minutes_counter>=60)
		{
			Minutes_counter=0;
			Hours_counter++;
		}
		if (Hours_counter>=24)
		{
			Hours_counter=0;
		}
				 
    }
}

void __vector_5(void)__attribute__((signal,used));
void __vector_5(void)
{
	Seconds_counter++;
}