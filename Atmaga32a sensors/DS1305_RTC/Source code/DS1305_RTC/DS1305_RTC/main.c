/*
 * DS1305_RTC.c
 *
 * Created: 8/24/2021 7:29:40 PM
 * Author : Ahmed_Ayman
 */ 

#include <avr/io.h>
#include "RTC.h"
#include "S7egmant.h"

#define F_CPU 16000000 
#include "util/delay.h"

Time_Typedef  Time ={.Hours =10 ,.Minutes = 20 ,.RTC_Time_Format = RTC_Format_BIN },gettime ={.RTC_Time_Format = RTC_Format_BIN};
Date_Typedef  Date ={.Day = 1 ,.Year = 20,.month = 11,.RTC_Time_Format = RTC_Format_BIN};
int main(void)
{
	uint8_t num =0 ;
	DS1305_Init();

	S7egment_Init(GPIOD ,GPIOB, 0X3F);
	S7egment_Write(7 ,GPIO_PIN_0);
	RTC_Set_Time(&Time);
	RTC_Set_Date(&Date);
    /* Replace with your application code */
    while (1) 
    {	
		RTC_Get_Time(&gettime);
		
		
		S7egment_Write(gettime.Hours ,GPIO_PIN_0);
		S7egment_Write(gettime.Minutes ,GPIO_PIN_2);
		S7egment_Write(gettime.Seconds ,GPIO_PIN_4);

		 //RTC_Set_Time(&Time);
    }
}

