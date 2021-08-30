/*
 * _7Segmant.c
 *
 * Created: 8/26/2021 12:39:18 PM
 *  Author: Ahmed_Ayman
 */ 

#include "S7egmant.h"


static Seg7_Handler S7egment_Handler   ;


	
	
void S7egment_Init(GPIO_TypeDef * Control_S7eg_Port ,GPIO_TypeDef * Seg7_write_Port, uint8_t S7eg_Control_Pin)
{
		GPIO_InitTypeDef  S7eg_PIN_CONFIG ;
		S7eg_PIN_CONFIG.pinS = S7eg_Control_Pin ;
		S7eg_PIN_CONFIG.mode = GPIO_MODE_OUTPUT ;
		S7eg_PIN_CONFIG.pull = GPIO_NOPULL ;

	S7egment_Handler.Control_S7eg_Port = Control_S7eg_Port ;
	S7egment_Handler.Seg7_write_Port = Seg7_write_Port ;
	S7egment_Handler.Num_Of_7Seg = S7eg_Control_Pin;
	HAL_GPIO_INIT_PIN(S7egment_Handler.Control_S7eg_Port,&S7eg_PIN_CONFIG);
	S7eg_PIN_CONFIG.pinS = 0x0fu ;
	HAL_GPIO_INIT_PIN(S7egment_Handler.Seg7_write_Port,&S7eg_PIN_CONFIG);
	HAL_GPIO_WRITEPIN(S7egment_Handler.Control_S7eg_Port,S7eg_Control_Pin,0);
	
	
}
void S7egment_Write(uint8_t Num_To_S7eg , uint8_t S7eg_Num)
{
	uint8_t High_Num=0,Low_Num=0 ;
	Low_Num = Num_To_S7eg % 10 ;
	Num_To_S7eg /= 10 ;
	if (Num_To_S7eg > 0){
		High_Num = Num_To_S7eg % 10 ; 
	}else{
		High_Num = 0 ;
	}
	
	HAL_GPIO_WRITEPIN(S7egment_Handler.Control_S7eg_Port,S7egment_Handler.Num_Of_7Seg , 0);
	HAL_GPIO_WRITEPORT(S7egment_Handler.Seg7_write_Port,0x0f,High_Num ,0x0f);
	HAL_GPIO_WRITEPIN(S7egment_Handler.Control_S7eg_Port,S7eg_Num,1);
	_delay_ms(1);
	HAL_GPIO_WRITEPIN(S7egment_Handler.Control_S7eg_Port,S7egment_Handler.Num_Of_7Seg , 0);
	HAL_GPIO_WRITEPORT(S7egment_Handler.Seg7_write_Port,0x0f,Low_Num,0x0f);
	HAL_GPIO_WRITEPIN(S7egment_Handler.Control_S7eg_Port,S7eg_Num<<1 ,1);
	_delay_ms(10);	
}