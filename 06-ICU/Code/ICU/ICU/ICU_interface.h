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


u8 ICU_Calculate_DutyCycle(u16 *PtrCopy_u16Freq, u16 *ptrCopy_u16Duty);
void LCD_Display_DutyCycle_Freq(u16 Duty_Cycle,u16 Frequency,u8 Status);
#endif /* ICU_INTERFACE_H_ */