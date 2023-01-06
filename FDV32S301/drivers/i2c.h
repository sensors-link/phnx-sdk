/**
  ******************************************************************************
  * @file    i2c.h
  * @author  yongda.wang
  * @version 0.2
  * @date    2022-09-08
  * @brief   This file contains all functional prototypes of the I2C firmware library.
  ******************************************************************************
  * @attention
  *
  * @copyright Fanhai Data Tech. (c) 2022
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __I2C_H__
#define __I2C_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "phnx02.h"

/** @addtogroup FDV32S301_StdPeriph_Driver
  * @{
  */

/** @addtogroup I2C
  * @{
  */

/** @defgroup I2C_module_register_bit_definition
  * @{
  */

/* I2C_CON */
#define I2C_CON_GEIE	   BIT(27)
#define I2C_CON_STIE	   BIT(26)
#define I2C_CON_STPIE	   BIT(25)
#define I2C_CON_ACTIE	   BIT(24)
#define I2C_CON_RXDIE	   BIT(23)
#define I2C_CON_TXABIE	   BIT(22)
#define I2C_CON_RDRIE	   BIT(21)
#define I2C_CON_TXEIE	   BIT(20)
#define I2C_CON_RXFIE	   BIT(18)
#define I2C_CON_GCEN	   BIT(4)
#define I2C_CON_RESTART_EN BIT(3)
#define I2C_CON_SLAVE_DIS  BIT(2)
#define I2C_CON_MASTER	   BIT(1)
#define I2C_CON_ENABLE	   BIT(0)

/* I2C_ADDR */
#define I2C_ADDR_SAR BITS(16, 22)
#define I2C_ADDR_TAR BITS(0, 6)

#define I2C_ADDR_SAR_pos (16)
#define I2C_ADDR_TAR_pos (0)

/* I2C_DATACMD */
#define I2C_DATACMD_RESTART BIT(10)
#define I2C_DATACMD_STOP	BIT(9)
#define I2C_DATACMD_WREN	BIT(8)
#define I2C_DATACMD_DATA	BITS(0, 7)

#define I2C_DATACMD_DATA_pos (0)

/* I2C_SCLCR */
#define I2C_SCLCR_HCNT BITS(16, 24)
#define I2C_SCLCR_LCNT BITS(0, 8)

#define I2C_SCLCR_HCNT_pos (16)
#define I2C_SCLCR_LCNT_pos (0)

/* I2C_ISR */
#define I2C_ISR_ABRT_SLV_ARBLOST   BIT(20)
#define I2C_ISR_ARB_LOST		   BIT(19)
#define I2C_ISR_ABRT_GCALL_NOACK   BIT(18)
#define I2C_ISR_ABRT_7B_ADDR_NOACK BIT(17)
#define I2C_ISR_ACTIVITY		   BIT(16)
#define I2C_ISR_R_GEN_CALL		   BIT(11)
#define I2C_ISR_R_START_DET		   BIT(10)
#define I2C_ISR_R_STOP_DET		   BIT(9)
#define I2C_ISR_R_ACTIVITY		   BIT(8)
#define I2C_ISR_R_RX_DONE		   BIT(7)
#define I2C_ISR_R_TX_ABRT		   BIT(6)
#define I2C_ISR_R_RD_REQ		   BIT(5)
#define I2C_ISR_R_TX_EMPTY		   BIT(4)
#define I2C_ISR_R_RX_FULL		   BIT(2)

/* I2C_TIMING */
#define I2C_TIMING_SDA_RX_HOLD BITS(8, 11)
#define I2C_TIMING_SDA_TX_HOLD BITS(4, 7)
#define I2C_TIMING_SDA_SETUP   BITS(0, 3)

#define I2C_TIMING_SDA_RX_HOLD_pos (8)
#define I2C_TIMING_SDA_TX_HOLD_pos (4)
#define I2C_TIMING_SDA_SETUP_pos   (0)

/**
  * @}
  */

/** @defgroup I2C_Exported_Types
  * @{
  */

/**
  * @brief I2C Init structure definition
  */

