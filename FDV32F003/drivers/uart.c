/**
  ******************************************************************************
  * @file    uart.c
  * @author  yongda.wang
  * @version 0.2
  * @date    2022-09-27
  * @brief   This file provides all the UART firmware functions.
  ******************************************************************************
  * @attention
  *
  * @copyright Fanhai Data Tech. (c) 2022
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "uart.h"
#include "sysc.h"

/** @addtogroup FDV32F003_StdPeriph_Driver
  * @{
  */

/** @defgroup UART
  * @brief UART driver modules
  * @{
  */

/** @defgroup UART_Private_Defines
  * @{
  */

/* UART_SCON register Mask */
#define UART_SCON_CLEAR_Mask ((u32)0xFFFFF0BF)

/**
  * @}
  */

/** @defgroup UART_Private_Functions
  * @{
  */

/**
  * @brief  Deinitialize the UART peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void UART_DeInit(void)
{
	/* Reset the UART module settings */
	SYSC_ResetPeripher(SYSC_RESET_MOUDLE_UART);
}

/**
  * @brief  Initializes the UART peripheral according to the specified parameters
  *         in the UART_InitStruct.
  * @param  UART_InitStruct: pointer to a UART_InitTypeDef structure that contains
  *         the configuration information for the specified UART peripheral.
  * @retval None
  */
void UART_Init(UART_InitTypeDef *UART_InitStruct)
{
	u32 tempreg = 0, bauddiv = 0;
	SYSC_ClocksTypeDef SYSC_Clocks;

	/* Check the parameters */
	PARAM_CHECK(IS_UART_PARITY(UART_InitStruct->UART_Parity));
	PARAM_CHECK(IS_UART_STOPBITS(UART_InitStruct->UART_StopBits));
	PARAM_CHECK(IS_UART_BAUDRATE(UART_InitStruct->UART_BaudRate));

	/*---------------------------- UART SCON Configuration -----------------------*/
	tempreg = UART1->SCON;
	/* Clear UART_SCON initialization configuration bit */
	tempreg &= UART_SCON_CLEAR_Mask;

	/* Configure UART Parity and Work Mode ---------------------------------------*/
	/* Set the PACFG bits according to UART_Parity value */
	/* Set the SM01 bits according to UART_Parity and UART_StopBits value */
	tempreg |= UART_InitStruct->UART_Parity;
	if (UART_InitStruct->UART_Parity == UART_PARITY_NO)
	{
		tempreg |= UART_InitStruct->UART_StopBits;
	}

	/* Enable UART reception */
	tempreg |= UART_SCON_REN;

	/* Write to UART SCON */
	UART1->SCON = tempreg;

	/*---------------------------- UART BDIV Configuration -----------------------*/
	/* Get system clock */
	SYSC_GetClocksFreq(&SYSC_Clocks);

	if (UART_InitStruct->UART_StopBits == UART_STOPBITS_0 && UART_InitStruct->UART_Parity == UART_PARITY_NO)
	{
		/* Baud rate calculation for UART mode 0 */
		bauddiv =
			(SYSC_Clocks.PCLK_Frequency + UART_InitStruct->UART_BaudRate) / (2 * UART_InitStruct->UART_BaudRate) - 1;
	}
	else
	{
		/* Baud rate calculation for UART mode 1/2/3 */
		bauddiv =
			(SYSC_Clocks.PCLK_Frequency + 8 * UART_InitStruct->UART_BaudRate) / (16 * UART_InitStruct->UART_BaudRate) -
			1;
	}

	/* Check the value written to the baud rate register (BDIV) */
	PARAM_CHECK(IS_UART_BAUDDIV(bauddiv));

	/* Write to UART BDIV */
	UART1->BDIV = bauddiv;
}

/**
  * @brief  Sets the slave device address and mask for the selected UART peripheral.
  * @param  Addr: Specifies the slave device address of the UART peripheral.
  * @param  Mask: Specifies the slave device address mask for the UART peripheral.
  * @retval None
  */
void UART_SetAddrAndMask(u8 Addr, u8 Mask)
{
	/* Set UART slave device address */
	UART1->SADDR = Addr;
	/* Set UART slave device address mask */
	UART1->SADEN = Mask;
}

/**
  * @brief  Enables or disables multi-master communication for specified UART peripherals.
  * @param  NewState: The new state of multi-master communication.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void UART_SM2Cmd(FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enables multi-master communication for selected UART peripherals */
		UART1->SCON |= UART_SCON_SM2;
	}
	else
	{
		/* Disable multi-master communication for selected UART peripherals */
		UART1->SCON &= ~UART_SCON_SM2;
	}
}

/**
  * @brief  Enables or disables start bit detection for selected UART peripherals.
  * @param  NewState: New state of start bit detection.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void UART_StartDetectCmd(FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable start bit detection for selected UART peripherals */
		UART1->SCON |= UART_SCON_SFDEN;
	}
	else
	{
		/* Disable start bit detection for selected UART peripherals */
		UART1->SCON &= ~UART_SCON_SFDEN;
	}
}

