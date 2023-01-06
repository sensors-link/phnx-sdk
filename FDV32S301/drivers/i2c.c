/**
  ******************************************************************************
  * @file    i2c.c
  * @author  yongda.wang
  * @version 0.2
  * @date    2022-09-08
  * @brief   This file provides all the I2C firmware functions.
  ******************************************************************************
  * @attention
  *
  * @copyright Fanhai Data Tech. (c) 2022
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "i2c.h"
#include "sysc.h"

/** @addtogroup FDV32S301_StdPeriph_Driver
  * @{
  */

/** @defgroup I2C
  * @brief I2C driver modules
  * @{
  */

/** @defgroup I2C_Private_Functions
  * @{
  */

/**
  * @brief  Deinitialize the I2C peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void I2C_DeInit(void)
{
	/* Reset the I2C module settings */
	SYSC_ResetPeripher(SYSC_RESET_MOUDLE_I2C);
}

/**
  * @brief  Initializes the I2C peripheral according to the specified parameters
  *         in the I2C_InitStruct.
  * @param  I2C_InitStruct: pointer to an I2C_InitTypeDef structure that contains
  *         the configuration information for the I2C peripheral.
  * @retval None
  */
void I2C_Init(I2C_InitTypeDef *I2C_InitStruct)
{
	u32 tempreg1 = 0, tempreg2 = 0;

	/* Check the parameters */
	PARAM_CHECK(IS_I2C_OWN_ADDR(I2C_InitStruct->I2C_OwnAddr));
	PARAM_CHECK(IS_I2C_HIGH_CNT(I2C_InitStruct->I2C_HighCnt));
	PARAM_CHECK(IS_I2C_LOW_CNT(I2C_InitStruct->I2C_LowCnt));
	PARAM_CHECK(IS_I2C_WORK_MODE(I2C_InitStruct->I2C_WorkMode));

	/* Get the I2C_CON value */
	tempreg1 = I2C->CON;

	/* Turn off the I2C module enable */
	I2C->CON &= ~I2C_CON_ENABLE;

	/* Set I2C own address */
	I2C->ADDR &= ~I2C_ADDR_SAR;
	I2C->ADDR |= I2C_InitStruct->I2C_OwnAddr << I2C_ADDR_SAR_pos;

	/* Get the I2C_SCLCR value */
	tempreg2 = I2C->SCLCR;

	/* Set clock high count value */
	tempreg2 &= ~I2C_SCLCR_HCNT;
	tempreg2 |= I2C_InitStruct->I2C_HighCnt << I2C_SCLCR_HCNT_pos;

	/* Set clock low count value */
	tempreg2 &= ~I2C_SCLCR_LCNT;
	tempreg2 |= I2C_InitStruct->I2C_LowCnt << I2C_SCLCR_LCNT_pos;

	/* Write to I2C_SCLCR */
	I2C->SCLCR = tempreg2;

	/* Set I2C work mode */
	if (I2C_InitStruct->I2C_WorkMode == I2C_WORK_MODE_MASTER)
	{
		/* The working mode of the I2C peripheral is the master mode */
		tempreg1 |= I2C_CON_SLAVE_DIS | I2C_CON_MASTER;
	}
	else
	{
		/* The working mode of the I2C peripheral is the slave mode */
		tempreg1 &= ~(I2C_CON_SLAVE_DIS | I2C_CON_MASTER);
	}

	/* Write to I2C_CON */
	I2C->CON = tempreg1;
}

/**
  * @brief  Configure the hold time for internally received data.
  * @param  HoldTime: Specifies the hold time for internally received data.
  *   This parameter value must be lower than 0x10.
  * @retval None
  */
void I2C_ReceiveHoldConfig(u8 HoldTime)
{
	u32 tempreg = 0;

	/* Check the parameters */
	PARAM_CHECK(IS_I2C_RECEIVE_HOLD(HoldTime));

	/* Get the I2C_CON value */
	tempreg = I2C->CON;

	/* Turn off the I2C module enable */
	I2C->CON &= ~I2C_CON_ENABLE;

	/* Set the hold time for internally received data */
	I2C->TIMING &= ~I2C_TIMING_SDA_RX_HOLD;
	I2C->TIMING |= HoldTime << I2C_TIMING_SDA_RX_HOLD_pos;

	/* Write the original configuration back to I2C_CON */
	I2C->CON = tempreg;
}

