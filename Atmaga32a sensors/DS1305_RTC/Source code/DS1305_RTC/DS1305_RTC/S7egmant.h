/*
 * _7Segmant.h
 *
 * Created: 8/26/2021 12:39:28 PM
 *  Author: Ahmed_Ayman
 */ 

#include "HAL_GPIO.h"
#include "avr/io.h"
#define F_CPU 16000000
#include "util/delay.h"

#ifndef S7EGMANT_H_
#define S7EGMANT_H_

#define S7eg_One		0x01u
#define S7eg_Two		0x02u
#define S7eg_Three		0x03u
#define S7eg_Four		0x04u
#define S7eg_Five		0x05u

typedef struct {
	GPIO_TypeDef * Control_S7eg_Port;
	GPIO_TypeDef * Seg7_write_Port;
	uint8_t Num_Of_7Seg;
	}Seg7_Handler;

void S7egment_Init(GPIO_TypeDef * Control_S7eg_Port , GPIO_TypeDef * Seg7_write_Port,uint8_t Num_Of_7Seg);

void S7egment_Write(uint8_t Num , uint8_t S7eg_Num);



















#endif /* S7EGMANT_H_ */