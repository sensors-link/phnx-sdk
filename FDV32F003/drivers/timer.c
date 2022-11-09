/**
  ******************************************************************************
  * @file    timer.c
  * @author  yongda.wang
  * @version 0.2
  * @date    2022-09-23
  * @brief   This file provides all the TIM firmware functions.
  ******************************************************************************
  * @attention
  *
  * @copyright Fanhai Data Tech. (c) 2022
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "timer.h"
#include "sysc.h"

/** @addtogroup FDV32F003_StdPeriph_Driver
  * @{
  */

/** @defgroup TIM
  * @brief TIM driver modules
  * @{
  */

/** @defgroup TIM_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the TIMx peripheral registers to their default reset values.
  * @param  TIMx: where x can be 1 to 4 to select the TIM peripheral.
  * @retval None
  */
void TIM_DeInit(TIM_TypeDef *TIMx)
{
	/* Check the parameters */
	PARAM_CHECK(IS_TIM_ALL_PERIPH(TIMx));

	if (TIMx == TIM1)
	{
		/* Reset the TIM1 module settings */
		SYSC_ResetPeripher(SYSC_RESET_MOUDLE_TIM1);
	}
	else if (TIMx == TIM2)
	{
		/* Reset the TIM2 module settings */
		SYSC_ResetPeripher(SYSC_RESET_MOUDLE_TIM2);
	}
	else if (TIMx == TIM3)
	{
		/* Reset the TIM3 module settings */
		SYSC_ResetPeripher(SYSC_RESET_MOUDLE_TIM3);
	}
	else if (TIMx == TIM4)
	{
		/* Reset the TIM6 module settings */
		SYSC_ResetPeripher(SYSC_RESET_MOUDLE_TIM4);
	}
}

/**
  * @brief  Deinitializes the TIM0 peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void TIM_T0DeInit(void)
{
	/* Reset the TIM0 module settings */
	SYSC_ResetPeripher(SYSC_RESET_MOUDLE_TIM0);
}

/**
  * @brief  Initializes the TIMx Time Base Unit peripheral according to 
  *         the specified parameters in the TIM_BaseInitStruct.
  * @param  TIMx: where x can be 1 to 4 to select the TIM peripheral.
  * @param  TIM_BaseInitStruct: pointer to a TIM_BaseInitTypeDef structure
  *         that contains the configuration information for the specified TIM peripheral.
  * @retval None
  */
void TIM_BaseInit(TIM_TypeDef *TIMx, TIM_BaseInitTypeDef *TIM_BaseInitStruct)
{
	/* Check the parameters */
	PARAM_CHECK(IS_TIM_ALL_PERIPH(TIMx));
	PARAM_CHECK(IS_TIM_PRESCALER(TIM_BaseInitStruct->TIM_Prescaler));

	/* Set the TIMx input clock predivision value */
	TIMx->TCR &= ~TIM_TCR_TCKS;
	TIMx->TCR |= TIM_BaseInitStruct->TIM_Prescaler << TIM_TCR_TCKS_pos;

	/* Set preset values for TIMx peripherals */
	TIMx->PWMPD &= ~TIM_PWMPD_PWMPD;
	TIMx->PWMPD |= TIM_BaseInitStruct->TIM_PresetValue << TIM_PWMPD_PWMPD_pos;

	/* Set TIMx to timing mode */
	TIMx->TCR &= ~TIM_TCR_TCS;

	/* Set TIMx to disable PWM */
	TIMx->TCR &= ~TIM_TCR_PWMON;
}

/**
  * @brief  Initialize the TIMx PWM function according to the 
  *	        parameters specified in TIM_PWMInitStruct.
  * @param  TIMx: where x can be 1 to 4 to select the TIM peripheral.
  * @param  TIM_PWMInitStruct: Pointer to a TIM_PWMInitTypeDef structure 
  *         containing configuration information for the specified TIM PWM.
  * @retval None
  */