/**
  * @brief  Configure the hold time for send data.
  * @param  HoldTime: Specifies the hold time for send data.
  *   This parameter value must be lower than 0x10.
  * @retval None
  */
void I2C_SendHoldConfig(u8 HoldTime)
{
	u32 tempreg = 0;

	/* Check the parameters */
	PARAM_CHECK(IS_I2C_SEND_HOLD(HoldTime));

	/* Get the I2C_CON value */
	tempreg = I2C->CON;

	/* Turn off the I2C module enable */
	I2C->CON &= ~I2C_CON_ENABLE;

	/* Set the hold time for send data */
	I2C->TIMING &= ~I2C_TIMING_SDA_TX_HOLD;
	I2C->TIMING |= HoldTime << I2C_TIMING_SDA_TX_HOLD_pos;

	/* Write the original configuration back to I2C_CON */
	I2C->CON = tempreg;
}

/**
  * @brief  Configure the hold time for setup data.
  * @param  HoldTime: Specifies the hold time for setup data.
  *   This parameter value must be lower than 0x10.
  * @retval None
  */
void I2C_SetupHoldConfig(u8 HoldTime)
{
	u32 tempreg = 0;

	/* Check the parameters */
	PARAM_CHECK(IS_I2C_SETUP_HOLD(HoldTime));

	/* Get the I2C_CON value */
	tempreg = I2C->CON;

	/* Turn off the I2C module enable */
	I2C->CON &= ~I2C_CON_ENABLE;

	/* Set the hold time for setup data */
	I2C->TIMING &= ~I2C_TIMING_SDA_SETUP;
	I2C->TIMING |= HoldTime << I2C_TIMING_SDA_SETUP_pos;

	/* Write the original configuration back to I2C_CON */
	I2C->CON = tempreg;
}

/**
  * @brief  Set the I2C target access address.
  * @param  Addr: Specify the target access address.
  *   This parameter value must be lower than 0x80.
  * @retval None
  */
void I2C_SetAccessAddr(u8 Addr)
{
	u32 tempreg = 0;

	/* Check the parameters */
	PARAM_CHECK(IS_I2C_ACCESS_ADDR(Addr));

	/* Get the I2C_CON value */
	tempreg = I2C->CON;

	/* Turn off the I2C module enable */
	I2C->CON &= ~I2C_CON_ENABLE;

	/* Set I2C target access address */
	I2C->ADDR &= ~I2C_ADDR_TAR;
	I2C->ADDR |= Addr << I2C_ADDR_TAR_pos;

	/* Write the original configuration back to I2C_CON */
	I2C->CON = tempreg;
}

/**
  * @brief  Enable or disable I2C peripheral general call.
  * @param  NewState: New state for general calls.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_GeneralCallCmd(FunctionalState NewState)
{
	u32 tempreg = 0;
	
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	/* Get the I2C_CON value */
	tempreg = I2C->CON;

	/* Turn off the I2C module enable */
	I2C->CON &= ~I2C_CON_ENABLE;

	if (NewState == ENABLE)
	{
		/* Enable I2C peripheral general call */
		tempreg |= I2C_CON_GCEN;
	}
	else
	{
		/* Disable I2C peripheral general call */
		tempreg &= ~I2C_CON_GCEN;
	}

	/* Write the I2C_CON */
	I2C->CON = tempreg;
}

/**
  * @brief  Enable or disable I2C peripheral restart condition.
  * @param  NewState: The new state of the restart condition.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_ReStartCmd(FunctionalState NewState)
{
	u32 tempreg = 0;
	
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	/* Get the I2C_CON value */
	tempreg = I2C->CON;

	/* Turn off the I2C module enable */
	I2C->CON &= ~I2C_CON_ENABLE;

	if (NewState == ENABLE)
	{
		/* Enable I2C peripheral restart */
		tempreg |= I2C_CON_RESTART_EN;
	}
	else
	{
		/* Disable I2C peripheral restart */
		tempreg &= ~I2C_CON_RESTART_EN;
	}

	/* Write the I2C_CON */
	I2C->CON = tempreg;
}

