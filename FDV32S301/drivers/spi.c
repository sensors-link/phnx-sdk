/**
  ******************************************************************************
  * @file    spi.c
  * @author  yongda.wang
  * @version 0.2
  * @date    2022-09-21
  * @brief   This file provides all the SPI firmware functions.
  ******************************************************************************
  * @attention
  *
  * @copyright Fanhai Data Tech. (c) 2022
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "spi.h"
#include "sysc.h"

/** @addtogroup FDV32S301_StdPeriph_Driver
  * @{
  */

/** @defgroup SPI
  * @brief SPI driver modules
  * @{
  */

/** @defgroup SPI_Private_Functions
  * @{
  */

/**
  * @brief  Deinitialize the SPI peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void SPI_DeInit(void)
{
	/* Reset the SPI module settings */
	SYSC_ResetPeripher(SYSC_RESET_MOUDLE_SPI);
}

/**
  * @brief  Initializes the SPI peripheral according to the specified parameters
  *         in the SPI_InitStruct.
  * @param  SPI_InitStruct: pointer to an SPI_InitTypeDef structure that contains
  *         the configuration information for the SPI peripheral.
  * @retval None
  */
void SPI_Init(SPI_InitTypeDef *SPI_InitStruct)
{
	u32 tempreg = 0;

	/* Check the parameters */
	PARAM_CHECK(IS_SPI_CPOL(SPI_InitStruct->SPI_ClockPolarity));
	PARAM_CHECK(IS_SPI_CPHA(SPI_InitStruct->SPI_ClockPhase));
	PARAM_CHECK(IS_SPI_MODE(SPI_InitStruct->SPI_Mode));
	PARAM_CHECK(IS_SPI_SCLK_DIV(SPI_InitStruct->SPI_SclkDiv));

	/* Get the SPI_CR0 value */
	tempreg = SPI->CR0;

	/* Set SPI Serial Clock Polarity */
	if (SPI_InitStruct->SPI_ClockPolarity == SPI_CPOL_LOW)
	{
		/* SCLK is low when SPI is idle */
		tempreg &= ~SPI_CR0_CPOL;
	}
	else
	{
		/* SCLK is high when SPI is idle */
		tempreg |= SPI_CR0_CPOL;
	}

	/* Set the SPI serial clock phase */
	if (SPI_InitStruct->SPI_ClockPhase == SPI_CPHA_1EDGE)
	{
		/* The first clock transition edge counts */
		tempreg &= ~SPI_CR0_CPHA;
	}
	else
	{
		/* The second clock transition edge counts */
		tempreg |= SPI_CR0_CPHA;
	}

	/* Set SPI mode */
	if (SPI_InitStruct->SPI_Mode == SPI_MODE_SLAVE)
	{
		/* SPI mode is configured as slave */
		tempreg &= ~SPI_CR0_MSMODE;
	}
	else
	{
		/* SPI mode is configured as master */
		tempreg |= SPI_CR0_MSMODE;
	}

	/* Set SCLK clock divider */
	tempreg &= ~SPI_CR0_SCLKDIV;
	tempreg |= SPI_InitStruct->SPI_SclkDiv << SPI_CR0_SCLKDIV_pos;

	/* Write to SPI_CR0 */
	SPI->CR0 = tempreg;
}

/**
  * @brief  Enables or disables the specified SPI interrupts.
  * @param  SPI_IT: specifies the SPI interrupt sources to be enabled or disabled.
  *   This parameter can be any combination of the following values:
  *     @arg SPI_IT_MSTCFIE: spi cs conflict error interrupt
  *     @arg SPI_IT_DONEIE: Current byte send/receive complete interrupt
  * @param  NewState: new state of the specified SPI interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SPI_ITConfig(u8 SPI_IT, FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_SPI_CONFIG_IT(SPI_IT));
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable the selected SPI interrupts */
		SPI->CR0 |= SPI_IT;
	}
	else
	{
		/* Disable the selected SPI interrupts */
		SPI->CR0 &= ~SPI_IT;
	}
}