typedef struct
{
	u8 I2C_OwnAddr; 						/*!< Specify own device address.
											 	 This parameter is a 7-bit address. */

	u16 I2C_HighCnt; 						/*!< Specifies the I2C clock high count value, The source clock is pclk.
												 This parameter is a 9-bit value and must be greater than or equal to 0x01. */

	u16 I2C_LowCnt; 						/*!< Specifies the I2C clock low count value, The source clock is pclk.
												 This parameter is a 9-bit value and must be greater than or equal to 0x07. */

	u8 I2C_WorkMode; 						/*!< Specifies the work mode of the I2C peripheral.
											 	 This parameter can be a value of @ref I2C_work_mode. */
} I2C_InitTypeDef;

/**
  * @}
  */

/** @defgroup I2C_Exported_Constants
  * @{
  */

/** @defgroup I2C_work_mode
  * @{
  */

#define I2C_WORK_MODE_MASTER (0)
#define I2C_WORK_MODE_SLAVE	 (1)

#define IS_I2C_WORK_MODE(MODE) (((MODE) == I2C_WORK_MODE_MASTER) || ((MODE) == I2C_WORK_MODE_SLAVE))
/**
  * @}
  */

/** @defgroup I2C_own_address
  * @{
  */

#define IS_I2C_OWN_ADDR(ADDR) ((ADDR) <= 0x7F)
/**
  * @}
  */

/** @defgroup I2C_clock_high_count
  * @{
  */

#define IS_I2C_HIGH_CNT(CNT) (((CNT) <= 0x1FF) && ((CNT) >= 1))
/**
  * @}
  */

/** @defgroup I2C_clock_low_count
  * @{
  */

#define IS_I2C_LOW_CNT(CNT) (((CNT) <= 0x1FF) && ((CNT) >= 7))
/**
  * @}
  */

/** @defgroup I2C_receive_hold
  * @{
  */

#define IS_I2C_RECEIVE_HOLD(HOLD) ((HOLD) <= 0xF)
/**
  * @}
  */

/** @defgroup I2C_send_hold
  * @{
  */

#define IS_I2C_SEND_HOLD(HOLD) ((HOLD) <= 0xF)
/**
  * @}
  */

/** @defgroup I2C_setup_hold
  * @{
  */

#define IS_I2C_SETUP_HOLD(HOLD) ((HOLD) <= 0xF)
/**
  * @}
  */

/** @defgroup I2C_target_access_address
  * @{
  */

#define IS_I2C_ACCESS_ADDR(ADDR) ((ADDR) <= 0x7F)
/**
  * @}
  */

/** @defgroup I2C_interrupts_definition
  * @{
  */

#define I2C_IT_GEIE	  BIT(27)
#define I2C_IT_STIE	  BIT(26)
#define I2C_IT_STPIE  BIT(25)
#define I2C_IT_ACTIE  BIT(24)
#define I2C_IT_RXDIE  BIT(23)
#define I2C_IT_TXABIE BIT(22)
#define I2C_IT_RDRIE  BIT(21)
#define I2C_IT_TXEIE  BIT(20)
#define I2C_IT_RXFIE  BIT(18)

#define I2C_IT_ALL                                                                                                     \
	(I2C_IT_GEIE | I2C_IT_STIE | I2C_IT_STPIE | I2C_IT_ACTIE | I2C_IT_RXDIE | I2C_IT_TXABIE | I2C_IT_RDRIE |           \
	 I2C_IT_TXEIE | I2C_IT_RXFIE)

#define IS_I2C_CONFIG_IT(IT) (((IT)&I2C_IT_ALL) && (!((IT) & (~(I2C_IT_ALL)))))

#define IS_I2C_GET_IT(IT)                                                                                              \
	(((IT) == I2C_IT_GEIE) || ((IT) == I2C_IT_STIE) || ((IT) == I2C_IT_STPIE) || ((IT) == I2C_IT_ACTIE) ||             \
	 ((IT) == I2C_IT_RXDIE) || ((IT) == I2C_IT_TXABIE) || ((IT) == I2C_IT_RDRIE) || ((IT) == I2C_IT_TXEIE) ||          \
	 ((IT) == I2C_IT_RXFIE))

/**
  * @}
  */

/** @defgroup I2C_flags_definition
  * @{
  */

