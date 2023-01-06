/**
  ******************************************************************************
  * @file    anac.c
  * @author  yongda.wang
  * @version 0.2
  * @date    2022-08-29
  * @brief   This file provides ANAC related module firmware functions.
  ******************************************************************************
  * @attention
  *
  * @copyright Fanhai Data Tech. (c) 2022
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "anac.h"
#include "sysc.h"

/** @addtogroup FDV32F003_StdPeriph_Driver
  * @{
  */

/** @defgroup ANAC
  * @brief ANAC driver modules
  * @{
  */

/** @defgroup ANAC_Private_Defines
  * @{
  */

/* CMP_CFG register Mask */
#define CMP_CFG_CLEAR_Mask ((u32)0xFFFFFC01)

/* LVD_CFG register Mask */
#define LVD_CFG_CLEAR_Mask ((u32)0xFFFF0003)

/**
  * @}
  */

/** @defgroup ANAC_Private_Functions
  * @{
  */

/**
  * @brief  Deinitialize the ANAC module registers to their default reset values.
  * @param  None
  * @retval None
  */
void ANAC_DeInit(void)
{
	/* Reset the ANAC module settings */
	SYSC_ResetPeripher(SYSC_RESET_MOUDLE_ANAC);
}

/**
  * @brief  Set sleep LDO output voltage select bits.
  * @param  OutputVol: Specify the sleep LDO output voltage.
  *   This parameter can be one of the following values:
  *     @arg ANAC_SLDO_VRSEL_1P5V: sleep LDO output voltage select 1.5V
  *     @arg ANAC_SLDO_VRSEL_1P2V: sleep LDO output voltage select 1.2V
  * @retval None
  */
void ANAC_SetSleepLDOVoltage(u8 OutputVol)
{
	u32 tempreg = 0;

	/* Check the parameters */
	PARAM_CHECK(IS_ANAC_SLDO_VRSEL(OutputVol));

	/* Get the ANAC_CFG value */
	tempreg = ANAC->ANAC_CFG;

	if(OutputVol == ANAC_SLDO_VRSEL_1P2V)
	{
		/* The output voltage of the DSLEEP LDO is 1.2V */
		tempreg |= ANAC_ANAC_CFG_SLDO_VRSEL;
	}
	else
	{
		/* The output voltage of the DSLEEP LDO is 1.5V */
		tempreg &= ~ANAC_ANAC_CFG_SLDO_VRSEL;
	}
	
	/* Write to ANAC_CFG */
	ANAC_WPT_UNLOCK();
	ANAC->ANAC_CFG = tempreg;
}

/**
  * @brief  Enable or disable HRC clock.
  * @param  NewState: New state of the HRC clock.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ANAC_HRCClockCmd(FunctionalState NewState)
{
	u32 tempreg = 0;

	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	/* Get the ANAC_CFG value */
	tempreg = ANAC->ANAC_CFG;

	if (NewState == ENABLE)
	{
		/* Enable HRC clock */
		tempreg |= ANAC_ANAC_CFG_HRC_EN;
	}
	else
	{
		/* Disable HRC clock */
		tempreg &= ~ANAC_ANAC_CFG_HRC_EN;
	}

	/* Write to ANAC_CFG */
	ANAC_WPT_UNLOCK();
	ANAC->ANAC_CFG = tempreg;
}

/**
  * @brief  Enable or disable LRC clock.
  * @param  NewState: New state of the LRC clock.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ANAC_LRCClockCmd(FunctionalState NewState)
{
	u32 tempreg = 0;

	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	/* Get the ANAC_CFG value */
	tempreg = ANAC->ANAC_CFG;

	if (NewState == ENABLE)
	{
		/* Enable LRC clock */
		tempreg |= ANAC_ANAC_CFG_LRC_EN;
	}
	else
	{
		/* Disable LRC clock */
		tempreg &= ~ANAC_ANAC_CFG_LRC_EN;
	}

	/* Write to ANAC_CFG */
	ANAC_WPT_UNLOCK();
	ANAC->ANAC_CFG = tempreg;
}

