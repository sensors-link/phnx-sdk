/**
  ******************************************************************************
  * @file    spi.h
  * @author  yongda.wang
  * @version 0.2
  * @date    2022-09-21
  * @brief   This file contains all functional prototypes of the SPI firmware library.
  ******************************************************************************
  * @attention
  *
  * @copyright Fanhai Data Tech. (c) 2022
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPI_H__
#define __SPI_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "phnx02.h"

/** @addtogroup FDV32S301_StdPeriph_Driver
  * @{
  */

/** @addtogroup SPI
  * @{
  */

/** @defgroup SPI_module_register_bit_definition
  * @{
  */

/* SPI_CR0 */
#define SPI_CR0_CPOL	BIT(7)
#define SPI_CR0_CPHA	BIT(6)
#define SPI_CR0_MSTCFIE BIT(5)
#define SPI_CR0_DONEIE	BIT(4)
#define SPI_CR0_MSMODE	BIT(3)
#define SPI_CR0_SCLKDIV BITS(0, 2)

#define SPI_CR0_SCLKDIV_pos (0) /* 0-7 div(2^(x+1)) */

/* SPI_CSN */
#define SPI_CSN_CSN BIT(0)

/* SPI_SR */
#define SPI_SR_SPI_CS  BIT(2)
#define SPI_SR_MSTCFSR BIT(1)
#define SPI_SR_DONESR  BIT(0)

/**
  * @}
  */

/** @defgroup SPI_Exported_Types
  * @{
  */

/**
  * @brief SPI Init structure definition
  */

typedef struct
{
	u8 SPI_ClockPolarity; 					/*!< Specifies the serial clock steady state.
                                         		 This parameter can be a value of @ref SPI_clock_polarity. */

	u8 SPI_ClockPhase; 						/*!< Specifies the clock active edge for the bit capture.
                                        		 This parameter can be a value of @ref SPI_clock_phase. */

	u8 SPI_Mode; 							/*!< Specifies the SPI operating mode.
                                         		 This parameter can be a value of @ref SPI_mode. */

	u8 SPI_SclkDiv;							/*!< Specify the SCLK clock division factor.
                                         		 This parameter can be a value of @ref SPI_sclk_division .
                                        		 @note The source clock is pclk, 50% duty cycle. */
} SPI_InitTypeDef;

/**
  * @}
  */

/** @defgroup SPI_Exported_Constants
  * @{
  */

/** @defgroup SPI_clock_polarity
  * @{
  */
	
#define SPI_CPOL_LOW  (0)
#define SPI_CPOL_HIGH (1)

#define IS_SPI_CPOL(CPOL) (((CPOL) == SPI_CPOL_LOW) || ((CPOL) == SPI_CPOL_HIGH))
/**
  * @}
  */

/** @defgroup SPI_clock_phase
  * @{
  */

#define SPI_CPHA_1EDGE (0)
#define SPI_CPHA_2EDGE (1)

#define IS_SPI_CPHA(CPHA) (((CPHA) == SPI_CPHA_1EDGE) || ((CPHA) == SPI_CPHA_2EDGE))
/**
  * @}
  */

/** @defgroup SPI_mode
  * @{
  */
	
#define SPI_MODE_SLAVE                  (0)
#define SPI_MODE_MASTER                 (1)

#define IS_SPI_MODE(MODE) (((MODE) == SPI_MODE_SLAVE) || ((MODE) == SPI_MODE_MASTER))
/**
  * @}
  */

/** @defgroup SPI_sclk_division
  * @{
  */

#define SPI_SCLK_DIV2	(0)
#define SPI_SCLK_DIV4	(1)
#define SPI_SCLK_DIV8	(2)
#define SPI_SCLK_DIV16	(3)
#define SPI_SCLK_DIV32	(4)
#define SPI_SCLK_DIV64	(5)
#define SPI_SCLK_DIV128 (6)
#define SPI_SCLK_DIV256 (7)

#define IS_SPI_SCLK_DIV(DIV)                                                                                           \
	(((DIV) == SPI_SCLK_DIV2) || ((DIV) == SPI_SCLK_DIV4) || ((DIV) == SPI_SCLK_DIV8) || ((DIV) == SPI_SCLK_DIV16) ||  \
	 ((DIV) == SPI_SCLK_DIV32) || ((DIV) == SPI_SCLK_DIV64) || ((DIV) == SPI_SCLK_DIV128) ||                           \
	 ((DIV) == SPI_SCLK_DIV256))
/**
  * @}
  */

/** @defgroup SPI_interrupts_definition
  * @{
  */

#define SPI_IT_MSTCFIE BIT(5)
#define SPI_IT_DONEIE  BIT(4)

#define SPI_IT_ALL (SPI_IT_MSTCFIE | SPI_IT_DONEIE)

#define IS_SPI_CONFIG_IT(IT) (((IT)&SPI_IT_ALL) && (!((IT) & (~(SPI_IT_ALL)))))

#define IS_SPI_GET_IT(IT) (((IT) == SPI_IT_MSTCFIE) || ((IT) == SPI_IT_DONEIE))

/**
  * @}
  */

/** @defgroup SPI_flags_definition
  * @{
  */

#define SPI_FLAG_SPI_CS	 BIT(2)
#define SPI_FLAG_MSTCFSR BIT(1)
#define SPI_FLAG_DONESR	 BIT(0)

#define SPI_FLAG_ALL (SPI_FLAG_SPI_CS | SPI_FLAG_MSTCFSR | SPI_FLAG_DONESR)

#define IS_SPI_GET_FLAG(FLAG)                                                                                          \
	(((FLAG) == SPI_FLAG_SPI_CS) || ((FLAG) == SPI_FLAG_MSTCFSR) || ((FLAG) == SPI_FLAG_DONESR))

#define IS_SPI_CLEAR_FLAG(FLAG) (((FLAG) & SPI_FLAG_ALL) && (!((FLAG) & (~(SPI_FLAG_ALL)))))
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup SPI_Exported_Functions
  * @{
  */

void	   SPI_DeInit(void);
void	   SPI_Init(SPI_InitTypeDef *SPI_InitStruct);
void	   SPI_ITConfig(u8 SPI_IT, FunctionalState NewState);
FlagStatus SPI_GetFlagStatus(u8 SPI_FLAG);
ITStatus   SPI_GetITStatus(u8 SPI_IT);
void	   SPI_ClearFlag(u8 SPI_FLAG);
void	   SPI_SetCSN(void);
void	   SPI_ClrCSN(void);
void	   SPI_SendData(u8 data);
u8		   SPI_RecieveData(void);

#ifdef __cplusplus
}
#endif

#endif /* __SPI_H__ */

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

