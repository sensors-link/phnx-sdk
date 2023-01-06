/**
  ******************************************************************************
  * @file    uart.h
  * @author  yongda.wang
  * @version 0.2
  * @date    2022-09-27
  * @brief   This file contains all functional prototypes of the UART firmware library.
  ******************************************************************************
  * @attention
  *
  * @copyright Fanhai Data Tech. (c) 2022
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UART_H__
#define __UART_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "phnx02.h"

/** @addtogroup FDV32S301_StdPeriph_Driver
  * @{
  */

/** @addtogroup UART
  * @{
  */

/** @defgroup UART_module_register_bit_definition
  * @{
  */

/* UART_SCON */
#define UART_SCON_PACFG	 BIT(11)
#define UART_SCON_LPMODE BIT(10)
#define UART_SCON_SM01	 BITS(8, 9)
#define UART_SCON_SM2	 BIT(7)
#define UART_SCON_REN	 BIT(6)
#define UART_SCON_RB8	 BIT(5)
#define UART_SCON_TB8	 BIT(4)
#define UART_SCON_RXSIEN BIT(3)
#define UART_SCON_RIEN	 BIT(2)
#define UART_SCON_TIEN	 BIT(1)
#define UART_SCON_SFDEN	 BIT(0)

#define UART_SCON_SM01_pos (8)

/* UART_ISR */
#define UART_ISR_RXSF BIT(4)
#define UART_ISR_PE	  BIT(3)
#define UART_ISR_FE	  BIT(2)
#define UART_ISR_RI	  BIT(1)
#define UART_ISR_TI	  BIT(0)

/**
  * @}
  */

/** @defgroup UART_Exported_Types
  * @{
  */

/**
  * @brief UART Init structure definition
  */

typedef struct
{
	u16 UART_Parity; 						/*!< Specifies the parity mode.
                                           		 This parameter can be a value of @ref UART_parity. */

	u16 UART_StopBits; 						/*!< Specifies the number of stop bits transmitted.
												 This parameter can be a value of @ref UART_stop_bits. */

	u32 UART_BaudRate; 						/*!< Specify the UART communication baud rate.
												 The baud rate is computed using the following formula:
												  - MODE0:  UART_BaudRate = UART_CLK/(2*(BDIV+1))
												  - MODE1/2/3:  UART_BaudRate = UART_CLK/(16*(BDIV+1)) */
} UART_InitTypeDef;

/**
  * @}
  */

/** @defgroup UART_Exported_Constants
  * @{
  */

/** @defgroup UART_all_timer_peripheral
  * @{
  */

#define IS_UART_ALL_PERIPH(PERIPH) (((PERIPH) == UART1) || ((PERIPH) == UART2) || ((PERIPH) == LPUART))
/**
  * @}
  */

/** @defgroup UART_parity
  * @{
  */ 

#define UART_PARITY_NO	 ((u16)0x0000)
#define UART_PARITY_ODD	 ((u16)0x0200)
#define UART_PARITY_EVEN ((u16)0x0A00)
#define IS_UART_PARITY(PARITY)                                                                                         \
	(((PARITY) == UART_PARITY_NO) || ((PARITY) == UART_PARITY_ODD) || ((PARITY) == UART_PARITY_EVEN))
/**
  * @}
  */

/** @defgroup UART_stop_bits
  * @{
  */ 

#define UART_STOPBITS_0			   ((u16)0x0000)
#define UART_STOPBITS_1			   ((u16)0x0100)
#define IS_UART_STOPBITS(STOPBITS) (((STOPBITS) == UART_STOPBITS_0) || ((STOPBITS) == UART_STOPBITS_1))
/**
  * @}
  */

/** @defgroup UART_baud_rate
  * @{
  */

#define IS_UART_BAUDRATE(BAUDRATE) ((BAUDRATE) > 0)
/**
  * @}
  */

/** @defgroup UART_baud_divide
  * @{
  */

#define IS_UART_BAUDDIV(BAUDDIV) (((BAUDDIV) > 0) && ((BAUDDIV) <= 0xFFFF))
/**
  * @}
  */

/** @defgroup UART_interrupts_definition
  * @{
  */

#define UART_IT_RXSIEN BIT(3)
#define UART_IT_RIEN   BIT(2)
#define UART_IT_TIEN   BIT(1)

#define UART_IT_ALL (UART_IT_RXSIEN | UART_IT_RIEN | UART_IT_TIEN)

#define IS_UART_CONFIG_IT(IT) (((IT)&UART_IT_ALL) && (!((IT) & (~(UART_IT_ALL)))))

#define IS_UART_GET_IT(IT) (((IT) == UART_IT_RXSIEN) || ((IT) == UART_IT_RIEN) || ((IT) == UART_IT_TIEN))

/**
  * @}
  */

/** @defgroup UART_flags_definition
  * @{
  */

#define UART_FLAG_RXSF BIT(4)
#define UART_FLAG_PE   BIT(3)
#define UART_FLAG_FE   BIT(2)
#define UART_FLAG_RI   BIT(1)
#define UART_FLAG_TI   BIT(0)

#define UART_FLAG_ALL (UART_FLAG_RXSF | UART_FLAG_PE | UART_FLAG_FE | UART_FLAG_RI | UART_FLAG_TI)

#define IS_UART_GET_FLAG(FLAG)                                                                                         \
	(((FLAG) == UART_FLAG_RXSF) || ((FLAG) == UART_FLAG_PE) || ((FLAG) == UART_FLAG_FE) || ((FLAG) == UART_FLAG_RI) || \
	 ((FLAG) == UART_FLAG_TI))

#define IS_UART_CLEAR_FLAG(FLAG) (((FLAG) & UART_FLAG_ALL) && (!((FLAG) & (~(UART_FLAG_ALL)))))
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup UART_Exported_Functions
  * @{
  */

void	   UART_DeInit(UART_TypeDef *UARTx);
void	   UART_Init(UART_TypeDef *UARTx, UART_InitTypeDef *UART_InitStruct);
void	   UART_LPInit(UART_InitTypeDef *UART_InitStruct);
void	   UART_SetAddrAndMask(UART_TypeDef *UARTx, u8 Addr, u8 Mask);
void	   UART_SM2Cmd(UART_TypeDef *UARTx, FunctionalState NewState);
void	   UART_StartDetectCmd(UART_TypeDef *UARTx, FunctionalState NewState);
void	   UART_ITConfig(UART_TypeDef *UARTx, u8 UART_IT, FunctionalState NewState);
FlagStatus UART_GetFlagStatus(UART_TypeDef *UARTx, u8 UART_FLAG);
ITStatus   UART_GetITStatus(UART_TypeDef *UARTx, u8 UART_IT);
void	   UART_ClearFlag(UART_TypeDef *UARTx, u8 UART_FLAG);
FlagStatus UART_GetRxBit8(UART_TypeDef *UARTx);
void	   UART_ClrRxBit8(UART_TypeDef *UARTx);
void	   UART_SetTxBit8(UART_TypeDef *UARTx);
void	   UART_ClrTxBit8(UART_TypeDef *UARTx);
void	   UART_SendData(UART_TypeDef *UARTx, u8 Data);
u8		   UART_ReceiveData(UART_TypeDef *UARTx);

#ifdef __cplusplus
}
#endif

#endif /* __UART_H__ */

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

