
/*
 * DHT11.h
 *
 * Created: 5/8/2021 5:15:45 PM
 *  Author: Ahmed_Ayman
 */ 


#ifndef __DHT11__
#define __DHT11__

#define F_CPU 8000000
#include <util/delay.h>
#include <stdint.h>
#include "HAL_GPIO.h"


typedef struct 
{
	uint8_t Temp ;            /* hold the read temperature  */
	uint8_t HU ;             /* hold the read humidity  */
	uint8_t GPIO_PIN_NUM ;   /* must be value from one of GPIO_PIN_ */
	GPIO_TypeDef * PORT ;
}DHT11_Handler_t;  /* handler hold all configuration and data on DHT  */


typedef enum 
{
DHT11_OK =0,
DHT11_Error 	
}DHT11_Status; /* enum for DHT status */


#define PRIVATE static 
#define PUBLIC  



/* 
 * brief : this function is used to read the DHT sensor through one fuction call 
 * parameter Handler : handler to DHT sensor
 * return : status of the read operation 
 */
PUBLIC DHT11_Status DHT_GET_Measurements(DHT11_Handler_t * Handler);


#endif 