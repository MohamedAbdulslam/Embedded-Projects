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
  
  /* configure compare output mode */
  #if    COMPARE_OUT_MODE== OC0_DISCONNECTED
  CLR_BIT(TCCR0,4);
  CLR_BIT(TCCR0,5);
  #elif  COMPARE_OUT_MODE== TOGG_OC0_ON_COMP_MATCH
  SET_BIT(TCCR0,4);
  CLR_BIT(TCCR0,5);  
  #elif  COMPARE_OUT_MODE== CLR_OC0_ON_COMP_MATCH
  CLR_BIT(TCCR0,4);
  SET_BIT(TCCR0,5);  
  #elif  COMPARE_OUT_MODE== SET_OC0_ON_COMP_MATCH
  SET_BIT(TCCR0,4);
  SET_BIT(TCCR0,5);  
  #endif
  /* configure oc0 pin  */
  #if OC0_STATUS == OC0_ENABLED
  MDIO_voidSetPinDirection(DIOB,3,OUTPUT); // set PB3 as output pin
  #endif 
  /* Set OCR0 with a value if needed   */
  
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

void MTIMER2_voidInit(void)
{
	#if    TIMER2_CLOCK_SOURCE_TYPE == CPU_CLOCK
	CLR_BIT(ASSR,3);
	#elif  TIMER2_CLOCK_SOURCE_TYPE == EXTERNAL_CRYSTAL_ON_TOSC1
	SET_BIT(ASSR,3);
	#endif 
	
	/* configure timer2 clock */
	#if TIMER2_CLOCK == NO_CLOCK_SOURCE
	/* stop timer */
	CLR_BIT(TCCR2,0);
	CLR_BIT(TCCR2,1);
	CLR_BIT(TCCR2,2);
	
	#elif TIMER2_CLOCK == TIMER2_SOURCE_CLOCK
	SET_BIT(TCCR2,0);
	CLR_BIT(TCCR2,1);
	CLR_BIT(TCCR2,2);
	
	#elif TIMER2_CLOCK == TIMER2_SOURCE_CLOCK_DIV_BY_8
	CLR_BIT(TCCR2,0);
	SET_BIT(TCCR2,1);
	CLR_BIT(TCCR2,2);
	#elif TIMER2_CLOCK == TIMER2_SOURCE_CLOCK_DIV_BY_32
	SET_BIT(TCCR2,0);
	SET_BIT(TCCR2,1);
	CLR_BIT(TCCR2,2);
	
	#elif TIMER2_CLOCK == TIMER2_SOURCE_CLOCK_DIV_BY_64
	CLR_BIT(TCCR2,0);
	CLR_BIT(TCCR2,1);
	SET_BIT(TCCR2,2);
	#elif TIMER2_CLOCK == TIMER2_SOURCE_CLOCK_DIV_BY_128
	SET_BIT(TCCR2,0);
	CLR_BIT(TCCR2,1);
	SET_BIT(TCCR2,2);
	#elif TIMER2_CLOCK == TIMER2_SOURCE_CLOCK_DIV_BY_256
	CLR_BIT(TCCR2,0);
	SET_BIT(TCCR2,1);
	SET_BIT(TCCR2,2);
	#elif TIMER2_CLOCK == TIMER2_SOURCE_CLOCK_DIV_BY_1024
	SET_BIT(TCCR2,0);
	SET_BIT(TCCR2,1);
	SET_BIT(TCCR2,2);
	#endif	
	
  /* configure timer2 mode */
  #if   TIMER2_MODE == OVER_FLOW_MODE
  CLR_BIT(TCCR2,6);
  CLR_BIT(TCCR2,3);
  #elif TIMER2_MODE == PHASE_CORRECT_PWM_MODE
  SET_BIT(TCCR2,6);
  CLR_BIT(TCCR2,3);
  #elif TIMER2_MODE == CTC_MODE
  CLR_BIT(TCCR2,6);
  SET_BIT(TCCR2,3);
  #elif TIMER2_MODE == FAST_PWM_MODE
  SET_BIT(TCCR2,6);
  SET_BIT(TCCR2,3);
  #endif	
  
  /* configure compare output mode */
  #if    TIMER2_COMPARE_OUT_MODE== OC2_DISCONNECTED
  CLR_BIT(TCCR2,4);
  CLR_BIT(TCCR2,5);
  #elif  COMPARE_OUT_MODE== TOGG_OC2_ON_COMP_MATCH
  SET_BIT(TCCR2,4);
  CLR_BIT(TCCR2,5);
  #elif  COMPARE_OUT_MODE== CLR_OC2_ON_COMP_MATCH
  CLR_BIT(TCCR2,4);
  SET_BIT(TCCR2,5);
  #elif  COMPARE_OUT_MODE== SET_OC2_ON_COMP_MATCH
  SET_BIT(TCCR2,4);
  SET_BIT(TCCR2,5);
  #endif  
  
  /* configure oc2 pin  */
  #if OC2_STATUS == OC2_ENABLED
  MDIO_voidSetPinDirection(DIOD,7,OUTPUT); // set PB3 as output pin
  #endif  
  
/* Set OCR2 with a value if needed   */  


}

void MTIMER2_voidEnableInterrupt(void)
{
	MINT_voidSetGlobalInterrupt();
	
	#if   TIMER2_MODE == OVER_FLOW_MODE
	SET_BIT(TIMSK,6);  //enable interrupt in case of overflow
	#elif TIMER0_MODE == CTC_MODE
	SET_BIT(TIMSK,7); //enable interrupt in case of compare match
	#endif
}