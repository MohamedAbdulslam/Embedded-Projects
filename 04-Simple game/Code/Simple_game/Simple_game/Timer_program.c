/*
 * Timer_program.c
 *
 * Created: 3/26/2023 2:15:39 PM
 *  Author: mohamed abdelslam
 */ 

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#define F_CPU 8000000ul
#include "DELAY.h"

#include "Interupt_interface.h"
#include "Timer_interface.h"
#include "Timer_private.h"
#include "Timer_config.h"

void MTIMER0_voidInit(void)
{
	/* configure timer0 clock */
  #if TIMER0_CLOCK == NO_CLOCK_SOURCE
  /* stop timer */
  CLR_BIT(TCCR0,0);
  CLR_BIT(TCCR0,1);
  CLR_BIT(TCCR0,2);
  
  #elif TIMER0_CLOCK == CPU_CLOCK
  SET_BIT(TCCR0,0);
  CLR_BIT(TCCR0,1);
  CLR_BIT(TCCR0,2);
    
  #elif TIMER0_CLOCK == CPU_DIV_BY_8
  CLR_BIT(TCCR0,0);
  SET_BIT(TCCR0,1);
  CLR_BIT(TCCR0,2);  
  #elif TIMER0_CLOCK == CPU_DIV_BY_64
  SET_BIT(TCCR0,0);
  SET_BIT(TCCR0,1);
  CLR_BIT(TCCR0,2);  
  
  #elif TIMER0_CLOCK == CPU_DIV_BY_256
  CLR_BIT(TCCR0,0);
  CLR_BIT(TCCR0,1);
  SET_BIT(TCCR0,2);  
  #elif TIMER0_CLOCK == CPU_DIV_BY_1024
  SET_BIT(TCCR0,0);
  CLR_BIT(TCCR0,1);
  SET_BIT(TCCR0,2);  
  #elif TIMER0_CLOCK == EXTERNAL_FALLING_EDGE
  CLR_BIT(TCCR0,0);
  SET_BIT(TCCR0,1);
  SET_BIT(TCCR0,2);  
  #elif TIMER0_CLOCK == EXTERNAL_RISING_EDEG
  SET_BIT(TCCR0,0);
  SET_BIT(TCCR0,1);
  SET_BIT(TCCR0,2);  
  #endif
  
  /* configure timer0 mode */
  #if   TIMER0_MODE == OVER_FLOW_MODE
  CLR_BIT(TCCR0,6);
  CLR_BIT(TCCR0,3);
  #elif TIMER0_MODE == PHASE_CORRECT_PWM_MODE
  SET_BIT(TCCR0,6);
  CLR_BIT(TCCR0,3);  
  #elif TIMER0_MODE == CTC_MODE
  CLR_BIT(TCCR0,6);
  SET_BIT(TCCR0,3);  
  #elif TIMER0_MODE == FAST_PWM_MODE
  SET_BIT(TCCR0,6);
  SET_BIT(TCCR0,3);  
  #endif	
  	OCR0=80;
}

void MTIMER0_voidEnableInterrupt(void)
{
	MINT_voidSetGlobalInterrupt(); 
	
  #if   TIMER0_MODE == OVER_FLOW_MODE
  SET_BIT(TIMSK,0);  //enable interrupt in case of overflow
  #elif TIMER0_MODE == CTC_MODE
  SET_BIT(TIMSK,1); //enable interrupt in case of compare match
  #endif	
}