/**
  * @brief  Checks whether the specified SPI flag is set or not.
  * @param  SPI_FLAG: specifies the flag to check.
  *   This parameter can be one of the following values:
  *     @arg SPI_FLAG_SPI_CS: Real-time status flag of current SPI_CSN
  *     @arg SPI_FLAG_MSTCFSR: Generate spi cs conflict error flag
  *     @arg SPI_FLAG_DONESR: Current byte send/receive complete interrupt flag
  * @retval The new state of SPI_FLAG (SET or RESET).
  */
FlagStatus SPI_GetFlagStatus(u8 SPI_FLAG)
{
	FlagStatus bitstatus = RESET;

	/* Check the parameters */
	PARAM_CHECK(IS_SPI_GET_FLAG(SPI_FLAG));

	/* Check the status of the SPI flag */
	if (SPI->SR & SPI_FLAG)
	{
		/* SPI_FLAG is set */
		bitstatus = SET;
	}
	else
	{
		/* SPI_FLAG is reset */
		bitstatus = RESET;
	}
	/* Return the SPI_FLAG status */
	return bitstatus;
}

/**
  * @brief  Checks whether the specified SPI interrupt has occurred or not.
  * @param  SPI_IT: specifies the SPI interrupt source to check.
  *   This parameter can be one of the following values:
  *     @arg SPI_IT_MSTCFIE: spi cs conflict error interrupt
  *     @arg SPI_IT_DONEIE: Current byte send/receive complete interrupt
  * @retval The new state of SPI_IT (SET or RESET).
  */
ITStatus SPI_GetITStatus(u8 SPI_IT)
{
	ITStatus bitstatus = RESET;

	/* Check the parameters */
	PARAM_CHECK(IS_SPI_GET_IT(SPI_IT));

	/* Check the status of the specified SPI interrupt */
	if ((SPI->CR0 & SPI_IT) && (SPI->SR & (SPI_IT >> 4)))
	{
		/* SPI_IT is set */
		bitstatus = SET;
	}
	else
	{
		/* SPI_IT is reset */
		bitstatus = RESET;
	}
	/* Return the SPI_IT status */
	return bitstatus;
}

/**
  * @brief  Clear the pending flag for SPI.
  * @param  SPI_FLAG: specifies the flag to clear.
  *   This parameter can be any combination of the following values:
  *     @arg SPI_FLAG_MSTCFSR: Generate spi cs conflict error flag
  *     @arg SPI_FLAG_DONESR: Current byte send/receive complete interrupt flag
  * @retval None
  */
void SPI_ClearFlag(u8 SPI_FLAG)
{
	u32 tempreg = 0;

	/* Check the parameters */
	PARAM_CHECK(IS_SPI_CLEAR_FLAG(SPI_FLAG));

	/* Clear the selected SPI flags */
	if (SPI_FLAG == SPI_FLAG_MSTCFSR)
	{
		/* Clear the spi cs conflict error flag */
		tempreg = SPI->CR0;
	}
	else
	{
		/* Clear the current byte send/receive complete interrupt flag */
		tempreg = SPI->SR;
	}
	(void)tempreg;
}

/**
  * @brief  Set the level to control cs_n.
  * @param  None
  * @retval None
  */
void SPI_SetCSN(void)
{
	/* The level of cs_n is configured as high */
	SPI->CSN |= SPI_CSN_CSN;
}

/**
  * @brief  Reset the level to control cs_n.
  * @param  None
  * @retval None
  */
void SPI_ClrCSN(void)
{
	/* The level of cs_n is configured as low */
	SPI->CSN &= ~SPI_CSN_CSN;
}

/**
  * @brief  Transmits a Data through the SPI peripheral.
  * @param  Data : Data to be transmitted.
  * @retval None
  */
void SPI_SendData(u8 data)
{
	/* Write in the DR register the data to be sent */
	SPI->DR = data;
}

/**
  * @brief  Returns the most recent received data by the SPI peripheral. 
  * @param  None
  * @retval The value of the received data.
  */
u8 SPI_RecieveData(void)
{
	/* Return the data in the DR register */
	return (u8)(SPI->DR);
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

