/**
  ******************************************************************************
  * @file    WDT.c
  * @author  yongda.wang
  * @version 0.2
  * @date    2022-09-27
  * @brief   This file provides all the WDT firmware functions.
  ******************************************************************************
  * @attention
  *
  * @copyright Fanhai Data Tech. (c) 2022
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "wdt.h"
#include "sysc.h"

/** @addtogroup FDV32S301_StdPeriph_Driver
  * @{
  */

/** @defgroup WDT
  * @brief WDT driver modules
  * @{
  */

/** @defgroup WDT_Private_Defines
  * @{
  */

/* The RST register of the WDT controls starting/clearing the watchdog */
#define WDT_RST_VALUE_0 (0x69)
#define WDT_RST_VALUE_1 (0x96)
/**
  * @}
  */

/** @defgroup WDT_Private_Functions
  * @{
  */

/**
  * @brief  Initializes the WDT peripheral according to the specified parameters
  *         in the WDT_InitStruct.
  * @param  WDT_InitStruct: pointer to an WDT_InitTypeDef structure that contains
  *         the configuration information for the WDT peripheral.
  * @retval None
  */
void WDT_Init(WDT_InitTypeDef *WDT_InitStruct)
{
	/* Check the parameters */
	PARAM_CHECK(IS_WDT_OVER_LOAD(WDT_InitStruct->WDT_OverValue));

	/* Set WDT overload value */
	WDT->CR &= ~WDT_CR_WOV;
	WDT->CR |= WDT_InitStruct->WDT_OverValue << WDT_CR_WOV_pos;
}

/**
  * @brief  Enables or disables the WDT interrupts.
  * @param  NewState: new state of the specified WDT interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void WDT_ITConfig(FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable the WDT interrupts */
		WDT->CR |= WDT_CR_INTEN;
	}
	else
	{
		/* Disable the WDT interrupts */
		WDT->CR &= ~WDT_CR_INTEN;
	}
}

/**
  * @brief  Checks whether the specified WDT flag is set or not.
  * @param  WDT_FLAG: specifies the flag to check.
  *   This parameter can be one of the following values:
  *     @arg WDT_FLAG_INTFLAG: WDT interrupt flag
  *     @arg WDT_FLAG_RUN: WDT running flag
  * @retval The new state of WDT_FLAG (SET or RESET).
  */
FlagStatus WDT_GetFlagStatus(u32 WDT_FLAG)
{
	FlagStatus bitstatus = RESET;

	/* Check the parameters */
	PARAM_CHECK(IS_WDT_GET_FLAG(WDT_FLAG));

	/* Check the status of the WDT flag */
	if (WDT->CR & WDT_FLAG)
	{
		/* WDT_FLAG is set */
		bitstatus = SET;
	}
	else
	{
		/* WDT_FLAG is reset */
		bitstatus = RESET;
	}
	/* Return the WDT_FLAG status */
	return bitstatus;
}

/**
  * @brief  Checks whether the specified WDT interrupt has occurred or not.
  * @param  None
  * @retval The new state of WDTIMER interrupt (SET or RESET).
  */
ITStatus WDT_GetITStatus(void)
{
	ITStatus bitstatus = RESET;

	/* Check the status of the WDT interrupt */
	if ((WDT->CR & WDT_CR_INTEN) && (WDT->CR & WDT_CR_INTFLAG))
	{
		/* WDT interrupt is set */
		bitstatus = SET;
	}
	else
	{
		/* WDT interrupt is reset */
		bitstatus = RESET;
	}
	/* Return the WDT interrupt status */
	return bitstatus;
}

/**
  * @brief  Clear the pending flag for WDT.
  * @param  None
  * @retval None
  */
void WDT_ClearFlag(void)
{
	/* Clear the WDT interrupt flags */
	WDT->RST = WDT_RST_VALUE_0;
	WDT->RST = WDT_RST_VALUE_1;
}

/**
  * @brief  Start the WDT count.
  * @param  None
  * @retval None
  */
void WDT_StartCount(void)
{
	/* Start the WDT count */
	WDT->RST = WDT_RST_VALUE_0;
	WDT->RST = WDT_RST_VALUE_1;
}

/**
  * @brief  Clear the WDT count.
  * @param  None
  * @retval None
  */
void WDT_ClearCount(void)
{
	/* Clear the WDT count */
	WDT->RST = WDT_RST_VALUE_0;
	WDT->RST = WDT_RST_VALUE_1;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2022 Fanhai Data Tech *****END OF FILE****/

