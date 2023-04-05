/*
 * ICU.c
 *
 * Created: 4/4/2023 1:37:32 PM
 *  Author: mohamed abdelslam
 */ 

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Timer_interface.h"
#include "ICU_interface.h"
u16 Frequency,Duty_cycle;
int main(void)
{


MTIMER1_voidInit();
MTIMER1_voidEnableInterrupt();
u8 Local_result=ICU_Calculate_DutyCycle(&Frequency,&Duty_cycle);
if (Local_result==IN_RANGE)
{
	LCD_Display_DutyCycle_Freq(Duty_cycle,Frequency,IN_RANGE);
}
else if (Local_result==OUT_OF_RANGE)
{
	LCD_Display_DutyCycle_Freq(Duty_cycle,Frequency,OUT_OF_RANGE);
}
  
    while(1)
    {
		    
    }
}

