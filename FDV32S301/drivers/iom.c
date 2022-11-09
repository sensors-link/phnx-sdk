/**
  ******************************************************************************
  * @file    iom.c
  * @author  yongda.wang
  * @version 0.2
  * @date    2022-09-09
  * @brief   This file provides all the IOM firmware functions.
  ******************************************************************************
  * @attention
  *
  * @copyright Fanhai Data Tech. (c) 2022
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "iom.h"
#include "sysc.h"

/** @addtogroup FDV32S301_StdPeriph_Driver
  * @{
  */

/** @defgroup IOM
  * @brief IOM driver modules
  * @{
  */

/** @defgroup IOM_Private_Functions
  * @{
  */

/**
  * @brief  Initializes the IOM peripheral according to the specified parameters
  *         in the IOM_InitStruct.
  * @param  IOM_InitStruct: pointer to an IOM_InitTypeDef structure that contains
  *         the configuration information for the IOM peripheral.
  * @retval None
  */
void IOM_Init(IOM_InitTypeDef *IOM_InitStruct)
{
	u8 i;

	/* Check the parameters */
	PARAM_CHECK(IS_IOM_PIN(IOM_InitStruct->IOM_Pin));
	PARAM_CHECK(IS_FUNCTIONAL_STATE(IOM_InitStruct->IOM_OutCmd));
	PARAM_CHECK(IS_FUNCTIONAL_STATE(IOM_InitStruct->IOM_PuCmd));
	PARAM_CHECK(IS_FUNCTIONAL_STATE(IOM_InitStruct->IOM_PdCmd));
	PARAM_CHECK(IS_IOM_OTYPE(IOM_InitStruct->IOM_OutType));
	PARAM_CHECK(IS_IOM_ADS(IOM_InitStruct->IOM_ADState));
	PARAM_CHECK(IS_IOM_DRS(IOM_InitStruct->IOM_DRState));
	PARAM_CHECK(IS_IOM_ALTFUNC(IOM_InitStruct->IOM_AltFunc));

	if (IOM_InitStruct->IOM_ADState == IOM_ADS_ANALOG)
	{
		/* Set the corresponding IO as an analog function */
		IOM->ADS |= IOM_InitStruct->IOM_Pin;
	}
	else
	{
		/* Set the corresponding IO as an digital function */
		IOM->ADS &= ~IOM_InitStruct->IOM_Pin;

		/* Clear the corresponding IO alternate function configure*/
		for (i = 0; i < 20; ++i)
		{
			if (IOM_InitStruct->IOM_Pin & (0x01 << i))
			{
				if (i < 16)
				{
					IOM->AF0 &= ~(IOM_ALT_FUNC_ALL << (i << 1));
				}
				else
				{
					IOM->AF1 &= ~(IOM_ALT_FUNC_ALL << ((i - 16) << 1));
				}
			}
		}

		/* Configure general purpose GPIO */
		if (IOM_InitStruct->IOM_AltFunc == IOM_ALT_FUNC_0)
		{
			/* Set the output enable register OE */
			if (IOM_InitStruct->IOM_OutCmd == ENABLE)
			{
				IOM->OE |= IOM_InitStruct->IOM_Pin;
			}
			else
			{
				IOM->OE &= ~IOM_InitStruct->IOM_Pin;
			}
		}

		/* Set the alternate function register corresponding to IO */
		for (i = 0; i < 20; ++i)
		{
			if (IOM_InitStruct->IOM_Pin & (0x01 << i))
			{
				if (i < 16)
				{
					IOM->AF0 |= (IOM_InitStruct->IOM_AltFunc << (i << 1));
				}
				else
				{
					IOM->AF1 |= (IOM_InitStruct->IOM_AltFunc << ((i - 16) << 1));
				}
			}
		}

		/* Set IO pull-up register PU */
		if (IOM_InitStruct->IOM_PuCmd == ENABLE)
		{
			IOM->PU |= IOM_InitStruct->IOM_Pin;
		}
		else
		{
			IOM->PU &= ~IOM_InitStruct->IOM_Pin;
		}

		/* Set IO pull-down register PD */
		if (IOM_InitStruct->IOM_PdCmd == ENABLE)
		{
			IOM->PD |= IOM_InitStruct->IOM_Pin;
		}
		else
		{
			IOM->PD &= ~IOM_InitStruct->IOM_Pin;
		}

		/* Set IO output type register OTYPE */
		if (IOM_InitStruct->IOM_OutType == IOM_OTYPE_DRAIN)
		{
			IOM->OTYPE |= IOM_InitStruct->IOM_Pin;
		}
		else
		{
			IOM->OTYPE &= ~IOM_InitStruct->IOM_Pin;
		}

		/* Set IO drive capability register DRS */
		if (IOM_InitStruct->IOM_DRState == IOM_DRS_HIGH)
		{
			IOM->DRS |= IOM_InitStruct->IOM_Pin;
		}
		else
		{
			IOM->DRS &= ~IOM_InitStruct->IOM_Pin;
		}
	}
}

