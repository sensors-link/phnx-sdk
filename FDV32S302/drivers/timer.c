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

/** @addtogroup FDV32S302_StdPeriph_Driver
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
  * @param  TIMx: where x can be 1 to 2 to select the TIM peripheral.
  * @retval None
  */
void TIM_DeInit(TIM_TypeDef *TIMx)
{
	/* Check the parameters */
	PARAM_CHECK(IS_TIM_ALL_PERIPH(TIMx));

	if (TIMx == TIM1)
	{
		/* Clear the state of the control register (CON) TIM1 */
		TIMERS->CON &= ~TIM_CON_TE_TIM1;
		TIMERS->CON &= ~TIM_CON_TM_TIM1;
		TIMERS->CON &= ~TIM_CON_IE_TIM1;
		TIMERS->CON &= ~TIM_CON_PWM_TIM1;
		TIMERS->CON &= ~TIM_CON_EXTEN_TIM1;
		TIMERS->CON &= ~TIM_CON_EXTPOL_TIM1;
		TIMERS->CON &= ~TIM_CON_PAUSE_TIM1;
	}
	else if (TIMx == TIM2)
	{
		/* Clear the state of the control register (CON) TIM2 */
		TIMERS->CON &= ~TIM_CON_TE_TIM2;
		TIMERS->CON &= ~TIM_CON_TM_TIM2;
		TIMERS->CON &= ~TIM_CON_IE_TIM2;
		TIMERS->CON &= ~TIM_CON_PWM_TIM2;
		TIMERS->CON &= ~TIM_CON_EXTEN_TIM2;
		TIMERS->CON &= ~TIM_CON_EXTPOL_TIM2;
		TIMERS->CON &= ~TIM_CON_PAUSE_TIM2;
	}

	/* Check all timers are enabled */
	if ((TIMERS->CON & TIM_CON_TE) == 0)
	{
		/* Reset the TIMER module settings */
		SYSC_ResetPeripher(SYSC_RESET_MOUDLE_TIMER);
	}
}

/**
  * @brief  Initializes the TIMx Time Base Unit peripheral according to 
  *         the specified parameters in the TIM_BaseInitStruct.
  * @param  TIMx: where x can be 1 to 2 to select the TIM peripheral.
  * @param  TIM_BaseInitStruct: pointer to a TIM_BaseInitTypeDef structure
  *         that contains the configuration information for the specified TIM peripheral.
  * @retval None
  */
void TIM_BaseInit(TIM_TypeDef *TIMx, TIM_BaseInitTypeDef *TIM_BaseInitStruct)
{
	/* Check the parameters */
	PARAM_CHECK(IS_TIM_ALL_PERIPH(TIMx));
	PARAM_CHECK(IS_TIM_RUN_MODE(TIM_BaseInitStruct->TIM_RunMode));

	if (TIMx == TIM1)
	{
		if (TIM_BaseInitStruct->TIM_RunMode == TIM_RUN_MODE_FREE_RUN)
		{
			/* Set TIM1 to free running mode */
			TIMERS->CON &= ~TIM_CON_TM_TIM1;
		}
		else
		{
			/* Set TIM1 to User Defined Mode */
			TIMERS->CON |= TIM_CON_TM_TIM1;
		}
	}
	else if (TIMx == TIM2)
	{
		/* Set the running mode of the TIMx */
		if (TIM_BaseInitStruct->TIM_RunMode == TIM_RUN_MODE_FREE_RUN)
		{
			/* Set TIM2 to free running mode */
			TIMERS->CON &= ~TIM_CON_TM_TIM2;
		}
		else
		{
			/* Set TIM2 to User Defined Mode */
			TIMERS->CON |= TIM_CON_TM_TIM2;
		}
	}

	/* Set preset values for TIMx peripherals */
	TIMx->CTCG1 = TIM_BaseInitStruct->TIM_PresetValue & 0xFFFF;
	TIMx->CTCG2 = TIM_BaseInitStruct->TIM_PresetValue >> 16;
}

/**
  * @brief  Initialize the TIMx PWM function according to the 
  *	        parameters specified in TIM_PWMInitStruct.
  * @param  TIMx: where x can be 1 to 2 to select the TIM peripheral.
  * @param  TIM_PWMInitStruct: Pointer to a TIM_PWMInitTypeDef structure 
  *         containing configuration information for the specified TIM PWM.
  * @retval None
  */