void TIM_PWMInit(TIM_TypeDef *TIMx, TIM_PWMInitTypeDef *TIM_PWMInitStruct)
{
	/* Check the parameters */
	PARAM_CHECK(IS_TIM_ALL_PERIPH(TIMx));
	PARAM_CHECK(IS_TIM_PRESCALER(TIM_PWMInitStruct->TIM_Prescaler));

	/* Set the TIMx input clock predivision value */
	TIMx->TCR &= ~TIM_TCR_TCKS;
	TIMx->TCR |= TIM_PWMInitStruct->TIM_Prescaler << TIM_TCR_TCKS_pos;

	/* Set the PWM period for the TIMx peripheral */
	TIMx->PWMPD &= ~TIM_PWMPD_PWMPD;
	TIMx->PWMPD |= TIM_PWMInitStruct->TIM_PWMPeriod << TIM_PWMPD_PWMPD_pos;

	/* Set the PWM duty cycle for the TIMx peripheral */
	TIMx->PWMDC &= ~TIM_PWMDC_PWMDC;
	TIMx->PWMDC |= TIM_PWMInitStruct->TIM_PWMDuty << TIM_PWMDC_PWMDC_pos;

	/* Set TIMx to timing mode */
	TIMx->TCR &= ~TIM_TCR_TCS;

	/* Set TIMx to enable PWM */
	TIMx->TCR |= TIM_TCR_PWMON;
}

/**
  * @brief  Initialize the TIMx external pulse count according to the 
  *         parameters specified in TIM_CountInitStruct.
  * @param  TIMx: where x can be 1 to 4 to select the TIM peripheral.
  * @param  TIM_CountInitStruct: Pointer to a TIM_CountInitTypeDef structure containing 
  *         external pulse count configuration information for the specified TIM peripheral.
  * @retval None
  */
void TIM_CountInit(TIM_TypeDef *TIMx, TIM_CountInitTypeDef *TIM_CountInitStruct)
{
	/* Check the parameters */
	PARAM_CHECK(IS_TIM_ALL_PERIPH(TIMx));

	/* Set overflow values for TIMx peripherals */
	TIMx->PWMPD &= ~TIM_PWMPD_PWMPD;
	TIMx->PWMPD |= TIM_CountInitStruct->TIM_OverValue << TIM_PWMPD_PWMPD_pos;

	/* Set TIMx to count mode */
	TIMx->TCR |= TIM_TCR_TCS;

	/* Set TIMx to disable PWM */
	TIMx->TCR &= ~TIM_TCR_PWMON;
}

/**
  * @brief  Initializes the TIM0 Time Base Unit peripheral according to 
  *         the specified parameters in the TIM_T0InitStruct.
  * @param  TIM_T0InitStruct: pointer to a TIM_T0InitTypeDef structure
  *         that contains the configuration information for the TIM0 peripheral.
  * @retval None
  */
void TIM_T0Init(TIM_T0InitTypeDef *TIM_T0InitStruct)
{
	/* Check the parameters */
	PARAM_CHECK(IS_TIM_T0_PRESCALER(TIM_T0InitStruct->TIM_T0Prescaler));
	PARAM_CHECK(IS_FUNCTIONAL_STATE(TIM_T0InitStruct->TIM_ReloadCmd));

	/* Set the TIM0 input clock predivision value */
	if(TIM_T0InitStruct->TIM_T0Prescaler > 0)
	{
		TIMERS->T0CR &= ~TIM_T0CR_PSA;
		TIMERS->T0CR &= ~TIM_T0CR_PS;
		TIMERS->T0CR |= (TIM_T0InitStruct->TIM_T0Prescaler - 1) << TIM_T0CR_PS_pos;
	}
	else
	{
		TIMERS->T0CR |= TIM_T0CR_PSA;
	}

	if(TIM_T0InitStruct->TIM_ReloadCmd == ENABLE)
	{
		/* Enable TIM0 overload */
		TIMERS->T0CR |= TIM_T0CR_T0RLDEN;
	}
	else
	{
		/* Disnable TIM0 overload */
		TIMERS->T0CR &= ~TIM_T0CR_T0RLDEN;
	}

	/* Set reload values for TIM0 peripherals */
	TIMERS->T0RLD &= ~TIM_T0RLD_T0RLD;
	TIMERS->T0RLD |= TIM_T0InitStruct->TIM_ReloadValue << TIM_T0RLD_T0RLD_pos;
}