/**
  * @brief  Set the interrupt property for the selected pin.
  * @param  IOM_Pin: Specifies the data port bits to configure.
  *   This parameter can be any combination of GPIO_PINx where x can be (0..19).
  * @param  IntType: Specifies the type of interrupt to configure.
  *   This parameter can be one of the following values:
  *     @arg IOM_INT_TYPE_EDGE: edge-triggered interrupt
  *     @arg IOM_INT_TYPE_LEVEL: level-triggered interrupt
  * @param  IntPolarity: Specifies the polarity of interrupt to configure.
  *   This parameter can be one of the following values:
  *     @arg IOM_INT_POL_HIGH: High level or rising edge trigger interrupt
  *     @arg IOM_INT_POL_LOW: Low level or falling edge trigger interrupt
  * @retval None
  */
void IOM_SetPinIntProperty(u32 IOM_Pin, u8 IntType, u8 IntPolarity)
{
	/* Check the parameters */
	PARAM_CHECK(IS_IOM_PIN(IOM_Pin));
	PARAM_CHECK(IS_IOM_INTTYPE(IntType));
	PARAM_CHECK(IS_IOM_INTPOL(IntPolarity));

	/* Set the interrupt type for the selected pin */
	if (IntType == IOM_INT_TYPE_LEVEL)
	{
		IOM->INT_TYPE |= IOM_Pin;
	}
	else
	{
		IOM->INT_TYPE &= ~IOM_Pin;
	}

	/* Set interrupt polarity for selected pins */
	if (IntPolarity == IOM_INT_POL_HIGH)
	{
		IOM->INT_POLARITY |= IOM_Pin;
	}
	else
	{
		IOM->INT_POLARITY &= ~IOM_Pin;
	}
}

/**
  * @brief  Enable or enable IO port level input synchronization to APB.
  * @param  NewState: New state of IO port level input synchronization to APB.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void IOM_SyncAPBCmd(FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable IO port level input synchronization to APB */
		IOM->CTL |= IOM_CTL_LS_SYNC;
	}
	else
	{
		/* Disable IO port level input synchronization to APB */
		IOM->CTL &= ~IOM_CTL_LS_SYNC;
	}
}

/**
  * @brief  Enable or disable IO port debounce function.
  * @param  NewState: New state of IO port debounce function.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void IOM_DebounceCmd(FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable IO port debounce function */
		IOM->CTL |= IOM_CTL_DEBOUNCE;
	}
	else
	{
		/* Disable IO port debounce function */
		IOM->CTL &= ~IOM_CTL_DEBOUNCE;
	}
}

/**
  * @brief  Enable or disable IOM global interrupt.
  * @param  NewState: New state of IOM global interrupt.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void IOM_GlobalIntCmd(FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable IOM global interrupt */
		IOM->CTL |= IOM_CTL_INTE;
	}
	else
	{
		/* Disable IOM global interrupt */
		IOM->CTL &= ~IOM_CTL_INTE;
	}
}

