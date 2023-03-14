/*
 * EVM.c
 *
 * Created: 3/14/2023 11:24:41 AM
 *  Author: mohamed abdelslam
 */ 

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#define F_CPU 8000000UL 
#include "DELAY.h"

#include "DIO_interface.h"
#include "LCD_interface.h"

/* Define 4 counters represent 4 candidates */
 u8 C1_counter=0;
 u8 C2_counter=0;
 u8 C3_counter=0;
 u8 C4_counter=0;
int main(void)
{
	HLCD_voidInit(); //Initialize LCD
    /* Define Pin3,Pin4,Pin5,Pin6 and Pin7 of port B as output pins */
	MDIO_voidSetPinDirection(DIOB,3,OUTPUT); //C1
	MDIO_voidSetPinDirection(DIOB,4,OUTPUT); //C2
	MDIO_voidSetPinDirection(DIOB,5,OUTPUT); //C3
	MDIO_voidSetPinDirection(DIOB,6,OUTPUT); //C4
	MDIO_voidSetPinDirection(DIOB,7,OUTPUT); //RESET
	/* Define Pin3,Pin4,Pin5,Pin6 and Pin7 of port B as output pins */
	
	/* Set the initial interface of the LCD */
	HLCD_voidSendString("C1=0");
	HLCD_voidMoveCursor(1,12);
	HLCD_voidSendString("C2=0");
	HLCD_voidMoveCursor(2,1);
	HLCD_voidSendString("C3=0");
	HLCD_voidMoveCursor(2,12);
	HLCD_voidSendString("C4=0");
	/* Set the initial interface of the LCD */
    while(1)
    {
        if ( MDIO_u8GetPinValue(DIOB,3) ==1 )
        {
			C1_counter++;
			HLCD_voidMoveCursor(1,4);
			HLCD_voidSendChar(C1_counter+48);
        }
		else if (MDIO_u8GetPinValue(DIOB,4) ==1)
		{
			C2_counter++;
			HLCD_voidMoveCursor(1,15);
			HLCD_voidSendChar(C2_counter+48);
		}
		else if (MDIO_u8GetPinValue(DIOB,5) ==1)
		{
			C3_counter++;
			HLCD_voidMoveCursor(2,4);
			HLCD_voidSendChar(C3_counter+48);			
		}
		else if (MDIO_u8GetPinValue(DIOB,6) ==1)
		{
			C4_counter++;
			HLCD_voidMoveCursor(2,15);
			HLCD_voidSendChar(C4_counter+48);			
		}
		else if (MDIO_u8GetPinValue(DIOB,7) ==1)
		{
			HLCD_voidClearScreen();
			/* Reset all counters to zeros */
			C1_counter=C2_counter=C3_counter=C4_counter=0;
	        /* Reset the initial interface of the LCD */
	        HLCD_voidSendString("C1=0");
	        HLCD_voidMoveCursor(1,12);
	        HLCD_voidSendString("C2=0");
	        HLCD_voidMoveCursor(2,1);
	        HLCD_voidSendString("C3=0");
	        HLCD_voidMoveCursor(2,12);
	        HLCD_voidSendString("C4=0");			
		}
		Delay_ms(300);
    }
}