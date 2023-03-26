/*
 * Timer_interface.h
 *
 * Created: 3/26/2023 2:15:59 PM
 *  Author: mohamed abdelslam
 */ 


#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

/* timer modes */
#define  OVER_FLOW_MODE                  0
#define  PHASE_CORRECT_PWM_MODE          1
#define  CTC_MODE                        2
#define  FAST_PWM_MODE                   3

/* timer clock prescaler */
#define NO_CLOCK_SOURCE                  0
#define CPU_CLOCK                        1
#define CPU_DIV_BY_8                     2
#define CPU_DIV_BY_64                    3
#define CPU_DIV_BY_256                   4
#define CPU_DIV_BY_1024                  5
#define EXTERNAL_FALLING_EDGE            6
#define EXTERNAL_RISING_EDEG             7

/* Function name        : MTIMER0_voidInit
   Function description : configure clock and modes of timer0
   Function arguments   : void
   Function returns     : void
*/
void MTIMER0_voidInit(void);

/* Function name        : MTIMER0_voidEnableInterrupt
   Function description : enable specific interrupt for timer 0
   Function arguments   : void
   Function returns     : void
*/
void MTIMER0_voidEnableInterrupt(void);




#endif /* TIMER_INTERFACE_H_ */