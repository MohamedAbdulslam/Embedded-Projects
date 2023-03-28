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

/* timer 0 clock prescaler */
#define NO_CLOCK_SOURCE                  0
#define CPU_CLOCK                        1
#define CPU_DIV_BY_8                     2
#define CPU_DIV_BY_64                    3
#define CPU_DIV_BY_256                   4
#define CPU_DIV_BY_1024                  5
#define EXTERNAL_FALLING_EDGE            6
#define EXTERNAL_RISING_EDEG             7

/* timer 2 clock prescaler */
#define NO_CLOCK_SOURCE                           0
#define TIMER2_SOURCE_CLOCK                       1
#define TIMER2_SOURCE_CLOCK_DIV_BY_8              2
#define TIMER2_SOURCE_CLOCK_DIV_BY_32             3
#define TIMER2_SOURCE_CLOCK_DIV_BY_64             4
#define TIMER2_SOURCE_CLOCK_DIV_BY_128            5
#define TIMER2_SOURCE_CLOCK_DIV_BY_256            6
#define TIMER2_SOURCE_CLOCK_DIV_BY_1024           7

/* compare output mode options for timer 0 */
#define OC0_DISCONNECTED                 0
#define TOGG_OC0_ON_COMP_MATCH           1  // only for non PWM modes
#define CLR_OC0_ON_COMP_MATCH            2
#define SET_OC0_ON_COMP_MATCH            3

/* compare output mode options for timer 2 */
#define OC2_DISCONNECTED                 0
#define TOGG_OC2_ON_COMP_MATCH           1  // only for non PWM modes
#define CLR_OC2_ON_COMP_MATCH            2
#define SET_OC2_ON_COMP_MATCH            3
/* OC0 status options */
#define OC0_ENABLED            0
#define OC0_DISABLED           1

/* OC2 status options */
#define OC2_ENABLED            0
#define OC2_DISABLED           1

/* options for timer2 clock source types*/
#define  CPU_CLOCK                         0
#define  EXTERNAL_CRYSTAL_ON_TOSC1         1  

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

/* Function name        : MTIMER2_voidInit
   Function description : configure clock and modes of timer2
   Function arguments   : void
   Function returns     : void
*/
void MTIMER2_voidInit(void);

/* Function name        : MTIMER2_voidEnableInterrupt
   Function description : enable specific interrupt for timer 2
   Function arguments   : void
   Function returns     : void
*/
void MTIMER2_voidEnableInterrupt(void);

#endif /* TIMER_INTERFACE_H_ */