/**
  * @brief  Set the edge trigger type of TIMx interrupt pulse.
  * @param  TIMx: where x can be 1 to 4 to select the TIM peripheral.
  * @param  IntTriggerType: Specifies the type of interrupt edge trigger.
  *   This parameter can be one of the following values:
  *     @arg TIM_INT_TRIGGER_FALL: Falling edge trigger
  *     @arg TIM_INT_TRIGGER_RISE: Rising edge trigger
  * @retval None
  */
void TIM_SetIntTriggerType(TIM_TypeDef *TIMx, u8 IntTriggerType)
{
	/* Check the parameters */
	PARAM_CHECK(IS_TIM_INTTRIGGER_TYPE(IntTriggerType));

	if (IntTriggerType == TIM_INT_TRIGGER_FALL)
	{
		/* Set falling edge trigger interrupt */
		TIMx->TCR &= ~TIM_TCR_INTSE;	
	}
	else
	{
		/* Set rising edge trigger interrupt */
		TIMx->TCR |= TIM_TCR_INTSE;
	}
}

/**
  * @brief  Enable or disable the gating of selected TIM peripherals.
  * @param  TIMx: where x can be 1 to 4 to select the TIMx peripheral.
  * @param  NewState: The new state of the selected TIM peripheral gating.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TIM_GatingCmd(TIM_TypeDef *TIMx, FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_TIM_ALL_PERIPH(TIMx));
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable the gating of selected TIM peripherals */
		TIMx->TCR |= TIM_TCR_TGC;
	}
	else
	{
		/* Disable the gating of selected TIM peripherals */
		TIMx->TCR &= ~TIM_TCR_TGC;
	}
}

/**
  * @brief  Enables or disables the specified TIM peripheral.
  * @param  TIMx: where x can be 1 to 4 to select the TIMx peripheral.
  * @param  NewState: new state of the TIMx peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TIM_Cmd(TIM_TypeDef *TIMx, FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_TIM_ALL_PERIPH(TIMx));
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable the specified TIM peripheral */
		TIMx->TCR |= TIM_TCR_TON;
	}
	else
	{
		/* Disable the specified TIM peripheral */
		TIMx->TCR &= ~TIM_TCR_TON;
	}
}

/**
  * @brief  Enables or disables the TIM0 peripheral.
  * @param  NewState: new state of the TIM0 peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TIM_T0Cmd(FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable the specified TIM0 peripheral */
		TIMERS->T0CR |= TIM_T0CR_T0EN;
	}
	else
	{
		/* Disable the specified TIM0 peripheral */
		TIMERS->T0CR &= ~TIM_T0CR_T0EN;
	}
}

/**
  * @brief  Enables or disables the specified TIM interrupts.
  * @param  TIM_IT: specifies the TIM interrupt sources to be enabled or disabled.
  *   This parameter can be any combination of the following values:
  *     @arg TIM_IT_T4IE: TIM4 interrupt or PWM4 interrupt
  *     @arg TIM_IT_T3IE: TIM3 interrupt or PWM3 interrupt
  *     @arg TIM_IT_T2IE: TIM2 interrupt or PWM2 interrupt
  *     @arg TIM_IT_T1IE: TIM1 interrupt or PWM1 interrupt
  *     @arg TIM_IT_T0IE: TIM0 interrupt
  * @param  NewState: new state of the specified TIM interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TIM_ITConfig(u32 TIM_IT, FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_TIM_CONFIG_IT(TIM_IT));
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable the selected TIM interrupts */
		TIMERS->TIE |= TIM_IT;
	}
	else
	{
		/* Disable the selected TIM interrupts */
		TIMERS->TIE &= ~TIM_IT;
	}
}

/**
  * @brief  Checks whether the specified TIM flag is set or not.
  * @param  TIM_FLAG: specifies the flag to check.
  *   This parameter can be one of the following values:
  *     @arg TIM_FLAG_T4IF: TIM4 overflow interrupt flag
  *     @arg TIM_FLAG_T3IF: TIM3 overflow interrupt flag
  *     @arg TIM_FLAG_T2IF: TIM2 overflow interrupt flag
  *     @arg TIM_FLAG_T1IF: TIM1 overflow interrupt flag
  *     @arg TIM_FLAG_T0IF: TIM0 overflow interrupt flag
  * @retval The new state of TIM_FLAG (SET or RESET).
  */