#define I2C_FLAG_ABRT_SLV_ARBLOST	BIT(20)
#define I2C_FLAG_ARB_LOST			BIT(19)
#define I2C_FLAG_ABRT_GCALL_NOACK	BIT(18)
#define I2C_FLAG_ABRT_7B_ADDR_NOACK BIT(17)
#define I2C_FLAG_ACTIVITY			BIT(16)
#define I2C_FLAG_R_GEN_CALL			BIT(11)
#define I2C_FLAG_R_START_DET		BIT(10)
#define I2C_FLAG_R_STOP_DET			BIT(9)
#define I2C_FLAG_R_ACTIVITY			BIT(8)
#define I2C_FLAG_R_RX_DONE			BIT(7)
#define I2C_FLAG_R_TX_ABRT			BIT(6)
#define I2C_FLAG_R_RD_REQ			BIT(5)
#define I2C_FLAG_R_TX_EMPTY			BIT(4)
#define I2C_FLAG_R_RX_FULL			BIT(2)

#define I2C_FLAG_ALL                                                                                                   \
	(I2C_FLAG_R_GEN_CALL | I2C_FLAG_R_START_DET | I2C_FLAG_R_STOP_DET | I2C_FLAG_R_ACTIVITY | I2C_FLAG_R_RX_DONE |     \
	 I2C_FLAG_R_TX_ABRT | I2C_FLAG_R_RD_REQ)

#define IS_I2C_GET_FLAG(FLAG)                                                                                          \
	(((FLAG) == I2C_FLAG_ABRT_SLV_ARBLOST) || ((FLAG) == I2C_FLAG_ARB_LOST) ||                                         \
	 ((FLAG) == I2C_FLAG_ABRT_GCALL_NOACK) || ((FLAG) == I2C_FLAG_ABRT_7B_ADDR_NOACK) ||                               \
	 ((FLAG) == I2C_FLAG_ACTIVITY) || ((FLAG) == I2C_FLAG_R_GEN_CALL) || ((FLAG) == I2C_FLAG_R_START_DET) ||           \
	 ((FLAG) == I2C_FLAG_R_STOP_DET) || ((FLAG) == I2C_FLAG_R_ACTIVITY) || ((FLAG) == I2C_FLAG_R_RX_DONE) ||           \
	 ((FLAG) == I2C_FLAG_R_TX_ABRT) || ((FLAG) == I2C_FLAG_R_RD_REQ) || ((FLAG) == I2C_FLAG_R_TX_EMPTY) ||             \
	 ((FLAG) == I2C_FLAG_R_RX_FULL))

#define IS_I2C_CLEAR_FLAG(FLAG) (((FLAG) & I2C_FLAG_ALL) && (!((FLAG) & (~(I2C_FLAG_ALL)))))
/**
  * @}
  */

/** @defgroup I2C_data_cmd_type
  * @{
  */

#define I2C_CMD_RESTART BIT(10)
#define I2C_CMD_STOP	BIT(9)
#define I2C_CMD_READ	BIT(8)
#define I2C_CMD_NONE	(0)

#define IS_I2C_DATACMD_TYPE(TYPE) (!((TYPE) & (~(I2C_CMD_RESTART | I2C_CMD_STOP | I2C_CMD_READ))))
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup I2C_Exported_Functions
  * @{
  */

void	   I2C_DeInit(void);
void	   I2C_Init(I2C_InitTypeDef *I2C_InitStruct);
void	   I2C_ReceiveHoldConfig(u8 HoldTime);
void	   I2C_SendHoldConfig(u8 HoldTime);
void	   I2C_SetupHoldConfig(u8 HoldTime);
void	   I2C_SetAccessAddr(u8 Addr);
void	   I2C_GeneralCallCmd(FunctionalState NewState);
void	   I2C_ReStartCmd(FunctionalState NewState);
void	   I2C_Cmd(FunctionalState NewState);
void	   I2C_ITConfig(u32 I2C_IT, FunctionalState NewState);
FlagStatus I2C_GetFlagStatus(u32 I2C_FLAG);
ITStatus   I2C_GetITStatus(u32 I2C_IT);
void	   I2C_ClearFlag(u32 I2C_FLAG);
void	   I2C_SendData(u32 CmdType, u8 Data);
u8		   I2C_ReceiveData(void);

#ifdef __cplusplus
}
#endif

#endif /* __I2C_H__ */

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

