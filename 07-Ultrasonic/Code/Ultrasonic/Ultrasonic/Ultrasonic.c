/*
 * Ultrasonic.c
 *
 * Created: 4/6/2023 12:37:47 AM
 *  Author: mohamed abdelslam
 */ 


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Timer_interface.h"
#include "ICU_interface.h"
#include "LCD_interface.h"

int main(void)
{ 
	
	HLCD_voidInit(); //Initialize LCD
	
	u8 Local_u8Distance=0;
    while(1)
    {
		Local_u8Distance=Ultrasonic_u8GetDistance();
      	LCD_voidDisplayUltrasonicDistance(Local_u8Distance);
    }
}