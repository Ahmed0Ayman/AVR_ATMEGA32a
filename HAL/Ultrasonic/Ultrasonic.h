/*
 * Ultrasonic.h
 *
 * Created: 1/7/2022 8:21:36 PM
 *  Author: Ahmed_Ayman
 */ 


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_



#define  F_CPU 16000000
#include "util/delay.h"
#include "HAL_GPIO.h"

#include "TIMER_Interface.h"

typedef uint8_t PIN_TypeDef ;  

typedef enum {Ultrasonic_OK , Ultrasonic_PARAM_ERROR , Ultrasonic_CONFIG_ERROR }Ultrs_Status_t;


typedef struct 
{
	GPIO_TypeDef * PORT  ;
	PIN_TypeDef   PINNum ;
	
}Ultrasonic_pinConfig_t;


typedef struct
{
	Ultrasonic_pinConfig_t  ECO_PIN ;
	Ultrasonic_pinConfig_t  TRIGGER_PIN ;
	
}Ultrasonic_GPIOPINS_t;






Ultrs_Status_t Ultrasonic_Init(	Ultrasonic_GPIOPINS_t * Ultrasonic_PINS );













Ultrs_Status_t Ultrasonic_GetDistance(float *  Distance , Ultrasonic_GPIOPINS_t * Ultrasonic_PINS );







#endif /* ULTRASONIC_H_ */