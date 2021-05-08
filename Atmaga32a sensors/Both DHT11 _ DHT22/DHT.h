
/*
 * DHT22.h
 *
 * Created: 5/8/2021 5:15:45 PM
 *  Author: Ahmed_Ayman
 */ 


#ifndef __DHT__
#define __DHT__

#define F_CPU 8000000
#include <util/delay.h>
#include <stdint.h>
#include "HAL_GPIO.h"


#define DHT11 0


#if DHT11 
typedef float    ITEM_TYPE ;
#else
typedef uint8_t ITEM_TYPE ;
#endif




 
typedef struct 
{
	ITEM_TYPE Temp ;            /* hold the read temperature  */
	ITEM_TYPE HU ;             /* hold the read humidity  */
	uint8_t GPIO_PIN_NUM ;   /* must be value from one of GPIO_PIN_ */
	GPIO_TypeDef * PORT ;
}DHT_Handler_t;  /* handler hold all configuration and data on DHT  */


typedef enum 
{
DHT_OK =0,
DHT_Error 	
}DHT_Status; /* enum for DHT status */


#define PRIVATE static 
#define PUBLIC  



/* 
 * brief : this function is used to read the DHT sensor through one fuction call 
 * parameter Handler : handler to DHT sensor
 * return : status of the read operation 
 */
PUBLIC DHT_Status DHT_GET_Measurements(DHT_Handler_t * Handler);


#endif 