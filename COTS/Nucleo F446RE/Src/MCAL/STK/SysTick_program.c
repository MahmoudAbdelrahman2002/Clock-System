

/********************************************************************************************/
/* Include libraries                                                                        */
/********************************************************************************************/
#include <stdint.h>
#include <stdio.h>

#include "../../LIB/Utils.h"
#include "../../LIB/Stm32F466xx.h"
#include "../../LIB/ErrorType.h"


/******************************************************************************/
/************************ MCAL Layer ******************************************/
/******************************************************************************/
#include "SysTick_private.h"
#include "SysTick_config.h"
#include "SysTick_interface.h"

/******************************************************************************/
/*************************** Global *******************************************/
/******************************************************************************/
static uint8_t STK_u8IntervalType=PERIODIC;
static void (* SysTick_CallBack)(void) = NULL;

/*************************************************************************************************************************************/
/********************************************************* Functions implementations *************************************************/
/*************************************************************************************************************************************/
/**
 ******************************************************************************
 * @fn             : MSTK_u8ClockConfig
 * @brief          : Set STK Clock
 * @param[in]      : Copy_ClockType --> get option from @STKclock_t  enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t MSTK_u8ClockConfig              ( STKclock_t Copy_ClockType )
{
	uint8_t Local_u8ErrorState= OK;
	if ( Copy_ClockType <= STK_AHB )
	{
		STK->CTRL &=~(STK_CLKSOURCE_MASK << STK_CTRL_CLKSOURCE );
		STK->CTRL |= (Copy_ClockType << STK_CTRL_CLKSOURCE );
	}
	else
	{
		Local_u8ErrorState= NOK;
	}
	return Local_u8ErrorState ;

}
/**
 ******************************************************************************
 * @fn             : MSTK_voidStopTimer
 * @brief          : Stop Counter
 * @param          : void
 * @retval         : void
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
void   MSTK_voidStopTimer         ( void )
{
	    STK->CTRL &=~(STK_STOP_TIMER_MASK << STK_CTRL_ENABLE );
		STK->LOAD = STK_RESET_COUNTER;
		STK->VAL  = STK_RESET_COUNTER;
}
/**
 ******************************************************************************
 * @fn             : MSTK_u8BusyWait
 * @brief          : Busy Wait Counter
 * @param[in]      : Copy_u32Ticks --> Set Number of ticks  uint32_t
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MSTK_u8BusyWait            ( uint32_t Copy_u32Ticks )
{
	 uint8_t Local_u8ErrorState =  OK ;
	 if ( Copy_u32Ticks <= STK_MAX_TICKS)
	 {
	     STK->LOAD =  2*(Copy_u32Ticks*1000) - 1 ;
	     STK->CTRL |= (STK_ENABLE_MASK << STK_CTRL_ENABLE );
	     while ( STK_LOW_FLAG == GET_BIT( STK->CTRL , STK_CTRL_COUNTFLAG ));
	     MSTK_voidStopTimer();
	 }
	 else
	 {
		 Local_u8ErrorState =  NOK ;
	 }
	 return Local_u8ErrorState ;
}
/**
 ******************************************************************************
 * @fn             : STK_u8Delayms
 * @brief          : Delay Timer
 * @param[in]      : Copy_u32TimeMs --> Set time in Ms    uint32_t
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 * STK Clock Must be STK_AHB_DIV_8
 *
 ******************************************************************************
 */
