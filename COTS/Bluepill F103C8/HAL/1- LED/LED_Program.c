

/*******************************************************************************
 *                        		Inclusions                                     *
 *******************************************************************************/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/stm32f103xx.h"

#include "../../MCAL/RCC/RCC_interface.h"
#include "../../MCAL/GPIO/GPIO_interface.h"
#include "LED_Interface.h"

/*******************************************************************************
 *                      Functions Definitions                                   *
 *******************************************************************************/

/*******************************************************************************
 * Function Name:		LED_init
 ********************************************************************************/
u8 LED_init(LED_NUM led)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;

	if(led>= LA0 && led <= LA15)
	{
		RCC_u8EnableDisablPeripheralClk(RCC_u8_GPIOA, RCC_u8_Enable);
		GPIO_u8SetPinMode(GPIO_u8_GPIOA,led % 16, GPIO_u8_OUTPUT_GP_PP_50MHZ);
		GPIO_u8WritePinValue(GPIO_u8_GPIOA,led % 16, GPIO_u8_LOW);
	}
	else if(led>= LB0 && led <= LB15)
	{
		RCC_u8EnableDisablPeripheralClk(RCC_u8_GPIOB, RCC_u8_Enable);
		GPIO_u8SetPinMode(GPIO_u8_GPIOB,led % 16, GPIO_u8_OUTPUT_GP_PP_50MHZ);
		GPIO_u8WritePinValue(GPIO_u8_GPIOB,led % 16, GPIO_u8_LOW);
	}
	else if(led>= LC13 && led <= LC15)
	{
		RCC_u8EnableDisablPeripheralClk(RCC_u8_GPIOC, RCC_u8_Enable);
		GPIO_u8SetPinMode(GPIO_u8_GPIOC,led % 16, GPIO_u8_OUTPUT_GP_PP_50MHZ);
		GPIO_u8WritePinValue(GPIO_u8_GPIOC,led % 16, GPIO_u8_LOW);
	}
	return Local_u8ErrorState;
}

/*******************************************************************************
 * Function Name:		LED_ON
 ********************************************************************************/
u8 LED_ON(LED_NUM led)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if(led>= LA0 && led <= LA15)
	{
		GPIO_u8WritePinValue(GPIO_u8_GPIOA,led % 16, GPIO_u8_HIGH);
	}
	else if(led>= LB0 && led <= LB15)
	{
		GPIO_u8WritePinValue(GPIO_u8_GPIOB,led % 16, GPIO_u8_HIGH);
	}
	else if(led>= LC13 && led <= LC15)
	{
		GPIO_u8WritePinValue(GPIO_u8_GPIOC,led % 16, GPIO_u8_HIGH);
	}
	return Local_u8ErrorState;
}


/*******************************************************************************
 * Function Name:		LED_OFF
 ********************************************************************************/
u8 LED_OFF(LED_NUM led)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if(led>= LA0 && led <= LA15)
	{
		GPIO_u8WritePinValue(GPIO_u8_GPIOA,led % 16, GPIO_u8_LOW);
	}
	else if(led>= LB0 && led <= LB15)
	{
		GPIO_u8WritePinValue(GPIO_u8_GPIOB,led % 16, GPIO_u8_LOW);
	}
	else if(led>= LC13 && led <= LC15)
	{
		GPIO_u8WritePinValue(GPIO_u8_GPIOC,led % 16, GPIO_u8_LOW);
	}
	return Local_u8ErrorState;
}




/*******************************************************************************
 * Function Name:		LED_TOG
 ********************************************************************************/
u8 LED_TOG(LED_NUM led)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;

	if(led>= LA0 && led <= LA15)
	{
		GPIO_u8TogPinValue(GPIO_u8_GPIOA,led % 16);
	}
	else if(led>= LB0 && led <= LB15)
	{
		GPIO_u8TogPinValue(GPIO_u8_GPIOB,led % 16);
	}
	else if(led>= LC13 && led <= LC15)
	{
		GPIO_u8TogPinValue(GPIO_u8_GPIOC,led % 16);
	}
	return Local_u8ErrorState;
}