/**
  * @brief  Enables or disables the specified I2C peripheral.
  * @param  NewState: New state of the I2C peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_Cmd(FunctionalState NewState)
{
	/* Check the parameters */
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	if (NewState == ENABLE)
	{
		/* Enable I2C peripheral */
		I2C->CON |= I2C_CON_ENABLE;
	}
	else
	{
		/* Disable I2C peripheral */
		I2C->CON &= ~I2C_CON_ENABLE;
	}
}

/**
  * @brief  Enables or disables the specified I2C interrupts.
  * @param  I2C_IT: specifies the I2C interrupt sources to be enabled or disabled.
  *   This parameter can be any combination of the following values:
  *     @arg I2C_IT_GEIE: General Call interrupt
  *     @arg I2C_IT_STIE: Start or restart condition interrupts
  *     @arg I2C_IT_STPIE: stop condition interrupt
  *     @arg I2C_IT_ACTIE: busy interrupt
  *     @arg I2C_IT_RXDIE: Receive transfer complete interrupt
  *     @arg I2C_IT_TXABIE: send abort interrupt
  *     @arg I2C_IT_RDRIE: read request interrupt
  *     @arg I2C_IT_TXEIE: Send BUFFER empty interrupt
  *     @arg I2C_IT_RXFIE: Receive data complete interrupt
  * @param  NewState: new state of the specified I2C interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_ITConfig(u32 I2C_IT, FunctionalState NewState)
{
	u32 tempreg = 0;
	
	/* Check the parameters */
	PARAM_CHECK(IS_I2C_CONFIG_IT(I2C_IT));
	PARAM_CHECK(IS_FUNCTIONAL_STATE(NewState));

	/* Get the I2C_CON value */
	tempreg = I2C->CON;

	/* Turn off the I2C module enable */
	I2C->CON &= ~I2C_CON_ENABLE;

	if (NewState == ENABLE)
	{
		/* Enable the selected I2C interrupts */
		tempreg |= I2C_IT;
	}
	else
	{
		/* Disable the selected I2C interrupts */
		tempreg &= ~I2C_IT;
	}

	/* Write the I2C_CON */
	I2C->CON = tempreg;
}

/**
  * @brief  Checks whether the specified I2C flag is set or not.
  * @param  I2C_FLAG: specifies the flag to check.
  *   This parameter can be one of the following values:
  *     @arg I2C_FLAG_ABRT_SLV_ARBLOST: The machine lost control of the bus during data transfer flag
  *     @arg I2C_FLAG_ARB_LOST: Master or Slave Lost Arbitration flag
  *     @arg I2C_FLAG_ABRT_GCALL_NOACK: The master sends general call without ack flag
  *     @arg I2C_FLAG_ABRT_7B_ADDR_NOACK: There is no ack in the 7bit address sent by the master flag
  *     @arg I2C_FLAG_ACTIVITY: I2C is busy flag
  *     @arg I2C_FLAG_R_GEN_CALL: General Call Address Confirmation Flag
  *     @arg I2C_FLAG_R_START_DET: Start condition or restart condition generate flag
  *     @arg I2C_FLAG_R_STOP_DET: stop signal generation flag
  *     @arg I2C_FLAG_R_ACTIVITY: I2C busy flag
  *     @arg I2C_FLAG_R_RX_DONE: Receive transfer complete flag
  *     @arg I2C_FLAG_R_TX_ABRT: send abort flag
  *     @arg I2C_FLAG_R_RD_REQ: read request flag
  *     @arg I2C_FLAG_R_TX_EMPTY: Send BUFFER empty flag
  *     @arg I2C_FLAG_R_RX_FULL: Receive data completion flag
  * @retval The new state of I2C_FLAG (SET or RESET).
  */