/**
  * @brief  Enable or enable acitve LDO for digital.
  * @param  NewState: New state ofacitve LDO for digital.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ANAC_ActiveLDO4DigitalCmd(FunctionalState NewState)
{
	u32 tempreg = 0;

	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	/* Get the ANAC_CFG value */
	tempreg = ANAC->ANAC_CFG;

	if (NewState == ENABLE)
	{
		/* Enable acitve LDO for digital */
		tempreg |= ANAC_ANAC_CFG_ALDO4D_EN;
	}
	else
	{
		/* Disable acitve LDO for digital */
		tempreg &= ~ANAC_ANAC_CFG_ALDO4D_EN;
	}

	/* Write to ANAC_CFG */
	ANAC_WPT_UNLOCK();
	ANAC->ANAC_CFG = tempreg;
}

/**
  * @brief  Initializes the CMP peripheral according to the specified parameters
  *         in the CMP_InitStruct.
  * @param  CMP_InitStruct: pointer to an CMP_InitTypeDef structure that contains
  *         the configuration information for the CMP peripheral.
  * @retval None
  */
void CMP_Init(CMP_InitTypeDef *CMP_InitStruct)
{
	u32 tempreg = 0;

	/* Check the parameters */
	PARAM_CHECK(IS_CMP_HYSSEL(CMP_InitStruct->CMP_HysSel));
	PARAM_CHECK(IS_CMP_VINSEL(CMP_InitStruct->CMP_VinSel));
	PARAM_CHECK(IS_CMP_VIPSEL(CMP_InitStruct->CMP_VipSel));
	PARAM_CHECK(IS_FUNCTIONAL_STATE(CMP_InitStruct->CMP_InvertedOutCmd));

	/*---------------------------- CMP_CFG Configuration ------------------------*/
	/* Get the CMP_CFG value */
	tempreg = ANAC->CMP_CFG;
	/* Clear CMP_CFG initialization configuration bit */
	tempreg &= CMP_CFG_CLEAR_Mask;

	/* CMP hysteresis function selection */
	tempreg |= CMP_InitStruct->CMP_HysSel << ANAC_CMP_CFG_HYSSEL_pos;
	/* CMP negative input signal selection */
	tempreg |= CMP_InitStruct->CMP_VinSel << ANAC_CMP_CFG_VINSEL_pos;
	/* CMP positive input signal selection */
	tempreg |= CMP_InitStruct->CMP_VipSel << ANAC_CMP_CFG_VIPSEL_pos;
	if (CMP_InitStruct->CMP_InvertedOutCmd == ENABLE)
	{
		/* Set CMP result inversion output */
		tempreg |= ANAC_CMP_CFG_INV;
	}

	/* Write to CMP_CFG */
	ANAC->CMP_CFG = tempreg;
}

/**
  * @brief  Enable or disable the CMP peripheral.
  * @param  NewState: New state of the CMP peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void CMP_Cmd(FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable CMP peripheral */
		ANAC->CMP_CFG |= ANAC_CMP_CFG_EN;
	}
	else
	{
		/* Disable CMP peripheral */
		ANAC->CMP_CFG &= ~ANAC_CMP_CFG_EN;
	}
}

/**
  * @brief  Initializes the LVD peripheral according to the specified parameters
  *         in the LVD_InitStruct.
  * @param  LVD_InitStruct: pointer to an LVD_InitTypeDef structure that contains
  *         the configuration information for the LVD peripheral.
  * @retval None
  */
void LVD_Init(LVD_InitTypeDef *LVD_InitStruct)
{
	u32 tempreg = 0;

	/* Check the parameters */
	PARAM_CHECK(IS_LVD_THRESHOLD_VOL(LVD_InitStruct->LVD_ThresholdVoltage));
	PARAM_CHECK(IS_LVD_MONITOR_SOURCE(LVD_InitStruct->LVD_MonitoSource));

	/*---------------------------- LVD_CFG Configuration ------------------------*/
	tempreg = ANAC->LVD_CFG;
	/* Clear LVD_CFG initialization configuration bit */
	tempreg &= LVD_CFG_CLEAR_Mask;

	/* Set low voltage detection LVD_OUT filter time */
	tempreg |= LVD_InitStruct->LVD_FilterTime << ANAC_LVD_CFG_FLT_pos;
	/* Set LVD threshold voltage selection */
	tempreg |= LVD_InitStruct->LVD_ThresholdVoltage << ANAC_LVD_CFG_VTSEL_pos;
	/* Set Set LVD monitoring source selection */
	tempreg |= LVD_InitStruct->LVD_MonitoSource << ANAC_LVD_CFG_SRCSEL_pos;

	/* Write to LVD_CFG */
	ANAC->LVD_CFG = tempreg;
}