void TIM_PWMInit(TIM_TypeDef *TIMx, TIM_PWMInitTypeDef *TIM_PWMInitStruct)
{
	/* Check the parameters */
	PARAM_CHECK(IS_TIM_ALL_PERIPH(TIMx));
	PARAM_CHECK(IS_TIM_PWM_POL(TIM_PWMInitStruct->TIM_PWMPolarity));
	PARAM_CHECK(IS_FUNCTIONAL_STATE(TIM_PWMInitStruct->TIM_DTCmd));

	if (TIMx == TIM1)
	{
		/* Set TIM1 to User Defined Mode */
		TIMERS->CON |= TIM_CON_TM_TIM1;

		/* Enable PWM pulse width modulation */
		TIMERS->CON |= TIM_CON_PWM_TIM1;
	}
	else if (TIMx == TIM2)
	{
		/* Set TIM2 to User Defined Mode */
		TIMERS->CON |= TIM_CON_TM_TIM2;

		/* Enable PWM pulse width modulation */
		TIMERS->CON |= TIM_CON_PWM_TIM2;
	}

	/* Set PWM pulse high and low level width */
	TIMx->CTCG1 = TIM_PWMInitStruct->TIM_PWMLow;
	TIMx->CTCG2 = TIM_PWMInitStruct->TIM_PWMHigh;

	/* Set complementary TMR_TOG and TMR_TOGN polarity control */
	TIMx->PWCON &= ~TIM_PWCON_PWMCPOL;
	TIMx->PWCON |= TIM_PWMInitStruct->TIM_PWMPolarity << TIM_PWCON_PWMCPOL_pos;

	if (TIM_PWMInitStruct->TIM_DTCmd == ENABLE)
	{
		/* Enable dead time control function */
		TIMx->PWCON |= TIM_PWCON_DTEN;
	}
	else
	{
		/* Disable dead time control function */
		TIMx->PWCON &= ~TIM_PWCON_DTEN;
	}

	/* Configure PWM dead time width */
	TIMx->PWCON &= ~TIM_PWCON_DTUGAP;
	TIMx->PWCON |= TIM_PWMInitStruct->TIM_DTUGap << TIM_PWCON_DTUGAP_pos;
}

/**
  * @brief  Initialize the TIMx external pulse count according to the 
  *         parameters specified in TIM_CountInitStruct.
  * @param  TIMx: where x can be 1 to 2 to select the TIM peripheral.
  * @param  TIM_CountInitStruct: Pointer to a TIM_CountInitTypeDef structure containing 
  *         external pulse count configuration information for the specified TIM peripheral.
  * @retval None
  */
void TIM_CountInit(TIM_TypeDef *TIMx, TIM_CountInitTypeDef *TIM_CountInitStruct)
{
	/* Check the parameters */
	PARAM_CHECK(IS_TIM_ALL_PERIPH(TIMx));
	PARAM_CHECK(IS_TIM_EXTERN_POL(TIM_CountInitStruct->TIM_ExternPolarity));

	if (TIMx == TIM1)
	{
		/* Set TIM1 to free-running mode */
		TIMERS->CON &= ~TIM_CON_TM_TIM1;

		/* Enable external pulse counting */
		TIMERS->CON |= TIM_CON_EXTEN_TIM1;

		if (TIM_CountInitStruct->TIM_ExternPolarity == TIM_EXTERN_POL_HIGH)
		{
			/* Set the external pulse enable port to count when high */
			TIMERS->CON &= ~TIM_CON_EXTPOL;
		}
		else
		{
			/* Set the external pulse enable port to count when low */
			TIMERS->CON |= TIM_CON_EXTPOL;
		}
	}
	else if (TIMx == TIM2)
	{
		/* Set TIM2 to free-running mode */
		TIMERS->CON &= ~TIM_CON_TM_TIM2;

		/* Enable external pulse counting */
		TIMERS->CON |= TIM_CON_EXTEN_TIM2;

		if (TIM_CountInitStruct->TIM_ExternPolarity == TIM_EXTERN_POL_HIGH)
		{
			/* Set the external pulse enable port to count when high */
			TIMERS->CON &= ~TIM_CON_EXTPOL;
		}
		else
		{
			/* Set the external pulse enable port to count when low */
			TIMERS->CON |= TIM_CON_EXTPOL;
		}
	}

	/* Set overflow values for TIMx peripherals */
	TIMx->CTCG1 = TIM_CountInitStruct->TIM_OverValue & 0xFFFF;
	TIMx->CTCG2 = TIM_CountInitStruct->TIM_OverValue >> 16;
}

/**
  * @brief  Enable or disable the pause function of the specified TIM peripheral.
  * @param  TIMx: where x can be 1 to 2 to select the TIM peripheral.
  * @param  NewState: New state of pause function for specified TIM peripherals.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TIM_PauseCmd(TIM_TypeDef *TIMx, FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_TIM_ALL_PERIPH(TIMx));
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable the pause function of the specified TIM peripheral */
		if (TIMx == TIM1)
		{
			TIMERS->CON |= TIM_CON_PAUSE_TIM1;
		}
		else if (TIMx == TIM2)
		{
			TIMERS->CON |= TIM_CON_PAUSE_TIM2;
		}
	}
	else
	{
		/* Disable the pause function of the specified TIM peripheral */
		if (TIMx == TIM1)
		{
			TIMERS->CON &= ~TIM_CON_PAUSE_TIM1;
		}
		else if (TIMx == TIM2)
		{
			TIMERS->CON &= ~TIM_CON_PAUSE_TIM2;
		}
	}
}