FlagStatus TIM_GetFlagStatus(u16 TIM_FLAG)
{
	FlagStatus bitstatus = RESET;

	/* Check the parameters */
	PARAM_CHECK(IS_TIM_GET_FLAG(TIM_FLAG));

	/* Check the status of the TIM flag */
	if (TIMERS->TIF & TIM_FLAG)
	{
		/* TIM_FLAG is set */
		bitstatus = SET;
	}
	else
	{
		/* TIM_FLAG is reset */
		bitstatus = RESET;
	}
	/* Return the TIM_FLAG status */
	return bitstatus;
}

/**
  * @brief  Checks whether the specified TIM interrupt has occurred or not.
  * @param  TIM_IT: specifies the TIM interrupt source to check.
  *   This parameter can be one of the following values:
  *     @arg TIM_IT_T4IE: TIM4 interrupt or PWM4 interrupt
  *     @arg TIM_IT_T3IE: TIM3 interrupt or PWM3 interrupt
  *     @arg TIM_IT_T2IE: TIM2 interrupt or PWM2 interrupt
  *     @arg TIM_IT_T1IE: TIM1 interrupt or PWM1 interrupt
  *     @arg TIM_IT_T0IE: TIM0 interrupt
  * @retval The new state of TIM_IT (SET or RESET).
  */
ITStatus TIM_GetITStatus(u32 TIM_IT)
{
	ITStatus bitstatus = RESET;

	/* Check the parameters */
	PARAM_CHECK(IS_TIM_GET_IT(TIM_IT));

	/* Check the status of the specified TIM interrupt */
	if ((TIMERS->TIE & TIM_IT) && (TIMERS->TIF & TIM_IT))
	{
		/* TIM_IT is set */
		bitstatus = SET;
	}
	else
	{
		/* TIM_IT is reset */
		bitstatus = RESET;
	}
	/* Return the TIM_IT status */
	return bitstatus;
}

/**
  * @brief  Clear the pending flag for TIM.
  * @param  TIM_FLAG: specifies the flag to clear.
  *   This parameter can be any combination of the following values:
  *     @arg TIM_FLAG_T4IF: TIM4 overflow interrupt flag
  *     @arg TIM_FLAG_T3IF: TIM3 overflow interrupt flag
  *     @arg TIM_FLAG_T2IF: TIM2 overflow interrupt flag
  *     @arg TIM_FLAG_T1IF: TIM1 overflow interrupt flag
  *     @arg TIM_FLAG_T0IF: TIM0 overflow interrupt flag
  * @retval None
  */
void TIM_ClearFlag(u16 TIM_FLAG)
{
	/* Check the parameters */
	PARAM_CHECK(IS_TIM_CLEAR_FLAG(TIM_FLAG));

	/* Clear the selected TIM flags */
	TIMERS->TIF = TIM_FLAG;
}

/**
  * @brief  Sets the TIMx Counter Register value
  * @param  TIMx: where x can be 1 to 4 to select the TIM peripheral.
  * @param  Counter: specifies the Counter register new value.
  * @retval None
  */
void TIM_SetCounter(TIM_TypeDef *TIMx, u16 Counter)
{
	/* Check the parameters */
	PARAM_CHECK(IS_TIM_ALL_PERIPH(TIMx));

	/* Set the Counter Register value */
	TIMx->TN = Counter;
}

/**
  * @brief  Gets the TIMx Counter value.
  * @param  TIMx: where x can be 1 to 4 to select the TIM peripheral.
  * @retval Counter Register value.
  */
u16 TIM_GetCounter(TIM_TypeDef *TIMx)
{
	/* Check the parameters */
	PARAM_CHECK(IS_TIM_ALL_PERIPH(TIMx));
	
	/* Get the Counter Register value */
	return (u16)TIMx->TN;
}

/**
  * @brief  Sets the TIM0 Counter Register value
  * @param  Counter: specifies the Counter register new value.
  * @retval None
  */
void TIM_SetT0Counter(u8 Counter)
{
	/* Set the Counter Register value */
	TIMERS->T0 = Counter;
}

/**
  * @brief  Gets the TIM0 Counter value.
  * @param  None
  * @retval Counter Register value.
  */
u8 TIM_GetT0Counter(void)
{
	/* Get the Counter Register value */
	return (u8)TIMERS->T0;
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

