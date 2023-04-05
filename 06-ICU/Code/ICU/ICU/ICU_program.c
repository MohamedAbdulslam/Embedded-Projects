/*
 * ICU_program.c
 *
 * Created: 4/5/2023 11:25:07 AM
 *  Author: mohamed abdelslam
 */ 
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#define F_CPU 8000000UL
#include "DELAY.h"
#include "Timer_interface.h"
#include "Timer_private.h"
#include "Timer_config.h"
#include "ICU_interface.h"
#include "LCD_interface.h"
u16 x,y,z,On_Time,Time_period;
u8 ICU_Calculate_DutyCycle(u16 *PtrCopy_u16Freq, u16 *ptrCopy_u16Duty)
{
	
    SET_BIT(TIFR,5); //Clear ICU interrupt flag
	MTIMER1_voidICUInit();
	while((TIFR&(1<<5))==0); //wait while capture is occured
	x=ICR1;  // store time before first rising capture
	SET_BIT(TIFR,5); //Clear ICU interrupt flag
	SET_BIT(TCCR1B,0);//for cpu clock
	CLR_BIT(TCCR1B,6); //Configure ICU to FALLING EDGE
	SET_BIT(TCCR1B,7); // for noise canceller
	while((TIFR&(1<<5))==0); //wait while capture is occured
	y=ICR1; // store time before falling capture
	SET_BIT(TIFR,5); //Clear ICU interrupt flag
	TCCR1B=0Xc1;
	while((TIFR&(1<<5))==0); //wait while capture is occured
	z=ICR1;  //store time before second rising capture
	SET_BIT(TIFR,5); //Clear ICU interrupt flag
	/* stop timer1 */
	CLR_BIT(TCCR1B,0);
	CLR_BIT(TCCR1B,1);
	CLR_BIT(TCCR1B,2);
	if((x<y) && (y<z)) // check for condition to avoid timer overflow reading
	{
		On_Time=y-x;
		Time_period=z-x;
		*ptrCopy_u16Duty=((f32) On_Time/Time_period )*100;
		*PtrCopy_u16Freq=( F_CPU/ (Time_period) );
		return 1;
	}
	else
	{
		return 0;
	}
}

void LCD_Display_DutyCycle_Freq(u16 Duty_Cycle,u16 Frequency,u8 Status)
{
	if (Status==IN_RANGE)
	{
		HLCD_voidInit();
		HLCD_voidSendString("Duty:");
		HLCD_voidSendChar( (Duty_Cycle/10)+48 );
		HLCD_voidSendChar( (Duty_Cycle%10)+48 );
		HLCD_voidSendChar('%');
		HLCD_voidMoveCursor(2,1);
		HLCD_voidSendString("Frequency:");
		HLCD_voidSendChar( (Frequency/1000) + 48 );
		HLCD_voidSendChar( ( (Frequency/100)%10 ) + 48 );
		HLCD_voidSendChar( ( (Frequency/10)%10 ) + 48 );
		HLCD_voidSendChar( ( Frequency%10 )+48 );
		HLCD_voidSendString("HZ");
		
	}
	else if (Status==OUT_OF_RANGE)
	{
		HLCD_voidClearScreen();
		HLCD_voidSendString("OUT OF RANGE");
	}
	
	
}