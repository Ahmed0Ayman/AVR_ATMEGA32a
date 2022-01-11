/*
 * KeyPad.h
 *
 * Created: 5/5/2021 11:20:19 AM
 *  Author: Ahmed_Ayman
 */ 

#include <stdint.h>
#include "HAL_GPIO.h"
#include "stdbool.h"

#define __Keypad_4_4_    1    /* one means keypad 4*4 if set to zero means keypad 3*4 depending on our keypad characteristic */ 


typedef struct
{
	  GPIO_TypeDef * Port ;
	   uint8_t      PinNum ;
	
}KeyPad_PinTypeDef;      /* this struct used to hold the config of each pin of keypad */


/*
 * brief : this typedef struct is a handler to the keypad hold 
 * all required information a bout keypad so this function first 
 * need this handler to initialize the keypad
 */
typedef struct 
{
  KeyPad_PinTypeDef PortColumn1 ;
  KeyPad_PinTypeDef PortColumn2 ;
  KeyPad_PinTypeDef PortColumn3 ;

  KeyPad_PinTypeDef PortRow1 ;
  KeyPad_PinTypeDef PortRow2 ;
  KeyPad_PinTypeDef PortRow3 ;
  KeyPad_PinTypeDef PortRow4 ;
  
 #if(__Keypad_4_4_)    /* here this code will insert or removed depending on preprocessor configuration */
  KeyPad_PinTypeDef PortColumn4 ;

 #endif

}KeyPad_Handler;



/*
 * brief  : this function used to return the pressed key 
 * param. : KeyPadInit pointer to the handler of keypad
 * return : pressed character 
 */
char GetPressedKey(KeyPad_Handler * KeyPadInit);

/*
 * brief  : this function used to initialize keypad
 * param. : KeyPadInit pointer to the handler of keypad
 * return : void 
 */
void KeyPad_Initialization(KeyPad_Handler * KeyPadInit);