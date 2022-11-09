/**
  ******************************************************************************
  * @file    wdt.h
  * @author  yongda.wang
  * @version 0.2
  * @date    2022-09-27
  * @brief   This file contains all functional prototypes of the WDT firmware library.
  ******************************************************************************
  * @attention
  *
  * @copyright Fanhai Data Tech. (c) 2022
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WDT_H__
#define __WDT_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "phnx05.h"

/** @addtogroup FDV32F003_StdPeriph_Driver
  * @{
  */

/** @addtogroup WDT
  * @{
  */

/** @defgroup WDT_module_register_bit_definition
  * @{
  */

/* WDT_CR */
#define WDT_CR_PS		  BITS(8, 10)
#define WDT_CR_INTFLAG	  BIT(7)
#define WDT_CR_INTEN	  BIT(5)
#define WDT_CR_RUN		  BIT(4)
#define WDT_CR_WOV		  BITS(0, 3)

#define WDT_CR_PS_pos  (8)
#define WDT_CR_WOV_pos (0) /* 0:0f  2^(wov+1) * 1/fclk 4ms */

/**
  * @}
  */

/** @defgroup WDT_Exported_Types
  * @{
  */

/**
  * @brief WDT Init structure definition
  */

typedef struct
{
	u8 WDT_Prescaler; 							/*!< Specifies the prescaler value used to divide the WDT clock.
													  - divide = 2^WDT_Prescaler.
												 	 This parameter can be a value between 0 to 7. */
											 	 
	u8 WDT_OverValue; 							/*!< Specify WDT overflow value.
												 	 This parameter can be a number between 0x00 and 0x0F.
												 	 The overflow time is calculated using the following formula:
												 	  - reset mode: over_time = (2^(WDT_OverValue+1)-1)/WDT_CLK
												 	  - interrupt mode: over_time = 2^(WDT_OverValue+1)/WDT_CLK */
} WDT_InitTypeDef;

/**
  * @}
  */

/** @defgroup WDT_Exported_Constants
  * @{
  */

/** @defgroup WDT_prescaler_value
  * @{
  */

#define IS_WDT_PRESCALER(PRESCALER) (((PRESCALER) <= 0x7))
/**
  * @}
  */

/** @defgroup WDT_over_load
  * @{
  */

#define IS_WDT_OVER_LOAD(LOAD) ((LOAD) <= 0xF)
/**
  * @}
  */

/** @defgroup WDT_flags_definition
  * @{
  */

#define WDT_FLAG_INTFLAG BIT(7)
#define WDT_FLAG_RUN	 BIT(4)

#define IS_WDT_GET_FLAG(FLAG) (((FLAG) == WDT_FLAG_INTFLAG) || ((FLAG) == WDT_FLAG_RUN))
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup WDT_Exported_Functions
  * @{
  */

void	   WDT_Init(WDT_InitTypeDef *WDT_InitStruct);
void	   WDT_ITConfig(FunctionalState NewState);
FlagStatus WDT_GetFlagStatus(u32 WDT_FLAG);
ITStatus   WDT_GetITStatus(void);
void	   WDT_ClearFlag(void);
void	   WDT_StartCount(void);
void	   WDT_ClearCount(void);

#ifdef __cplusplus
}
#endif

#endif /* __WDT_H__ */

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