uint8_t   STK_u8Delayms            ( uint32_t Copy_u32TimeMs )
{
	uint8_t Local_u8ErrorState =  OK ;
	 if ( Copy_u32TimeMs <= STK_MAX_TIME_MS)
	 {
		 /* convert from ms to us as
		  * 1 ms = 900 us */
		 Copy_u32TimeMs *= STK_CONVERT_US_TO_MS;
		 MSTK_u8BusyWait(Copy_u32TimeMs);
	 }
	 else
	 {
		 Local_u8ErrorState =  NOK ;
	 }
	 return Local_u8ErrorState ;
}
/**
 ******************************************************************************
 * @fn             : MSTK_u8SetInterval
 * @brief          : Set Interval Counter
 * @param[in]      : Copy_u32Ticks -->  Set Number of ticks  uint32_t
 * @param[in]      : Copy_IntervalType --> get option from @Interval_t  enum
 * @param[  ]      : Copy_pFun         --> Set Call back function
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MSTK_u8SetInterval   ( uint32_t Copy_u32Ticks , Interval_t Copy_IntervalType ,void (* Copy_pFun)(void) )
{
	uint8_t Local_u8ErrorState =  OK ;
	 if ( Copy_u32Ticks <= STK_MAX_TICKS && Copy_pFun != NULL && Copy_IntervalType<= PERIODIC )
	 {
		 STK->CTRL &=~ (STK_ENABLE_MASK << STK_CTRL_ENABLE );
		 STK->VAL =STK_RESET_COUNTER ;

		 STK_u8IntervalType = Copy_IntervalType ;
	     STK->LOAD = Copy_u32Ticks ;
	     STK->CTRL |=  (STK_ENABLE_MASK << STK_CTRL_ENABLE );
	     SysTick_CallBack = Copy_pFun ;
	     STK->CTRL |=  (STK_INT_MASK << STK_CTRL_TICKINT );
	 }
	 else
	 {
		 Local_u8ErrorState =  NOK ;
	 }
	 return Local_u8ErrorState ;

}
/**
 ******************************************************************************
 * @fn             : MSTK_voidStopInterval
 * @brief          : Stop Interval
 * @param          : void
 * @retval         : void
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
void   MSTK_voidStopInterval         ( void )
{
	STK->CTRL &=~ (STK_INT_MASK << STK_CTRL_TICKINT );
	STK->CTRL |=  (STK_ENABLE_MASK << STK_CTRL_ENABLE );
	STK -> LOAD = STK_RESET_COUNTER;
	STK -> VAL  = STK_RESET_COUNTER;
}
/**
 ******************************************************************************
 * @fn             : MSTK_u8GetElapsedTime
 * @brief          : Get Elapsed Counter
 * @param[OUT]     : Copy_pu32Ticks -->  Get Number of ticks  uint32_t
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MSTK_u8GetElapsedTime      ( uint32_t * Copy_pu32Ticks )
{
	uint8_t Local_u8ErrorState =  OK ;
	 if ( Copy_pu32Ticks != NULL )
	 {
		 *Copy_pu32Ticks = ( (STK->LOAD) - (STK->VAL) );
	 }
	 else
	 {
		 Local_u8ErrorState =  NOK ;
	 }
	 return Local_u8ErrorState ;
}
/**
 ******************************************************************************
 * @fn             : MSTK_u8GetReminingTime
 * @brief          : Get Remaining Counter
 * @param[OUT]     : Copy_pu32Ticks -->  Get Number of ticks  uint32_t
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MSTK_u8GetRemainingTime     ( uint32_t * Copy_pu32Ticks )
{
	uint8_t Local_u8ErrorState =  OK ;
	 if ( Copy_pu32Ticks != NULL )
	 {
	     *Copy_pu32Ticks = ( STK->VAL ) ;
	 }
	 else
	 {
		 Local_u8ErrorState =  NOK ;
	 }
	 return Local_u8ErrorState ;
}

/**
 ******************************************************************************
 * @fn             : SysTick_Handler
 * @brief          : ISR for  SysTick
 * @param          : void
 * @retval         : void
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
void SysTick_Handler (void)
{
    if ( SysTick_CallBack != NULL)
    {
         if ( SINGLE == STK_u8IntervalType )
         {
        	 SysTick_CallBack();
        	 MSTK_voidStopTimer();
         }
         else if ( PERIODIC == STK_u8IntervalType )
         {
        	 SysTick_CallBack();
         }
    }
}
