/*
 * DS1305_RTC.c
 *
 * Created: 8/24/2021 7:29:40 PM
 * Author : Ahmed_Ayman
 */ 

#include <avr/io.h>
#include "RTC.h"
#include "S7egmant.h"


#define S7eg_ControlBit0     0x0u
#define S7eg_ControlBit1     0x1u
#define S7eg_ControlBit2     0x2u
#define S7eg_ControlBit3     0x3u
#define S7eg_ControlBit4     0x4u
#define S7eg_ControlBit5     0x5u


#define S7eg_Bit0			 0x0u
#define S7eg_Bit1			 0x1u
#define S7eg_Bit2			 0x2u
#define S7eg_Bit3			 0x3u

#define F_CPU 16000000 
#include "util/delay.h"

Time_Typedef  Time ={.Hours =10 ,.Minutes = 20 ,.RTC_Time_Format = RTC_Format_BIN },gettime ={.RTC_Time_Format = RTC_Format_BIN};
Date_Typedef  Date ={.Day = 1 ,.Year = 20,.month = 11,.RTC_Time_Format = RTC_Format_BIN};

Seg7_Handler S7egHendler = {
	
	/* each bit has two attributes Port and Pin number */
	.S7eg_Bits[S7eg_Bit0].Port = GPIOC ,
	.S7eg_Bits[S7eg_Bit0].Pin_Num = GPIO_PIN_4 ,
	.S7eg_Bits[S7eg_Bit1].Port = GPIOC ,
	.S7eg_Bits[S7eg_Bit1].Pin_Num = GPIO_PIN_5 ,
	.S7eg_Bits[S7eg_Bit2].Port = GPIOC ,
	.S7eg_Bits[S7eg_Bit2].Pin_Num = GPIO_PIN_6 ,
	.S7eg_Bits[S7eg_Bit3].Port = GPIOC ,
	.S7eg_Bits[S7eg_Bit3].Pin_Num = GPIO_PIN_7 ,


	.S7eg_Control[S7eg_ControlBit0].Port = GPIOA ,
	.S7eg_Control[S7eg_ControlBit0].Pin_Num = GPIO_PIN_0 ,
	.S7eg_Control[S7eg_ControlBit1].Port = GPIOA ,
	.S7eg_Control[S7eg_ControlBit1].Pin_Num = GPIO_PIN_1 ,
	.S7eg_Control[S7eg_ControlBit2].Port = GPIOA ,
	.S7eg_Control[S7eg_ControlBit2].Pin_Num = GPIO_PIN_2,
	.S7eg_Control[S7eg_ControlBit3].Port = GPIOA ,
	.S7eg_Control[S7eg_ControlBit3].Pin_Num = GPIO_PIN_3 ,
	.S7eg_Control[S7eg_ControlBit4].Port = GPIOA ,
	.S7eg_Control[S7eg_ControlBit4].Pin_Num = GPIO_PIN_4 ,
	.S7eg_Control[S7eg_ControlBit5].Port = GPIOA ,
	.S7eg_Control[S7eg_ControlBit5].Pin_Num = GPIO_PIN_5 ,

	
	
};


int main(void)
{
	DS1305_Init();
	S7egment_Init(&S7egHendler);
	RTC_Set_Time(&Time);
	RTC_Set_Date(&Date);
	
	//InterrutInt();
	//EXIT_INT0_CallBack(NULL);
	
	
	//	xBinarySemaSETTask =  xSemaphoreCreateBinary();
	//	XQueueSETTask      = xQueueCreate(1,sizeof(Set_Message ));
	
	
	
	//xTaskCreate(MainTask,NULL,400,NULL,1,NULL);//&MainTaskhandler);
	//xTaskCreate(SETTask,NULL,100,NULL,0,NULL);
	
	
	//vTaskStartScheduler();


	/* Replace with your application code */
	while (1)
	{
		RTC_Get_Time(&gettime);
		
		
		S7egment_Write(gettime.Hours  , 0,&S7egHendler);
		S7egment_Write(gettime.Minutes ,2,&S7egHendler);
		S7egment_Write(gettime.Seconds ,4,&S7egHendler);
		
	}
}

