/*
 * Ultrasonic.c
 *
 * Created: 1/7/2022 8:21:19 PM
 *  Author: Ahmed_Ayman
 */ 
#include "Ultrasonic.h"





PRIVATE uint16_t HighValue ;
PRIVATE uint8_t status ;


PRIVATE Ultrs_Status_t  Ultrasonic_Start(	Ultrasonic_GPIOPINS_t * Ultrasonic_PINS );



void UltrasonicTrigger(Ultrasonic_GPIOPINS_t * Ultrasonic_PINS );




void StartUltrsinocTregger(void );




static TIMInit_t UltrasonicTIM_Handler = { .Instance = TIM1 , .TIMMode = TIM_Mode_InputCapture , .TimPreScaler = TIM_1_Prescaler_8};
	
	
	

Ultrs_Status_t Ultrasonic_Init(	Ultrasonic_GPIOPINS_t * Ultrasonic_PINS )
{
	GPIO_InitTypeDef   PIN_CONFIG = {.mode = GPIO_MODE_OUTPUT , .pin = Ultrasonic_PINS->TRIGGER_PIN.PINNum ,.pull = GPIO_NOPULL };
	
	if(Ultrasonic_PINS == NULL)
	{
		return Ultrasonic_PARAM_ERROR ; 
		
	}
	else
	{
		HAL_GPIO_INIT_PIN(Ultrasonic_PINS->TRIGGER_PIN.PORT , &PIN_CONFIG);
		PIN_CONFIG.mode = GPIO_MODE_INPUT ;
		PIN_CONFIG.pin = Ultrasonic_PINS->ECO_PIN.PINNum ; 
		HAL_GPIO_INIT_PIN(Ultrasonic_PINS->ECO_PIN.PORT , &PIN_CONFIG);
		
		TIM_InputCaptureModeInit(TIM16Bit_InputCapture_CAPTURE_EDGE_Rising);
		TIM_CallBack_FuctionSet(TIM_1_IT_CAPT ,  StartUltrsinocTregger);
		_TIM_IT_EN(TIM_1_IT_CAPT);
		sei();
	}
	
		return Ultrasonic_OK ;
}


void UltrasonicTrigger(Ultrasonic_GPIOPINS_t * Ultrasonic_PINS )
{

	HAL_GPIO_WRITEPIN(Ultrasonic_PINS->TRIGGER_PIN.PORT,Ultrasonic_PINS->TRIGGER_PIN.PINNum,GPIO_PIN_SET);
	_delay_us(10);///triggering the sensor for 10usec
	HAL_GPIO_WRITEPIN(Ultrasonic_PINS->TRIGGER_PIN.PORT,Ultrasonic_PINS->TRIGGER_PIN.PINNum,GPIO_PIN_RESET);
	
}



Ultrs_Status_t Ultrasonic_Start(Ultrasonic_GPIOPINS_t * Ultrasonic_PINS )
{
	
	TIM_Start(&UltrasonicTIM_Handler);

	UltrasonicTrigger(Ultrasonic_PINS);

	return Ultrasonic_OK ; 
	
}






Ultrs_Status_t Ultrasonic_GetDistance(float * Distance ,Ultrasonic_GPIOPINS_t * Ultrasonic_PINS )
{
	
	if(Distance == NULL)
	{
		return Ultrasonic_PARAM_ERROR ;
	}
	else
	{

		Ultrasonic_Start(Ultrasonic_PINS);
		while (status != 1);
		*Distance = (HighValue ) * 0.034/4 ;
	}
	return Ultrasonic_OK ;

}








void StartUltrsinocTregger(void )
{
	PRIVATE uint8_t  Edge = 0 ;
	if(Edge == 0)
	{
		TCNT1 = 0x00;
		TIM_InputCaptureModeInit(TIM16Bit_InputCapture_CAPTURE_EDGE_Falling);
		Edge = 1  ;
		status = 0;
	}
	else
	{
		TIM_InputCaptureModeInit(TIM16Bit_InputCapture_CAPTURE_EDGE_Rising);
		HighValue =  ICR1 ;
		Edge = 0   ;
		status = 1 ;
		
	}




		TIFR = (1<<ICF1);		/* clear capture flag */
}