/**
  * @brief  Enable or disable the LVD peripheral.
  * @param  NewState: New state of the LVD peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LVD_Cmd(FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable LVD peripheral */
		ANAC_WPT_UNLOCK();
		ANAC->LVD_CFG |= ANAC_LVD_CFG_LVD_EN;
	}
	else
	{
		/* Disable LVD peripheral */
		ANAC_WPT_UNLOCK();
		ANAC->LVD_CFG &= ~ANAC_LVD_CFG_LVD_EN;
	}
}

/**
  * @brief  Enables or disables the LVD interrupts.
  * @param  NewState: new state of the specified LVD interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LVD_ITConfig(FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable the LVD interrupts */
		ANAC->LVD_CFG |= ANAC_LVD_CFG_LVD_IE;
	}
	else
	{
		/* Disable the LVD interrupts */
		ANAC->LVD_CFG &= ~ANAC_LVD_CFG_LVD_IE;
	}
}


/**
  * @brief  Checks whether the specified LVD flag is set or not.
  * @param  None
  * @retval The new state of LVD flag (SET or RESET).
  */
FlagStatus LVD_GetFlagStatus(void)
{
	FlagStatus bitstatus = RESET;

	/* Check the status of the LVD flag */
	if (ANAC->ANAC_FLAG & ANAC_ANAC_FLAG_LVD_INTF)
	{
		/* LVD flag is set */
		bitstatus = SET;
	}
	else
	{
		/* LVD flag is reset */
		bitstatus = RESET;
	}
	/* Return the LVD flag status */
	return bitstatus;
}

/**
  * @brief  Checks whether the specified LVD interrupt has occurred or not.
  * @param  None
  * @retval The new state of LVD interrupt (SET or RESET).
  */
ITStatus LVD_GetITStatus(void)
{
	ITStatus bitstatus = RESET;

	/* Check the status of the LVD interrupt */
	if ((ANAC->LVD_CFG & ANAC_LVD_CFG_LVD_IE) && (ANAC->ANAC_FLAG & ANAC_ANAC_FLAG_LVD_INTF))
	{
		/* LVD interrupt is set */
		bitstatus = SET;
	}
	else
	{
		/* LVD interrupt is reset */
		bitstatus = RESET;
	}
	/* Return the LVD interrupt status */
	return bitstatus;
}

/**
  * @brief  Clear the pending flag for LVD.
  * @param  None
  * @retval None
  */
void LVD_ClearFlag(void)
{
	/* Clear the LVD flags */
	ANAC->ANAC_FLAG = ANAC_ANAC_FLAG_LVD_INTF;
}

