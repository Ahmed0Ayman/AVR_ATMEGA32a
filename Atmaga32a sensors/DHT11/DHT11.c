
/*
 * DHT11.c
 *
 * Created: 5/8/2021 5:15:32 PM
 *  Author: Ahmed_Ayman
 */ 

#include "DHT11.h"



/* used by this module to control GPIO operation */
PRIVATE GPIO_InitTypeDef DHT11_GPIOPin ;

/* DHT11_ReadedByte static variable hold the readed value to shared between moules */
PRIVATE uint8_t DHT11_ReadedByte ;


/* 
 *brief : this function used to read one byte from DHT
 *parameter Handler : handler to DHT sensor 
 * return : void 
 */
PRIVATE void  DHT11_READ_DATA(DHT11_Handler_t * Handler);

/*
 * brief : this function used to read the response state from the DHT sensor if response is not readed the return DHT11_ERROR 
 * parameter Handler : handler to DHT sensor 
 *return : status of the readed response state 
*/
PRIVATE DHT11_Status DHT11_GET_RESP(DHT11_Handler_t * Handler);




/*
 * brief : this function used to read the response state from the DHT sensor if response is not readed the retrun DHT11_ERROR 
 * parameter Handler : handler to DHT sensor 
 *return : status of the resded response state 
*/
PRIVATE DHT11_Status DHT11_GET_RESP(DHT11_Handler_t * Handler)
{
	DHT11_Status Status ;
	/* set the GPIO configuration */
	DHT11_GPIOPin.mode = GPIO_MODE_OUTPUT ;
	DHT11_GPIOPin.pinS = Handler->GPIO_PIN_NUM ;
	HAL_GPIO_INIT_PIN(Handler->PORT ,&DHT11_GPIOPin);
	/* first write start pulse */
	HAL_GPIO_WRITEPIN(Handler->PORT ,Handler->GPIO_PIN_NUM ,GPIO_PIN_RESET);
	_delay_ms(18);
	HAL_GPIO_WRITEPIN(Handler->PORT ,Handler->GPIO_PIN_NUM ,GPIO_PIN_SET);
	_delay_us(20);
	
	/* now we try to read the response if their is now response the the DHT11 not detected and return error */
	DHT11_GPIOPin.mode = GPIO_MODE_INPUT ;
	HAL_GPIO_INIT_PIN(Handler->PORT ,&DHT11_GPIOPin);
	/* delay 40 Us to sample the response if the pin is readed as zero then the sensor is response successfully */
	_delay_us(40);
	if(!HAL_GPIO_READPIN(Handler->PORT ,Handler->GPIO_PIN_NUM))
	{
	Status = DHT11_OK ;
	_delay_us(120); 
	}
	else{        /* return error to the caller */
	Status = DHT11_Error ;
	}
	
	return Status ;
}/* END_FUN DHT11_GET_RESP() */





/* 
 *brief : this function used to read one byte from DHT
 *parameter Handler : handler to DHT sensor 
 * return : void 
 */
PRIVATE void  DHT11_READ_DATA(DHT11_Handler_t * Handler)
{
	DHT11_Status Status ;
	DHT11_ReadedByte =0 ; /* set to zero before read the new byte */
	for (uint8_t iterator = 0 ;iterator <8 ;iterator++) /* iterate for 8 time */
	{
     while(!HAL_GPIO_READPIN(Handler->PORT ,Handler->GPIO_PIN_NUM));	
	 _delay_us(30);
	 if(HAL_GPIO_READPIN(Handler->PORT ,Handler->GPIO_PIN_NUM))
	 {
		 DHT11_ReadedByte |= (1<<(7-iterator));
     while(HAL_GPIO_READPIN(Handler->PORT ,Handler->GPIO_PIN_NUM));		/* wait until the positive pulse is end */ 
	 }
	 
	 
	}
	
}/* END_FUN DHT11_READ_DATA() */





/* 
 * brief : this function is used to read the DHT sensor through one fuction call 
 * parameter Handler : handler to DHT sensor
 * return : status of the read operation 
 */
PUBLIC DHT11_Status DHT_GET_Measurements(DHT11_Handler_t * Handler)
{
	DHT11_Status Status ;
	Status = DHT11_GET_RESP(Handler);
	if (Status == DHT11_Error )
	{
		return DHT11_Error ;
	}else{
		DHT11_READ_DATA(Handler);   /* first read equal the Temp decimal */
		Handler->Temp =  DHT11_ReadedByte;
		DHT11_READ_DATA(Handler);   /* second read equal integrate Temp */
		DHT11_READ_DATA(Handler);   /* third read equal the humidity in decimal */
		Handler->HU   = DHT11_ReadedByte;
		DHT11_READ_DATA(Handler);   /* forth read equal integrate humidity */
		DHT11_READ_DATA(Handler);	/* fifth read equal CRC */	
		return DHT11_OK ;           /* return OK if the readed data is performed successfully */
	}
	
	

}/* END_FUN DHT_GET_Measurements() */