/**
  * @brief  Enables or disables interrupts for selected data port bits.
  * @param  IOM_Pin: Specifies the data port bits to configure.
  *   This parameter can be any combination of GPIO_PINx where x can be (0..19).
  * @param  NewState: The new state of the selected IO pin interrupt.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void IOM_ITConfig(u32 IOM_Pin, FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_IOM_PIN(IOM_Pin));
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable interrupts for selected data port bits */
		IOM->EXT_INTE |= IOM_Pin;
	}
	else
	{
		/* Disable interrupts for selected data port bits */
		IOM->EXT_INTE &= ~IOM_Pin;
	}
}

/**
  * @brief  Check if the flag for the selected data port bit is set.
  * @param  IOM_Pin: Specifies the data port bits to check.
  *   This parameter can be GPIO_PINx where x can be (0..19).
  * @retval The new state of IOM_Pin (SET or RESET).
  */
FlagStatus IOM_GetFlagStatus(u32 IOM_Pin)
{
	FlagStatus bitstatus = RESET;

	/* Check the parameters */
	PARAM_CHECK(IS_GET_IOM_PIN(IOM_Pin));

	/* Check the flag status of the selected data port bit */
	if (IOM->INTF & IOM_Pin)
	{
		/* IOM_Pin is set */
		bitstatus = SET;
	}
	else
	{
		/* IOM_Pin is reset */
		bitstatus = RESET;
	}
	/* Return the IOM_Pin status */
	return bitstatus;
}

/**
  * @brief  Check if the interrupt for the selected data port bit is set.
  * @param  IOM_Pin: Specifies the data port bits to check.
  *   This parameter can be GPIO_PINx where x can be (0..19).
  * @retval The new state of IOM_Pin (SET or RESET).
  */
ITStatus IOM_GetITStatus(u32 IOM_Pin)
{
	FlagStatus bitstatus = RESET;

	/* Check the parameters */
	PARAM_CHECK(IS_GET_IOM_PIN(IOM_Pin));

	/* Check the interrupt status of the selected data port bit */
	if ((IOM->EXT_INTE & IOM_Pin) && (IOM->INTF & IOM_Pin))
	{
		/* IOM_Pin is set */
		bitstatus = SET;
	}
	else
	{
		/* IOM_Pin is reset */
		bitstatus = RESET;
	}
	/* Return the IOM_Pin status */
	return bitstatus;
}

/**
  * @brief  Clear the flag of the selected data port bit.
  * @param  IOM_Pin: Specifies the data port bits to clear.
  *   This parameter can be any combination of GPIO_PINx where x can be (0..19).
  * @retval None
  */
void IOM_ClearFlag(u32 IOM_Pin)
{
	/* Check the parameters */
	PARAM_CHECK(IS_IOM_PIN(IOM_Pin));

	/* Clear the flag of the selected data port bit */
	IOM->INTF = IOM_Pin;
}

/**
  * @brief  Get the IOM data port.
  * @param  None
  * @retval IOM data port value.
  */
u32 IOM_GetData(void)
{
	/* Return the data in the DATA register */
	return IOM->DATA;
}

/**
  * @brief  Sets the selected data port bits.
  * @param  pin: Specifies the data port bits to set.
  *   This parameter can be any combination of GPIO_PINx where x can be (0..19).
  * @retval None
  */
void IOM_SetPin(u32 IOM_Pin)
{
	/* Check the parameters */
	PARAM_CHECK(IS_IOM_PIN(IOM_Pin));

	/* Set selected bits in DATA */
	IOM->DATA |= IOM_Pin;
}

/**
  * @brief  Clear the selected data port bits.
  * @param  pin: Specifies the data port bits to clear.
  *   This parameter can be any combination of GPIO_PINx where x can be (0..19).
  * @retval None
  */
void IOM_ClrPin(u32 IOM_Pin)
{
	/* Check the parameters */
	PARAM_CHECK(IS_IOM_PIN(IOM_Pin));

	/* Clear selected bits in DATA */
	IOM->DATA &= ~IOM_Pin;
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

