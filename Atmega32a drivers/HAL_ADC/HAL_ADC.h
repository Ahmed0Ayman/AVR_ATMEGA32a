/*
 * ADC.h
 *
 * Created: 4/26/2021 5:16:10 PM
 *  Author: Ahmed_Ayman
 */ 
#include <stdint.h>
#include "HAL_GPIO.h"
#include "GPIO_TYPEDEF.h"
#include <avr/interrupt.h>


#define  PRIVATE static            /* file access only */
#define  PUBLIC                   /* client access */

typedef struct
{
	uint8_t ADC_TRIG_SOURCE ;		   /* select one value of  ADC_TRIG     _ */
	uint8_t ADC_PreScaler ;			  /* select one value of ADC_Presaler_  */
	uint8_t ADC_Adjust_Select ;		 /* select one value of ADC_Adjust_   */
	uint8_t ADC_Intrrupet_Select;	/* select one value of ADC_INIT_    */
	uint8_t ADC_Vref_Select ;	   /* select one value of ADC_Vref_   */
	float ADC_Value ;
	
}ADC_Handler_t;     /* struct used to hold all ADC configurations */




/* channel number select the user must select one of them */
#define ADC_CH_0					0x00u
#define ADC_CH_1					0x01u
#define ADC_CH_2					0x02u
#define ADC_CH_3					0x03u
#define ADC_CH_4					0x04u
#define ADC_CH_5					0x05u
#define ADC_CH_6					0x06u
#define ADC_CH_7					0x07u

/* prescaler select value as far as you know the ADC in ATMEGA32a work only in clock range 50K - 200K */
#define  ADC_Presaler_2			     0x01u
#define  ADC_Presaler_4		         0x02u
#define  ADC_Presaler_8				 0x03u
#define  ADC_Presaler_16		     0x04u
#define  ADC_Presaler_32	         0x05u
#define  ADC_Presaler_64			 0x06u
#define  ADC_Presaler_128			 0x07u

/* triger source select the user must select one of these */
#define  ADC_TRIG_FREE_RUNNING		 0x00u
#define  ADC_TRIG_ANALOG_COMP		 0x01u
#define  ADC_TRIG_EXTI_0			 0x02u
#define  ADC_TRIG_TIM0_COMP	         0x03u
#define  ADC_TRIG_TIM0_OV		     0x04u
#define  ADC_TRIG_TIM1_COMPB	     0x05u
#define  ADC_TRIG_TIM1_OV            0x06u
#define  ADC_TRIG_TIM1_IC_CAPTURE    0x07u

/* adjust value left or right select one of these */
#define ADC_Adjust_Left              0x20u
#define ADC_Adjust_Right  		     0x00u

#define  ADC_INIT_ENABLE             0x08u
#define  ADC_INIT_DISABLE            0x00u


/* hint if you try to use external voltage reference you will make a lite bit modification is this library */
#define  ADC_Vref_Intrnal2_56v       0xc0u
#define  ADC_Vref_AVCC               0x40u







/*
 * brief  : this function used to initialize ADC
 * param. : Handler pointer to the handler of ADC hold all configuration that done by user to initialize the ADC
 * return : void 
 */
PUBLIC void ADC_INIT(ADC_Handler_t *Handler);





/*
 * brief  : this function used to initialize keypad
 * param. : KeyPadInit pointer to the handler of keypad
 * return : void 
 */
PUBLIC void ADC_GET_VALUE(ADC_Handler_t *Handler,uint8_t AdcChannel);

