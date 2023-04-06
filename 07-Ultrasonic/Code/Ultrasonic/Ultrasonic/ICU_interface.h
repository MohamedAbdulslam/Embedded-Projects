/*
 * ICU_interface.h
 *
 * Created: 4/5/2023 11:25:35 AM
 *  Author: mohamed abdelslam
 */ 


#ifndef ICU_INTERFACE_H_
#define ICU_INTERFACE_H_

#define OUT_OF_RANGE   0
#define IN_RANGE       1

/* Function name        : ICU_Calculate_DutyCycle
   Function description : Calculate duty cycle and frequency of PWM signal 
   Function arguments   : u16 *PtrCopy_u16Freq, u16 *ptrCopy_u16Duty
   Function returns     : u8
*/
u8 ICU_Calculate_DutyCycle(u16 *PtrCopy_u16Freq, u16 *ptrCopy_u16Duty);

/* Function name        : LCD_Display_DutyCycle_Freq
   Function description : Display duty cycle and frequency on LCD  
   Function arguments   : u16 Duty_Cycle,u16 Frequency,u8 Status
   Function returns     : void
*/
void LCD_Display_DutyCycle_Freq(u16 Duty_Cycle,u16 Frequency,u8 Status);

/* Function name        : Ultrasonic_u8GetDistance
   Function description : Get the distance of specific opject 
   Function arguments   : void
   Function returns     : u8
*/
u8 Ultrasonic_u8GetDistance(void);

/* Function name        : LCD_voidDisplayUltrasonicDistance
   Function description : Display the distance in LCD 
   Function arguments   : u8 distance
   Function returns     : void
*/
void LCD_voidDisplayUltrasonicDistance(u8 distance);
#endif /* ICU_INTERFACE_H_ */