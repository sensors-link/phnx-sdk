/**
  ******************************************************************************
  * @file    lptimer.c
  * @author  yongda.wang
  * @version 0.2
  * @date    2022-09-09
  * @brief   This file provides all the LPTIMER firmware functions.
  ******************************************************************************
  * @attention
  *
  * @copyright Fanhai Data Tech. (c) 2022
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "lptimer.h"
#include "sysc.h"

/** @addtogroup FDV32F003_StdPeriph_Driver
  * @{
  */

/** @defgroup LPTIMER
  * @brief LPTIMER driver modules
  * @{
  */

/** @defgroup LPTIMER_Private_Functions
  * @{
  */

/**
  * @brief  Initializes the LPT peripheral according to the specified parameters
  *         in the LPT_InitStruct.
  * @param  LPT_InitStruct: pointer to an LPT_InitTypeDef structure that
  *         contains the configuration information for the LPT peripheral.
  * @retval None
  */
void LPT_Init(LPT_InitTypeDef *LPT_InitStruct)
{
	/* Check the parameters */
	PARAM_CHECK(IS_LPT_PRESCALER(LPT_InitStruct->LPT_Prescaler));
	PARAM_CHECK(IS_LPT_COUNT_MODE(LPT_InitStruct->LPT_CntMode));

	/* Set the Prescaler value */
	LPTIM->CR &= ~LPTIM_CR_PS;
	LPTIM->CR |= LPT_InitStruct->LPT_Prescaler << LPTIM_CR_PS_pos;

	/* Set LPTIMER count mode */
	if (LPT_InitStruct->LPT_CntMode == LPT_CNT_MODE_SING)
	{
		/* Set LPT to normal count mode */
		LPTIM->CR &= ~LPTIM_CR_PITE;
	}
	else
	{
		/* Set LPT to PIT cycle count mode */
		LPTIM->CR |= LPTIM_CR_PITE;
	}

	/* Configure count/timing value configuration register CFG */
	LPTIM->CFG = LPT_InitStruct->LPT_Period;
}

/**
  * @brief  Get the current count value of LPTIMER.
  * @param  None
  * @retval Counter Register value.
  */
u16 LPT_GetCount(void)
{
	u16 tempreg1 = 0, tempreg2 = 0;

	while (1)
	{
		/* Get the count value from the count value register CNT */
		tempreg1 = LPTIM->CNT & LPTIM_CNT_CNT;
		tempreg2 = LPTIM->CNT & LPTIM_CNT_CNT;

		/* Exit after reading the same value twice in a row */
		if (tempreg1 == tempreg2)
			break;
	}

	/* Return current count value */
	return tempreg1;
}

/**
  * @brief  Enables or disables the specified LPT peripheral.
  * @param  NewState: New state of the LPT peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LPT_Cmd(FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable LPTIMER Counter */
		LPTIM->CR |= LPTIM_CR_EN;
	}
	else
	{
		/* Disable LPTIMER Counter */
		LPTIM->CR &= ~LPTIM_CR_EN;
	}
}

/**
  * @brief  Enables or disables the specified LPT interrupt.
  * @param  NewState: new state of the specified LPT interrupt.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LPT_ITConfig(FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable the LPT interrupt */
		LPTIM->CR |= LPTIM_CR_IE;
	}
	else
	{
		/* Disable the LPT interrupt */
		LPTIM->CR &= ~LPTIM_CR_IE;
	}
}

/**
  * @brief  Checks whether the specified LPT flag is set or not.
  * @param  None
  * @retval The new state of LPTIMER flag (SET or RESET).
  */
FlagStatus LPT_GetFlagStatus(void)
{
	FlagStatus bitstatus = RESET;

	/* Check the status of the LPT flag */
	if (LPTIM->INTSTS & LPTIM_INTSTS_STS)
	{
		/* LPTIMER flag is set */
		bitstatus = SET;
	}
	else
	{
		/* LPTIMER flag is reset */
		bitstatus = RESET;
	}
	/* Return the LPTIMER flag status */
	return bitstatus;
}

/**
  * @brief  Checks whether the specified LPT interrupt has occurred or not.
  * @param  None
  * @retval The new state of LPTIMER interrupt (SET or RESET).
  */
ITStatus LPT_GetITStatus(void)
{
	ITStatus bitstatus = RESET;

	/* Check the status of the LPT interrupt */
	if ((LPTIM->CR & LPTIM_CR_IE) && (LPTIM->INTSTS & LPTIM_INTSTS_STS))
	{
		/* LPTIMER interrupt is set */
		bitstatus = SET;
	}
	else
	{
		/* LPTIMER interrupt is reset */
		bitstatus = RESET;
	}
	/* Return the LPTIMER interrupt status */
	return bitstatus;
}

/**
  * @brief  Clear the pending flag for LPT.
  * @param  None
  * @retval None
  */
void LPT_ClearFlag(void)
{
	/* Clear the LPTIMER flags */
	LPTIM->INTSTS = LPTIM_INTSTS_STS;
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