/**
  * @brief  Enables or disables the specified UART interrupts.
  * @param  UART_IT: specifies the UART interrupt sources to be enabled or disabled.
  *   This parameter can be any combination of the following values:
  *     @arg UART_IT_RXSIEN: Receive START bit interrupt
  *     @arg UART_IT_RIEN: receive interrupt
  *     @arg UART_IT_TIEN: send interrupt
  * @param  NewState: new state of the specified UART interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void UART_ITConfig(u8 UART_IT, FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_UART_CONFIG_IT(UART_IT));
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable the selected UART interrupts */
		UART1->SCON |= UART_IT;
	}
	else
	{
		/* Disable the selected UART interrupts */
		UART1->SCON &= ~UART_IT;
	}
}

/**
  * @brief  Checks whether the specified UART flag is set or not.
  * @param  UART_FLAG: specifies the flag to check.
  *   This parameter can be one of the following values:
  *     @arg UART_FLAG_PE: Receive parity error flag
  *     @arg UART_FLAG_FE: Receive frame error flag
  *     @arg UART_FLAG_RXSF: Receive start bit flag
  *     @arg UART_FLAG_RI: Receive complete interrupt flag
  *     @arg UART_FLAG_TI: Transmit complete interrupt flag
  * @retval The new state of UART_FLAG (SET or RESET).
  */
FlagStatus UART_GetFlagStatus(u8 UART_FLAG)
{
	FlagStatus bitstatus = RESET;

	/* Check the parameters */
	PARAM_CHECK(IS_UART_GET_FLAG(UART_FLAG));

	/* Check the status of the UART flag */
	if (UART1->ISR & UART_FLAG)
	{
		/* UART_FLAG is set */
		bitstatus = SET;
	}
	else
	{
		/* UART_FLAG is reset */
		bitstatus = RESET;
	}
	/* Return the UART_FLAG status */
	return bitstatus;
}

/**
  * @brief  Checks whether the specified UART interrupt has occurred or not.
  * @param  UART_IT: specifies the UART interrupt sources to be enabled or disabled.
  *   This parameter can be any combination of the following values:
  *     @arg UART_IT_RXSIEN: Receive START bit interrupt
  *     @arg UART_IT_RIEN: receive interrupt
  *     @arg UART_IT_TIEN: send interrupt
  * @retval The new state of UART_IT (SET or RESET).
  */
ITStatus UART_GetITStatus(u8 UART_IT)
{
	ITStatus bitstatus = RESET;

	/* Check the parameters */
	PARAM_CHECK(IS_UART_GET_IT(UART_IT));

	/* Check the status of the specified UART interrupt */
	if ((UART1->SCON & UART_IT) && (UART1->ISR & UART_IT))
	{
		/* UART_IT is set */
		bitstatus = SET;
	}
	else
	{
		/* UART_IT is reset */
		bitstatus = RESET;
	}
	/* Return the UART_IT status */
	return bitstatus;
}

/**
  * @brief  Clears the UART's pending flags.
  * @param  UART_FLAG: specifies the flag to clear.
  *   This parameter can be any combination of the following values:
  *     @arg UART_FLAG_PE: Receive parity error flag
  *     @arg UART_FLAG_FE: Receive frame error flag
  *     @arg UART_FLAG_RXSF: Receive start bit flag
  *     @arg UART_FLAG_RI: Receive complete interrupt flag
  *     @arg UART_FLAG_TI: Transmit complete interrupt flag
  * @retval None
  */
void UART_ClearFlag(u8 UART_FLAG)
{
	/* Check the parameters */
	PARAM_CHECK(IS_UART_CLEAR_FLAG(UART_FLAG));

	/* Clear the selected UART flags */
	UART1->ISR = UART_FLAG;
}

/**
  * @brief  Check if bit 8 of UART's receive data is set.
  * @param  None
  * @retval The new state of UART_FLAG (SET or RESET).
  */
FlagStatus UART_GetRxBit8(void)
{
	FlagStatus bitstatus = RESET;

	if (UART1->SCON & UART_SCON_RB8)
	{
		/* The 8th bit of the received data is set */
		bitstatus = SET;
	}
	else
	{
		/* The 8th bit of the received data is reset */
		bitstatus = RESET;
	}
	/* Returns the status of the 8th bit of the received data */
	return bitstatus;
}

/**
  * @brief  Clear the 8th bit of UART's receive data.
  * @param  None
  * @retval None
  */
void UART_ClrRxBit8(void)
{
	/* Clear the 8th bit of UART's receive data */
	UART1->SCON &= ~UART_SCON_RB8;
}

/**
  * @brief  Set the 8th bit of UART's transmit data.
  * @param  None
  * @retval None
  */
void UART_SetTxBit8(void)
{
	/* Set the 8th bit of UART's transmit data */
	UART1->SCON |= UART_SCON_TB8;
}

/**
  * @brief  Clear the 8th bit of UART's transmit data.
  * @param  None
  * @retval None
  */
void UART_ClrTxBit8(void)
{
	/* Clear the 8th bit of UART's transmit data */
	UART1->SCON &= ~UART_SCON_TB8;
}

/**
  * @brief  Send a data through the UART peripheral.
  * @param  Data: Data to be transmitted.
  * @retval None
  */
void UART_SendData(u8 Data)
{
	/* Write in the SBUF register the data to be sent */
	UART1->SBUF = Data;
}

/**
  * @brief  Returns the most recent received data by the UART peripheral.
  * @param  None
  * @retval The value of the received data.
  */
u8 UART_ReceiveData(void)
{
	/* Return the data in the SBUF register */
	return (u8)(UART1->SBUF);
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

