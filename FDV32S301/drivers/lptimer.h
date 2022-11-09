/**
  ******************************************************************************
  * @file    lptimer.h
  * @author  yongda.wang
  * @version 0.2
  * @date    2022-09-09
  * @brief   This file contains all functional prototypes of the LPTIMER firmware library.
  ******************************************************************************
  * @attention
  *
  * @copyright Fanhai Data Tech. (c) 2022
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LPTIM_H__
#define __LPTIM_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "phnx02.h"

/** @addtogroup FDV32S301_StdPeriph_Driver
  * @{
  */

/** @addtogroup LPTIMER
  * @{
  */

/** @defgroup LPTIMER_module_register_bit_definition
  * @{
  */

/* LPTIM_CR */
#define LPTIM_CR_IE	  BIT(3)
#define LPTIM_CR_PITE BIT(2)
#define LPTIM_CR_EN	  BIT(0)

/* LPTIM_CFG */
#define LPTIM_CFG BITS(0, 15)

#define LPTIM_CFG_pos (0) /* 0-0xffff:(x+1)*(1/fclk) */

/* LPTIM_CNT */
#define LPTIM_CNT_CNT BITS(0, 15)

#define LPTIM_CNT_CNT_pos (0)

/* LPTIM_INTSTS */
#define LPTIM_INTSTS_STS BIT(0)

/**
  * @}
  */

/** @defgroup LPTIMER_Exported_Types
  * @{
  */

/**
  * @brief LPTIMER Init structure definition
  */

typedef struct
{
	u8 LPT_CntMode; 						/*!< Specifies the counting mode of the LPTIMER.
											 	 This parameter can be a value of @ref LPT_count_mode. */

	u16 LPT_Period; 						/*!< Specify the count period value of LPTIMER.
												 This parameter must be a number between 0x0000 and 0xFFFF */

} LPT_InitTypeDef;

/**
  * @}
  */

/** @defgroup LPTIMER_Exported_Constants
  * @{
  */

/** @defgroup LPT_count_mode
  * @{
  */

#define LPT_CNT_MODE_SING (0)
#define LPT_CNT_MODE_LOOP (1)

#define IS_LPT_COUNT_MODE(MODE) (((MODE) == LPT_CNT_MODE_SING) || ((MODE) == LPT_CNT_MODE_LOOP))
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup LPTIMER_Exported_Functions
  * @{
  */

void	   LPT_Init(LPT_InitTypeDef *LPT_InitStruct);
u16		   LPT_GetCount(void);
void	   LPT_Cmd(FunctionalState NewState);
void	   LPT_ITConfig(FunctionalState NewState);
FlagStatus LPT_GetFlagStatus(void);
ITStatus   LPT_GetITStatus(void);
void	   LPT_ClearFlag(void);

#ifdef __cplusplus
}
#endif

#endif /* __LPTIMER_H__ */

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