/**
  * @brief  Configure the analog GPIO multiplexing function.
  * @param  MultiplexSel: Specifies the analog multiplexing capabilities of GPIO.
  *   This parameter can be one of the following values:
  *     @arg AINSEL_MULTIPLEX_P00_SEL_RSV		: GP00 multiplex select RSV		
  *     @arg AINSEL_MULTIPLEX_P00_SEL_VC1P0		: GP00 multiplex select VC1P0		
  *     @arg AINSEL_MULTIPLEX_P01_SEL_AIN04		: GP01 multiplex select AIN04		
  *     @arg AINSEL_MULTIPLEX_P01_SEL_VC1O		: GP01 multiplex select VC1O		
  *     @arg AINSEL_MULTIPLEX_P02_SEL_LVDI0		: GP02 multiplex select LVDI0		
  *     @arg AINSEL_MULTIPLEX_P02_SEL_AIN02		: GP02 multiplex select AIN02		
  *     @arg AINSEL_MULTIPLEX_P03_SEL_LVDI1		: GP03 multiplex select LVDI1		
  *     @arg AINSEL_MULTIPLEX_P03_SEL_AIN03		: GP03 multiplex select AIN03		
  *     @arg AINSEL_MULTIPLEX_P04_SEL_VC1P2		: GP04 multiplex select VC1P2		
  *     @arg AINSEL_MULTIPLEX_P04_SEL_AIN05		: GP04 multiplex select AIN05		
  *     @arg AINSEL_MULTIPLEX_P05_SEL_VC1P3		: GP05 multiplex select VC1P3		
  *     @arg AINSEL_MULTIPLEX_P05_SEL_AIN06		: GP05 multiplex select AIN06		
  *     @arg AINSEL_MULTIPLEX_P06_SEL_VC1N0		: GP06 multiplex select VC1N0		
  *     @arg AINSEL_MULTIPLEX_P06_SEL_AIN07		: GP06 multiplex select AIN07		
  *     @arg AINSEL_MULTIPLEX_P07_SEL_VREF_FLASH: GP07 multiplex select VREF_FLASH
  *     @arg AINSEL_MULTIPLEX_P07_SEL_AIN11		: GP07 multiplex select AIN11		
  *     @arg AINSEL_MULTIPLEX_P08_SEL_VC1N2		: GP08 multiplex select VC1N2		
  *     @arg AINSEL_MULTIPLEX_P08_SEL_AIN08		: GP08 multiplex select AIN08		
  *     @arg AINSEL_MULTIPLEX_P09_SEL_AIN09		: GP09 multiplex select AIN09		
  *     @arg AINSEL_MULTIPLEX_P09_SEL_VC1N1		: GP09 multiplex select VC1N1		
  *     @arg AINSEL_MULTIPLEX_P10__SEL_RSV		: GP10 multiplex select _RSV		
  *     @arg AINSEL_MULTIPLEX_P10__SEL_VC1N3	: GP10 multiplex select _VC1N3	
  *     @arg AINSEL_MULTIPLEX_P11__SEL_ATS1		: GP11 multiplex select _ATS1		
  *     @arg AINSEL_MULTIPLEX_P11__SEL_AIN10	: GP11 multiplex select _AIN10	
  *     @arg AINSEL_MULTIPLEX_P12__SEL_VC1P1	: GP12 multiplex select _VC1P1	
  *     @arg AINSEL_MULTIPLEX_P12__SEL_VREF		: GP12 multiplex select _VREF		
  *     @arg AINSEL_MULTIPLEX_P13__SEL_RSV		: GP13 multiplex select _RSV		
  *     @arg AINSEL_MULTIPLEX_P13__SEL_AIN03	: GP13 multiplex select _AIN03	
  *     @arg AINSEL_MULTIPLEX_P14__SEL_RSV		: GP14 multiplex select _RSV		
  *     @arg AINSEL_MULTIPLEX_P14__SEL_AIN02	: GP14 multiplex select _AIN02	
  *     @arg AINSEL_MULTIPLEX_P15__SEL_AIN01	: GP15 multiplex select _AIN01	
  *     @arg AINSEL_MULTIPLEX_P15__SEL_VC1N0	: GP15 multiplex select _VC1N0	
  *     @arg AINSEL_MULTIPLEX_P16__SEL_AIN00	: GP16 multiplex select _AIN00	
  *     @arg AINSEL_MULTIPLEX_P16__SEL_LVDI0	: GP16 multiplex select _LVDI0	
  * @retval None
  */
void AINSEL_MultiplexConfig(u8 MultiplexSel)
{
	/* Check the parameters */
	PARAM_CHECK(IS_AINSEL_MULTIPLEXSEL(MultiplexSel));

	/* Clear analog GPIO alternate function pin bit */
	ANAC->AINSEL &= ~(1 << (MultiplexSel >> 1));
	/* Set the pin to simulate the GPIO multiplexing function */
	ANAC->AINSEL |= (MultiplexSel & 1) << (MultiplexSel >> 1);
}

/**
  * @brief  Checks whether the specified ANAC flag is set or not.
  * @param  ANAC_FLAG: specifies the flag to check.
  *   This parameter can be one of the following values:
  *     @arg ANAC_FLAG_CMP_OUT: Comparator result output flag
  *     @arg ANAC_FLAG_LVD_OUT: Low voltage detection result output flag
  *     @arg ANAC_FLAG_LVD_INTF: Low voltage detection interrupt flag
  * @retval The new state of ANAC_FLAG (SET or RESET).
  */
FlagStatus ANAC_GetFlagStatus(u16 ANAC_FLAG)
{
	FlagStatus bitstatus = RESET;

	/* Check the parameters */
	PARAM_CHECK(IS_ANAC_GET_FLAG(ANAC_FLAG));

	/* Check the status of the ANAC flag */
	if (ANAC->ANAC_FLAG & ANAC_FLAG)
	{
		/* ANAC_FLAG is set */
		bitstatus = SET;
	}
	else
	{
		/* ANAC_FLAG is reset */
		bitstatus = RESET;
	}
	/* Return the ANAC_FLAG status */
	return bitstatus;
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

