/*
 * KedPad.c
 *
 * Created: 5/5/2021 11:20:00 AM
 *  Author: Ahmed_Ayman
 */ 


#include  "KeyPad.h"


/* gpio structure used by this file to handle all gpio functions */
static GPIO_InitTypeDef KeyPad_gpio ;



/*
 * brief  : this function used to initialize keypad
 * param. : KeyPadInit pointer to the handler of keypad
 * return : void 
 */
void KeyPad_Initialization(KeyPad_Handler * KeyPadInit)
{
    /* for output pins  --> all colomn will set as autput pins*/
	KeyPad_gpio.mode = GPIO_MODE_OUTPUT ;
	KeyPad_gpio.pull = GPIO_NOPULL ;
	
	KeyPad_gpio.pinS = KeyPadInit->PortColumn1.PinNum ;
	HAL_GPIO_INIT_PIN( KeyPadInit->PortColumn1.Port,&KeyPad_gpio);
	
	KeyPad_gpio.pinS = KeyPadInit->PortColumn2.PinNum ;
	HAL_GPIO_INIT_PIN( KeyPadInit->PortColumn2.Port,&KeyPad_gpio);

	KeyPad_gpio.pinS = KeyPadInit->PortColumn3.PinNum ;
	HAL_GPIO_INIT_PIN( KeyPadInit->PortColumn3.Port,&KeyPad_gpio);
#if(__Keypad_4_4_)
	KeyPad_gpio.pinS = KeyPadInit->PortColumn4.PinNum ;
	HAL_GPIO_INIT_PIN( KeyPadInit->PortColumn4.Port,&KeyPad_gpio);
#endif
    /* for input pins  ----> all rows will set as input pins */
	KeyPad_gpio.mode = GPIO_MODE_INPUT ;
	KeyPad_gpio.pull = GPIO_NOPULL ;
	
	KeyPad_gpio.pinS = KeyPadInit->PortRow1.PinNum ;
	HAL_GPIO_INIT_PIN( KeyPadInit->PortRow1.Port,&KeyPad_gpio);
	
	KeyPad_gpio.pinS = KeyPadInit->PortRow2.PinNum ;
	HAL_GPIO_INIT_PIN( KeyPadInit->PortRow2.Port,&KeyPad_gpio);

	KeyPad_gpio.pinS = KeyPadInit->PortRow3.PinNum ;
	HAL_GPIO_INIT_PIN( KeyPadInit->PortRow3.Port,&KeyPad_gpio);

	KeyPad_gpio.pinS = KeyPadInit->PortRow4.PinNum ;
	HAL_GPIO_INIT_PIN( KeyPadInit->PortRow4.Port,&KeyPad_gpio);

	
}/* END_FUN KeyPad_Initialization()*/


/*
 * brief  : this function used to return the pressed key 
 * param. : void
 * return : pressed character 
 */
char GetPressedKey(KeyPad_Handler * KeyPadInit)
{
	char Key =0;
	
	HAL_GPIO_WRITEPIN(KeyPadInit->PortColumn3.Port,KeyPadInit->PortColumn3.PinNum,GPIO_PIN_SET);  /*  set first column as high */
	if(HAL_GPIO_READPIN(KeyPadInit->PortRow1.Port,KeyPadInit->PortRow1.PinNum)) Key = '3';        /* read all rows */
	if(HAL_GPIO_READPIN(KeyPadInit->PortRow2.Port,KeyPadInit->PortRow2.PinNum)) Key = '6';
	if(HAL_GPIO_READPIN(KeyPadInit->PortRow3.Port,KeyPadInit->PortRow3.PinNum)) Key = '9';
	if(HAL_GPIO_READPIN(KeyPadInit->PortRow4.Port,KeyPadInit->PortRow4.PinNum)) Key = '#';
	HAL_GPIO_WRITEPIN(KeyPadInit->PortColumn3.Port,KeyPadInit->PortColumn3.PinNum,GPIO_PIN_RESET);
	if(Key > 0)  return Key ;    /* if there is any pressed key detected the terminate and return pressed key to the caller */
	
	HAL_GPIO_WRITEPIN(KeyPadInit->PortColumn2.Port,KeyPadInit->PortColumn2.PinNum,GPIO_PIN_SET);     /*  set second column as high */
	if(HAL_GPIO_READPIN(KeyPadInit->PortRow1.Port,KeyPadInit->PortRow1.PinNum)) Key = '2';			/* read all rows */
	if(HAL_GPIO_READPIN(KeyPadInit->PortRow2.Port,KeyPadInit->PortRow2.PinNum)) Key = '5';
	if(HAL_GPIO_READPIN(KeyPadInit->PortRow3.Port,KeyPadInit->PortRow3.PinNum)) Key = '8';
	if(HAL_GPIO_READPIN(KeyPadInit->PortRow4.Port,KeyPadInit->PortRow4.PinNum)) Key = '0';
	HAL_GPIO_WRITEPIN(KeyPadInit->PortColumn2.Port,KeyPadInit->PortColumn2.PinNum,GPIO_PIN_RESET);
	if(Key > 0) return Key ;		/* if there is any pressed key detected the terminate and return pressed key to the caller */
	
	HAL_GPIO_WRITEPIN(KeyPadInit->PortColumn1.Port,KeyPadInit->PortColumn1.PinNum,GPIO_PIN_SET);    /*  set third column as high */
	if(HAL_GPIO_READPIN(KeyPadInit->PortRow1.Port,KeyPadInit->PortRow1.PinNum)) Key = '1';         /* read all rows */
	if(HAL_GPIO_READPIN(KeyPadInit->PortRow2.Port,KeyPadInit->PortRow2.PinNum)) Key = '4';
	if(HAL_GPIO_READPIN(KeyPadInit->PortRow3.Port,KeyPadInit->PortRow3.PinNum)) Key = '7';
	if(HAL_GPIO_READPIN(KeyPadInit->PortRow4.Port,KeyPadInit->PortRow4.PinNum)) Key = '*';
	HAL_GPIO_WRITEPIN(KeyPadInit->PortColumn1.Port,KeyPadInit->PortColumn1.PinNum,GPIO_PIN_RESET);
	if(Key > 0)  return Key ;	  /* if there is any pressed key detected the terminate and return pressed key to the caller */
	
#if (__Keypad_4_4_)
	HAL_GPIO_WRITEPIN(KeyPadInit->PortColumn4.Port,KeyPadInit->PortColumn4.PinNum,GPIO_PIN_SET);       /*  set third column as high only in case keypad 4*4 */
	if(HAL_GPIO_READPIN(KeyPadInit->PortRow1.Port,KeyPadInit->PortRow1.PinNum)) Key = 'A';            /* read all rows */
	if(HAL_GPIO_READPIN(KeyPadInit->PortRow2.Port,KeyPadInit->PortRow2.PinNum)) Key = 'B';
	if(HAL_GPIO_READPIN(KeyPadInit->PortRow3.Port,KeyPadInit->PortRow3.PinNum)) Key = 'C';
	if(HAL_GPIO_READPIN(KeyPadInit->PortRow4.Port,KeyPadInit->PortRow4.PinNum)) Key = 'D';
	HAL_GPIO_WRITEPIN(KeyPadInit->PortColumn4.Port,KeyPadInit->PortColumn4.PinNum,GPIO_PIN_RESET);
	if(Key > 0)  return Key ;    /* if there is any pressed key detected the terminate and return pressed key to the caller */
#endif

}/* END_FUN GetPressedKey()*/