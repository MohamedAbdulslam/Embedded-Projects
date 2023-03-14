/*
 * Safe.c
 *
 * Created: 3/14/2023 3:59:39 PM
 *  Author: mohamed abdelslam
 */ 
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#define F_CPU 8000000UL
#include "DELAY.h"

#include "DIO_interface.h"
#include "EEPROM_interface.h"
#include "LCD_interface.h"
#include "KEYPAD_interface.h"

#define EEPROM_CHECK_LOCATION     0X10   // to check if the safe has password or first time 
#define EEPROM_PASSWORD_LOC1      0X11   //location of first number in password 
#define EEPROM_PASSWORD_LOC2      0X12   //location of second number in password
#define EEPROM_PASSWORD_LOC3      0X13   //location of third number in password
#define EEPROM_PASSWORD_LOC4      0X14   //location of fourth number in password
#define MAX_TRIAL                  3     //max trials to enter correct password
u8 Password_Arr[4];
int main(void)
{
	u8 data,i,flag=0;
	u8 trials=MAX_TRIAL;
    HLCD_voidInit(); //Initialize LCD
	HKEYPAD_voidInit(); //Initialize keypad
	
	if (  MEEPROM_voidRead(EEPROM_CHECK_LOCATION)==0XFF )  //if the location has 0xff value this means it is unprogrammed(first time)
	{
		HLCD_voidSendString("Set Password");
		HLCD_voidMoveCursor(2,1);
		for (i=0;i<=3;i++)
		{
		  do 
		  {
			data=HKEYPAD_u8Read();
		  } while (data==0xff);
		  HLCD_voidSendChar(data);
		  Delay_ms(800);
		  HLCD_voidMoveCursor(2,1+i);
		  HLCD_voidSendChar('*'); // for security
		  //Delay_ms(400);
		  MEEPROM_voidWrite(EEPROM_PASSWORD_LOC1+i,data);		  
		}
		
		MEEPROM_voidWrite(EEPROM_CHECK_LOCATION,0x00); // to set that it is not first time

	}
	
	while(flag==0)
	{
		HLCD_voidClearScreen();
		HLCD_voidSendString("Enter Password");
		HLCD_voidMoveCursor(2,1);
		for (i=0;i<=3;i++)
		{
			do
			{
				Password_Arr[i]=HKEYPAD_u8Read();
			} while (Password_Arr[i]==0xff);
			HLCD_voidSendChar(Password_Arr[i]);
			Delay_ms(800);
			HLCD_voidMoveCursor(2,1+i);
			HLCD_voidSendChar('*'); // for security
			//Delay_ms(400);
			
		}		
		
		if ( MEEPROM_voidRead(EEPROM_PASSWORD_LOC1) ==Password_Arr[0] && MEEPROM_voidRead(EEPROM_PASSWORD_LOC2) ==Password_Arr[1] && MEEPROM_voidRead(EEPROM_PASSWORD_LOC3) ==Password_Arr[2] && MEEPROM_voidRead(EEPROM_PASSWORD_LOC4) ==Password_Arr[3])
		{
			HLCD_voidClearScreen();
			HLCD_voidMoveCursor(1,1);
			HLCD_voidSendString("Correct Password");
			Delay_ms(1000);
			HLCD_voidClearScreen();
			HLCD_voidMoveCursor(1,1);
			HLCD_voidSendString("The safe is open");
			flag=1; 
		}
		else
		{
			trials--;
			if (trials>0)
			{
				HLCD_voidClearScreen();
				HLCD_voidSendString("Wrong Password");
				Delay_ms(1000);
				HLCD_voidClearScreen();
				HLCD_voidSendString("Left trials:");
				HLCD_voidSendChar(trials+48);
				Delay_ms(1000);
				
			}
			else
			{
				HLCD_voidClearScreen();
				HLCD_voidMoveCursor(1,1);
				HLCD_voidSendString("Wrong Password");
				HLCD_voidClearScreen();
				HLCD_voidMoveCursor(1,1);
				HLCD_voidSendString("The safe is closed");
				flag=1;
			}
		}
	}
	
	
	

}