FlagStatus I2C_GetFlagStatus(u32 I2C_FLAG)
{
	FlagStatus bitstatus = RESET;

	/* Check the parameters */
	PARAM_CHECK(IS_I2C_GET_FLAG(I2C_FLAG));

	/* Check the status of the I2C flag */
	if (I2C->ISR & I2C_FLAG)
	{
		/* I2C_FLAG is set */
		bitstatus = SET;
	}
	else
	{
		/* I2C_FLAG is reset */
		bitstatus = RESET;
	}
	/* Return the I2C_FLAG status */
	return bitstatus;
}

/**
  * @brief  Checks whether the specified I2C interrupt has occurred or not.
  * @param  I2C_IT: specifies the I2C interrupt source to check.
  *   This parameter can be one of the following values:
  *     @arg I2C_IT_GEIE: General Call interrupt
  *     @arg I2C_IT_STIE: Start or restart condition interrupts
  *     @arg I2C_IT_STPIE: stop condition interrupt
  *     @arg I2C_IT_ACTIE: busy interrupt
  *     @arg I2C_IT_RXDIE: Receive transfer complete interrupt
  *     @arg I2C_IT_TXABIE: send abort interrupt
  *     @arg I2C_IT_RDRIE: read request interrupt
  *     @arg I2C_IT_TXEIE: Send BUFFER empty interrupt
  *     @arg I2C_IT_RXFIE: Receive data complete interrupt
  * @retval The new state of I2C_IT (SET or RESET).
  */
ITStatus I2C_GetITStatus(u32 I2C_IT)
{
	ITStatus bitstatus = RESET;

	/* Check the parameters */
	PARAM_CHECK(IS_I2C_GET_IT(I2C_IT));

	/* Check the status of the specified I2C interrupt */
	if ((I2C->CON & I2C_IT) && (I2C->ISR & (I2C_IT >> 16)))
	{
		/* I2C_IT is set */
		bitstatus = SET;
	}
	else
	{
		/* I2C_IT is reset */
		bitstatus = RESET;
	}
	/* Return the I2C_IT status */
	return bitstatus;
}

/**
  * @brief  Clear the pending flag for I2C.
  * @param  I2C_FLAG: specifies the flag to clear.
  *   This parameter can be any combination of the following values:
  *     @arg I2C_FLAG_R_GEN_CALL: General Call Address Confirmation Flag
  *     @arg I2C_FLAG_R_START_DET: Start condition or restart condition generate flag
  *     @arg I2C_FLAG_R_STOP_DET: stop signal generation flag
  *     @arg I2C_FLAG_R_ACTIVITY: I2C busy flag
  *     @arg I2C_FLAG_R_RX_DONE: Receive transfer complete flag
  *     @arg I2C_FLAG_R_TX_ABRT: send abort flag
  *     @arg I2C_FLAG_R_RD_REQ: read request flag
  * @retval None
  */
void I2C_ClearFlag(u32 I2C_FLAG)
{
	/* Check the parameters */
	PARAM_CHECK(IS_I2C_CLEAR_FLAG(I2C_FLAG));

	/* Clear the selected I2C flags */
	I2C->ISR = I2C_FLAG;
}

/**
  * @brief  Sends a data byte through the I2C peripheral.
  * @param  CmdType: Specifies the data transfer command type.
  *   This parameter can be any combination of the following values:
  *     @arg I2C_CMD_RESTART: Issue a START signal before sending out data
  *     @arg I2C_CMD_STOP: STOP signal after sending data
  *     @arg I2C_CMD_READ: The host enters read mode. If this parameter is
  *                        not specified, the host enters write mode
  *     @arg I2C_CMD_NONE: None of the above commands are executed
  * @param  Data: Specify the data to send.
  * @retval None
  */
void I2C_SendData(u32 CmdType, u8 Data)
{
	/* Check the parameters */
	PARAM_CHECK(IS_I2C_DATACMD_TYPE(CmdType));

	/* Write commands and data to DATACMD */
	I2C->DATACMD = CmdType | Data;
}

/**
  * @brief  Returns the most recent received data by the I2C peripheral.
  * @param  None
  * @retval The value of the received data.
  */
u8 I2C_ReceiveData(void)
{
	/* Return the data in the DATACMD register */
	return (u8)(I2C->DATACMD);
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