/**
  * @brief  Enables or disables the specified TIM peripheral.
  * @param  TIMx: where x can be 1 to 2 to select the TIMx peripheral.
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
		if (TIMx == TIM1)
		{
			TIMERS->CON |= TIM_CON_TE_TIM1;
		}
		else if (TIMx == TIM2)
		{
			TIMERS->CON |= TIM_CON_TE_TIM2;
		}
	}
	else
	{
		/* Disable the specified TIM peripheral */
		if (TIMx == TIM1)
		{
			TIMERS->CON &= ~TIM_CON_TE_TIM1;
		}
		else if (TIMx == TIM2)
		{
			TIMERS->CON &= ~TIM_CON_TE_TIM2;
		}
	}
}

/**
  * @brief  Enables or disables the specified TIM interrupts.
  * @param  TIMx: where x can be 1 to 2 to select the TIMx peripheral.   
  * @param  NewState: new state of the TIM interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TIM_ITConfig(TIM_TypeDef *TIMx, FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_TIM_ALL_PERIPH(TIMx));
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable the specified TIM interrupts */
		if (TIMx == TIM1)
		{
			TIMERS->CON |= TIM_CON_IE_TIM1;
		}
		else if (TIMx == TIM2)
		{
			TIMERS->CON |= TIM_CON_IE_TIM2;
		}
	}
	else
	{
		/* Disable the specified TIM interrupts */
		if (TIMx == TIM1)
		{
			TIMERS->CON &= ~TIM_CON_IE_TIM1;
		}
		else if (TIMx == TIM2)
		{
			TIMERS->CON &= ~TIM_CON_IE_TIM2;
		}
	}
}

/**
  * @brief  Checks whether the specified TIM flag is set or not.
  * @param  TIMx: where x can be 1 to 2 to select the TIM peripheral. 
  * @retval The new state of specified TIM flag (SET or RESET).
  */
FlagStatus TIM_GetFlagStatus(TIM_TypeDef *TIMx)
{
	FlagStatus bitstatus = RESET;

	/* Check the parameters */
	PARAM_CHECK(IS_TIM_ALL_PERIPH(TIMx));

	/* Check the specified TIM flag */
	if ((TIMx == TIM1) && (TIMERS->INTFLAG & TIM_INTFLAG_TIM1))
	{
		/* the specified TIM flag is set */
		bitstatus = SET;
	}
	else if ((TIMx == TIM2) && (TIMERS->INTFLAG & TIM_INTFLAG_TIM2))
	{
		/* the specified TIM flag is set */
		bitstatus = SET;
	}
	else
	{
		/* the specified TIM flag is reset */
		bitstatus = RESET;
	}

	/* Return the specified TIM flag status */
	return bitstatus;
}

/**
  * @brief  Checks whether the TIM interrupt has occurred or not.
  * @param  TIMx: where x can be 1 to 2 to select the TIM peripheral. 
  * @retval The new state of specified TIM interrupt (SET or RESET).
  */
ITStatus TIM_GetITStatus(TIM_TypeDef *TIMx)
{
	ITStatus bitstatus = RESET;

	/* Check the parameters */
	PARAM_CHECK(IS_TIM_ALL_PERIPH(TIMx));

	/* Check the specified TIM interrupt */
	if ((TIMx == TIM1) && (TIMERS->INTFLAG & TIM_INTFLAG_TIM1) && (TIMERS->CON & TIM_CON_IE_TIM1))
	{
		/* the specified TIM interrupt is set */
		bitstatus = SET;
	}
	else if ((TIMx == TIM2) && (TIMERS->INTFLAG & TIM_INTFLAG_TIM2) && (TIMERS->CON & TIM_CON_IE_TIM2))
	{
		/* the specified TIM interrupt is set */
		bitstatus = SET;
	}
	else
	{
		/* the specified TIM interrupt is reset */
		bitstatus = RESET;
	}

	/* Return the specified TIM interrupt status */
	return bitstatus;
}
/**
  * @brief  Clears the TIMx's pending flags.
  * @param  TIMx: where x can be 1 to 2 to select the TIM peripheral. 
  * @retval None
  */
void TIM_ClearFlag(TIM_TypeDef *TIMx)
{
	/* Check the parameters */
	PARAM_CHECK(IS_TIM_ALL_PERIPH(TIMx));

	/* Clear the selected TIMx's flags */
	if (TIMx == TIM1)
	{
		TIMERS->INTCLR = TIM_INTCLR_TIM1;
	}
	else if (TIMx == TIM2)
	{
		TIMERS->INTCLR = TIM_INTCLR_TIM2;
	}
}

/**
  * @brief  Gets the TIMx Counter value.
  * @param  TIMx: where x can be 1 to 2 to select the TIM peripheral.
  * @retval Counter Register value.
  */
u32 TIM_GetCounter(TIM_TypeDef *TIMx)
{
	/* Check the parameters */
	PARAM_CHECK(IS_TIM_ALL_PERIPH(TIMx));
	
	/* Get the Counter Register value */
	return TIMx->CTVAL;
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

