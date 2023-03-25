/*
 * Temperature_meter.c
 *
 * Created: 3/25/2023 2:04:02 PM
 *  Author: mohamed abdelslam
 */ 

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ADC_interface.h"
#include "LCD_interface.h"

u8 temp;

int main(void)
{
	HLCD_voidInit();
	MADC_voidInit();
	HLCD_voidSendString("TEMP ");
	
    while(1)
    {
		// temp=( ( 2.56*1000*MADC_u16Read() ) / (1024*10) )
       temp=( 0.25*MADC_u16Read() ) ;
	   if(temp<10)
	   {
		   HLCD_voidMoveCursor(1,6);
		   HLCD_voidSendChar(temp+48);
		   HLCD_voidSendChar(0xDF); // degree character
		   HLCD_voidSendChar('C');
		   HLCD_voidSendChar(0x20); 
	   }
	   else if (temp<100)
	   {
		   HLCD_voidMoveCursor(1,6);
		   HLCD_voidSendChar( (temp/10) +48);
		   HLCD_voidSendChar( (temp%10) +48);
		   HLCD_voidSendChar(0xDF); // degree character
		   HLCD_voidSendChar('C');		   
	   }
	   else if (temp<1000)
	   {
		   HLCD_voidMoveCursor(1,6);
		   HLCD_voidSendChar( (temp/100) +48);
		   HLCD_voidSendChar( ( (temp/10)%10 ) +48);
		   HLCD_voidSendChar( (temp%10) +48);
		   HLCD_voidSendChar(0xDF); // degree character
		   HLCD_voidSendChar('C');
	   }	   
	   else
	   {
		   /* Do nothing */
	   }
    }
}