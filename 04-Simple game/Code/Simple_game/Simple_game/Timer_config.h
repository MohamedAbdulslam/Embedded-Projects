/*
 * Timer_config.h
 *
 * Created: 3/26/2023 2:16:15 PM
 *  Author: mohamed abdelslam
 */ 


#ifndef TIMER_CONFIG_H_
#define TIMER_CONFIG_H_

/* options for timer0 mode: 
  OVER_FLOW_MODE
  PHASE_CORRECT_PWM_MODE
  CTC_MODE
  FAST_PWM_MODE
 */
#define TIMER0_MODE    CTC_MODE  

/* options for timer0 clock
NO_CLOCK_SOURCE
CPU_CLOCK
CPU_DIV_BY_8
CPU_DIV_BY_64
CPU_DIV_BY_256
CPU_DIV_BY_1024
EXTERNAL_FALLING_EDGE
EXTERNAL_RISING_EDEG
 */
#define TIMER0_CLOCK     CPU_DIV_BY_1024     

#endif /* TIMER_CONFIG_H_ */