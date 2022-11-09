/**
  ******************************************************************************
  * @file    adc.c
  * @author  yongda.wang
  * @version 0.2
  * @date    2022-10-27
  * @brief   This file provides all the ADC firmware functions.
  ******************************************************************************
  * @attention
  *
  * @copyright Fanhai Data Tech. (c) 2022
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "adc.h"
#include "sysc.h"

/** @addtogroup FDV32F003_StdPeriph_Driver
  * @{
  */

/** @defgroup ADC
  * @brief ADC driver modules
  * @{
  */

/** @defgroup ADC_Private_Defines
  * @{
  */

/* ADC_CFG register Mask */
#define ADC_CFG_CLEAR_Mask ((u32)0xFFFFFC07)

/**
  * @}
  */

/** @defgroup ADC_Private_Functions
  * @{
  */

/**
  * @brief  Deinitialize the ADC peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void ADC_DeInit(void)
{
	/* Reset the ADC module settings */
	SYSC_ResetPeripher(SYSC_RESET_MOUDLE_ADC);
}

/**
  * @brief  Initializes the ADC peripheral according to the specified parameters
  *         in the ADC_InitStruct.
  * @param  ADC_InitStruct: pointer to an ADC_InitTypeDef structure that contains
  *         the configuration information for the ADC peripheral.
  * @retval None
  */
void ADC_Init(ADC_InitTypeDef *ADC_InitStruct)
{
	u32 tempreg = 0;

	/* Check the parameters */
	PARAM_CHECK(IS_ADC_CHANNEL(ADC_InitStruct->ADC_Channel));
	PARAM_CHECK(IS_ADC_VREFSEL(ADC_InitStruct->ADC_VrefSel));
	PARAM_CHECK(IS_ADC_SMPCYCLE(ADC_InitStruct->ADC_SmpCycle));

	/*---------------------------- ADC_CFG Configuration ------------------------*/
	tempreg = ADC->CFG;
	/* Clear ADC_CFG initialization configuration bit */
	tempreg &= ADC_CFG_CLEAR_Mask;

	/* ADC input channel selection */
	tempreg |= ADC_InitStruct->ADC_Channel << ADC_CFG_CHSEL_pos;
	/* Set ADC input signal sample and hold time */
	tempreg |= ADC_InitStruct->ADC_SmpCycle << ADC_CFG_SMP_CYCLE_pos;

	/* ADC reference voltage input source input selection */
	if(ADC_InitStruct->ADC_VrefSel == ADC_VREF_SEL_VCC)
	{
		ADC->CFG |= ADC_CFG_VRSEL;
	}

	/* Write to ADC_CFG */
	ADC->CFG = tempreg;
}

/**
  * @brief  Returns the last ADC conversion result data for regular channel.
  * @param  None
  * @retval The Data conversion value.
  */
u16 ADC_GetConversionValue(void)
{
	/* Return the ADC conversion value */
	return (u16)ADC->DATA;
}

/**
  * @brief  Enables or disables the ADC software start conversion .
  * @param  NewState: new state of the ADC software start conversion.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_SoftwareStartConvCmd(FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable ADC software to initiate conversions */
		ADC->CFG |= ADC_CFG_SST;
	}
	else
	{
		/* Disable ADC software to initiate conversions */
		ADC->CFG &= ~ADC_CFG_SST;
	}
}

/**
  * @brief  Enable or disable the ADC peripheral.
  * @param  NewState: New state of the ADC peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_Cmd(FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable ADC peripheral */
		ADC->CFG |= ADC_CFG_ADC_EN;
	}
	else
	{
		/* Disable ADC peripheral */
		ADC->CFG &= ~ADC_CFG_ADC_EN;
	}
}

/**
  * @brief  Enables or disables the ADC interrupts.
  * @param  NewState: new state of the specified ADC interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_ITConfig(FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable the ADC interrupts */
		ADC->CFG |= ADC_CFG_ADC_IE;
	}
	else
	{
		/* Disable the ADC interrupts */
		ADC->CFG &= ~ADC_CFG_ADC_IE;
	}
}

/**
  * @brief  Checks whether the specified ADC flag is set or not.
  * @param  None
  * @retval The new state of ADC flag (SET or RESET).
  */
FlagStatus ADC_GetFlagStatus(void)
{
	FlagStatus bitstatus = RESET;

	/* Check the status of the ADC flag */
	if (ADC->CFG & ADC_INTF_INTF)
	{
		/* ADC flag is set */
		bitstatus = SET;
	}
	else
	{
		/* ADC flag is reset */
		bitstatus = RESET;
	}
	/* Return the ADC flag status */
	return bitstatus;
}

/**
  * @brief  Checks whether the specified ADC interrupt has occurred or not.
  * @param  None
  * @retval The new state of ADC interrupt (SET or RESET).
  */
ITStatus ADC_GetITStatus(void)
{
	ITStatus bitstatus = RESET;

	/* Check the status of the ADC interrupt */
	if ((ADC->CFG & ADC_CFG_ADC_IE) && (ADC->INTF & ADC_INTF_INTF))
	{
		/* ADC interrupt is set */
		bitstatus = SET;
	}
	else
	{
		/* ADC interrupt is reset */
		bitstatus = RESET;
	}
	/* Return the ADC interrupt status */
	return bitstatus;
}

/**
  * @brief  Clear the pending flag for ADC.
  * @param  None
  * @retval None
  */
void ADC_ClearFlag(void)
{
	/* Clear the ADC flags */
	ADC->INTF = ADC_INTF_INTF;
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

